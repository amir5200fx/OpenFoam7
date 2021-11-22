/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/

#include <surfaceMeshWriter.hxx>

#include <writeFuns.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfaceMeshWriter::surfaceMeshWriter
(
    const bool binary,
    const indirectPrimitivePatch& pp,
    const word& name,
    const fileName& fName
)
    :
    binary_(binary),
    pp_(pp),
    fName_(fName),
    os_(fName.c_str())
{
    // Write header
    writeFuns::writeHeader(os_, binary_, name);

    os_ << "DATASET POLYDATA" << std::endl;

    // Write topology
    label nFaceVerts = 0;

    forAll(pp, facei)
    {
        nFaceVerts += pp[facei].size() + 1;
    }

    os_ << "POINTS " << pp.nPoints() << " float" << std::endl;

    DynamicList<floatScalar> ptField(3 * pp.nPoints());
    writeFuns::insert(pp.localPoints(), ptField);
    writeFuns::write(os_, binary, ptField);


    os_ << "POLYGONS " << pp.size() << ' ' << nFaceVerts << std::endl;

    DynamicList<label> vertLabels(nFaceVerts);

    forAll(pp, facei)
    {
        const face& f = pp.localFaces()[facei];

        vertLabels.append(f.size());
        writeFuns::insert(f, vertLabels);
    }
    writeFuns::write(os_, binary_, vertLabels);
}


// ************************************************************************* //
