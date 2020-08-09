#include <surfaceTensionModel.hxx>

#include <fvMesh.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(surfaceTensionModel, 0);
	defineRunTimeSelectionTable(surfaceTensionModel, dictionary);
}

const tnbLib::dimensionSet tnbLib::surfaceTensionModel::dimSigma(1, 0, -2, 0, 0);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfaceTensionModel::surfaceTensionModel(const fvMesh& mesh)
	:
	regIOobject
	(
		tnbLib::IOobject
		(
			typeName, mesh.name(),
			mesh.time().timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		)
	),
	mesh_(mesh)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfaceTensionModel::~surfaceTensionModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::surfaceTensionModel::writeData(Ostream& os) const
{
	return os.good();
}


// ************************************************************************* //