#pragma once

// .cxx

#include <IOobjectList.hxx>
#include <HashSet.hxx>
#include "vtkMesh.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    // * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

    template<class GeoField>
    void readFields
    (
        const vtkMesh& vMesh,
        const typename GeoField::Mesh& mesh,
        const IOobjectList& objects,
        const HashSet<word>& selectedFields,
        PtrList<GeoField>& fields
    )
    {
        // Search list of objects for volScalarFields
        IOobjectList fieldObjects(objects.lookupClass(GeoField::typeName));

        // Construct the vol scalar fields
        label nFields = fields.size();
        fields.setSize(nFields + fieldObjects.size());

        forAllIter(IOobjectList, fieldObjects, iter)
        {
            if (selectedFields.empty() || selectedFields.found(iter()->name()))
            {
                fields.set
                (
                    nFields,
                    vMesh.interpolate
                    (
                        GeoField
                        (
                            *iter(),
                            mesh
                        )
                    )
                );
                nFields++;
            }
        }

        fields.setSize(nFields);
    }


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
