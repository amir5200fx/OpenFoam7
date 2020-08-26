#include <isotropic.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace TimeScaleModels
	{
		defineTypeNameAndDebug(isotropic, 0);

		addToRunTimeSelectionTable
		(
			TimeScaleModel,
			isotropic,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::TimeScaleModels::isotropic::isotropic
(
	const dictionary& dict
)
	:
	TimeScaleModel(dict)
{}


tnbLib::TimeScaleModels::isotropic::isotropic
(
	const isotropic& hc
)
	:
	TimeScaleModel(hc)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::TimeScaleModels::isotropic::~isotropic()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::FieldField<tnbLib::Field, tnbLib::scalar>>
tnbLib::TimeScaleModels::isotropic::oneByTau
(
	const FieldField<Field, scalar>& alpha,
	const FieldField<Field, scalar>& r32,
	const FieldField<Field, scalar>& uSqr,
	const FieldField<Field, scalar>& f
) const
{
	static const scalar a =
		8.0*sqrt(2.0) / (5.0*constant::mathematical::pi)
		*0.25*(3.0 - e_)*(1.0 + e_);

	return a * f*alphaPacked_ / max(alphaPacked_ - alpha, small);
}


// ************************************************************************* //