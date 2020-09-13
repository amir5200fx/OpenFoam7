#pragma once
#include <Random.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SHF<CloudType>::SHF
(
	const dictionary& dict,
	CloudType& owner
)
	:
	BreakupModel<CloudType>(dict, owner, typeName),
	weCorrCoeff_(readScalar(this->coeffDict().lookup("weCorrCoeff"))),
	weBuCrit_(readScalar(this->coeffDict().lookup("weBuCrit"))),
	weBuBag_(readScalar(this->coeffDict().lookup("weBuBag"))),
	weBuMM_(readScalar(this->coeffDict().lookup("weBuMM"))),
	ohnCoeffCrit_(readScalar(this->coeffDict().lookup("ohnCoeffCrit"))),
	ohnCoeffBag_(readScalar(this->coeffDict().lookup("ohnCoeffBag"))),
	ohnCoeffMM_(readScalar(this->coeffDict().lookup("ohnCoeffMM"))),
	ohnExpCrit_(readScalar(this->coeffDict().lookup("ohnExpCrit"))),
	ohnExpBag_(readScalar(this->coeffDict().lookup("ohnExpBag"))),
	ohnExpMM_(readScalar(this->coeffDict().lookup("ohnExpMM"))),
	cInit_(readScalar(this->coeffDict().lookup("Cinit"))),
	c1_(readScalar(this->coeffDict().lookup("C1"))),
	c2_(readScalar(this->coeffDict().lookup("C2"))),
	c3_(readScalar(this->coeffDict().lookup("C3"))),
	cExp1_(readScalar(this->coeffDict().lookup("Cexp1"))),
	cExp2_(readScalar(this->coeffDict().lookup("Cexp2"))),
	cExp3_(readScalar(this->coeffDict().lookup("Cexp3"))),
	weConst_(readScalar(this->coeffDict().lookup("Weconst"))),
	weCrit1_(readScalar(this->coeffDict().lookup("Wecrit1"))),
	weCrit2_(readScalar(this->coeffDict().lookup("Wecrit2"))),
	coeffD_(readScalar(this->coeffDict().lookup("CoeffD"))),
	onExpD_(readScalar(this->coeffDict().lookup("OnExpD"))),
	weExpD_(readScalar(this->coeffDict().lookup("WeExpD"))),
	mu_(readScalar(this->coeffDict().lookup("mu"))),
	sigma_(readScalar(this->coeffDict().lookup("sigma"))),
	d32Coeff_(readScalar(this->coeffDict().lookup("d32Coeff"))),
	cDmaxBM_(readScalar(this->coeffDict().lookup("cDmaxBM"))),
	cDmaxS_(readScalar(this->coeffDict().lookup("cDmaxS"))),
	corePerc_(readScalar(this->coeffDict().lookup("corePerc")))
{}


