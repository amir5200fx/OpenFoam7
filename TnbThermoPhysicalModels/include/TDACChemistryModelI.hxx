#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ReactionThermo, class ThermoType>
inline bool
tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::variableTimeStep() const
{
	return variableTimeStep_;
}


template<class ReactionThermo, class ThermoType>
inline tnbLib::label
tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::timeSteps() const
{
	return timeSteps_;
}


template<class ReactionThermo, class ThermoType>
inline tnbLib::autoPtr<tnbLib::OFstream>
tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::
logFile(const word& name) const
{
	mkDir(this->mesh().time().path() / "TDAC" / this->group());
	return autoPtr<OFstream>
		(
			new OFstream
			(
				this->mesh().time().path() / "TDAC" / this->group() / name
			)
			);
}


template<class ReactionThermo, class ThermoType>
inline tnbLib::PtrList<tnbLib::volScalarField>&
tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::Y()
{
	return this->Y_;
}


template<class ReactionThermo, class ThermoType>
inline
tnbLib::autoPtr<tnbLib::chemistryReductionMethod<ReactionThermo, ThermoType>>&
tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::mechRed()
{
	return mechRed_;
}


template<class ReactionThermo, class ThermoType>
inline void tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::setActive
(
	const label i
)
{
	this->thermo().composition().setActive(i);
}


template<class ReactionThermo, class ThermoType>
inline bool tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::active
(
	const label i
) const
{
	return this->thermo().composition().active(i);
}


template<class ReactionThermo, class ThermoType>
inline void tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::
setNsDAC(const label newNsDAC)
{
	NsDAC_ = newNsDAC;
}


template<class ReactionThermo, class ThermoType>
inline void tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::
setNSpecie(const label newNs)
{
	this->nSpecie_ = newNs;
}


template<class ReactionThermo, class ThermoType>
inline tnbLib::DynamicList<tnbLib::label>&
tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::
simplifiedToCompleteIndex()
{
	return simplifiedToCompleteIndex_;
}


template<class ReactionThermo, class ThermoType>
inline tnbLib::Field<tnbLib::label>&
tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::
completeToSimplifiedIndex()
{
	return completeToSimplifiedIndex_;
}


template<class ReactionThermo, class ThermoType>
inline const tnbLib::Field<tnbLib::label>&
tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::
completeToSimplifiedIndex() const
{
	return completeToSimplifiedIndex_;
}


template<class ReactionThermo, class ThermoType>
inline tnbLib::Field<bool>&
tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::reactionsDisabled()
{
	return reactionsDisabled_;
}


template<class ReactionThermo, class ThermoType>
inline tnbLib::scalarField&
tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::completeC()
{
	return completeC_;
}


template<class ReactionThermo, class ThermoType>
inline tnbLib::scalarField&
tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::simplifiedC()
{
	return simplifiedC_;
}


template<class ReactionThermo, class ThermoType>
inline tnbLib::List<tnbLib::List<tnbLib::specieElement>>&
tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::specieComp()
{
	return specieComp_;
}


template<class ReactionThermo, class ThermoType>
void tnbLib::TDACChemistryModel<ReactionThermo, ThermoType>::
resetTabulationResults()
{
	forAll(tabulationResults_, tabi)
	{
		tabulationResults_[tabi] = 2;
	}
}


// ************************************************************************* //