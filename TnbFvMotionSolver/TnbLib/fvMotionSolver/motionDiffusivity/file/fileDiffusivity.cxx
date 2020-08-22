#include <fileDiffusivity.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(fileDiffusivity, 0);

	addToRunTimeSelectionTable
	(
		motionDiffusivity,
		fileDiffusivity,
		Istream
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fileDiffusivity::fileDiffusivity
(
	const fvMesh& mesh,
	Istream& mdData
)
	:
	motionDiffusivity(mesh),
	faceDiffusivity_
	(
		tnbLib::IOobject
		(
			word(mdData),
			mesh.time().constant(),
			mesh,
			tnbLib::IOobject::MUST_READ,
			tnbLib::IOobject::NO_WRITE
		),
		mesh
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fileDiffusivity::~fileDiffusivity()
{}


// ************************************************************************* //