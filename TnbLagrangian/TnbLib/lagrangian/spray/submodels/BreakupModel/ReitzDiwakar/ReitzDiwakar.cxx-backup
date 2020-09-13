#include <ReitzDiwakar.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ReitzDiwakar<CloudType>::ReitzDiwakar
(
	const dictionary& dict,
	CloudType& owner
)
	:
	BreakupModel<CloudType>(dict, owner, typeName),
	Cbag_(6.0),
	Cb_(0.785),
	Cstrip_(0.5),
	Cs_(10.0)
{
	if (!this->defaultCoeffs(true))
	{
		this->coeffDict().lookup("Cbag") >> Cbag_;
		this->coeffDict().lookup("Cb") >> Cb_;
		this->coeffDict().lookup("Cstrip") >> Cstrip_;
		this->coeffDict().lookup("Cs") >> Cs_;
	}
}


template<class CloudType>
tnbLib::ReitzDiwakar<CloudType>::ReitzDiwakar(const ReitzDiwakar<CloudType>& bum)
	:
	BreakupModel<CloudType>(bum),
	Cbag_(bum.Cbag_),
	Cb_(bum.Cb_),
	Cstrip_(bum.Cstrip_),
	Cs_(bum.Cs_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ReitzDiwakar<CloudType>::~ReitzDiwakar()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::ReitzDiwakar<CloudType>::update
(
	const scalar dt,
	const vector& g,
	scalar& d,
	scalar& tc,
	scalar& ms,
	scalar& nParticle,
	scalar& KHindex,
	scalar& y,
	scalar& yDot,
	const scalar d0,
	const scalar rho,
	const scalar mu,
	const scalar sigma,
	const vector& U,
	const scalar rhoc,
	const scalar muc,
	const vector& Urel,
	const scalar Urmag,
	const scalar tMom,
	scalar& dChild,
	scalar& massChild
)
{
	scalar d1 = d;
	scalar nuc = muc / rhoc;
	scalar We = 0.5*rhoc*sqr(Urmag)*d / sigma;
	scalar Re = Urmag * d / nuc;

	if (We > Cbag_)
	{
		if (We > Cstrip_*sqrt(Re))
		{
			scalar dStrip = sqr(2.0*Cstrip_*sigma) / (rhoc*pow3(Urmag)*muc);
			scalar tauStrip = Cs_ * d*sqrt(rho / rhoc) / Urmag;
			scalar fraction = dt / tauStrip;

			// new droplet diameter, implicit calculation
			d = (fraction*dStrip + d) / (1.0 + fraction);
		}
		else
		{
			scalar dBag = 2.0*Cbag_*sigma / (rhoc*sqr(Urmag));
			scalar tauBag = Cb_ * d*sqrt(rho*d / sigma);
			scalar fraction = dt / tauBag;

			// new droplet diameter, implicit calculation
			d = (fraction*dBag + d) / (1.0 + fraction);
		}

		// preserve the total mass/volume by updating the number of
		// particles in parcels due to breakup
		nParticle *= pow3(d1 / d);
	}

	return false;
}


// ************************************************************************* //