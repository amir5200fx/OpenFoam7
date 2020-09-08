#pragma once
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <fvScalarMatrix.hxx>
#include <fvmDdt.hxx>
#include <fvmLaplacian.hxx>
#include <fvcDiv.hxx>
#include <fixedValueFvPatchFields.hxx>
#include <zeroGradientFvPatchFields.hxx>
#include <adjustPhi.hxx>
#include <fvcMeshPhi.hxx>
#include <nonOrthogonalSolutionControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class RAUfType, class DivUType>
void tnbLib::CorrectPhi
(
	volVectorField& U,
	surfaceScalarField& phi,
	const volScalarField& p,
	const RAUfType& rAUf,
	const DivUType& divU,
	nonOrthogonalSolutionControl& pcorrControl,
	const bool evaluateUBCs
)
{
	const fvMesh& mesh = U.mesh();
	const Time& runTime = mesh.time();

	correctUphiBCs(U, phi, evaluateUBCs);

	// Initialize BCs list for pcorr to zero-gradient
	wordList pcorrTypes
	(
		p.boundaryField().size(),
		zeroGradientFvPatchScalarField::typeName
	);

	// Set BCs of pcorr to fixed-value for patches at which p is fixed
	forAll(p.boundaryField(), patchi)
	{
		if (p.boundaryField()[patchi].fixesValue())
		{
			pcorrTypes[patchi] = fixedValueFvPatchScalarField::typeName;
		}
	}

	volScalarField pcorr
	(
		IOobject
		(
			"pcorr",
			runTime.timeName(),
			mesh
		),
		mesh,
		dimensionedScalar(p.dimensions(), 0),
		pcorrTypes
	);

	if (pcorr.needReference())
	{
		fvc::makeRelative(phi, U);
		adjustPhi(phi, U, pcorr);
		fvc::makeAbsolute(phi, U);
	}

	mesh.setFluxRequired(pcorr.name());

	while (pcorrControl.correctNonOrthogonal())
	{
		// Solve for pcorr such that the divergence of the corrected flux
		// matches the divU provided (from previous iteration, time-step...)
		fvScalarMatrix pcorrEqn
		(
			fvm::laplacian(rAUf, pcorr) == fvc::div(phi) - divU
		);

		pcorrEqn.setReference(0, 0);

		pcorrEqn.solve();

		if (pcorrControl.finalNonOrthogonalIter())
		{
			phi -= pcorrEqn.flux();
		}
	}
}


template<class RAUfType, class DivRhoUType>
void tnbLib::CorrectPhi
(
	volVectorField& U,
	surfaceScalarField& phi,
	const volScalarField& p,
	const volScalarField& rho,
	const volScalarField& psi,
	const RAUfType& rAUf,
	const DivRhoUType& divRhoU,
	nonOrthogonalSolutionControl& pcorrControl,
	const bool evaluateUBCs
)
{
	const fvMesh& mesh = U.mesh();
	const Time& runTime = mesh.time();

	correctUphiBCs(rho, U, phi, evaluateUBCs);

	// Initialize BCs list for pcorr to zero-gradient
	wordList pcorrTypes
	(
		p.boundaryField().size(),
		zeroGradientFvPatchScalarField::typeName
	);

	// Set BCs of pcorr to fixed-value for patches at which p is fixed
	forAll(p.boundaryField(), patchi)
	{
		if (p.boundaryField()[patchi].fixesValue())
		{
			pcorrTypes[patchi] = fixedValueFvPatchScalarField::typeName;
		}
	}

	volScalarField pcorr
	(
		IOobject
		(
			"pcorr",
			runTime.timeName(),
			mesh
		),
		mesh,
		dimensionedScalar(p.dimensions(), 0),
		pcorrTypes
	);

	mesh.setFluxRequired(pcorr.name());

	while (pcorrControl.correctNonOrthogonal())
	{
		// Solve for pcorr such that the divergence of the corrected flux
		// matches the divRhoU provided (from previous iteration, time-step...)
		fvScalarMatrix pcorrEqn
		(
			fvm::ddt(psi, pcorr)
			+ fvc::div(phi)
			- fvm::laplacian(rAUf, pcorr)
			==
			divRhoU
		);

		pcorrEqn.solve();

		if (pcorrControl.finalNonOrthogonalIter())
		{
			phi += pcorrEqn.flux();
		}
	}
}


// ************************************************************************* //