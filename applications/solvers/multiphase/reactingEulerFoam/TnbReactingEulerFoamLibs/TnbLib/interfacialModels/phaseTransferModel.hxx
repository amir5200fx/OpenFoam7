#pragma once
#ifndef _phaseTransferModel_Header
#define _phaseTransferModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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
    tnbLib::phaseTransferModel

Description

SourceFiles
    phaseTransferModel.C

\*---------------------------------------------------------------------------*/

#include <reactingEulerFoamLibs_Module.hxx>

#include <volFields.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

namespace tnbLib
{

    class phasePair;

    /*---------------------------------------------------------------------------*\
                            Class phaseTransferModel Declaration
    \*---------------------------------------------------------------------------*/

    class phaseTransferModel
    {
    protected:

        // Protected data

            //- Phase pair
        const phasePair& pair_;


    public:

        //- Runtime type information
        TypeName("phaseTransferModel");


        // Declare runtime construction

        declareRunTimeSelectionTable
        (
            autoPtr,
            phaseTransferModel,
            dictionary,
            (
                const dictionary& dict,
                const phasePair& pair
                ),
            (dict, pair)
        );


        // Static Data Members

            //- Mass transfer rate dimensions
        static const dimensionSet dimDmdt;


        // Constructors

            //- Construct from a dictionary and a phase pair
        phaseTransferModel
        (
            const dictionary& dict,
            const phasePair& pair
        );


        //- Destructor
        virtual ~phaseTransferModel();


        // Selectors

        static autoPtr<phaseTransferModel> New
        (
            const dictionary& dict,
            const phasePair& pair
        );


        // Member Functions

            //- The mass transfer rate
        virtual tmp<volScalarField> dmdt() const = 0;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_phaseTransferModel_Header
