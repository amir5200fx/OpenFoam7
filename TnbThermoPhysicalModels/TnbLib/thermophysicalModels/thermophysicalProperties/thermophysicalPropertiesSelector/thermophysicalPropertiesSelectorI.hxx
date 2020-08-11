#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ThermophysicalProperties>
inline const ThermophysicalProperties&
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>
::properties() const
{
	return propertiesPtr_();
}

template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::W() const
{
	return propertiesPtr_->W();
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::limit
(
	const scalar T
) const
{
	return propertiesPtr_->limit(T);
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::rho
(
	scalar p,
	scalar T
) const
{
	return propertiesPtr_->rho(p, T);
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::psi
(
	scalar p,
	scalar T
) const
{
	return propertiesPtr_->psi(p, T);
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::CpMCv
(
	scalar p,
	scalar T
) const
{
	return propertiesPtr_->CpMCv(p, T);
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::Cp
(
	scalar p,
	scalar T
) const
{
	return propertiesPtr_->Cp(p, T);
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::Hs
(
	scalar p,
	scalar T
) const
{
	return propertiesPtr_->Hs(p, T);
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::Hc() const
{
	return propertiesPtr_->Hc();
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::Ha
(
	scalar p,
	scalar T
) const
{
	return propertiesPtr_->Ha(p, T);
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::Cv
(
	scalar p,
	scalar T
) const
{
	return propertiesPtr_->Cp(p, T) - CpMCv(p, T);
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::Es
(
	scalar p,
	scalar T
) const
{
	return propertiesPtr_->Hs(p, T) - p / propertiesPtr_->rho(p, T);
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::Ea
(
	scalar p,
	scalar T
) const
{
	return propertiesPtr_->Ha(p, T) - p / propertiesPtr_->rho(p, T);
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::S
(
	scalar p,
	scalar T
) const
{
	return propertiesPtr_->S(p, T);
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::mu
(
	scalar p,
	scalar T
) const
{
	return propertiesPtr_->mu(p, T);
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::kappa
(
	scalar p,
	scalar T
) const
{
	return propertiesPtr_->kappa(p, T);
}


template<class ThermophysicalProperties>
inline tnbLib::scalar
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::alphah
(
	scalar p,
	scalar T
) const
{
	return propertiesPtr_->alphah(p, T);
}


// ************************************************************************* //