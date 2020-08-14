#include <incompressibleTurbulenceModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(incompressibleTurbulenceModel, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::incompressibleTurbulenceModel::incompressibleTurbulenceModel
(
	const geometricOneField&,
	const volVectorField& U,
	const surfaceScalarField& alphaRhoPhi,
	const surfaceScalarField& phi,
	const word& propertiesName
)
	:
	turbulenceModel
	(
		U,
		alphaRhoPhi,
		phi,
		propertiesName
	)
{}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::incompressibleTurbulenceModel::mu() const
{
	return nu();
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::incompressibleTurbulenceModel::mu(const label patchi) const
{
	return nu(patchi);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::incompressibleTurbulenceModel::mut() const
{
	return nut();
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::incompressibleTurbulenceModel::mut(const label patchi) const
{
	return nut(patchi);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::incompressibleTurbulenceModel::muEff() const
{
	return nuEff();
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::incompressibleTurbulenceModel::muEff(const label patchi) const
{
	return nuEff(patchi);
}


// ************************************************************************* //