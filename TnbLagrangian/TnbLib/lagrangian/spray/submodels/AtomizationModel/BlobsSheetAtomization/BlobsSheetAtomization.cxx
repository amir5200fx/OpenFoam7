#include <BlobsSheetAtomization.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::BlobsSheetAtomization<CloudType>::BlobsSheetAtomization
(
	const dictionary& dict,
	CloudType& owner
)
	:
	AtomizationModel<CloudType>(dict, owner, typeName),
	B_(readScalar(this->coeffDict().lookup("B"))),
	angle_(readScalar(this->coeffDict().lookup("angle")))
{}


template<class CloudType>
tnbLib::BlobsSheetAtomization<CloudType>::BlobsSheetAtomization
(
	const BlobsSheetAtomization<CloudType>& am
)
	:
	AtomizationModel<CloudType>(am),
	B_(am.B_),
	angle_(am.angle_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::BlobsSheetAtomization<CloudType>::~BlobsSheetAtomization()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::scalar tnbLib::BlobsSheetAtomization<CloudType>::initLiquidCore() const
{
	return 1.0;
}


template<class CloudType>
bool tnbLib::BlobsSheetAtomization<CloudType>::calcChi() const
{
	return false;
}


template<class CloudType>
void tnbLib::BlobsSheetAtomization<CloudType>::update
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
{
	scalar lBU =
		B_
		* sqrt
		(
			rho*sigma*d*cos(angle_*constant::mathematical::pi / 360.0)
			/ sqr(rhoAv*Urel)
		);

	scalar pWalk = mag(pos - injectionPos);

	if (pWalk > lBU)
	{
		liquidCore = 0.0;
	}
}


// ************************************************************************* //