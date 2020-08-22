#include <polyMeshModifier.hxx>

#include <dictionary.hxx>
#include <polyTopoChanger.hxx>
#include <polyMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(polyMeshModifier, 0);

	defineRunTimeSelectionTable(polyMeshModifier, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
tnbLib::polyMeshModifier::polyMeshModifier
(
	const word& name,
	const label index,
	const polyTopoChanger& mme,
	const bool act
)
	:
	name_(name),
	index_(index),
	topoChanger_(mme),
	active_(act)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::polyMeshModifier::~polyMeshModifier()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::polyTopoChanger& tnbLib::polyMeshModifier::topoChanger() const
{
	return topoChanger_;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const polyMeshModifier& pmm)
{
	pmm.write(os);
	os.check("Ostream& operator<<(Ostream& f, const polyMeshModifier& pmm)");
	return os;
}


// ************************************************************************* //