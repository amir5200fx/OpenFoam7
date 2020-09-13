#include <Basic.hxx>

#include <zeroGradientFvPatchField.hxx>
#include <fvMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::AveragingMethods::Basic<Type>::Basic
(
	const IOobject& io,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	AveragingMethod<Type>(io, dict, mesh, labelList(1, mesh.nCells())),
	data_(FieldField<Field, Type>::operator[](0)),
	dataGrad_(mesh.nCells())
{}


template<class Type>
tnbLib::AveragingMethods::Basic<Type>::Basic
(
	const Basic<Type>& am
)
	:
	AveragingMethod<Type>(am),
	data_(FieldField<Field, Type>::operator[](0)),
	dataGrad_(am.dataGrad_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::AveragingMethods::Basic<Type>::~Basic()
{}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::AveragingMethods::Basic<Type>::updateGrad()
{
	GeometricField<Type, fvPatchField, volMesh> tempData
	(
		tnbLib::IOobject
		(
			"BasicAverage::Data",
			this->mesh_,
			tnbLib::IOobject::NO_READ,
			tnbLib::IOobject::NO_WRITE,
			false
		),
		this->mesh_,
		dimensioned<Type>("zero", dimless, Zero),
		zeroGradientFvPatchField<Type>::typeName
	);
	tempData.primitiveFieldRef() = data_;
	tempData.correctBoundaryConditions();
	dataGrad_ = fvc::grad(tempData)->primitiveField();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::AveragingMethods::Basic<Type>::add
(
	const barycentric& coordinates,
	const tetIndices& tetIs,
	const Type& value
)
{
	data_[tetIs.cell()] += value / this->mesh_.V()[tetIs.cell()];
}


template<class Type>
Type tnbLib::AveragingMethods::Basic<Type>::interpolate
(
	const barycentric& coordinates,
	const tetIndices& tetIs
) const
{
	return data_[tetIs.cell()];
}


template<class Type>
typename tnbLib::AveragingMethods::Basic<Type>::TypeGrad
tnbLib::AveragingMethods::Basic<Type>::interpolateGrad
(
	const barycentric& coordinates,
	const tetIndices& tetIs
) const
{
	return dataGrad_[tetIs.cell()];
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::AveragingMethods::Basic<Type>::primitiveField() const
{
	return tmp<Field<Type>>(data_);
}


// ************************************************************************* //