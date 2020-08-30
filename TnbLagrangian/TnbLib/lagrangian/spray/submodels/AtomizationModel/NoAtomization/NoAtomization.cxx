#include <NoAtomization.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoAtomization<CloudType>::NoAtomization
(
	const dictionary& dict,
	CloudType& owner
)
	:
	AtomizationModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::NoAtomization<CloudType>::NoAtomization
(
	const NoAtomization<CloudType>& am
)
	:
	AtomizationModel<CloudType>(am)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoAtomization<CloudType>::~NoAtomization()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::NoAtomization<CloudType>::active() const
{
	return false;
}


template<class CloudType>
tnbLib::scalar tnbLib::NoAtomization<CloudType>::initLiquidCore() const
{
	return 0.0;
}


template<class CloudType>
bool tnbLib::NoAtomization<CloudType>::calcChi() const
{
	return false;
}


template<class CloudType>
void tnbLib::NoAtomization<CloudType>::update
(
	const scalar dt,
	scalar& d,
	scalar& liquidCore,
	scalar& tc,
	const scalar rho,
	const scalar mu,
	const scalar sigma,
	const scalar volFlowRate,
	const scalar rhoAv,
	const scalar Urel,
	const vector& pos,
	const vector& injectionPos,
	const scalar pAmbient,
	const scalar chi,
	Random& rndGen
) const
{}


// ************************************************************************* //