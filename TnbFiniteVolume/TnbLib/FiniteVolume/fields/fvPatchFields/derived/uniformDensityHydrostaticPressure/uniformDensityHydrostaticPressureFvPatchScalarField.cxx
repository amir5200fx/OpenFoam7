#include <uniformDensityHydrostaticPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField::
uniformDensityHydrostaticPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	rho_(0.0),
	pRef_(0.0),
	pRefPointSpecified_(false),
	pRefPoint_(Zero)
{}


tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField::
uniformDensityHydrostaticPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF, dict, false),
	rho_(readScalar(dict.lookup("rhoRef"))),
	pRef_(readScalar(dict.lookup("pRef"))),
	pRefPointSpecified_(dict.found("pRefPoint")),
	pRefPoint_(dict.lookupOrDefault<vector>("pRefPoint", Zero))
{
	if (dict.found("value"))
	{
		fvPatchScalarField::operator=
			(
				scalarField("value", dict, p.size())
				);
	}
	else
	{
		fvPatchField<scalar>::operator=(pRef_);
	}
}


tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField::
uniformDensityHydrostaticPressureFvPatchScalarField
(
	const uniformDensityHydrostaticPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	rho_(ptf.rho_),
	pRef_(ptf.pRef_),
	pRefPointSpecified_(ptf.pRefPointSpecified_),
	pRefPoint_(ptf.pRefPoint_)
{}


tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField::
uniformDensityHydrostaticPressureFvPatchScalarField
(
	const uniformDensityHydrostaticPressureFvPatchScalarField& ptf
)
	:
	fixedValueFvPatchScalarField(ptf),
	rho_(ptf.rho_),
	pRef_(ptf.pRef_),
	pRefPointSpecified_(ptf.pRefPointSpecified_),
	pRefPoint_(ptf.pRefPoint_)
{}


tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField::
uniformDensityHydrostaticPressureFvPatchScalarField
(
	const uniformDensityHydrostaticPressureFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(ptf, iF),
	rho_(ptf.rho_),
	pRef_(ptf.pRef_),
	pRefPointSpecified_(ptf.pRefPointSpecified_),
	pRefPoint_(ptf.pRefPoint_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const uniformDimensionedVectorField& g =
		db().lookupObject<uniformDimensionedVectorField>("g");

	scalar ghRef = g.value() & pRefPoint_;

	if (!pRefPointSpecified_)
	{
		const uniformDimensionedScalarField& hRef =
			db().lookupObject<uniformDimensionedScalarField>("hRef");

		ghRef = -mag(g.value())*hRef.value();
	}

	operator==
		(
			pRef_
			+ rho_ * ((g.value() & patch().Cf()) - ghRef)
			);

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField::write
(
	Ostream& os
) const
{
	fvPatchScalarField::write(os);
	writeEntry(os, "rhoRef", rho_);
	writeEntry(os, "pRef", pRef_);
	if (pRefPointSpecified_)
	{
		writeEntry(os, "pRefPoint", pRefPoint_);
	}
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		uniformDensityHydrostaticPressureFvPatchScalarField
	);
}

// ************************************************************************* //