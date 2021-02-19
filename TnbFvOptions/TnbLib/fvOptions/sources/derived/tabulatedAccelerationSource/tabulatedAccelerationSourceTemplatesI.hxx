#pragma once
#include <fvMesh.hxx>
#include <fvMatrices.hxx>
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class RhoFieldType>
void tnbLib::fv::tabulatedAccelerationSource::addSup
(
	const RhoFieldType& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	Vector<vector> acceleration(motion_.acceleration());

	// If gravitational force is present combine with the linear acceleration
	if (mesh_.foundObject<uniformDimensionedVectorField>("g"))
	{
		uniformDimensionedVectorField& g =
			mesh_.lookupObjectRef<uniformDimensionedVectorField>("g");

		const uniformDimensionedScalarField& hRef =
			mesh_.lookupObject<uniformDimensionedScalarField>("hRef");

		g = g0_ - dimensionedVector("a", dimAcceleration, acceleration.x());

		dimensionedScalar ghRef(-mag(g)*hRef);

		mesh_.lookupObjectRef<volScalarField>("gh") = (g & mesh_.C()) - ghRef;

		mesh_.lookupObjectRef<surfaceScalarField>("ghf") =
			(g & mesh_.Cf()) - ghRef;
	}
	// ... otherwise include explicitly in the momentum equation
	else
	{
		eqn -= rho * dimensionedVector("a", dimAcceleration, acceleration.x());
	}

	dimensionedVector Omega
	(
		"Omega",
		dimensionSet(0, 0, -1, 0, 0),
		acceleration.y()
	);

	dimensionedVector dOmegaDT
	(
		"dOmegaDT",
		dimensionSet(0, 0, -2, 0, 0),
		acceleration.z()
	);

	eqn -=
		(
			rho*(2 * Omega ^ eqn.psi())         // Coriolis force
			+ rho * (Omega ^ (Omega ^ mesh_.C())) // Centrifugal force
			+ rho * (dOmegaDT ^ mesh_.C())        // Angular tabulatedAcceleration force
			);
}


// ************************************************************************* //