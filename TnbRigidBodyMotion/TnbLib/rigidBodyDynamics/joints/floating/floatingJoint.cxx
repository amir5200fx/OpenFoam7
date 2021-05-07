#include <floatingJoint.hxx>

#include <rigidBodyModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Rs.hxx>
#include <Rzyx.hxx>
#include <Pxyz.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace joints
		{
			defineTypeNameAndDebug(floating, 0);

			addToRunTimeSelectionTable
			(
				joint,
				floating,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::RBD::joints::composite>
tnbLib::RBD::joints::floating::sixDoF(const rigidBodyModel& model)
{
	PtrList<joint> cj(2);
	cj.set(0, new joints::Pxyz(model));

	// The quaternion-based spherical joint could be used
	// but then w must be set appropriately
	// cj.set(1, new joints::Rs(model));

	// Alternatively the Euler-angle joint can be used
	cj.set(1, new joints::Rzyx(model));

	return autoPtr<composite>(new composite(cj));
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::floating::floating(const rigidBodyModel& model)
	:
	composite(sixDoF(model))
{}


tnbLib::RBD::joints::floating::floating
(
	const rigidBodyModel& model,
	const dictionary& dict
)
	:
	composite(sixDoF(model))
{}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::floating::clone() const
{
	return autoPtr<joint>(new floating(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::floating::~floating()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::floating::write(Ostream& os) const
{
	joint::write(os);
}


// ************************************************************************* //