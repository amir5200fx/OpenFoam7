#pragma once
#ifndef _Ergun_Header
#define _Ergun_Header

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
    tnbLib::dragModels::Ergun

Description

    Reference:
    \verbatim
        Enwald, H., Peirano, E., & Almstedt, A. E. (1996).
        Eulerian two-phase flow theory applied to fluidization.
        International Journal of Multiphase Flow, 22, 21-66.
    \endverbatim

SourceFiles
    Ergun.C

\*---------------------------------------------------------------------------*/

#include <dragModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace dragModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class Ergun Declaration
        \*---------------------------------------------------------------------------*/

        class Ergun
            :
            public dragModel
        {
        public:

            //- Runtime type information
            TypeName("Ergun");


            // Constructors

                //- Construct from a dictionary and a phase pair
            Ergun
            (
                const dictionary& dict,
                const phasePair& pair,
                const bool registerObject
            );


            //- Destructor
            virtual ~Ergun();


            // Member Functions

                //- Drag coefficient
            virtual tmp<volScalarField> CdRe() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace dragModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Ergun_Header
