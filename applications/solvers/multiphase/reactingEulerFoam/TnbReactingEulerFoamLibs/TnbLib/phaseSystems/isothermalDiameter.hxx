#pragma once
#ifndef _isothermalDiameter_Header
#define _isothermalDiameter_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
    tnbLib::diameterModels::isothermal

Description
    Isothermal dispersed-phase particle diameter model.

SourceFiles
    isothermal.C

\*---------------------------------------------------------------------------*/

#include <diameterModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class isothermal Declaration
        \*---------------------------------------------------------------------------*/

        class isothermal
            :
            public diameterModel
        {
            // Private Data

                //- Reference diameter for the isothermal expansion
            dimensionedScalar d0_;

            //- Reference pressure for the isothermal expansion
            dimensionedScalar p0_;

            //- Actual diameter field
            volScalarField d_;


        public:

            //- Runtime type information
            TypeName("isothermal");


            // Constructors

                //- Construct from components
            FoamReactingEulerFoamLibs_EXPORT isothermal
            (
                const dictionary& diameterProperties,
                const phaseModel& phase
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~isothermal();


            // Member Functions

                //- Return the diameter field
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> d() const;

            //- Correct the diameter field
            FoamReactingEulerFoamLibs_EXPORT virtual void correct();

            //- Read phaseProperties dictionary
            FoamReactingEulerFoamLibs_EXPORT virtual bool read(const dictionary& phaseProperties);
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace diameterModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_isothermalDiameter_Header
