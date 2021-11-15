#include <powerLawGeneralizedNewtonian.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{
		namespace generalizedNewtonianViscosityModels
		{
			defineTypeNameAndDebug(powerLaw, 0);

			addToRunTimeSelectionTable
			(
				generalizedNewtonianViscosityModel,
				powerLaw,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::laminarModels::generalizedNewtonianViscosityModels::powerLaw::powerLaw
(
	const dictionary& viscosityProperties
)
	:
	generalizedNewtonianViscosityModel(viscosityProperties),
	k_("k", dimViscosity, 0),
	n_("n", dimless, 0),
	nuMin_("nuMin", dimViscosity, 0),
	nuMax_("nuMax", dimViscosity, 0)
{
	read(viscosityProperties);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::laminarModels::generalizedNewtonianViscosityModels::powerLaw::read
(
	const dictionary& viscosityProperties
)
{
	generalizedNewtonianViscosityModel::read(viscosityProperties);

	const dictionary& coeffs =
		viscosityProperties.optionalSubDict(typeName + "Coeffs");

	coeffs.lookup("k") >> k_;
	coeffs.lookup("n") >> n_;
	coeffs.lookup("nuMin") >> nuMin_;
	coeffs.lookup("nuMax") >> nuMax_;

	return true;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarModels::generalizedNewtonianViscosityModels::powerLaw::
nu
(
	const volScalarField& nu0,
	const volScalarField& strainRate
) const
{
	return max
	(
		nuMin_,
		min
		(
			nuMax_,
			k_*pow
			(
				max
				(
					dimensionedScalar(dimTime, 1.0)*strainRate,
					dimensionedScalar(dimless, small)
				),
				n_.value() - scalar(1)
			)
		)
	);
}


// ************************************************************************* //