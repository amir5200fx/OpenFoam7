#include <CrossPowerLaw.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{
		namespace generalizedNewtonianViscosityModels
		{
			defineTypeNameAndDebug(CrossPowerLaw, 0);

			addToRunTimeSelectionTable
			(
				generalizedNewtonianViscosityModel,
				CrossPowerLaw,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::laminarModels::generalizedNewtonianViscosityModels::CrossPowerLaw::
CrossPowerLaw
(
	const dictionary& viscosityProperties
)
	:
	generalizedNewtonianViscosityModel(viscosityProperties),
	nuInf_("nuInf", dimViscosity, 0),
	m_("m", dimTime, 0),
	tauStar_("tauStar", dimViscosity / dimTime, 0),
	n_("n", dimless, 0)
{
	read(viscosityProperties);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::laminarModels::generalizedNewtonianViscosityModels::CrossPowerLaw::
read
(
	const dictionary& viscosityProperties
)
{
	generalizedNewtonianViscosityModel::read(viscosityProperties);

	const dictionary& coeffs =
		viscosityProperties.optionalSubDict(typeName + "Coeffs");

	coeffs.lookup("nuInf") >> nuInf_;

	if (coeffs.found("tauStar"))
	{
		coeffs.lookup("tauStar") >> tauStar_;
	}
	else
	{
		coeffs.lookup("m") >> m_;
	}

	coeffs.lookup("n") >> n_;

	return true;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarModels::generalizedNewtonianViscosityModels::CrossPowerLaw::
nu
(
	const volScalarField& nu0,
	const volScalarField& strainRate
) const
{
	return
		nuInf_
		+ (nu0 - nuInf_)
		/ (
			scalar(1)
			+ pow
			(
				tauStar_.value() > 0
				? nu0 * strainRate / tauStar_
				: m_ * strainRate,
				n_
			)
			);
}


// ************************************************************************* //