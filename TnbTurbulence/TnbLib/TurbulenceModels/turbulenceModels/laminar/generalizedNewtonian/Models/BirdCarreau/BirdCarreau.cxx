#include <BirdCarreau.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{
		namespace generalizedNewtonianViscosityModels
		{
			defineTypeNameAndDebug(BirdCarreau, 0);
			addToRunTimeSelectionTable
			(
				generalizedNewtonianViscosityModel,
				BirdCarreau,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::laminarModels::generalizedNewtonianViscosityModels::BirdCarreau::
BirdCarreau
(
	const dictionary& viscosityProperties
)
	:
	generalizedNewtonianViscosityModel(viscosityProperties),
	nuInf_("nuInf", dimViscosity, 0),
	k_("k", dimTime, 0),
	tauStar_("tauStar", dimViscosity / dimTime, 0),
	n_("n", dimless, 0),
	a_("a", dimless, 2)
{
	read(viscosityProperties);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::laminarModels::generalizedNewtonianViscosityModels::BirdCarreau::
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
		coeffs.lookup("k") >> k_;
	}

	coeffs.lookup("n") >> n_;

	a_ = coeffs.lookupOrDefault
	(
		"a",
		dimensionedScalar("a", dimless, 2)
	);

	return true;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarModels::generalizedNewtonianViscosityModels::BirdCarreau::
nu
(
	const volScalarField& nu0,
	const volScalarField& strainRate
) const
{
	return
		nuInf_
		+ (nu0 - nuInf_)
		*pow
		(
			scalar(1)
			+ pow
			(
				tauStar_.value() > 0
				? nu0 * strainRate / tauStar_
				: k_ * strainRate,
				a_
			),
			(n_ - 1.0) / a_
		);
}


// ************************************************************************* //