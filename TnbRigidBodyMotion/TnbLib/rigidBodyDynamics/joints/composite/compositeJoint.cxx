#include <compositeJoint.hxx>

#include <rigidBodyModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace joints
		{
			defineTypeNameAndDebug(composite, 0);

			addToRunTimeSelectionTable
			(
				joint,
				composite,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void tnbLib::RBD::joints::composite::setLastJoint()
{
	last().joint::operator=(*this);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::composite::composite(const PtrList<joint>& joints)
	:
	PtrList<joint>(joints),
	joint(last())
{}


tnbLib::RBD::joints::composite::composite
(
	const rigidBodyModel& model,
	const dictionary& dict
)
	:
	PtrList<joint>(dict.lookup("joints"), joint::iNew(model)),
	joint(last())
{}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::composite::clone() const
{
	return autoPtr<joint>(new composite(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::composite::~composite()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::composite::jcalc
(
	joint::XSvc& J,
	const rigidBodyModelState& state
) const
{
	last().jcalc(J, state);
}


void tnbLib::RBD::joints::composite::write(Ostream& os) const
{
	joint::write(os);
	os.writeKeyword("joints");
	os << static_cast<const PtrList<joint>&>(*this);
}


// ************************************************************************* //