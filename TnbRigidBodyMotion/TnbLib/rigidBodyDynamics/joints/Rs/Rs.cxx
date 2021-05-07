#include <Rs.hxx>

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
			defineTypeNameAndDebug(Rs, 0);

			addToRunTimeSelectionTable
			(
				joint,
				Rs,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Rs::Rs(const rigidBodyModel& model)
	:
	joint(model, 3)
{
	S_[0] = spatialVector(1, 0, 0, 0, 0, 0);
	S_[1] = spatialVector(0, 1, 0, 0, 0, 0);
	S_[2] = spatialVector(0, 0, 1, 0, 0, 0);
}


tnbLib::RBD::joints::Rs::Rs(const rigidBodyModel& model, const dictionary& dict)
	:
	joint(model, 3)
{
	S_[0] = spatialVector(1, 0, 0, 0, 0, 0);
	S_[1] = spatialVector(0, 1, 0, 0, 0, 0);
	S_[2] = spatialVector(0, 0, 1, 0, 0, 0);
}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::Rs::clone() const
{
	return autoPtr<joint>(new Rs(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Rs::~Rs()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::RBD::joints::Rs::unitQuaternion() const
{
	return true;
}


void tnbLib::RBD::joints::Rs::jcalc
(
	joint::XSvc& J,
	const rigidBodyModelState& state
) const
{
	J.X.E() = joint::unitQuaternion(state.q()).R().T();
	J.X.r() = Zero;

	J.S = Zero;
	J.S.xx() = 1;
	J.S.yy() = 1;
	J.S.zz() = 1;

	J.v = spatialVector(state.qDot().block<vector>(qIndex_), Zero);
	J.c = Zero;
}


// ************************************************************************* //