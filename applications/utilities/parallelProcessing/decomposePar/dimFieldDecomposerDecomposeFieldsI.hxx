#pragma once

// .cxx

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::DimensionedField<Type, tnbLib::volMesh>>
tnbLib::dimFieldDecomposer::decomposeField
(
    const DimensionedField<Type, volMesh>& field
) const
{
    // Create and map the internal field values
    Field<Type> mappedField(field, cellAddressing_);

    // Create the field for the processor
    return tmp<DimensionedField<Type, volMesh>>
        (
            new DimensionedField<Type, volMesh>
            (
                IOobject
                (
                    field.name(),
                    procMesh_.time().timeName(),
                    procMesh_,
                    IOobject::NO_READ,
                    IOobject::NO_WRITE,
                    false
                ),
                procMesh_,
                field.dimensions(),
                mappedField
                )
            );
}


template<class GeoField>
void tnbLib::dimFieldDecomposer::decomposeFields
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
