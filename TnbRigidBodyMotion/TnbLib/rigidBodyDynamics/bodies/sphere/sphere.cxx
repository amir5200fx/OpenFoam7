#include <sphere.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		defineTypeNameAndDebug(sphere, 0);

		addToRunTimeSelectionTable
		(
			rigidBody,
			sphere,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::RBD::rigidBody> tnbLib::RBD::sphere::clone() const
{
	return autoPtr<rigidBody>(new sphere(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::sphere::~sphere()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::sphere::write(Ostream& os) const
{
	writeEntry(os, "type", type());

	writeEntry(os, "mass", m());

	writeEntry(os, "radius", r());
}


// ************************************************************************* //