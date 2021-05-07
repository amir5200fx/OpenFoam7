#include <Ry.hxx>

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
			defineTypeNameAndDebug(Ry, 0);

			addToRunTimeSelectionTable
			(
				joint,
				Ry,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Ry::Ry(const rigidBodyModel& model)
	:
	joint(model, 1)
{
	S_[0] = spatialVector(0, 1, 0, 0, 0, 0);
}


tnbLib::RBD::joints::Ry::Ry(const rigidBodyModel& model, const dictionary& dict)
	:
	joint(model, 1)
{
	S_[0] = spatialVector(0, 1, 0, 0, 0, 0);
}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::Ry::clone() const
{
	return autoPtr<joint>(new Ry(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Ry::~Ry()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::Ry::jcalc
(
	joint::XSvc& J,
	const rigidBodyModelState& state
) const
{
	J.X = Xry(state.q()[qIndex_]);
	J.S1 = S_[0];
	J.v = Zero;
	J.v.wy() = state.qDot()[qIndex_];
	J.c = Zero;
}


// ************************************************************************* //