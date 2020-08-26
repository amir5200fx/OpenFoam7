#include <exponentialParticleStressModel.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace ParticleStressModels
	{
		defineTypeNameAndDebug(exponential, 0);

		addToRunTimeSelectionTable
		(
			ParticleStressModel,
			exponential,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::ParticleStressModels::exponential::exponential
(
	const dictionary& dict
)
	:
	ParticleStressModel(dict),
	preExp_(readScalar(dict.lookup("preExp"))),
	expMax_(readScalar(dict.lookup("expMax"))),
	g0_(readScalar(dict.lookup("g0")))
{}


tnbLib::ParticleStressModels::exponential::exponential
(
	const exponential& hc
)
	:
	ParticleStressModel(hc),
	preExp_(hc.preExp_),
	expMax_(hc.expMax_),
	g0_(hc.g0_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::ParticleStressModels::exponential::~exponential()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::Field<tnbLib::scalar>>
tnbLib::ParticleStressModels::exponential::tau
(
	const Field<scalar>& alpha,
	const Field<scalar>& rho,
	const Field<scalar>& uSqr
) const
{
	return dTaudTheta(alpha, rho, uSqr) / preExp_;
}


tnbLib::tmp<tnbLib::Field<tnbLib::scalar>>
tnbLib::ParticleStressModels::exponential::dTaudTheta
(
	const Field<scalar>& alpha,
	const Field<scalar>& rho,
	const Field<scalar>& uSqr
) const
{
	return
		g0_
		* min
		(
			exp(preExp_*(alpha - alphaPacked_)),
			expMax_
		);
}


// ************************************************************************* //