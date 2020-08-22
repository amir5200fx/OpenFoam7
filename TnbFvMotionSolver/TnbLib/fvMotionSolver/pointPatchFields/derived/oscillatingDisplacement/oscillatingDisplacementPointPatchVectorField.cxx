#include <oscillatingDisplacementPointPatchVectorField.hxx>

#include <pointPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <Time.hxx> 
#include <polyMesh.hxx>

#include <pointMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	oscillatingDisplacementPointPatchVectorField::
		oscillatingDisplacementPointPatchVectorField
		(
			const pointPatch& p,
			const DimensionedField<vector, pointMesh>& iF
		)
		:
		fixedValuePointPatchField<vector>(p, iF),
		amplitude_(Zero),
		omega_(0.0)
	{}


	oscillatingDisplacementPointPatchVectorField::
		oscillatingDisplacementPointPatchVectorField
		(
			const pointPatch& p,
			const DimensionedField<vector, pointMesh>& iF,
			const dictionary& dict
		)
		:
		fixedValuePointPatchField<vector>(p, iF, dict),
		amplitude_(dict.lookup("amplitude")),
		omega_(readScalar(dict.lookup("omega")))
	{
		if (!dict.found("value"))
		{
			updateCoeffs();
		}
	}


	oscillatingDisplacementPointPatchVectorField::
		oscillatingDisplacementPointPatchVectorField
		(
			const oscillatingDisplacementPointPatchVectorField& ptf,
			const pointPatch& p,
			const DimensionedField<vector, pointMesh>& iF,
			const pointPatchFieldMapper& mapper
		)
		:
		fixedValuePointPatchField<vector>(ptf, p, iF, mapper),
		amplitude_(ptf.amplitude_),
		omega_(ptf.omega_)
	{}


	oscillatingDisplacementPointPatchVectorField::
		oscillatingDisplacementPointPatchVectorField
		(
			const oscillatingDisplacementPointPatchVectorField& ptf,
			const DimensionedField<vector, pointMesh>& iF
		)
		:
		fixedValuePointPatchField<vector>(ptf, iF),
		amplitude_(ptf.amplitude_),
		omega_(ptf.omega_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void oscillatingDisplacementPointPatchVectorField::updateCoeffs()
	{
		if (this->updated())
		{
			return;
		}

		const polyMesh& mesh = this->internalField().mesh()();
		const Time& t = mesh.time();

		Field<vector>::operator=(amplitude_*sin(omega_*t.value()));

		fixedValuePointPatchField<vector>::updateCoeffs();
	}


	void oscillatingDisplacementPointPatchVectorField::write(Ostream& os) const
	{
		pointPatchField<vector>::write(os);
		writeEntry(os, "amplitude", amplitude_);
		writeEntry(os, "omega", omega_);
		writeEntry(os, "value", *this);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePointPatchTypeField
	(
		pointPatchVectorField,
		oscillatingDisplacementPointPatchVectorField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //