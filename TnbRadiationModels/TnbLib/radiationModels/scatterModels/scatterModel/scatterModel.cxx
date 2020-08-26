#include <scatterModel.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		defineTypeNameAndDebug(scatterModel, 0);
		defineRunTimeSelectionTable(scatterModel, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::scatterModel::scatterModel
(
	const dictionary&,
	const fvMesh& mesh
)
	:
	mesh_(mesh)
{}


// * * * * * * * * * * * * * * * * Destructor    * * * * * * * * * * * * * * //

tnbLib::radiationModels::scatterModel::~scatterModel()
{}


// ************************************************************************* //