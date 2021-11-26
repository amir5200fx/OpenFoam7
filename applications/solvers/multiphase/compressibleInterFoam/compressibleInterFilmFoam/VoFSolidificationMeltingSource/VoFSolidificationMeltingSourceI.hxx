#pragma once
#include <fvcDdt.hxx>
#include <twoPhaseMixtureThermo.hxx>


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class RhoFieldType>
void tnbLib::fv::VoFSolidificationMeltingSource::apply
(
	const RhoFieldType& rho,
	fvMatrix<scalar>& eqn
)
{
	if (debug)
	{
		Info << type() << ": applying source to " << eqn.psi().name() << endl;
	}

	update();

	const twoPhaseMixtureThermo& thermo
	(
		mesh_.lookupObject<twoPhaseMixtureThermo>
		(
			twoPhaseMixtureThermo::dictName
			)
	);

	const volScalarField CpVoF(thermo.thermo1().Cp());

	if (eqn.psi().dimensions() == dimTemperature)
	{
		eqn += L_ / CpVoF * (fvc::ddt(rho, alphaSolid_));
	}
	else
	{
		eqn += L_ * (fvc::ddt(rho, alphaSolid_));
	}
}


// ************************************************************************* //