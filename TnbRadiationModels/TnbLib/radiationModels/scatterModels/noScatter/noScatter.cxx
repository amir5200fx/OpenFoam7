#include <noScatter.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace scatterModels
		{
			defineTypeNameAndDebug(noScatter, 0);
			addToRunTimeSelectionTable(scatterModel, noScatter, dictionary);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::scatterModels::noScatter::noScatter
(
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	scatterModel(dict, mesh)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::scatterModels::noScatter::~noScatter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::scatterModels::noScatter::sigmaEff() const
{
	return volScalarField::New
	(
		"sigma",
		mesh_,
		dimensionedScalar(dimless / dimLength, 0)
	);
}


// ************************************************************************* //