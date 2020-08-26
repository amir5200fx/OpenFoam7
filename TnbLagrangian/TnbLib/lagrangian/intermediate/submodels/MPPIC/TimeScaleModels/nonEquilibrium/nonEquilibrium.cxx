#include <nonEquilibrium.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace TimeScaleModels
	{
		defineTypeNameAndDebug(nonEquilibrium, 0);

		addToRunTimeSelectionTable
		(
			TimeScaleModel,
			nonEquilibrium,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::TimeScaleModels::nonEquilibrium::nonEquilibrium
(
	const dictionary& dict
)
	:
	TimeScaleModel(dict)
{}


tnbLib::TimeScaleModels::nonEquilibrium::nonEquilibrium
(
	const nonEquilibrium& hc
)
	:
	TimeScaleModel(hc)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::TimeScaleModels::nonEquilibrium::~nonEquilibrium()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::FieldField<tnbLib::Field, tnbLib::scalar>>
tnbLib::TimeScaleModels::nonEquilibrium::oneByTau
(
	const FieldField<Field, scalar>& alpha,
	const FieldField<Field, scalar>& r32,
	const FieldField<Field, scalar>& uSqr,
	const FieldField<Field, scalar>& f
) const
{
	static const scalar a =
		8.0*sqrt(2.0) / (3.0*constant::mathematical::pi)
		*0.25*(1.0 - e_ * e_);

	return a * f*alphaPacked_ / max(alphaPacked_ - alpha, small);
}


// ************************************************************************* //