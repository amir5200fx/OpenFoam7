#include <compressibleTurbulenceModel.hxx>

#include <surfaceInterpolate.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(compressibleTurbulenceModel, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::compressibleTurbulenceModel::compressibleTurbulenceModel
(
	const volScalarField& rho,
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
	),
	rho_(rho)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::compressibleTurbulenceModel::phi() const
{
	if (phi_.dimensions() == dimensionSet(0, 3, -1, 0, 0))
	{
		return phi_;
	}
	else
	{
		return phi_ / fvc::interpolate(rho_);
	}
}


void tnbLib::compressibleTurbulenceModel::correctEnergyTransport()
{}


// ************************************************************************* //