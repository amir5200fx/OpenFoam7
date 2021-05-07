#include <function.hxx>

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
			defineTypeNameAndDebug(function, 0);

			addToRunTimeSelectionTable
			(
				joint,
				function,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::joints::function::function
(
	const rigidBodyModel& model,
	const dictionary& dict
)
	:
	joint(model, 0),
	f_(Function1<scalar>::New("function", dict)),
	delta_(dict.lookupOrDefault<scalar>("delta", rootSmall))
{}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joints::function::clone() const
{
	return autoPtr<joint>(new function(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joints::function::~function()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joints::function::jcalc
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
		const scalar q = state.q()[parent.qIndex() + i];
		const scalar qDot = state.qDot()[parent.qIndex() + i];
		const scalar qDdot = state.qDdot()[parent.qIndex() + i];

		const scalar f = f_->value(q);
		const scalar fMinusDf = f_->value(q - delta_ / 2);
		const scalar fPlusDf = f_->value(q + delta_ / 2);
		const scalar dfdq = (fPlusDf - fMinusDf) / delta_;
		const scalar d2fdq2 = (fPlusDf - 2 * f + fMinusDf) / sqr(delta_);

		const spatialVector& s = parent.S()[i];

		x += f * s;
		v += dfdq * qDot*s;
		c += (dfdq*qDdot + d2fdq2 * sqr(qDot))*s;
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