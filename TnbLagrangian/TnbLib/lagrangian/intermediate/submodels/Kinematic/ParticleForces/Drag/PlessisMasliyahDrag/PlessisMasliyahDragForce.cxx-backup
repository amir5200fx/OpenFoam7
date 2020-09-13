#include <PlessisMasliyahDragForce.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PlessisMasliyahDragForce<CloudType>::PlessisMasliyahDragForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	DenseDragForce<CloudType>(owner, mesh, dict, typeName)
{}


template<class CloudType>
tnbLib::PlessisMasliyahDragForce<CloudType>::PlessisMasliyahDragForce
(
	const PlessisMasliyahDragForce<CloudType>& df
)
	:
	DenseDragForce<CloudType>(df)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PlessisMasliyahDragForce<CloudType>::~PlessisMasliyahDragForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::forceSuSp tnbLib::PlessisMasliyahDragForce<CloudType>::calcCoupled
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

	const scalar cbrtAlphap = pow(1 - alphac, 1.0 / 3.0);

	const scalar A =
		26.8*pow3(alphac)
		/ (
			sqr(cbrtAlphap)
			*(1 - cbrtAlphap)
			*sqr(1 - sqr(cbrtAlphap))
			+ small
			);

	const scalar B =
		sqr(alphac)
		/ sqr(1 - sqr(cbrtAlphap));

	return forceSuSp
	(
		Zero,
		(mass / p.rho())
		*(A*(1 - alphac) / alphac + B * Re)*muc / (alphac*sqr(p.d()))
	);
}


// ************************************************************************* //