#include <sootModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		defineTypeNameAndDebug(sootModel, 0);
		defineRunTimeSelectionTable(sootModel, dictionary);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::sootModel::sootModel
(
	const dictionary& dict,
	const fvMesh& mesh,
	const word& modelType
)
	:
	dict_(dict),
	mesh_(mesh)
{}


// * * * * * * * * * * * * * * * * Destructor    * * * * * * * * * * * * * * //

tnbLib::radiationModels::sootModel::~sootModel()
{}


// ************************************************************************* //