#include <Ryxz.hxx>

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
			defineTypeNameAndDebug(Ryxz, 0);

			addToRunTimeSelectionTable
			(
				joint,
				Ryxz,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Ryxz::Ryxz(const rigidBodyModel& model)
	:
	joint(model, 3)
{
	S_[0] = spatialVector(0, 1, 0, 0, 0, 0);
	S_[1] = spatialVector(1, 0, 0, 0, 0, 0);
	S_[2] = spatialVector(0, 0, 1, 0, 0, 0);
}


tnbLib::RBD::joints::Ryxz::Ryxz
(
	const rigidBodyModel& model,
	const dictionary& dict
)
	:
	joint(model, 3)
{
	S_[0] = spatialVector(0, 1, 0, 0, 0, 0);
	S_[1] = spatialVector(1, 0, 0, 0, 0, 0);
	S_[2] = spatialVector(0, 0, 1, 0, 0, 0);
}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::Ryxz::clone() const
{
	return autoPtr<joint>(new Ryxz(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::Ryxz::~Ryxz()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::Ryxz::jcalc
(
	joint::XSvc& J,
	const rigidBodyModelState& state
) const
{
	vector qj(state.q().block<vector>(qIndex_));

	scalar s0 = sin(qj.x());
	scalar c0 = cos(qj.x());
	scalar s1 = sin(qj.y());
	scalar c1 = cos(qj.y());
	scalar s2 = sin(qj.z());
	scalar c2 = cos(qj.z());

	J.X.E() = tensor
	(
		c2*c0 + s2 * s1*s0, s2*c1, -c2 * s0 + s2 * s1*c0,
		-s2 * c0 + c2 * s1*s0, c2*c1, s2*s0 + c2 * s1*c0,
		c1*s0, -s1, c1*c0
	);
	J.X.r() = Zero;

	J.S = Zero;
	J.S.xx() = s2 * c1;
	J.S.xy() = c2;
	J.S.yx() = c2 * c1;
	J.S.yy() = -s2;
	J.S.zx() = -s1;
	J.S.zz() = 1;

	vector qDotj(state.qDot().block<vector>(qIndex_));
	J.v = J.S & qDotj;

	J.c = spatialVector
	(
		c2*c1*qDotj.z()*qDotj.x()
		- s2 * s1*qDotj.y()*qDotj.x()
		- s2 * qDotj.z()*qDotj.y(),

		-s2 * c1*qDotj.z()*qDotj.x()
		- c2 * s1*qDotj.y()*qDotj.x()
		- c2 * qDotj.z()*qDotj.y(),

		-c1 * qDotj.y()*qDotj.x(),

		0,
		0,
		0
	);
}


// ************************************************************************* //