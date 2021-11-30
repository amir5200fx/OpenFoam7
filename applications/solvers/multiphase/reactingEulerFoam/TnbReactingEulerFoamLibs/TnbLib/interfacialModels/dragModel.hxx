#pragma once
#ifndef _dragModel_Header
#define _dragModel_Header

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
    tnbLib::dragModel

Description

SourceFiles
    dragModel.C
    newDragModel.C

\*---------------------------------------------------------------------------*/

#include <reactingEulerFoamLibs_Module.hxx>

#include <volFields.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

namespace tnbLib
{

    class phasePair;
    class swarmCorrection;

    /*---------------------------------------------------------------------------*\
                               Class dragModel Declaration
    \*---------------------------------------------------------------------------*/

    class dragModel
        :
        public regIOobject
    {
    protected:

        // Protected data

            //- Phase pair
        const phasePair& pair_;

        //- Swarm correction
        autoPtr<swarmCorrection> swarmCorrection_;


    public:

        //- Runtime type information
        TypeName("dragModel");


        // Declare runtime construction

        FoamReactingEulerFoamLibs_EXPORT declareRunTimeSelectionTable
        (
            autoPtr,
            dragModel,
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
        static FoamReactingEulerFoamLibs_EXPORT const dimensionSet dimK;


        // Constructors

            // Construct without residual constants
        FoamReactingEulerFoamLibs_EXPORT dragModel
        (
            const phasePair& pair,
            const bool registerObject
        );

        // Construct with residual constants
        FoamReactingEulerFoamLibs_EXPORT dragModel
        (
            const dictionary& dict,
            const phasePair& pair,
            const bool registerObject
        );


        //- Destructor
        FoamReactingEulerFoamLibs_EXPORT virtual ~dragModel();


        // Selectors

        static FoamReactingEulerFoamLibs_EXPORT autoPtr<dragModel> New
        (
            const dictionary& dict,
            const phasePair& pair
        );


        // Member Functions

            //- Drag coefficient
        virtual tmp<volScalarField> CdRe() const = 0;

        //- Return the phase-intensive drag coefficient Ki
        //  used in the momentum equations
        //    ddt(alpha1*rho1*U1) + ... = ... alphad*K*(U1-U2)
        //    ddt(alpha2*rho2*U2) + ... = ... alphad*K*(U2-U1)
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> Ki() const;

        //- Return the drag coefficient K
        //  used in the momentum equations
        //    ddt(alpha1*rho1*U1) + ... = ... K*(U1-U2)
        //    ddt(alpha2*rho2*U2) + ... = ... K*(U2-U1)
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> K() const;

        //- Return the drag coefficient Kf
        //  used in the face-momentum equations
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<surfaceScalarField> Kf() const;

        //- Dummy write for regIOobject
        FoamReactingEulerFoamLibs_EXPORT bool writeData(Ostream& os) const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dragModel_Header
