#include <jointBody.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		defineTypeNameAndDebug(jointBody, 0);

		addToRunTimeSelectionTable
		(
			rigidBody,
			jointBody,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::RBD::rigidBody> tnbLib::RBD::jointBody::clone() const
{
	return autoPtr<rigidBody>(new jointBody(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::jointBody::~jointBody()
{}


// ************************************************************************* //