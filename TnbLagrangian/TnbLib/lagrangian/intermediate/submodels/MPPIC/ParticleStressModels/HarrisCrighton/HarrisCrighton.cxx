#include <HarrisCrighton.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace ParticleStressModels
	{
		defineTypeNameAndDebug(HarrisCrighton, 0);

		addToRunTimeSelectionTable
		(
			ParticleStressModel,
			HarrisCrighton,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::ParticleStressModels::HarrisCrighton::HarrisCrighton
(
	const dictionary& dict
)
	:
	ParticleStressModel(dict),
	pSolid_(readScalar(dict.lookup("pSolid"))),
	beta_(readScalar(dict.lookup("beta"))),
	eps_(readScalar(dict.lookup("eps")))
{}


tnbLib::ParticleStressModels::HarrisCrighton::HarrisCrighton
(
	const HarrisCrighton& hc
)
	:
	ParticleStressModel(hc),
	pSolid_(hc.pSolid_),
	beta_(hc.beta_),
	eps_(hc.eps_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::ParticleStressModels::HarrisCrighton::~HarrisCrighton()
{}


// * * * * * * * * * * * * * Privare Member Functions  * * * * * * * * * * * //

tnbLib::tmp<tnbLib::Field<tnbLib::scalar>>
tnbLib::ParticleStressModels::HarrisCrighton::denominator
(
	const Field<scalar>& alpha
) const
{
	return
		max
		(
			alphaPacked_ - alpha,
			max(eps_*(1.0 - alpha), small)
		);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::Field<tnbLib::scalar>>
tnbLib::ParticleStressModels::HarrisCrighton::tau
(
	const Field<scalar>& alpha,
	const Field<scalar>& rho,
	const Field<scalar>& uSqr
) const
{
	return
		(
			pSolid_
			* pow(alpha, beta_)
			/ denominator(alpha)
			);
}


tnbLib::tmp<tnbLib::Field<tnbLib::scalar>>
tnbLib::ParticleStressModels::HarrisCrighton::dTaudTheta
(
	const Field<scalar>& alpha,
	const Field<scalar>& rho,
	const Field<scalar>& uSqr
) const
{
	const Field<scalar> d(denominator(alpha));

	return
		(
			pSolid_
			* pow(alpha, beta_)
			/ d
			* (beta_ / alpha + 1.0 / d)
			);
}


// ************************************************************************* //