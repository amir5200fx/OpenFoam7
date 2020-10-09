#include <turbulenceFields.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::functionObjects::turbulenceFields::processField
(
	const word& fieldName,
	const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvalue
)
{
	typedef GeometricField<Type, fvPatchField, volMesh> FieldType;

	const word scopedName = prefix_ + fieldName;

	if (obr_.foundObject<FieldType>(scopedName))
	{
		obr_.lookupObjectRef<FieldType>(scopedName) == tvalue();
	}
	else if (obr_.found(scopedName))
	{
		WarningInFunction
			<< "Cannot store turbulence field " << scopedName
			<< " since an object with that name already exists"
			<< nl << endl;
	}
	else
	{
		obr_.store
		(
			new FieldType
			(
				IOobject
				(
					scopedName,
					obr_.time().timeName(),
					obr_,
					IOobject::READ_IF_PRESENT,
					IOobject::NO_WRITE
				),
				tvalue
			)
		);
	}
}


template<class Model>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::functionObjects::turbulenceFields::omega
(
	const Model& model
) const
{
	const scalar Cmu = 0.09;

	// Assume k and epsilon are available
	const volScalarField k(model.k());
	const volScalarField epsilon(model.epsilon());

	return tmp<volScalarField>
		(
			new volScalarField
			(
				IOobject
				(
					"omega",
					k.mesh().time().timeName(),
					k.mesh()
				),
				epsilon / (Cmu*k),
				epsilon.boundaryField().types()
			)
			);
}


// ************************************************************************* //