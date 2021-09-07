#pragma once
#ifndef _checkMeshQuality_Header
#define _checkMeshQuality_Header

#include <includeAllModules.hxx>

#include <polyMesh.hxx>

namespace tnbLib
{
    class surfaceWriter;

    label checkMeshQuality
    (
        const polyMesh&,
        const dictionary&,
        const autoPtr<surfaceWriter>&
    );
}
#endif // !_checkMeshQuality_Header

