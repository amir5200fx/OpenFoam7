#include <functionDot.hxx>

#include <rigidBodyModelState.hxx>  // added by amir
#include <rigidBodyModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace joints
		{
			defineTypeNameAndDebug(functionDot, 0);

			addToRunTimeSelectionTable
			(
				joint,
				functionDot,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::functionDot::functionDot
(
	const rigidBodyModel& model,
	const dictionary& dict
)
	:
	joint(model, 0),
	f_(Function1<scalar>::New("function", dict)),
	delta_(dict.lookupOrDefault<scalar>("delta", rootSmall))
{}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::functionDot::clone() const
{
	return autoPtr<joint>(new functionDot(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::functionDot::~functionDot()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::functionDot::jcalc
(
	joint::XSvc& J,
	const rigidBodyModelState& state
) const
{
	const label lambda = model_.lambda()[index_];
	const joint& parent = model_.joints()[lambda];

	spatialVector x(Zero), v(Zero), c(Zero);
	for (label i = 0; i < model_.joints()[lambda].nDoF(); ++i)
	{
		const scalar qDot = state.qDot()[parent.qIndex() + i];
		const scalar qDdot = state.qDdot()[parent.qIndex() + i];
		const scalar qDddot = 0; // the third derivative is not stored

		const scalar f = f_->value(qDot);
		const scalar fMinusDf = f_->value(qDot - delta_ / 2);
		const scalar fPlusDf = f_->value(qDot + delta_ / 2);
		const scalar dfdqDot = (fPlusDf - fMinusDf) / delta_;
		const scalar d2fdqDot2 = (fPlusDf - 2 * f + fMinusDf) / sqr(delta_);

		const spatialVector& s = parent.S()[i];

		x += f * s;
		v += dfdqDot * qDdot*s;
		c += (dfdqDot*qDddot + d2fdqDot2 * sqr(qDdot))*s;
	}

	const scalar magW = mag(x.w());

	const tensor X(magW > vSmall ? quaternion(x.w(), magW).R() : tensor::I);

	J.X = spatialTransform(X, x.l());
	J.S = Zero;
	J.S1 = Zero;
	J.v = v;
	J.c = c;
}


// ************************************************************************* //