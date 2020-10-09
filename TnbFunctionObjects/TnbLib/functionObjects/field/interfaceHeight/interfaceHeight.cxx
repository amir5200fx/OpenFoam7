#include <interfaceHeight.hxx>

#include <fvMesh.hxx>
#include <interpolation.hxx>
#include <IOmanip.hxx>
#include <meshSearch.hxx>
#include <lineCellFace.hxx>
#include <Time.hxx>
#include <uniformDimensionedFields.hxx>
#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(interfaceHeight, 0);
		addToRunTimeSelectionTable(functionObject, interfaceHeight, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::interfaceHeight::writePositions()
{
	const uniformDimensionedVectorField& g =
		mesh_.lookupObject<uniformDimensionedVectorField>("g");
	const vector gHat = g.value() / mag(g.value());

	const volScalarField& alpha =
		mesh_.lookupObject<volScalarField>(alphaName_);

	autoPtr<interpolation<scalar>>
		interpolator
		(
			interpolation<scalar>::New(interpolationScheme_, alpha)
		);

	if (Pstream::master())
	{
		writeTime(file(fileID::heightFile));
		writeTime(file(fileID::positionFile));
	}

	forAll(locations_, li)
	{
		// Create a set along a ray projected in the direction of gravity
		const sampledSets::lineCellFace set
		(
			"",
			mesh_,
			meshSearch(mesh_),
			"xyz",
			locations_[li] + gHat * mesh_.bounds().mag(),
			locations_[li] - gHat * mesh_.bounds().mag()
		);

		// Find the height of the location above the boundary
		scalar hLB = set.size() ? -gHat & (locations_[li] - set[0]) : -vGreat;
		reduce(hLB, maxOp<scalar>());

		// Calculate the integrals of length and length*alpha along the sampling
		// line. The latter is equal to the equivalent length with alpha equal
		// to one.
		scalar sumLength = 0, sumLengthAlpha = 0;
		for (label si = 0; si < set.size() - 1; ++si)
		{
			if (set.segments()[si] != set.segments()[si + 1])
			{
				continue;
			}

			const vector& p0 = set[si], p1 = set[si + 1];
			const label c0 = set.cells()[si], c1 = set.cells()[si + 1];
			const label f0 = set.faces()[si], f1 = set.faces()[si + 1];
			const scalar a0 = interpolator->interpolate(p0, c0, f0);
			const scalar a1 = interpolator->interpolate(p1, c1, f1);

			const scalar l = -gHat & (p1 - p0);
			sumLength += l;
			sumLengthAlpha += l * (a0 + a1) / 2;
		}

		reduce(sumLength, sumOp<scalar>());
		reduce(sumLengthAlpha, sumOp<scalar>());

		// Write out
		if (Pstream::master())
		{
			// Interface heights above the boundary and location
			const scalar hIB =
				liquid_ ? sumLengthAlpha : sumLength - sumLengthAlpha;
			const scalar hIL = hIB - hLB;

			// Position of the interface
			const point p = locations_[li] - gHat * hIL;

			const tnbLib::Omanip<int> w = valueWidth(1);

			file(fileID::heightFile) << w << hIB << w << hIL;
			file(fileID::positionFile) << '(' << w << p.x() << w << p.y()
				<< valueWidth() << p.z() << ") ";
		}
	}

	if (Pstream::master())
	{
		file(fileID::heightFile).endl();
		file(fileID::positionFile).endl();
	}
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::interfaceHeight::writeFileHeader(const label i)
{
	forAll(locations_, li)
	{
		writeHeaderValue
		(
			file(i),
			"Location " + tnbLib::name(li),
			locations_[li]
		);
	}

	switch (fileID(i))
	{
	case fileID::heightFile:
		writeHeaderValue
		(
			file(i),
			"hB",
			"Interface height above the boundary"
		);
		writeHeaderValue
		(
			file(i),
			"hL",
			"Interface height above the location"
		);
		break;
	case fileID::positionFile:
		writeHeaderValue(file(i), "p", "Interface position");
		break;
	}

	const tnbLib::Omanip<int> w = valueWidth(1);

	writeCommented(file(i), "Location");
	forAll(locations_, li)
	{
		switch (fileID(i))
		{
		case fileID::heightFile:
			file(i) << w << li << w << ' ';
			break;
		case fileID::positionFile:
			file(i) << w << li << w << ' ' << w << ' ' << "  ";
			break;
		}
	}
	file(i).endl();

	writeCommented(file(i), "Time");
	forAll(locations_, li)
	{
		switch (fileID(i))
		{
		case fileID::heightFile:
			file(i) << w << "hB" << w << "hL";
			break;
		case fileID::positionFile:
			file(i) << w << "p" << w << ' ' << w << ' ' << "  ";
			break;
		}
	}
	file(i).endl();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::interfaceHeight::interfaceHeight
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	logFiles(mesh_, name),
	alphaName_("alpha"),
	liquid_(true),
	locations_(),
	interpolationScheme_("cellPoint")
{
	read(dict);
	resetNames({ "height", "position" });
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::interfaceHeight::~interfaceHeight()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::interfaceHeight::read(const dictionary& dict)
{
	dict.readIfPresent("alpha", alphaName_);
	dict.readIfPresent("liquid", liquid_);
	dict.lookup("locations") >> locations_;
	dict.readIfPresent("interpolationScheme", interpolationScheme_);

	return true;
}


bool tnbLib::functionObjects::interfaceHeight::execute()
{
	return true;
}


bool tnbLib::functionObjects::interfaceHeight::end()
{
	return true;
}


bool tnbLib::functionObjects::interfaceHeight::write()
{
	logFiles::write();

	writePositions();

	return true;
}


// ************************************************************************* //