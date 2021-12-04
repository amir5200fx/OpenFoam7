#pragma once
#ifndef _heatTransferModel_Header
#define _heatTransferModel_Header

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
    tnbLib::heatTransferModel

Description

SourceFiles
    heatTransferModel.C

\*---------------------------------------------------------------------------*/

#include <reactingEulerFoamLibs_Module.hxx>

#include <volFields.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

namespace tnbLib
{

    class phasePair;

    /*---------------------------------------------------------------------------*\
                            Class heatTransferModel Declaration
    \*---------------------------------------------------------------------------*/

    class heatTransferModel
    {
    protected:

        // Protected data

            //- Phase pair
        const phasePair& pair_;

        //- Residual phase fraction
        const dimensionedScalar residualAlpha_;


    public:

        //- Runtime type information
        TypeName("heatTransferModel");


        // Declare runtime construction

        declareRunTimeSelectionTable
        (
            autoPtr,
            heatTransferModel,
            dictionary,
            (
                const dictionary& dict,
                const phasePair& pair
                ),
            (dict, pair)
        );


        // Static Data Members

            //- Coefficient dimensions
        static FoamReactingEulerFoamLibs_EXPORT const dimensionSet dimK;


        // Constructors

            //- Construct froma dictionary and a phase pair
        FoamReactingEulerFoamLibs_EXPORT heatTransferModel
        (
            const dictionary& dict,
            const phasePair& pair
        );


        //- Destructor
        FoamReactingEulerFoamLibs_EXPORT virtual ~heatTransferModel();


        // Selectors

        static FoamReactingEulerFoamLibs_EXPORT autoPtr<heatTransferModel> New
        (
            const dictionary& dict,
            const phasePair& pair
        );


        // Member Functions

            //- The heat transfer function K used in the enthalpy equation
            //    ddt(alpha1*rho1*ha) + ... = ... K*(Ta - Tb)
            //    ddt(alpha2*rho2*hb) + ... = ... K*(Tb - Ta)
        FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> K() const;

        //- The heat transfer function K used in the enthalpy equation
        //    ddt(alpha1*rho1*ha) + ... = ... K*(Ta - Tb)
        //    ddt(alpha2*rho2*hb) + ... = ... K*(Tb - Ta)
        //  with a specified residual volume fraction
        virtual tmp<volScalarField> K(const scalar residualAlpha) const = 0;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_heatTransferModel_Header
