#include <SaffmanMeiLiftForce.hxx>

#include <mathematicalConstants.hxx>

using namespace tnbLib::constant;

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class CloudType>
tnbLib::scalar tnbLib::SaffmanMeiLiftForce<CloudType>::SaffmanMeiLiftForce::Cl
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const vector& curlUc,
	const scalar Re,
	const scalar muc
) const
{
	scalar Rew = td.rhoc()*mag(curlUc)*sqr(p.d()) / (muc + rootVSmall);
	scalar beta = 0.5*(Rew / (Re + rootVSmall));
	scalar alpha = 0.3314*sqrt(beta);
	scalar f = (1.0 - alpha)*exp(-0.1*Re) + alpha;

	scalar Cld = 0.0;
	if (Re < 40)
	{
		Cld = 6.46*f;
	}
	else
	{
		Cld = 6.46*0.0524*sqrt(beta*Re);
	}

	return 3.0 / (mathematical::twoPi*sqrt(Rew + rootVSmall))*Cld;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SaffmanMeiLiftForce<CloudType>::SaffmanMeiLiftForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& forceType
)
	:
	LiftForce<CloudType>(owner, mesh, dict, forceType)
{}


template<class CloudType>
tnbLib::SaffmanMeiLiftForce<CloudType>::SaffmanMeiLiftForce
(
	const SaffmanMeiLiftForce& lf
)
	:
	LiftForce<CloudType>(lf)
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SaffmanMeiLiftForce<CloudType>::~SaffmanMeiLiftForce()
{}


// ************************************************************************* //
