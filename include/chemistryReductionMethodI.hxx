#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CompType, class ThermoType>
inline bool
tnbLib::chemistryReductionMethod<CompType, ThermoType>::active() const
{
	return active_;
}


template<class CompType, class ThermoType>
inline bool
tnbLib::chemistryReductionMethod<CompType, ThermoType>::log() const
{
	return active_ && log_;
}


template<class CompType, class ThermoType>
inline const tnbLib::List<bool>&
tnbLib::chemistryReductionMethod<CompType, ThermoType>::activeSpecies() const
{
	return activeSpecies_;
}

template<class CompType, class ThermoType>
inline tnbLib::label
tnbLib::chemistryReductionMethod<CompType, ThermoType>::NsSimp()
{
	return NsSimp_;
}


template<class CompType, class ThermoType>
inline tnbLib::label
tnbLib::chemistryReductionMethod<CompType, ThermoType>::nSpecie()
{
	return nSpecie_;
}


template<class CompType, class ThermoType>
inline tnbLib::scalar
tnbLib::chemistryReductionMethod<CompType, ThermoType>::tolerance() const
{
	return tolerance_;
}


// ************************************************************************* //