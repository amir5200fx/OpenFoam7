#include <generalizedNewtonianViscosityModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{
		defineTypeNameAndDebug(generalizedNewtonianViscosityModel, 0);
		defineRunTimeSelectionTable(generalizedNewtonianViscosityModel, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::laminarModels::generalizedNewtonianViscosityModel::
generalizedNewtonianViscosityModel
(
	const dictionary& viscosityProperties
)
	:
	viscosityProperties_(viscosityProperties)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::laminarModels::generalizedNewtonianViscosityModel::read
(
	const dictionary& viscosityProperties
)
{
	viscosityProperties_ = viscosityProperties;

	return true;
}


// ************************************************************************* //