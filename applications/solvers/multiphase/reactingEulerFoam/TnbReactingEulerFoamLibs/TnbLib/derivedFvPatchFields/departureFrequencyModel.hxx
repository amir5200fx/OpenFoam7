#pragma once
#ifndef _departureFrequencyModel_Header
#define _departureFrequencyModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
    tnbLib::wallBoilingModels::departureFrequencyModel

Description
    Base class for bubble departure frequency models

SourceFiles
    departureFrequencyModel.C
    newdepartureFrequencyModel.C

\*---------------------------------------------------------------------------*/

#include <phaseModel.hxx>

#include <volFields.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace wallBoilingModels
    {

        /*---------------------------------------------------------------------------*\
                                 Class departureFrequencyModel Declaration
        \*---------------------------------------------------------------------------*/

        class departureFrequencyModel
        {
        public:

            //- Runtime type information
            TypeName("departureFrequencyModel");


            //- Declare runtime construction
            declareRunTimeSelectionTable
            (
                autoPtr,
                departureFrequencyModel,
                dictionary,
                (
                    const dictionary& dict
                    ),
                (dict)
            );


            // Constructors

                //- Construct null
            FoamReactingEulerFoamLibs_EXPORT departureFrequencyModel();

            //- Disallow default bitwise copy construction
            departureFrequencyModel(const departureFrequencyModel&) = delete;


            // Selectors

                //- Select null constructed
            static FoamReactingEulerFoamLibs_EXPORT autoPtr<departureFrequencyModel> New(const dictionary& dict);


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~departureFrequencyModel();


            // Member Functions

                //- Calculate and return the bubble departure frequency
            virtual tmp<scalarField> fDeparture
            (
                const phaseModel& liquid,
                const phaseModel& vapor,
                const label patchi,
                const scalarField& dDep
            ) const = 0;

            FoamReactingEulerFoamLibs_EXPORT virtual void write(Ostream& os) const;


            // Member Operators

                //- Disallow default bitwise assignment
            void operator=(const departureFrequencyModel&) = delete;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    } // End namespace wallBoilingModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_departureFrequencyModel_Header