#include <Rx.hxx>

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
			defineTypeNameAndDebug(Rx, 0);

			addToRunTimeSelectionTable
			(
				joint,
				Rx,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Rx::Rx(const rigidBodyModel& model)
	:
	joint(model, 1)
{
	S_[0] = spatialVector(1, 0, 0, 0, 0, 0);
}


tnbLib::RBD::joints::Rx::Rx(const rigidBodyModel& model, const dictionary& dict)
	:
	joint(model, 1)
{
	S_[0] = spatialVector(1, 0, 0, 0, 0, 0);
}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::Rx::clone() const
{
	return autoPtr<joint>(new Rx(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Rx::~Rx()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::Rx::jcalc
(
	joint::XSvc& J,
	const rigidBodyModelState& state
) const
{
	J.X = Xrx(state.q()[qIndex_]);
	J.S1 = S_[0];
	J.v = Zero;
	J.v.wx() = state.qDot()[qIndex_];
	J.c = Zero;
}


// ************************************************************************* //