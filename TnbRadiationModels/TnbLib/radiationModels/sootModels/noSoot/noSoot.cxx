#include <noSoot.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace sootModels
		{
			defineTypeNameAndDebug(noSoot, 0);

			addToRunTimeSelectionTable
			(
				sootModel,
				noSoot,
				dictionary
			);
		}
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::sootModels::noSoot::noSoot
(
	const dictionary& dict,
	const fvMesh& mesh,
	const word& modelType
)
	:
	sootModel(dict, mesh, modelType)
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::sootModels::noSoot::~noSoot()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::radiationModels::sootModels::noSoot::correct()
{}


const tnbLib::volScalarField&
tnbLib::radiationModels::sootModels::noSoot::soot() const
{
	NotImplemented;
	return tmp<volScalarField>(nullptr);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //