#include <singleRegionSolutionControl.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(singleRegionSolutionControl, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::singleRegionSolutionControl::singleRegionSolutionControl
(
	fvMesh& mesh,
	const word& algorithmName
)
	:
	solutionControl(mesh, mesh.time(), algorithmName),
	mesh_(mesh)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::singleRegionSolutionControl::~singleRegionSolutionControl()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

const tnbLib::dictionary& tnbLib::singleRegionSolutionControl::dict() const
{
	return mesh_.solutionDict().subDict(algorithmName());
}


bool tnbLib::singleRegionSolutionControl::isFinal() const
{
	return false;
}


void tnbLib::singleRegionSolutionControl::updateFinal() const
{
	mesh_.data::remove("finalIteration");

	if (isFinal())
	{
		mesh_.data::add("finalIteration", true);
	}
}


void tnbLib::singleRegionSolutionControl::storePrevIterFields()
{
	storePrevIterTypeFields<scalar>();
	storePrevIterTypeFields<vector>();
	storePrevIterTypeFields<sphericalTensor>();
	storePrevIterTypeFields<symmTensor>();
	storePrevIterTypeFields<tensor>();
}


// ************************************************************************* //