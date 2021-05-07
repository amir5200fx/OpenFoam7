#include <rigidBodyModelState.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::rigidBodyModelState::rigidBodyModelState
(
	const rigidBodyModel& model
)
	:
	q_(model.nDoF(), Zero),
	qDot_(model.nDoF(), Zero),
	qDdot_(model.nDoF(), Zero),
	t_(-1),
	deltaT_(0)
{}


tnbLib::RBD::rigidBodyModelState::rigidBodyModelState
(
	const rigidBodyModel& model,
	const dictionary& dict
)
	:
	q_(dict.lookupOrDefault("q", scalarField(model.nDoF(), Zero))),
	qDot_(dict.lookupOrDefault("qDot", scalarField(model.nDoF(), Zero))),
	qDdot_(dict.lookupOrDefault("qDdot", scalarField(model.nDoF(), Zero))),
	t_(dict.lookupOrDefault<scalar>("t", -1)),
	deltaT_(dict.lookupOrDefault<scalar>("deltaT", 0))
{}


// ************************************************************************* //