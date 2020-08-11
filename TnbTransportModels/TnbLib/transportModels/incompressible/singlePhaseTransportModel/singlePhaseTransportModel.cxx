#include <singlePhaseTransportModel.hxx>

#include <viscosityModel.hxx>
#include <volFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(singlePhaseTransportModel, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::singlePhaseTransportModel::singlePhaseTransportModel
(
	const volVectorField& U,
	const surfaceScalarField& phi
)
	:
	IOdictionary
	(
		IOobject
		(
			"transportProperties",
			U.time().constant(),
			U.db(),
			IOobject::MUST_READ_IF_MODIFIED,
			IOobject::NO_WRITE
		)
	),
	viscosityModelPtr_(viscosityModel::New("nu", *this, U, phi))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::singlePhaseTransportModel::~singlePhaseTransportModel()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::singlePhaseTransportModel::nu() const
{
	return viscosityModelPtr_->nu();
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::singlePhaseTransportModel::nu(const label patchi) const
{
	return viscosityModelPtr_->nu(patchi);
}


void tnbLib::singlePhaseTransportModel::correct()
{
	viscosityModelPtr_->correct();
}


bool tnbLib::singlePhaseTransportModel::read()
{
	if (regIOobject::read())
	{
		return viscosityModelPtr_->read(*this);
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //