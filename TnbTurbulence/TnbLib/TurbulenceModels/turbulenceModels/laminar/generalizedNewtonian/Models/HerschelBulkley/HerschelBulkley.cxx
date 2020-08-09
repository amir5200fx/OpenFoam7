#include <HerschelBulkley.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{
		namespace generalizedNewtonianViscosityModels
		{
			defineTypeNameAndDebug(HerschelBulkley, 0);

			addToRunTimeSelectionTable
			(
				generalizedNewtonianViscosityModel,
				HerschelBulkley,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::laminarModels::generalizedNewtonianViscosityModels::HerschelBulkley::
HerschelBulkley
(
	const dictionary& viscosityProperties
)
	:
	generalizedNewtonianViscosityModel(viscosityProperties),
	k_("k", dimViscosity, 0),
	n_("n", dimless, 0),
	tau0_("tau0", dimViscosity / dimTime, 0)
{
	read(viscosityProperties);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::laminarModels::generalizedNewtonianViscosityModels::
HerschelBulkley::read
(
	const dictionary& viscosityProperties
)
{
	generalizedNewtonianViscosityModel::read(viscosityProperties);

	const dictionary& coeffs =
		viscosityProperties.optionalSubDict(typeName + "Coeffs");

	coeffs.lookup("k") >> k_;
	coeffs.lookup("n") >> n_;
	coeffs.lookup("tau0") >> tau0_;

	return true;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarModels::generalizedNewtonianViscosityModels::HerschelBulkley::
nu
(
	const volScalarField& nu0,
	const volScalarField& strainRate
) const
{
	dimensionedScalar tone("tone", dimTime, 1.0);
	dimensionedScalar rtone("rtone", dimless / dimTime, 1.0);

	return
		(
			min
			(
				nu0,
				(tau0_ + k_ * rtone*pow(tone*strainRate, n_))
				/ max
				(
					strainRate,
					dimensionedScalar("vSmall", dimless / dimTime, vSmall)
				)
			)
			);
}


// ************************************************************************* //