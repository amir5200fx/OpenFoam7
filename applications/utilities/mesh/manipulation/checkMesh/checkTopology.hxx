#pragma once
#ifndef _checkTopology_Header
#define _checkTopology_Header

#include <includeAllModules.hxx>

#include <label.hxx>
#include <autoPtr.hxx>
#include <writer.hxx>

namespace tnbLib
{
    class polyMesh;
    class surfaceWriter;

    label checkTopology
    (
        const polyMesh&,
        const bool,
        const bool,
        const autoPtr<surfaceWriter>&,
        const autoPtr<writer<scalar>>&
    );
}

#endif // !_checkTopology_Header

