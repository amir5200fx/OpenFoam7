#pragma once
#ifndef _SyamlalOBrien_Header
#define _SyamlalOBrien_Header

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

Class
    tnbLib::dragModels::SyamlalOBrien

Description
    Syamlal, M., Rogers, W. and O'Brien, T. J. (1993) MFIX documentation,
    Theory Guide. Technical Note DOE/METC-94/1004. Morgantown, West Virginia,
    USA.

SourceFiles
    SyamlalOBrien.C

\*---------------------------------------------------------------------------*/

#include "dragModel.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace dragModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class SyamlalOBrien Declaration
        \*---------------------------------------------------------------------------*/

        class SyamlalOBrien
            :
            public dragModel
        {

        public:

            //- Runtime type information
            TypeName("SyamlalOBrien");


            // Constructors

                //- Construct from components
            SyamlalOBrien
            (
                const dictionary& interfaceDict,
                const phaseModel& phase1,
                const phaseModel& phase2
            );


            //- Destructor
            virtual ~SyamlalOBrien();


            // Member Functions

            tmp<volScalarField> K(const volScalarField& Ur) const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace dragModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SyamlalOBrien_Header