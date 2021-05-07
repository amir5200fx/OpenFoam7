#include <Rz.hxx>

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
			defineTypeNameAndDebug(Rz, 0);

			addToRunTimeSelectionTable
			(
				joint,
				Rz,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Rz::Rz(const rigidBodyModel& model)
	:
	joint(model, 1)
{
	S_[0] = spatialVector(0, 0, 1, 0, 0, 0);
}


tnbLib::RBD::joints::Rz::Rz(const rigidBodyModel& model, const dictionary& dict)
	:
	joint(model, 1)
{
	S_[0] = spatialVector(0, 0, 1, 0, 0, 0);
}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::Rz::clone() const
{
	return autoPtr<joint>(new Rz(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Rz::~Rz()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::Rz::jcalc
(
	joint::XSvc& J,
	const rigidBodyModelState& state
) const
{
	J.X = Xrz(state.q()[qIndex_]);
	J.S1 = S_[0];
	J.v = Zero;
	J.v.wz() = state.qDot()[qIndex_];
	J.c = Zero;
}


// ************************************************************************* //