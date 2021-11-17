#pragma once
#ifndef _CGALTriangulation2DKernel_Header
#define _CGALTriangulation2DKernel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Typedefs
    CGALTriangulation2DKernel

Description

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>

#include <CGAL/number_utils.h>
#include <CGAL/Delaunay_triangulation_2.h>

#ifdef CGAL_INEXACT

// Fast kernel using a double as the storage type but the triangulation
// may fail
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

#else

// Very robust but expensive kernel
#include "CGAL/Exact_predicates_exact_constructions_kernel.h"

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

#endif


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CGALTriangulation2DKernel_Header
