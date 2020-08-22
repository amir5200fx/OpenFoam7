#include <WenYuDragForce.hxx>

#include <SchillerNaumannDragForce.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::WenYuDragForce<CloudType>::WenYuDragForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	DenseDragForce<CloudType>(owner, mesh, dict, typeName)
{}


template<class CloudType>
tnbLib::WenYuDragForce<CloudType>::WenYuDragForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& typeName
)
	:
	DenseDragForce<CloudType>(owner, mesh, dict, typeName)
{}


template<class CloudType>
tnbLib::WenYuDragForce<CloudType>::WenYuDragForce
(
	const WenYuDragForce<CloudType>& df
)
	:
	DenseDragForce<CloudType>(df)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::WenYuDragForce<CloudType>::~WenYuDragForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::forceSuSp tnbLib::WenYuDragForce<CloudType>::calcCoupled
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar dt,
	const scalar mass,
	const scalar Re,
	const scalar muc
) const
{
	const scalar alphac =
		this->alphacInterp().interpolate
		(
			p.coordinates(),
			p.currentTetIndices()
		);
	const scalar CdRe = SchillerNaumannDragForce<CloudType>::CdRe(alphac*Re);

	return forceSuSp
	(
		Zero,
		0.75*(mass / p.rho())*CdRe*muc*pow(alphac, -2.65) / (alphac*sqr(p.d()))
	);
}


// ************************************************************************* //