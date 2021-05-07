#include <compositeBody.hxx>

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::compositeBody::~compositeBody()
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::RBD::rigidBody> tnbLib::RBD::compositeBody::clone() const
{
	return autoPtr<rigidBody>(new compositeBody(*this));
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

const tnbLib::word& tnbLib::RBD::compositeBody::type() const
{
	return body_->type();
}


void tnbLib::RBD::compositeBody::write(Ostream& os) const
{
	body_->write(os);
}


// ************************************************************************* //