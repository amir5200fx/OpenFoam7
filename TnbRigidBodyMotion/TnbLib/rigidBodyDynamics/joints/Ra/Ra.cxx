#include <Ra.hxx>

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
			defineTypeNameAndDebug(Ra, 0);

			addToRunTimeSelectionTable
			(
				joint,
				Ra,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Ra::Ra(const rigidBodyModel& model, const vector& axis)
	:
	joint(model, 1)
{
	S_[0] = spatialVector(axis / mag(axis), Zero);
}


tnbLib::RBD::joints::Ra::Ra(const rigidBodyModel& model, const dictionary& dict)
	:
	joint(model, 1)
{
	vector axis(dict.lookup("axis"));
	S_[0] = spatialVector(axis / mag(axis), Zero);
}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::Ra::clone() const
{
	return autoPtr<joint>(new Ra(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Ra::~Ra()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::Ra::jcalc
(
	joint::XSvc& J,
	const rigidBodyModelState& state
) const
{
	J.X = Xr(S_[0].w(), state.q()[qIndex_]);
	J.S1 = S_[0];
	J.v = S_[0] * state.qDot()[qIndex_];
	J.c = Zero;
}


void tnbLib::RBD::joints::Ra::write(Ostream& os) const
{
	joint::write(os);
	writeEntry(os, "axis", S_[0].w());
}


// ************************************************************************* //