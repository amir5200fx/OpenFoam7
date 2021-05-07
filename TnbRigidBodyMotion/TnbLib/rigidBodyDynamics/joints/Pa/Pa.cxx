#include <Pa.hxx>

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
			defineTypeNameAndDebug(Pa, 0);

			addToRunTimeSelectionTable
			(
				joint,
				Pa,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Pa::Pa(const rigidBodyModel& model, const vector& axis)
	:
	joint(model, 1)
{
	S_[0] = spatialVector(Zero, axis / mag(axis));
}


tnbLib::RBD::joints::Pa::Pa(const rigidBodyModel& model, const dictionary& dict)
	:
	joint(model, 1)
{
	vector axis(dict.lookup("axis"));
	S_[0] = spatialVector(Zero, axis / mag(axis));
}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::Pa::clone() const
{
	return autoPtr<joint>(new Pa(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Pa::~Pa()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::Pa::jcalc
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


void tnbLib::RBD::joints::Pa::write(Ostream& os) const
{
	joint::write(os);
	writeEntry(os, "axis", S_[0].l());
}


// ************************************************************************* //