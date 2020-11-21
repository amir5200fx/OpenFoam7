#include <CollidingParcel.hxx>

//// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
//
//template<class ParcelType>
//tnbLib::CollidingParcel<ParcelType>::CollidingParcel
//(
//	const CollidingParcel<ParcelType>& p
//)
//	:
//	ParcelType(p),
//	f_(p.f_),
//	angularMomentum_(p.angularMomentum_),
//	torque_(p.torque_),
//	collisionRecords_(p.collisionRecords_)
//{}
//
//
//template<class ParcelType>
//tnbLib::CollidingParcel<ParcelType>::CollidingParcel
//(
//	const CollidingParcel<ParcelType>& p,
//	const polyMesh& mesh
//)
//	:
//	ParcelType(p, mesh),
//	f_(p.f_),
//	angularMomentum_(p.angularMomentum_),
//	torque_(p.torque_),
//	collisionRecords_(p.collisionRecords_)
//{}
//
//
//// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//template<class ParcelType>
//template<class TrackCloudType>
//bool tnbLib::CollidingParcel<ParcelType>::move
//(
//	TrackCloudType& cloud,
//	trackingData& td,
//	const scalar trackTime
//)
//{
//	typename TrackCloudType::parcelType& p =
//		static_cast<typename TrackCloudType::parcelType&>(*this);
//
//	switch (td.part())
//	{
//	case trackingData::tpVelocityHalfStep:
//	{
//		// First and last leapfrog velocity adjust part, required
//		// before and after tracking and force calculation
//
//		p.U() += 0.5*trackTime*p.f() / p.mass();
//
//		p.angularMomentum() += 0.5*trackTime*p.torque();
//
//		td.keepParticle = true;
//		td.switchProcessor = false;
//
//		break;
//	}
//
//	case trackingData::tpLinearTrack:
//	{
//		ParcelType::move(cloud, td, trackTime);
//
//		break;
//	}
//
//	case trackingData::tpRotationalTrack:
//	{
//		NotImplemented;
//
//		break;
//	}
//
//	default:
//	{
//		FatalErrorInFunction
//			<< td.part() << " is an invalid part of the tracking method."
//			<< abort(FatalError);
//	}
//	}
//
//	return td.keepParticle;
//}
//
//
//template<class ParcelType>
//void tnbLib::CollidingParcel<ParcelType>::transformProperties(const tensor& T)
//{
//	ParcelType::transformProperties(T);
//
//	f_ = transform(T, f_);
//
//	angularMomentum_ = transform(T, angularMomentum_);
//
//	torque_ = transform(T, torque_);
//}
//
//
//template<class ParcelType>
//void tnbLib::CollidingParcel<ParcelType>::transformProperties
//(
//	const vector& separation
//)
//{
//	ParcelType::transformProperties(separation);
//}
//
//
//// * * * * * * * * * * * * * * IOStream operators  * * * * * * * * * * * * * //
//
//#include <CollidingParcelIO.cxx>
//
//// ************************************************************************* //