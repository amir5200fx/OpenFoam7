#include <cuboid.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		defineTypeNameAndDebug(cuboid, 0);

		addToRunTimeSelectionTable
		(
			rigidBody,
			cuboid,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::RBD::rigidBody> tnbLib::RBD::cuboid::clone() const
{
	return autoPtr<rigidBody>(new cuboid(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::cuboid::~cuboid()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::cuboid::write(Ostream& os) const
{
	writeEntry(os, "type", type());

	writeEntry(os, "mass", m());

	writeEntry(os, "L", L());
}


// ************************************************************************* //