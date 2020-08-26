#include <equilibrium.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace TimeScaleModels
	{
		defineTypeNameAndDebug(equilibrium, 0);

		addToRunTimeSelectionTable
		(
			TimeScaleModel,
			equilibrium,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::TimeScaleModels::equilibrium::equilibrium
(
	const dictionary& dict
)
	:
	TimeScaleModel(dict)
{}


tnbLib::TimeScaleModels::equilibrium::equilibrium
(
	const equilibrium& hc
)
	:
	TimeScaleModel(hc)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::TimeScaleModels::equilibrium::~equilibrium()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::FieldField<tnbLib::Field, tnbLib::scalar>>
tnbLib::TimeScaleModels::equilibrium::oneByTau
(
	const FieldField<Field, scalar>& alpha,
	const FieldField<Field, scalar>& r32,
	const FieldField<Field, scalar>& uSqr,
	const FieldField<Field, scalar>& f
) const
{
	static const scalar a =
		16.0 / sqrt(3.0*constant::mathematical::pi)
		*0.25*(1.0 - e_ * e_);

	return
		a
		* alpha*sqrt(max(uSqr, scalar(0))) / max(r32, small)
		*alphaPacked_ / max(alphaPacked_ - alpha, small);
}


// ************************************************************************* //