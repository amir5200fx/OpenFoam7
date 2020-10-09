#pragma once
#ifndef _makeSootTypes_Header
#define _makeSootTypes_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeSootTypesThermo(SootModelType, Thermo)                             \
                                                                               \
    typedef radiationModels::sootModels::SootModelType<Thermo>                 \
        SootModelType##Thermo;                                                 \
                                                                               \
    defineTemplateTypeNameAndDebugWithName                                     \
    (                                                                          \
        SootModelType##Thermo,                                                 \
        (                                                                      \
            word(SootModelType##Thermo::typeName_()) + "<"#Thermo">"           \
        ).c_str(),                                                             \
        0                                                                      \
    );                                                                         \
                                                                               \
    namespace radiationModels                                                  \
    {                                                                          \
        addToRunTimeSelectionTable                                             \
        (                                                                      \
            sootModel,                                                         \
            SootModelType##Thermo,                                             \
            dictionary                                                         \
        );                                                                     \
    }

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_makeSootTypes_Header