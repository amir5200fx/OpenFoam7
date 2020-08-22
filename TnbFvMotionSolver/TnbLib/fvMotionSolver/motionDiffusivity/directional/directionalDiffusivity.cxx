#include <directionalDiffusivity.hxx>

#include <surfaceFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(directionalDiffusivity, 0);

	addToRunTimeSelectionTable
	(
		motionDiffusivity,
		directionalDiffusivity,
		Istream
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::directionalDiffusivity::directionalDiffusivity
(
	const fvMesh& mesh,
	Istream& mdData
)
	:
	motionDiffusivity(mesh),
	diffusivityVector_(mdData)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::directionalDiffusivity::~directionalDiffusivity()
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::directionalDiffusivity::operator()() const
{
	const surfaceVectorField n(mesh().Sf() / mesh().magSf());

	return surfaceScalarField::New
	(
		"faceDiffusivity",
		n & cmptMultiply(diffusivityVector_, n)
	);
}


// ************************************************************************* //