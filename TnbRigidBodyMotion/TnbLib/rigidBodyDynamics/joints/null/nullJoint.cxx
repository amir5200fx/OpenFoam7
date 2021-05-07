#include <nullJoint.hxx>

#include <rigidBodyModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace joints
		{
			defineTypeNameAndDebug(null, 0);

			addToRunTimeSelectionTable
			(
				joint,
				null,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::null::null(const rigidBodyModel& model)
	:
	joint(model, 0)
{}


tnbLib::RBD::joints::null::null
(
	const rigidBodyModel& model,
	const dictionary& dict
)
	:
	joint(model, 0)
{}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::null::clone() const
{
	return autoPtr<joint>(new null(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::null::~null()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::null::jcalc
(
	joint::XSvc& J,
	const rigidBodyModelState& state
) const
{
	FatalErrorInFunction
		<< "Cannot calculate the state of a null-joint"
		<< abort(FatalError);
}


// ************************************************************************* //