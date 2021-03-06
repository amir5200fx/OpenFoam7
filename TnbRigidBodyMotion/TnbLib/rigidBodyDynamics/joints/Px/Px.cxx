#include <Px.hxx>

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
			defineTypeNameAndDebug(Px, 0);

			addToRunTimeSelectionTable
			(
				joint,
				Px,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Px::Px(const rigidBodyModel& model)
	:
	joint(model, 1)
{
	S_[0] = spatialVector(0, 0, 0, 1, 0, 0);
}


tnbLib::RBD::joints::Px::Px(const rigidBodyModel& model, const dictionary& dict)
	:
	joint(model, 1)
{
	S_[0] = spatialVector(0, 0, 0, 1, 0, 0);
}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::Px::clone() const
{
	return autoPtr<joint>(new Px(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Px::~Px()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::Px::jcalc
(
	joint::XSvc& J,
	const rigidBodyModelState& state
) const
{
	J.X = Xt(S_[0].l()*state.q()[qIndex_]);
	J.S1 = S_[0];
	J.v = S_[0] * state.qDot()[qIndex_];
	J.c = Zero;
}


// ************************************************************************* //