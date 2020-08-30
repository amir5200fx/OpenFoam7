#include <BrownianMotionForce.hxx>

#include <mathematicalConstants.hxx>
#include <fundamentalConstants.hxx>
#include <demandDrivenData.hxx>
#include <turbulenceModel.hxx>

#include <mathematicalConstants.hxx>

using namespace tnbLib::constant;
using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<class CloudType>
tnbLib::scalar tnbLib::BrownianMotionForce<CloudType>::erfInv(const scalar y) const
{
	const scalar a = 0.147;
	scalar k = 2.0 / (mathematical::pi*a) + 0.5*log(1.0 - y * y);
	scalar h = log(1.0 - y * y) / a;
	scalar x = sqrt(-k + sqrt(k*k - h));

	if (y < 0.0)
	{
		return -x;
	}
	else
	{
		return x;
	}
}


template<class CloudType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::BrownianMotionForce<CloudType>::kModel() const
{
	const objectRegistry& obr = this->owner().mesh();
	const word turbName =
		IOobject::groupName
		(
			turbulenceModel::propertiesName,
			this->owner().U().group()
		);

	if (obr.foundObject<turbulenceModel>(turbName))
	{
		const turbulenceModel& model =
			obr.lookupObject<turbulenceModel>(turbName);
		return model.k();
	}
	else
	{
		FatalErrorInFunction
			<< "Turbulence model not found in mesh database" << nl
			<< "Database objects include: " << obr.sortedToc()
			<< abort(FatalError);

		return tmp<volScalarField>(nullptr);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::BrownianMotionForce<CloudType>::BrownianMotionForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	ParticleForce<CloudType>(owner, mesh, dict, typeName, true),
	rndGen_(owner.rndGen()),
	lambda_(readScalar(this->coeffs().lookup("lambda"))),
	turbulence_(readBool(this->coeffs().lookup("turbulence"))),
	kPtr_(nullptr),
	ownK_(false)
{}


template<class CloudType>
tnbLib::BrownianMotionForce<CloudType>::BrownianMotionForce
(
	const BrownianMotionForce& bmf
)
	:
	ParticleForce<CloudType>(bmf),
	rndGen_(bmf.rndGen_),
	lambda_(bmf.lambda_),
	turbulence_(bmf.turbulence_),
	kPtr_(nullptr),
	ownK_(false)
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::BrownianMotionForce<CloudType>::~BrownianMotionForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::BrownianMotionForce<CloudType>::cacheFields(const bool store)
{
	if (turbulence_)
	{
		if (store)
		{
			tmp<volScalarField> tk = kModel();
			if (tk.isTmp())
			{
				kPtr_ = tk.ptr();
				ownK_ = true;
			}
			else
			{
				kPtr_ = &tk();
				ownK_ = false;
			}
		}
		else
		{
			if (ownK_ && kPtr_)
			{
				deleteDemandDrivenData(kPtr_);
				ownK_ = false;
			}
		}
	}
}


template<class CloudType>
tnbLib::forceSuSp tnbLib::BrownianMotionForce<CloudType>::calcCoupled
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

	const scalar dp = p.d();
	const scalar Tc = td.Tc();

	const scalar alpha = 2.0*lambda_ / dp;
	const scalar cc = 1.0 + alpha * (1.257 + 0.4*exp(-1.1 / alpha));

	// Boltzmann constant
	const scalar kb = physicoChemical::k.value();

	scalar f = 0;
	if (turbulence_)
	{
		const label celli = p.cell();
		const volScalarField& k = *kPtr_;
		const scalar kc = k[celli];
		const scalar Dp = kb * Tc*cc / (3 * mathematical::pi*muc*dp);
		f = sqrt(2.0*sqr(kc)*sqr(Tc) / (Dp*dt));
	}
	else
	{
		const scalar s0 =
			216 * muc*kb*Tc / (sqr(mathematical::pi)*pow5(dp)*sqr(p.rho())*cc);
		f = mass * sqrt(mathematical::pi*s0 / dt);
	}


	// To generate a cubic distribution (3 independent directions) :
	// const scalar sqrt2 = sqrt(2.0);
	// for (direction dir = 0; dir < vector::nComponents; dir++)
	// {
	//     const scalar x = rndGen_.sample01<scalar>();
	//     const scalar eta = sqrt2*erfInv(2*x - 1.0);
	//     value.Su()[dir] = f*eta;
	// }


	// To generate a spherical distribution:

	Random& rnd = this->owner().rndGen();

	const scalar theta = rnd.scalar01()*twoPi;
	const scalar u = 2 * rnd.scalar01() - 1;

	const scalar a = sqrt(1 - sqr(u));
	const vector dir(a*cos(theta), a*sin(theta), u);

	value.Su() = f * mag(rnd.scalarNormal())*dir;

	return value;
}


// ************************************************************************* //