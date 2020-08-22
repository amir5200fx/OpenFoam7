#include <Rebound.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::Rebound<CloudType>::Rebound
(
	const dictionary& dict,
	CloudType& cloud
)
	:
	PatchInteractionModel<CloudType>(dict, cloud, typeName),
	UFactor_(readScalar(this->coeffDict().lookup("UFactor")))
{}


template<class CloudType>
tnbLib::Rebound<CloudType>::Rebound(const Rebound<CloudType>& pim)
	:
	PatchInteractionModel<CloudType>(pim),
	UFactor_(pim.UFactor_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::Rebound<CloudType>::~Rebound()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::Rebound<CloudType>::correct
(
	typename CloudType::parcelType& p,
	const polyPatch& pp,
	bool& keepParticle
)
{
	vector& U = p.U();

	keepParticle = true;
	p.active() = true;

	vector nw;
	vector Up;

	this->owner().patchData(p, pp, nw, Up);

	// Calculate motion relative to patch velocity
	U -= Up;

	scalar Un = U & nw;

	if (Un > 0.0)
	{
		U -= UFactor_ * 2.0*Un*nw;
	}

	// Return velocity to global space
	U += Up;

	return true;
}


// ************************************************************************* //