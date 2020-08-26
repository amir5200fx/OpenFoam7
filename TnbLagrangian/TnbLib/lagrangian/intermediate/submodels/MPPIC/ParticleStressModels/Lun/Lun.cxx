#include <Lun.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace ParticleStressModels
	{
		defineTypeNameAndDebug(Lun, 0);

		addToRunTimeSelectionTable
		(
			ParticleStressModel,
			Lun,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::ParticleStressModels::Lun::Lun
(
	const dictionary& dict
)
	:
	ParticleStressModel(dict),
	e_(readScalar(dict.lookup("e"))),
	eps_(readScalar(dict.lookup("eps")))
{}


tnbLib::ParticleStressModels::Lun::Lun
(
	const Lun& ln
)
	:
	ParticleStressModel(ln),
	e_(ln.e_),
	eps_(ln.eps_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::ParticleStressModels::Lun::~Lun()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::Field<tnbLib::scalar>>
tnbLib::ParticleStressModels::Lun::tau
(
	const Field<scalar>& alpha,
	const Field<scalar>& rho,
	const Field<scalar>& uSqr
) const
{
	tmp<Field<scalar>> g0
	(
		0.6
		/ max
		(
			1.0 - pow(alpha / alphaPacked_, 1.0 / 3.0),
			max(eps_*(1.0 - alpha), small)
		)
	);

	tmp<Field<scalar>> gT(uSqr / 3.0);

	return alpha * rho*(1.0 + alpha * (1.0 + e_)*g0)*gT;
}


tnbLib::tmp<tnbLib::Field<tnbLib::scalar>>
tnbLib::ParticleStressModels::Lun::dTaudTheta
(
	const Field<scalar>& alpha,
	const Field<scalar>& rho,
	const Field<scalar>& uSqr
) const
{
	NotImplemented;

	return tmp<Field<scalar>>(nullptr);
}


// ************************************************************************* //