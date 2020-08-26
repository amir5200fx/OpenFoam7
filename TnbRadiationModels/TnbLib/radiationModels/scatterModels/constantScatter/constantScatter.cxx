#include <constantScatter.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace scatterModels
		{
			defineTypeNameAndDebug(constant, 0);

			addToRunTimeSelectionTable
			(
				scatterModel,
				constant,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::scatterModels::constant::constant
(
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	scatterModel(dict, mesh),
	coeffsDict_(dict.optionalSubDict(typeName + "Coeffs")),
	sigma_("sigma", dimless / dimLength, coeffsDict_),
	C_("C", dimless, coeffsDict_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::scatterModels::constant::~constant()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::scatterModels::constant::sigmaEff() const
{
	return volScalarField::New
	(
		"sigma",
		mesh_,
		sigma_*(3.0 - C_)
	);
}


// ************************************************************************* //