#include <Pz.hxx>

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
			defineTypeNameAndDebug(Pz, 0);

			addToRunTimeSelectionTable
			(
				joint,
				Pz,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Pz::Pz(const rigidBodyModel& model)
	:
	joint(model, 1)
{
	S_[0] = spatialVector(0, 0, 0, 0, 0, 1);
}


tnbLib::RBD::joints::Pz::Pz(const rigidBodyModel& model, const dictionary& dict)
	:
	joint(model, 1)
{
	S_[0] = spatialVector(0, 0, 0, 0, 0, 1);
}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::Pz::clone() const
{
	return autoPtr<joint>(new Pz(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Pz::~Pz()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::Pz::jcalc
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