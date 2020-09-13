#include <cellMotionFvPatchField.hxx>

#include <fvMesh.hxx>
#include <volMesh.hxx>
#include <pointFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::cellMotionFvPatchField<Type>::cellMotionFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::cellMotionFvPatchField<Type>::cellMotionFvPatchField
(
	const cellMotionFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<Type>(ptf, p, iF, mapper)
{}


template<class Type>
tnbLib::cellMotionFvPatchField<Type>::cellMotionFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<Type>(p, iF, dict)
{}


template<class Type>
tnbLib::cellMotionFvPatchField<Type>::cellMotionFvPatchField
(
	const cellMotionFvPatchField<Type>& ptf
)
	:
	fixedValueFvPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::cellMotionFvPatchField<Type>::cellMotionFvPatchField
(
	const cellMotionFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::cellMotionFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	const fvPatch& p = this->patch();
	const polyPatch& pp = p.patch();
	const fvMesh& mesh = this->internalField().mesh();
	const pointField& points = mesh.points();

	word pfName = this->internalField().name();
	pfName.replace("cell", "point");

	const GeometricField<Type, pointPatchField, pointMesh>& pointMotion =
		this->db().objectRegistry::template
		lookupObject<GeometricField<Type, pointPatchField, pointMesh>>
		(pfName);

	forAll(p, i)
	{
		this->operator[](i) = pp[i].average(points, pointMotion);
	}

	fixedValueFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::cellMotionFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	writeEntry(os, "value", *this);
}

// ************************************************************************* //