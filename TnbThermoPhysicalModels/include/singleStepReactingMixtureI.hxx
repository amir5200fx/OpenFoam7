#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class ThermoType>
inline const tnbLib::dimensionedScalar
tnbLib::singleStepReactingMixture<ThermoType>::stoicRatio() const
{
	return stoicRatio_;
}


template<class ThermoType>
inline const tnbLib::dimensionedScalar
tnbLib::singleStepReactingMixture<ThermoType>::s() const
{
	return s_;
}


template<class ThermoType>
inline const tnbLib::dimensionedScalar
tnbLib::singleStepReactingMixture<ThermoType>::qFuel() const
{
	return qFuel_;
}


template<class ThermoType>
inline const tnbLib::List<tnbLib::scalar>&
tnbLib::singleStepReactingMixture<ThermoType>::specieStoichCoeffs() const
{
	return specieStoichCoeffs_;
}


template<class ThermoType>
inline tnbLib::tmp<tnbLib::volScalarField>
tnbLib::singleStepReactingMixture<ThermoType>::fres
(
	const label index
) const
{
	return fres_[index];
}


template<class ThermoType>
inline tnbLib::label
tnbLib::singleStepReactingMixture<ThermoType>::inertIndex() const
{
	return inertIndex_;
}


template<class ThermoType>
inline tnbLib::label
tnbLib::singleStepReactingMixture<ThermoType>::fuelIndex() const
{
	return fuelIndex_;
}


template<class ThermoType>
inline const tnbLib::List<int>&
tnbLib::singleStepReactingMixture<ThermoType>::specieProd() const
{
	return specieProd_;
}


template<class ThermoType>
inline const tnbLib::scalarList&
tnbLib::singleStepReactingMixture<ThermoType>::Yprod0() const
{
	return Yprod0_;
}


// ************************************************************************* //