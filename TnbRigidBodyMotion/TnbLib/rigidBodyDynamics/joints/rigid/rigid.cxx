#include <rigid.hxx>

#include <rigidBodyModelState.hxx>
#include <rigidBodyModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace joints
		{
			defineTypeNameAndDebug(rigid, 0);

			addToRunTimeSelectionTable
			(
				joint,
				rigid,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::rigid::rigid(const rigidBodyModel& model)
	:
	joint(model, 0)
{}


tnbLib::RBD::joints::rigid::rigid
(
	const rigidBodyModel& model,
	const dictionary& dict
)
	:
	joint(model, 0)
{}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::rigid::clone() const
{
	return autoPtr<joint>(new rigid(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::rigid::~rigid()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::rigid::jcalc
(
	joint::XSvc& J,
	const rigidBodyModelState& state
) const
{
	J.X = spatialTransform();
	J.S = Zero;
	J.S1 = Zero;
	J.v = Zero;
	J.c = Zero;
}


// ************************************************************************* //