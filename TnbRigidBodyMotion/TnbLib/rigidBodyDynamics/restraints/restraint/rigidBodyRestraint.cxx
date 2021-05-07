#include <rigidBodyRestraint.hxx>

#include <rigidBodyModel.hxx>



// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		defineTypeNameAndDebug(restraint, 0);
		defineRunTimeSelectionTable(restraint, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::restraint::restraint
(
	const word& name,
	const dictionary& dict,
	const rigidBodyModel& model
)
	:
	name_(name),
	bodyID_(model.bodyID(dict.lookup("body"))),
	bodyIndex_(model.master(bodyID_)),
	coeffs_(dict),
	model_(model)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::restraint::~restraint()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

const tnbLib::dictionary& tnbLib::RBD::restraint::coeffDict() const
{
	return coeffs_;
}


bool tnbLib::RBD::restraint::read(const dictionary& dict)
{
	coeffs_ = dict;
	return true;
}


void tnbLib::RBD::restraint::write(Ostream& os) const
{
	writeEntry(os, "type", type());
	writeEntry(os, "body", model_.name(bodyID_));
}


// ************************************************************************* //