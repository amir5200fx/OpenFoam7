#pragma once
#ifndef _surfaceTensionModelMultiphase_Header
#define _surfaceTensionModelMultiphase_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
    tnbLib::surfaceTensionModel

Description

SourceFiles
    surfaceTensionModel.C
    newAspectRatioModel.C

\*---------------------------------------------------------------------------*/

#include <reactingEulerFoamLibs_Module.hxx>

#include <volFields.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

namespace tnbLib
{

    class phasePair;

    /*---------------------------------------------------------------------------*\
                               Class surfaceTensionModel Declaration
    \*---------------------------------------------------------------------------*/

    class surfaceTensionModel
        :
        public regIOobject
    {
    protected:

        // Protected data

            //- Phase pair
        const phasePair& pair_;


    public:

        //- Runtime type information
        TypeName("surfaceTensionModel");


        // Declare runtime construction
        declareRunTimeSelectionTable
        (
            autoPtr,
            surfaceTensionModel,
            dictionary,
            (
                const dictionary& dict,
                const phasePair& pair,
                const bool registerObject
                ),
            (dict, pair, registerObject)
        );


        // Static Data Members

            //- Coefficient dimensions
        static FoamReactingEulerFoamLibs_EXPORT const dimensionSet dimSigma;


        // Constructors

            //- Construct from a dictionary and a phase pair
        FoamReactingEulerFoamLibs_EXPORT surfaceTensionModel
        (
            const dictionary& dict,
            const phasePair& pair,
            const bool registerObject
        );


        //- Destructor
        FoamReactingEulerFoamLibs_EXPORT virtual ~surfaceTensionModel();


        // Selectors

        static FoamReactingEulerFoamLibs_EXPORT autoPtr<surfaceTensionModel> New
        (
            const dictionary& dict,
            const phasePair& pair
        );


        // Member Functions

            //- Aspect ratio
        virtual tmp<volScalarField> sigma() const = 0;

        //- Dummy write for regIOobject
        FoamReactingEulerFoamLibs_EXPORT bool writeData(Ostream& os) const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceTensionModelMultiphase_Header
