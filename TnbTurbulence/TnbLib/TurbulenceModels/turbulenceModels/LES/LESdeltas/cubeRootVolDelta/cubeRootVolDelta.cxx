#include <cubeRootVolDelta.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{
		defineTypeNameAndDebug(cubeRootVolDelta, 0);
		addToRunTimeSelectionTable(LESdelta, cubeRootVolDelta, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::LESModels::cubeRootVolDelta::calcDelta()
{
	const fvMesh& mesh = turbulenceModel_.mesh();

	label nD = mesh.nGeometricD();

	if (nD == 3)
	{
		delta_.primitiveFieldRef() = deltaCoeff_ * pow(mesh.V(), 1.0 / 3.0);
	}
	else if (nD == 2)
	{
		WarningInFunction
			<< "Case is 2D, LES is not strictly applicable\n"
			<< endl;

		const Vector<label>& directions = mesh.geometricD();

		scalar thickness = 0.0;
		for (direction dir = 0; dir < directions.nComponents; dir++)
		{
			if (directions[dir] == -1)
			{
				thickness = mesh.bounds().span()[dir];
				break;
			}
		}

		delta_.primitiveFieldRef() = deltaCoeff_ * sqrt(mesh.V() / thickness);
	}
	else
	{
		FatalErrorInFunction
			<< "Case is not 3D or 2D, LES is not applicable"
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::LESModels::cubeRootVolDelta::cubeRootVolDelta
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

void tnbLib::LESModels::cubeRootVolDelta::read(const dictionary& dict)
{
	dict.optionalSubDict(type() + "Coeffs").readIfPresent<scalar>
		(
			"deltaCoeff",
			deltaCoeff_
			);

	calcDelta();
}


void tnbLib::LESModels::cubeRootVolDelta::correct()
{
	if (turbulenceModel_.mesh().changing())
	{
		calcDelta();
	}
}


// ************************************************************************* //