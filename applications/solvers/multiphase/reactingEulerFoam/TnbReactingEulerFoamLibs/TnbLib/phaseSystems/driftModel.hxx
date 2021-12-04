#pragma once
#ifndef _driftModel_Header
#define _driftModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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
    tnbLib::diameterModels::driftModel

Description
    Base class for drift models.

SourceFiles
    driftModel.C

\*---------------------------------------------------------------------------*/

#include <populationBalanceModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {

        /*---------------------------------------------------------------------------*\
                                 Class driftModel Declaration
        \*---------------------------------------------------------------------------*/

        class driftModel
        {
        protected:

            // Protected data

                //- Reference to the populationBalanceModel
            const populationBalanceModel& popBal_;


        public:

            //- Runtime type information
            TypeName("driftModel");


            // Declare run-time constructor selection table

            declareRunTimeSelectionTable
            (
                autoPtr,
                driftModel,
                dictionary,
                (
                    const populationBalanceModel& popBal,
                    const dictionary& dict
                    ),
                (popBal, dict)
            );


            //- Class used for the read-construction of
            //  PtrLists of drift models
            class iNew
            {
                const populationBalanceModel& popBal_;

            public:

                iNew(const populationBalanceModel& popBal)
                    :
                    popBal_(popBal)
                {}

                autoPtr<driftModel> operator()(Istream& is) const
                {
                    word type(is);
                    dictionary dict(is);
                    return driftModel::New(type, popBal_, dict);
                }
            };


            // Constructor

            FoamReactingEulerFoamLibs_EXPORT driftModel
            (
                const populationBalanceModel& popBal,
                const dictionary& dict
            );

            autoPtr<driftModel> clone() const
            {
                NotImplemented;
                return autoPtr<driftModel>(nullptr);
            }


            // Selector

            static FoamReactingEulerFoamLibs_EXPORT autoPtr<driftModel> New
            (
                const word& type,
                const populationBalanceModel& popBal,
                const dictionary& dict
            );


            //- Destructor
            virtual ~driftModel()
            {}


            // Member Functions

                //- Return reference to the populationBalanceModel
            const populationBalanceModel& popBal() const
            {
                return popBal_;
            }

            //- Correct diameter independent expressions
            FoamReactingEulerFoamLibs_EXPORT virtual void correct();

            //- Add to driftRate
            virtual void addToDriftRate
            (
                volScalarField& driftRate,
                const label i
            ) = 0;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace diameterModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_driftModel_Header
