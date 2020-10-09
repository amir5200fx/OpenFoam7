#include <histogram.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(histogram, 0);
		addToRunTimeSelectionTable(functionObject, histogram, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::histogram::writeGraph
(
	const coordSet& coords,
	const word& fieldName,
	const scalarField& values
) const
{
	const wordList fieldNames(1, fieldName);

	fileName outputPath = file_.baseTimeDir();
	mkDir(outputPath);
	OFstream graphFile
	(
		outputPath / formatterPtr_().getFileName(coords, fieldNames)
	);

	TnbLog << "    Writing histogram of " << fieldName
		<< " to " << graphFile.name() << endl;

	List<const scalarField*> yPtrs(1);
	yPtrs[0] = &values;
	formatterPtr_().write(coords, fieldNames, yPtrs, graphFile);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::histogram::histogram
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	file_(obr_, name)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::histogram::~histogram()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::histogram::read(const dictionary& dict)
{
	dict.lookup("field") >> fieldName_;
	dict.lookup("max") >> max_;
	min_ = dict.lookupOrDefault<scalar>("min", 0);
	dict.lookup("nBins") >> nBins_;

	word format(dict.lookup("setFormat"));
	formatterPtr_ = writer<scalar>::New(format);

	return true;
}


bool tnbLib::functionObjects::histogram::execute()
{
	return true;
}


bool tnbLib::functionObjects::histogram::write()
{
	TnbLog << type() << " " << name() << " write:" << nl;

	autoPtr<volScalarField> fieldPtr;
	if (obr_.foundObject<volScalarField>(fieldName_))
	{
		TnbLog << "    Looking up field " << fieldName_ << endl;
	}
	else
	{
		TnbLog << "    Reading field " << fieldName_ << endl;
		fieldPtr.reset
		(
			new volScalarField
			(
				IOobject
				(
					fieldName_,
					mesh_.time().timeName(),
					mesh_,
					IOobject::MUST_READ,
					IOobject::NO_WRITE
				),
				mesh_
			)
		);
	}

	const volScalarField& field =
		(
			fieldPtr.valid()
			? fieldPtr()
			: obr_.lookupObject<volScalarField>(fieldName_)
			);

	// Calculate the mid-points of bins for the graph axis
	pointField xBin(nBins_);
	const scalar delta = (max_ - min_) / nBins_;

	scalar x = min_ + 0.5*delta;
	forAll(xBin, i)
	{
		xBin[i] = point(x, 0, 0);
		x += delta;
	}

	scalarField volFrac(nBins_, 0);
	const scalarField& V = mesh_.V();

	forAll(field, celli)
	{
		const label bini = (field[celli] - min_) / delta;
		if (bini >= 0 && bini < nBins_)
		{
			volFrac[bini] += V[celli];
		}
	}

	Pstream::listCombineGather(volFrac, plusEqOp<scalar>());

	if (Pstream::master())
	{
		const scalar sumVol = sum(volFrac);

		if (sumVol > small)
		{
			volFrac /= sumVol;

			const coordSet coords
			(
				"Volume_Fraction",
				"x",
				xBin,
				mag(xBin)
			);

			writeGraph(coords, field.name(), volFrac);
		}
	}

	return true;
}


// ************************************************************************* //