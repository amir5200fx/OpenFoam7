#include <MPPICParcel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::MPPICParcel<ParcelType>::MPPICParcel
(
	const MPPICParcel<ParcelType>& p
)
	:
	ParcelType(p),
	UCorrect_(p.UCorrect_)
{}


template<class ParcelType>
tnbLib::MPPICParcel<ParcelType>::MPPICParcel
(
	const MPPICParcel<ParcelType>& p,
	const polyMesh& mesh
)
	:
	ParcelType(p, mesh),
	UCorrect_(p.UCorrect_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ParcelType>
template<class TrackCloudType>
bool tnbLib::MPPICParcel<ParcelType>::move
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar trackTime
)
{
	typename TrackCloudType::parcelType& p =
		static_cast<typename TrackCloudType::parcelType&>(*this);

	switch (td.part())
	{
	case trackingData::tpLinearTrack:
	{
		ParcelType::move(cloud, td, trackTime);

		break;
	}
	case trackingData::tpDampingNoTrack:
	{
		p.UCorrect() =
			cloud.dampingModel().velocityCorrection(p, trackTime);

		td.keepParticle = true;
		td.switchProcessor = false;

		break;
	}
	case trackingData::tpPackingNoTrack:
	{
		p.UCorrect() =
			cloud.packingModel().velocityCorrection(p, trackTime);

		td.keepParticle = true;
		td.switchProcessor = false;

		break;
	}
	case trackingData::tpCorrectTrack:
	{
		const scalar f = p.stepFraction();
		const scalar a = p.age();

		Swap(p.U(), p.UCorrect());

		ParcelType::move(cloud, td, trackTime);

		Swap(p.U(), p.UCorrect());

		p.U() += (p.stepFraction() - f)*p.UCorrect();

		p.age() = a;

		break;
	}
	}

	return td.keepParticle;
}


// * * * * * * * * * * * * * * IOStream operators  * * * * * * * * * * * * * //

#include <MPPICParcelIO.cxx>

// ************************************************************************* //