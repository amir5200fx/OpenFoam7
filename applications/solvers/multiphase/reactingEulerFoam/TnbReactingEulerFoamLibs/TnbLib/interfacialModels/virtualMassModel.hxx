#pragma once
#ifndef _virtualMassModel_Header
#define _virtualMassModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2014-2019 OpenFOAM Foundation
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
    tnbLib::virtualMassModel

Description

SourceFiles
    virtualMassModel.C
    newVirtualMassModel.C

\*---------------------------------------------------------------------------*/

#include <reactingEulerFoamLibs_Module.hxx>

#include <volFields.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

namespace tnbLib
{

    class phasePair;

    /*---------------------------------------------------------------------------*\
                             Class virtualMassModel Declaration
    \*---------------------------------------------------------------------------*/

    class virtualMassModel
        :
        public regIOobject
    {
    protected:

        // Protected data

            //- Phase pair
        const phasePair& pair_;


    public:

        //- Runtime type information
        TypeName("virtualMassModel");


        // Declare runtime construction

        declareRunTimeSelectionTable
        (
            autoPtr,
            virtualMassModel,
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

            //- Construct from a dictionary and a phase pair
        FoamReactingEulerFoamLibs_EXPORT virtualMassModel
        (
            const dictionary& dict,
            const phasePair& pair,
            const bool registerObject
        );


        //- Destructor
        FoamReactingEulerFoamLibs_EXPORT virtual ~virtualMassModel();


        // Selectors

        static FoamReactingEulerFoamLibs_EXPORT autoPtr<virtualMassModel> New
        (
            const dictionary& dict,
            const phasePair& pair
        );


        // Member Functions

            //- Return the virtual mass coefficient
        virtual tmp<volScalarField> Cvm() const = 0;

        //- Return the phase-intensive virtual mass coefficient Ki
        //  used in the momentum equation
        //    ddt(alpha1*rho1*U1) + ... = ... alphad*K*(DU1_Dt - DU2_Dt)
        //    ddt(alpha2*rho2*U2) + ... = ... alphad*K*(DU1_Dt - DU2_Dt)
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> Ki() const;

        //- Return the virtual mass coefficient K
        //  used in the momentum equation
        //    ddt(alpha1*rho1*U1) + ... = ... K*(DU1_Dt - DU2_Dt)
        //    ddt(alpha2*rho2*U2) + ... = ... K*(DU1_Dt - DU2_Dt)
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> K() const;

        //- Return the virtual mass coefficient Kf
        //  used in the face-momentum equations
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<surfaceScalarField> Kf() const;

        // Dummy write for regIOobject
        FoamReactingEulerFoamLibs_EXPORT bool writeData(Ostream& os) const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_virtualMassModel_Header
