#include <maxDeltaxyz.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{
		defineTypeNameAndDebug(maxDeltaxyz, 0);
		addToRunTimeSelectionTable(LESdelta, maxDeltaxyz, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::LESModels::maxDeltaxyz::calcDelta()
{
	const fvMesh& mesh = turbulenceModel_.mesh();

	label nD = mesh.nGeometricD();

	const cellList& cells = mesh.cells();
	scalarField hmax(cells.size());

	forAll(cells, celli)
	{
		scalar deltaMaxTmp = 0.0;
		const labelList& cFaces = mesh.cells()[celli];
		const point& centrevector = mesh.cellCentres()[celli];

		forAll(cFaces, cFacei)
		{
			label facei = cFaces[cFacei];
			const point& facevector = mesh.faceCentres()[facei];
			scalar tmp = mag(facevector - centrevector);
			if (tmp > deltaMaxTmp)
			{
				deltaMaxTmp = tmp;
			}
		}

		hmax[celli] = deltaCoeff_ * deltaMaxTmp;
	}

	if (nD == 3)
	{
		delta_.primitiveFieldRef() = hmax;
	}
	else if (nD == 2)
	{
		WarningInFunction
			<< "Case is 2D, LES is not strictly applicable\n"
			<< endl;

		delta_.primitiveFieldRef() = hmax;
	}
	else
	{
		FatalErrorInFunction
			<< "Case is not 3D or 2D, LES is not applicable"
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::LESModels::maxDeltaxyz::maxDeltaxyz
(
	const word& name,
	const turbulenceModel& turbulence,
	const dictionary& dict
)
	:
	LESdelta(name, turbulence),
	deltaCoeff_
	(
		dict.optionalSubDict(type() + "Coeffs").lookupOrDefault<scalar>
		(
			"deltaCoeff",
			1
			)
	)
{
	calcDelta();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::LESModels::maxDeltaxyz::read(const dictionary& dict)
{
	const dictionary& coeffsDict(dict.optionalSubDict(type() + "Coeffs"));

	coeffsDict.readIfPresent<scalar>("deltaCoeff", deltaCoeff_);

	calcDelta();
}


void tnbLib::LESModels::maxDeltaxyz::correct()
{
	if (turbulenceModel_.mesh().changing())
	{
		calcDelta();
	}
}


// ************************************************************************* //