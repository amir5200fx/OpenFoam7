#pragma once
#ifndef _partitioningModel_Header
#define _partitioningModel_Header

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
    tnbLib::wallBoilingModels::partitioningModel

Description
    Base class for wall heat flux partitioning models

SourceFiles
    partitioningModel.C
    newpartitioningModel.C

\*---------------------------------------------------------------------------*/

#include <reactingEulerFoamLibs_Module.hxx>

#include <volFields.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace wallBoilingModels
    {

        /*---------------------------------------------------------------------------*\
                                 Class partitioningModel Declaration
        \*---------------------------------------------------------------------------*/

        class partitioningModel
        {
        public:

            //- Runtime type information
            TypeName("partitioningModel");


            //- Declare runtime construction
            declareRunTimeSelectionTable
            (
                autoPtr,
                partitioningModel,
                dictionary,
                (
                    const dictionary& dict
                    ),
                (dict)
            );


            // Constructors

                //- Construct null
            partitioningModel();

            //- Disallow default bitwise copy construction
            partitioningModel(const partitioningModel&) = delete;


            // Selectors

                //- Select null constructed
            static autoPtr<partitioningModel> New(const dictionary& dict);


            //- Destructor
            virtual ~partitioningModel();


            // Member Functions

                //- Calculate and return the wall heat-flux partitioning
            virtual tmp<scalarField> fLiquid
            (
                const scalarField& alphaLiquid
            ) const = 0;

            virtual void write(Ostream& os) const;


            // Member Operators

                //- Disallow default bitwise assignment
            void operator=(const partitioningModel&) = delete;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    } // End namespace wallBoilingModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_partitioningModel_Header