template<class CloudType>
tnbLib::SHF<CloudType>::SHF(const SHF<CloudType>& bum)
	:
	BreakupModel<CloudType>(bum),
	weCorrCoeff_(bum.weCorrCoeff_),
	weBuCrit_(bum.weBuCrit_),
	weBuBag_(bum.weBuBag_),
	weBuMM_(bum.weBuMM_),
	ohnCoeffCrit_(bum.ohnCoeffCrit_),
	ohnCoeffBag_(bum.ohnCoeffBag_),
	ohnCoeffMM_(bum.ohnCoeffMM_),
	ohnExpCrit_(bum.ohnExpCrit_),
	ohnExpBag_(bum.ohnExpBag_),
	ohnExpMM_(bum.ohnExpMM_),
	cInit_(bum.cInit_),
	c1_(bum.c1_),
	c2_(bum.c2_),
	c3_(bum.c3_),
	cExp1_(bum.cExp1_),
	cExp2_(bum.cExp2_),
	cExp3_(bum.cExp3_),
	weConst_(bum.weConst_),
	weCrit1_(bum.weCrit1_),
	weCrit2_(bum.weCrit2_),
	coeffD_(bum.coeffD_),
	onExpD_(bum.onExpD_),
	weExpD_(bum.weExpD_),
	mu_(bum.mu_),
	sigma_(bum.sigma_),
	d32Coeff_(bum.d32Coeff_),
	cDmaxBM_(bum.cDmaxBM_),
	cDmaxS_(bum.cDmaxS_),
	corePerc_(bum.corePerc_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SHF<CloudType>::~SHF()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::SHF<CloudType>::update
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
	Random& rndGen = this->owner().rndGen();

	bool addChild = false;

	scalar d03 = pow3(d);
	scalar rhopi6 = rho * constant::mathematical::pi / 6.0;
	scalar mass0 = nParticle * rhopi6*d03;
	scalar mass = mass0;

	scalar weGas = 0.5*rhoc*sqr(Urmag)*d / sigma;
	scalar weLiquid = 0.5*rho*sqr(Urmag)*d / sigma;

	// correct the Reynolds number. Reitz is using radius instead of diameter
	scalar reLiquid = 0.5*Urmag*d / mu;
	scalar ohnesorge = sqrt(weLiquid) / (reLiquid + vSmall);

	scalar weGasCorr = weGas / (1.0 + weCorrCoeff_ * ohnesorge);

	// droplet deformation characteristic time

	scalar tChar = d / Urmag * sqrt(rho / rhoc);

	scalar tFirst = cInit_ * tChar;

	scalar tSecond = 0;
	scalar tCharSecond = 0;

	bool bag = false;
	bool multimode = false;
	bool shear = false;
	bool success = false;


	// update the droplet characteristic time
	tc += dt;

	if (weGas > weConst_)
	{
		if (weGas < weCrit1_)
		{
			tCharSecond = c1_ * pow((weGas - weConst_), cExp1_);
		}
		else if (weGas >= weCrit1_ && weGas <= weCrit2_)
		{
			tCharSecond = c2_ * pow((weGas - weConst_), cExp2_);
		}
		else
		{
			tCharSecond = c3_ * pow((weGas - weConst_), cExp3_);
		}
	}

	scalar weC = weBuCrit_ * (1.0 + ohnCoeffCrit_ * pow(ohnesorge, ohnExpCrit_));
	scalar weB = weBuBag_ * (1.0 + ohnCoeffBag_ * pow(ohnesorge, ohnExpBag_));
	scalar weMM = weBuMM_ * (1.0 + ohnCoeffMM_ * pow(ohnesorge, ohnExpMM_));

	if (weGas > weC && weGas < weB)
	{
		bag = true;
	}

	if (weGas >= weB && weGas <= weMM)
	{
		multimode = true;
	}

	if (weGas > weMM)
	{
		shear = true;
	}

	tSecond = tCharSecond * tChar;

	scalar tBreakUP = tFirst + tSecond;
	if (tc > tBreakUP)
	{
		scalar d32 = coeffD_ * d*pow(ohnesorge, onExpD_)*pow(weGasCorr, weExpD_);

		if (bag || multimode)
		{
			scalar d05 = d32Coeff_ * d32;

			scalar x = 0.0;
			scalar yGuess = 0.0;
			scalar dGuess = 0.0;

			while (!success)
			{
				x = cDmaxBM_ * rndGen.sample01<scalar>();
				dGuess = sqr(x)*d05;
				yGuess = rndGen.sample01<scalar>();

				scalar p =
					x
					/ (2.0*sqrt(constant::mathematical::twoPi)*sigma_)
					*exp(-0.5*sqr((x - mu_) / sigma_));

				if (yGuess < p)
				{
					success = true;
				}
			}

			d = dGuess;
			tc = 0.0;
		}

		if (shear)
		{
			scalar dC = weConst_ * sigma / (rhoc*sqr(Urmag));
			scalar d32Red = 4.0*(d32*dC) / (5.0*dC - d32);

			scalar d05 = d32Coeff_ * d32Red;

			scalar x = 0.0;
			scalar yGuess = 0.0;
			scalar dGuess = 0.0;

			while (!success)
			{
				x = cDmaxS_ * rndGen.sample01<scalar>();
				dGuess = sqr(x)*d05;
				yGuess = rndGen.sample01<scalar>();

				scalar p =
					x
					/ (2.0*sqrt(constant::mathematical::twoPi)*sigma_)
					*exp(-0.5*sqr((x - mu_) / sigma_));

				if (yGuess < p)
				{
					success = true;
				}
			}

			d = dC;
			dChild = dGuess;
			massChild = corePerc_ * mass0;
			mass -= massChild;

			addChild = true;
			// reset timer
			tc = 0.0;
		}

		// correct nParticle to conserve mass
		nParticle = mass / (rhopi6*pow3(d));
	}

	return addChild;
}


// ************************************************************************* //