#include <SRFForce.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SRFForce<CloudType>::SRFForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	ParticleForce<CloudType>(owner, mesh, dict, typeName, false),
	srfPtr_(nullptr)
{}


template<class CloudType>
tnbLib::SRFForce<CloudType>::SRFForce
(
	const SRFForce& srff
)
	:
	ParticleForce<CloudType>(srff),
	srfPtr_(nullptr)
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SRFForce<CloudType>::~SRFForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::SRFForce<CloudType>::cacheFields(const bool store)
{
	if (store)
	{
		const typename SRF::SRFModel& model = this->mesh().template
			lookupObject<SRF::SRFModel>("SRFProperties");
		srfPtr_ = &model;
	}
	else
	{
		srfPtr_ = nullptr;
	}
}


template<class CloudType>
tnbLib::forceSuSp tnbLib::SRFForce<CloudType>::calcNonCoupled
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar dt,
	const scalar mass,
	const scalar Re,
	const scalar muc
) const
{
	forceSuSp value(Zero, 0.0);

	const typename SRF::SRFModel& srf = *srfPtr_;

	const vector& omega = srf.omega().value();

	const vector& r = p.position();

	// Coriolis and centrifugal acceleration terms
	value.Su() =
		mass * (1.0 - td.rhoc() / p.rho())
		*(2.0*(p.U() ^ omega) + (omega ^ (r ^ omega)));

	return value;
}


// ************************************************************************* //