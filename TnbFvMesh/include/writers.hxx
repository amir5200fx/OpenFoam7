#pragma once
#ifndef _writers_Header
#define _writers_Header

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

InClass
	Foam::writer

SourceFiles
	writers.C

\*---------------------------------------------------------------------------*/

#include <writer.hxx>
#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Only used internally
#define makeTypeSetWritersTypeName(typeWriter, dataType)                       \
                                                                               \
    defineNamedTemplateTypeNameAndDebug(typeWriter<dataType>, 0)

// Sometimes used externally
#define makeSetWritersTypeName(typeWriter)                                     \
                                                                               \
    makeTypeSetWritersTypeName(typeWriter, scalar);                            \
    makeTypeSetWritersTypeName(typeWriter, vector);                            \
    makeTypeSetWritersTypeName(typeWriter, sphericalTensor);                   \
    makeTypeSetWritersTypeName(typeWriter, symmTensor);                        \
    makeTypeSetWritersTypeName(typeWriter, tensor)

// Define type info for single dataType template instantiation (eg, vector)
#define makeSetWriterType(typeWriter, dataType)                                \
                                                                               \
    defineNamedTemplateTypeNameAndDebug(typeWriter<dataType>, 0);              \
    addTemplatedToRunTimeSelectionTable                                        \
    (                                                                          \
        writer, typeWriter, dataType, word                                     \
    )


// Define type info for scalar, vector etc. instantiations
#define makeSetWriters(typeWriter)                                             \
                                                                               \
    makeSetWriterType(typeWriter, scalar);                                     \
    makeSetWriterType(typeWriter, vector);                                     \
    makeSetWriterType(typeWriter, sphericalTensor);                            \
    makeSetWriterType(typeWriter, symmTensor);                                 \
    makeSetWriterType(typeWriter, tensor)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_writers_Header
