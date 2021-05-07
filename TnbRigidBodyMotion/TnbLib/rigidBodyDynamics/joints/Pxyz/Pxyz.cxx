#include <Pxyz.hxx>

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
			defineTypeNameAndDebug(Pxyz, 0);

			addToRunTimeSelectionTable
			(
				joint,
				Pxyz,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Pxyz::Pxyz(const rigidBodyModel& model)
	:
	joint(model, 3)
{
	S_[0] = spatialVector(0, 0, 0, 1, 0, 0);
	S_[1] = spatialVector(0, 0, 0, 0, 1, 0);
	S_[2] = spatialVector(0, 0, 0, 0, 0, 1);
}


tnbLib::RBD::joints::Pxyz::Pxyz
(
	const rigidBodyModel& model,
	const dictionary& dict
)
	:
	joint(model, 3)
{
	S_[0] = spatialVector(0, 0, 0, 1, 0, 0);
	S_[1] = spatialVector(0, 0, 0, 0, 1, 0);
	S_[2] = spatialVector(0, 0, 0, 0, 0, 1);
}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::Pxyz::clone() const
{
	return autoPtr<joint>(new Pxyz(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Pxyz::~Pxyz()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::Pxyz::jcalc
(
	joint::XSvc& J,
	const rigidBodyModelState& state
) const
{
	J.X.E() = tensor::I;
	J.X.r() = state.q().block<vector>(qIndex_);

	J.S = Zero;
	J.S(3, 0) = 1;
	J.S(4, 1) = 1;
	J.S(5, 2) = 1;

	J.v = spatialVector(Zero, state.qDot().block<vector>(qIndex_));
	J.c = Zero;
}


// ************************************************************************* //