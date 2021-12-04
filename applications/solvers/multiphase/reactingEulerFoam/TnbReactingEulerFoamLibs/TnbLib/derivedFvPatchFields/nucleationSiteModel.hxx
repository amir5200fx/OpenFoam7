#pragma once
#ifndef _nucleationSiteModel_Header
#define _nucleationSiteModel_Header

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
    tnbLib::wallBoilingModels::nucleationSiteModel

Description
    Base class for nucleation site density models

SourceFiles
    nucleationSiteModel.C
    newnucleationSiteModel.C

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
                                 Class nucleationSiteModel Declaration
        \*---------------------------------------------------------------------------*/

        class nucleationSiteModel
        {
        public:

            //- Runtime type information
            TypeName("nucleationSiteModel");


            //- Declare runtime construction
            declareRunTimeSelectionTable
            (
                autoPtr,
                nucleationSiteModel,
                dictionary,
                (
                    const dictionary& dict
                    ),
                (dict)
            );


            // Constructors

                //- Construct null
            nucleationSiteModel();

            //- Disallow default bitwise copy construction
            nucleationSiteModel(const nucleationSiteModel&) = delete;


            // Selectors

                //- Select null constructed
            static autoPtr<nucleationSiteModel> New(const dictionary& dict);


            //- Destructor
            virtual ~nucleationSiteModel();


            // Member Functions

                //- Calculate and return the nucleation-site density
            virtual tmp<scalarField> N
            (
                const phaseModel& liquid,
                const phaseModel& vapor,
                const label patchi,
                const scalarField& Tl,
                const scalarField& Tsatw,
                const scalarField& L
            ) const = 0;

            virtual void write(Ostream& os) const;


            // Member Operators

                //- Disallow default bitwise assignment
            void operator=(const nucleationSiteModel&) = delete;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    } // End namespace wallBoilingModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_nucleationSiteModel_Header