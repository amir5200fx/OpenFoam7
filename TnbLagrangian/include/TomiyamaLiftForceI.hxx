#pragma once
// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class CloudType>
tnbLib::scalar tnbLib::TomiyamaLiftForce<CloudType>::TomiyamaLiftForce::Cl
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const vector& curlUc,
	const scalar Re,
	const scalar muc
) const
{
	const vector& g = this->owner().g().value();

	scalar Eo = p.Eo(td, sigma_);
	scalar dH = p.d()*cbrt(1.0 + 0.163*pow(Eo, 0.757));
	scalar Eod = p.Eo(g, p.rho(), td.rhoc(), p.U(), dH, sigma_);
	scalar f = 0.00105*pow3(Eod) - 0.0159*sqr(Eod) - 0.0204*Eod + 0.474;

	if (Eod <= 4)
	{
		return min(0.288*tanh(0.121*Re), f);
	}
	else if ((Eod > 4) && (Eod <= 10))
	{
		return f;
	}
	else
	{
		return -0.27;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::TomiyamaLiftForce<CloudType>::TomiyamaLiftForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& forceType
)
	:
	LiftForce<CloudType>(owner, mesh, dict, forceType),
	sigma_(readScalar(this->coeffs().lookup("sigma")))
{}


template<class CloudType>
tnbLib::TomiyamaLiftForce<CloudType>::TomiyamaLiftForce
(
	const TomiyamaLiftForce& lf
)
	:
	LiftForce<CloudType>(lf),
	sigma_(lf.sigma_)
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::TomiyamaLiftForce<CloudType>::~TomiyamaLiftForce()
{}


// ************************************************************************* //