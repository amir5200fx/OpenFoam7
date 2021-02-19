#pragma once
#include <fvMatrices.hxx>
#include <fvcDdt.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class RhoFieldType>
void tnbLib::fv::solidificationMeltingSource::apply
(
	const RhoFieldType& rho,
	fvMatrix<scalar>& eqn
)
{
	if (debug)
	{
		Info << type() << ": applying source to " << eqn.psi().name() << endl;
	}

	const volScalarField Cp(this->Cp());

	update(Cp);

	dimensionedScalar L("L", dimEnergy / dimMass, L_);

	// Contributions added to rhs of solver equation
	if (eqn.psi().dimensions() == dimTemperature)
	{
		eqn -= L / Cp * (fvc::ddt(rho, alpha1_));
	}
	else
	{
		eqn -= L * (fvc::ddt(rho, alpha1_));
	}
}


// ************************************************************************* //