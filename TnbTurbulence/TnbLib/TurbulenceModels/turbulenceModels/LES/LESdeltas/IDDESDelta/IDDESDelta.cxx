#include <IDDESDelta.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <wallDist.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{
		defineTypeNameAndDebug(IDDESDelta, 0);
		addToRunTimeSelectionTable(LESdelta, IDDESDelta, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::LESModels::IDDESDelta::calcDelta()
{
	const volScalarField& hmax = hmax_;
	const fvMesh& mesh = turbulenceModel_.mesh();

	// Wall-normal vectors
	const volVectorField& n = wallDist::New(mesh).n();

	tmp<volScalarField> tfaceToFacenMax
	(
		volScalarField::New
		(
			"faceToFaceMax",
			mesh,
			dimensionedScalar(dimLength, 0)
		)
	);

	scalarField& faceToFacenMax = tfaceToFacenMax.ref().primitiveFieldRef();

	const cellList& cells = mesh.cells();
	const vectorField& faceCentres = mesh.faceCentres();

	forAll(cells, celli)
	{
		scalar maxDelta = 0.0;
		const labelList& cFaces = cells[celli];
		const vector nci = n[celli];

		forAll(cFaces, cFacei)
		{
			label facei = cFaces[cFacei];
			const point& fci = faceCentres[facei];

			forAll(cFaces, cFacej)
			{
				label facej = cFaces[cFacej];
				const point& fcj = faceCentres[facej];
				scalar ndfc = nci & (fcj - fci);

				if (ndfc > maxDelta)
				{
					maxDelta = ndfc;
				}
			}
		}

		faceToFacenMax[celli] = maxDelta;
	}


	label nD = mesh.nGeometricD();

	if (nD == 2)
	{
		WarningInFunction
			<< "Case is 2D, LES is not strictly applicable" << nl
			<< endl;
	}
	else if (nD != 3)
	{
		FatalErrorInFunction
			<< "Case must be either 2D or 3D" << exit(FatalError);
	}

	delta_.primitiveFieldRef() =
		min
		(
			max
			(
				max
				(
					Cw_*wallDist::New(mesh).y(),
					Cw_*hmax
				),
				tfaceToFacenMax
			),
			hmax
		);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::LESModels::IDDESDelta::IDDESDelta
(
	const word& name,
	const turbulenceModel& turbulence,
	const dictionary& dict
)
	:
	LESdelta(name, turbulence),
	hmax_
	(
		IOobject::groupName("hmax", turbulence.U().group()),
		turbulence,
		dict
	),
	Cw_
	(
		dict.optionalSubDict(type() + "Coeffs").lookupOrDefault<scalar>
		(
			"Cw",
			0.15
			)
	)
{
	calcDelta();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::LESModels::IDDESDelta::read(const dictionary& dict)
{
	const dictionary& coeffsDict(dict.optionalSubDict(type() + "Coeffs"));

	coeffsDict.readIfPresent<scalar>("Cw", Cw_);

	calcDelta();
}


void tnbLib::LESModels::IDDESDelta::correct()
{
	if (turbulenceModel_.mesh().changing())
	{
		hmax_.correct();
		calcDelta();
	}
}


// ************************************************************************* //