#pragma once

#include <externalCoupledMixedFvPatchField.hxx>
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::processField
(
	const fvMesh& mesh,
	const IOobjectList& objects,
	const word& fieldName,
	label& processed
)
{
	if (processed != -1)
	{
		return;
	}

	typedef GeometricField<Type, fvPatchField, volMesh> fieldType;

	const word timeName(mesh.time().timeName());

	IOobjectList fieldObjbjects(objects.lookupClass(fieldType::typeName));

	if (fieldObjbjects.lookup(fieldName) != nullptr)
	{
		fieldType vtf(*fieldObjbjects.lookup(fieldName), mesh);
		const typename fieldType::Boundary& bf =
			vtf.boundaryField();

		forAll(bf, patchi)
		{
			if (isA<externalCoupledMixedFvPatchField<Type>>(bf[patchi]))
			{
				Info << "Generating external coupled geometry for field "
					<< fieldName << endl;

				const externalCoupledMixedFvPatchField<Type>& pf =
					refCast<const externalCoupledMixedFvPatchField<Type>>
					(
						bf[patchi]
						);

				pf.writeGeometry();
				processed = 1;

				break;
			}
		}

		if (processed != 1)
		{
			processed = 0;

			Info << "Field " << fieldName << " found, but does not have any "
				<< externalCoupledMixedFvPatchField<Type>::typeName
				<< " boundary conditions" << endl;
		}
	}
}


// ************************************************************************* //
