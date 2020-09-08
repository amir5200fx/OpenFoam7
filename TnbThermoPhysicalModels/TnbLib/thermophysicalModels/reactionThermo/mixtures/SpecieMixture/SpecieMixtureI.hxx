#pragma once
#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class MixtureType>
tnbLib::SpecieMixture<MixtureType>::SpecieMixture
(
	const dictionary& thermoDict,
	const fvMesh& mesh,
	const word& phaseName
)
	:
	MixtureType
	(
		thermoDict,
		mesh,
		phaseName
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class MixtureType>
tnbLib::scalar tnbLib::SpecieMixture<MixtureType>::Wi
(
	const label speciei
) const
{
	return this->getLocalThermo(speciei).W();
}


template<class MixtureType>
tnbLib::scalar tnbLib::SpecieMixture<MixtureType>::Cp
(
	const label speciei,
	const scalar p,
	const scalar T
) const
{
	return this->getLocalThermo(speciei).Cp(p, T);
}


template<class MixtureType>
tnbLib::scalar tnbLib::SpecieMixture<MixtureType>::Cv
(
	const label speciei,
	const scalar p,
	const scalar T
) const
{
	return this->getLocalThermo(speciei).Cv(p, T);
}


template<class MixtureType>
tnbLib::scalar tnbLib::SpecieMixture<MixtureType>::Ha
(
	const label speciei,
	const scalar p,
	const scalar T
) const
{
	return this->getLocalThermo(speciei).Ha(p, T);
}


template<class MixtureType>
tnbLib::scalar tnbLib::SpecieMixture<MixtureType>::Hs
(
	const label speciei,
	const scalar p,
	const scalar T
) const
{
	return this->getLocalThermo(speciei).Hs(p, T);
}


template<class MixtureType>
tnbLib::scalar tnbLib::SpecieMixture<MixtureType>::Hc
(
	const label speciei
) const
{
	return this->getLocalThermo(speciei).Hc();
}


template<class MixtureType>
tnbLib::scalar tnbLib::SpecieMixture<MixtureType>::S
(
	const label speciei,
	const scalar p,
	const scalar T
) const
{
	return this->getLocalThermo(speciei).S(p, T);
}


template<class MixtureType>
tnbLib::scalar tnbLib::SpecieMixture<MixtureType>::Es
(
	const label speciei,
	const scalar p,
	const scalar T
) const
{
	return this->getLocalThermo(speciei).Es(p, T);
}


template<class MixtureType>
tnbLib::scalar tnbLib::SpecieMixture<MixtureType>::G
(
	const label speciei,
	const scalar p,
	const scalar T
) const
{
	return this->getLocalThermo(speciei).G(p, T);
}


template<class MixtureType>
tnbLib::scalar tnbLib::SpecieMixture<MixtureType>::A
(
	const label speciei,
	const scalar p,
	const scalar T
) const
{
	return this->getLocalThermo(speciei).A(p, T);
}


template<class MixtureType>
tnbLib::scalar tnbLib::SpecieMixture<MixtureType>::mu
(
	const label speciei,
	const scalar p,
	const scalar T
) const
{
	return this->getLocalThermo(speciei).mu(p, T);
}


template<class MixtureType>
tnbLib::scalar tnbLib::SpecieMixture<MixtureType>::kappa
(
	const label speciei,
	const scalar p,
	const scalar T
) const
{
	return this->getLocalThermo(speciei).kappa(p, T);
}


template<class MixtureType>
tnbLib::scalar tnbLib::SpecieMixture<MixtureType>::alphah
(
	const label speciei,
	const scalar p,
	const scalar T
) const
{
	return this->getLocalThermo(speciei).alphah(p, T);
}


template<class MixtureType>
tnbLib::scalar tnbLib::SpecieMixture<MixtureType>::rho
(
	const label speciei,
	const scalar p,
	const scalar T
) const
{
	return this->getLocalThermo(speciei).rho(p, T);
}


// ************************************************************************* //