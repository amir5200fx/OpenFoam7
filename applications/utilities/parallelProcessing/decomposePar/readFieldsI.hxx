#pragma once

// .cxx

//#include "readFields.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type, template<class> class PatchField, class GeoMesh>
void tnbLib::readFields
(
    const typename GeoMesh::Mesh& mesh,
    const IOobjectList& objects,
    PtrList<GeometricField<Type, PatchField, GeoMesh>>& fields,
    const bool readOldTime
)
{
    typedef GeometricField<Type, PatchField, GeoMesh> GeoField;

    // Search list of objects for fields of type GeomField
    IOobjectList fieldObjects(objects.lookupClass(GeoField::typeName));

    // Remove the cellDist field
    IOobjectList::iterator celDistIter = fieldObjects.find("cellDist");
    if (celDistIter != fieldObjects.end())
    {
        fieldObjects.erase(celDistIter);
    }

    // Get sorted set of names (different processors might read objects in
    // different order)
    const wordList masterNames(fieldObjects.sortedNames());

    // Construct the fields
    fields.setSize(masterNames.size());

    forAll(masterNames, i)
    {
        const IOobject& io = *fieldObjects[masterNames[i]];

        fields.set(i, new GeoField(io, mesh, readOldTime));
    }
}


template<class Mesh, class GeoField>
void tnbLib::readFields
(
    const Mesh& mesh,
    const IOobjectList& objects,
    PtrList<GeoField>& fields
)
{
    // Search list of objects for fields of type GeomField
    IOobjectList fieldObjects(objects.lookupClass(GeoField::typeName));

    // Construct the fields
    fields.setSize(fieldObjects.size());

    // Get sorted set of names (different processors might read objects in
    // different order)
    const wordList masterNames(fieldObjects.sortedNames());

    // Construct the fields
    fields.setSize(masterNames.size());

    forAll(masterNames, i)
    {
        const IOobject& io = *fieldObjects[masterNames[i]];

        fields.set(i, new GeoField(io, mesh));
    }
}


// ************************************************************************* //
