#pragma once

// .cxx

#include <processorPointPatchFields.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::pointPatchField, tnbLib::pointMesh>>
tnbLib::pointFieldDecomposer::decomposeField
(
    const GeometricField<Type, pointPatchField, pointMesh>& field
) const
{
    // Create and map the internal field values
    Field<Type> internalField(field.primitiveField(), pointAddressing_);

    // Create a list of pointers for the patchFields
    PtrList<pointPatchField<Type>> patchFields(boundaryAddressing_.size());

    // Create and map the patch field values
    forAll(boundaryAddressing_, patchi)
    {
        if (patchFieldDecomposerPtrs_[patchi])
        {
            patchFields.set
            (
                patchi,
                pointPatchField<Type>::New
                (
                    field.boundaryField()[boundaryAddressing_[patchi]],
                    procMesh_.boundary()[patchi],
                    DimensionedField<Type, pointMesh>::null(),
                    *patchFieldDecomposerPtrs_[patchi]
                )
            );
        }
        else
        {
            patchFields.set
            (
                patchi,
                new processorPointPatchField<Type>
                (
                    procMesh_.boundary()[patchi],
                    DimensionedField<Type, pointMesh>::null()
                    )
            );
        }
    }

    // Create the field for the processor
    return tmp<GeometricField<Type, pointPatchField, pointMesh>>
        (
            new GeometricField<Type, pointPatchField, pointMesh>
            (
                IOobject
                (
                    field.name(),
                    procMesh_().time().timeName(),
                    procMesh_(),
                    IOobject::NO_READ,
                    IOobject::NO_WRITE,
                    false
                ),
                procMesh_,
                field.dimensions(),
                internalField,
                patchFields
                )
            );
}


template<class GeoField>
void tnbLib::pointFieldDecomposer::decomposeFields
(
    const PtrList<GeoField>& fields
) const
{
    forAll(fields, fieldi)
    {
        decomposeField(fields[fieldi])().write();
    }
}


// ************************************************************************* //
