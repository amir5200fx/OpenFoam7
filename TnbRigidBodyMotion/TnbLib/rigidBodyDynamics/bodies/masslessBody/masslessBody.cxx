#include <masslessBody.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		defineTypeNameAndDebug(masslessBody, 0);

		addToRunTimeSelectionTable
		(
			rigidBody,
			masslessBody,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::RBD::rigidBody> tnbLib::RBD::masslessBody::clone() const
{
	return autoPtr<rigidBody>(new masslessBody(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::masslessBody::~masslessBody()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::RBD::masslessBody::massless() const
{
	return true;
}


void tnbLib::RBD::masslessBody::write(Ostream& os) const
{
	writeEntry(os, "type", type());
}


// ************************************************************************* //