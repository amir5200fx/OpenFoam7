#include <Casson.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{
		namespace generalizedNewtonianViscosityModels
		{
			defineTypeNameAndDebug(Casson, 0);
			addToRunTimeSelectionTable
			(
				generalizedNewtonianViscosityModel,
				Casson,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::laminarModels::generalizedNewtonianViscosityModels::Casson::Casson
(
	const dictionary& viscosityProperties
)
	:
	generalizedNewtonianViscosityModel(viscosityProperties),
	m_("m", dimViscosity, 0),
	tau0_("tau0", dimViscosity / dimTime, 0),
	nuMin_("nuMin", dimViscosity, 0),
	nuMax_("nuMax", dimViscosity, 0)
{
	read(viscosityProperties);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::laminarModels::generalizedNewtonianViscosityModels::Casson::read
(
	const dictionary& viscosityProperties
)
{
	generalizedNewtonianViscosityModel::read(viscosityProperties);

	const dictionary& coeffs =
		viscosityProperties.optionalSubDict(typeName + "Coeffs");

	coeffs.lookup("m") >> m_;
	coeffs.lookup("tau0") >> tau0_;
	coeffs.lookup("nuMin_") >> nuMin_;
	coeffs.lookup("nuMax_") >> nuMax_;

	return true;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarModels::generalizedNewtonianViscosityModels::Casson::
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
			sqr
			(
				sqrt
				(
					tau0_
					/ max
					(
						strainRate,
						dimensionedScalar(dimless / dimTime, vSmall)
					)
				) + sqrt(m_)
			)
		)
	);
}


// ************************************************************************* //