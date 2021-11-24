#pragma once
#ifndef _XiGModel_Header
#define _XiGModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpentnbLib: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://opentnbLib.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpentnbLib Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpentnbLib.

    OpentnbLib is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpentnbLib is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpentnbLib.  If not, see <http://www.gnu.org/licenses/>.

Class
    tnbLib::XiGModel

Description
    Base-class for all Xi generation models used by the b-Xi combustion model.
    See Technical Report SH/RE/01R for details on the PDR modelling. For details
    on the use of XiGModel see \link XiModel.H \endlink. The model available is
    \link instabilityG.H \endlink

SourceFiles
    XiGModel.C

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <IOdictionary.hxx>
#include <psiuReactionThermo.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                              Class XiGModel Declaration
    \*---------------------------------------------------------------------------*/

    class XiGModel
    {

    protected:

        // Protected data

        dictionary XiGModelCoeffs_;

        const psiuReactionThermo& thermo_;
        const compressible::RASModel& turbulence_;
        const volScalarField& Su_;


    public:

        //- Runtime type information
        TypeName("XiGModel");


        // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            XiGModel,
            dictionary,
            (
                const dictionary& XiGProperties,
                const psiuReactionThermo& thermo,
                const compressible::RASModel& turbulence,
                const volScalarField& Su
                ),
            (
                XiGProperties,
                thermo,
                turbulence,
                Su
                )
        );


        // Constructors

            //- Construct from components
        XiGModel
        (
            const dictionary& XiGProperties,
            const psiuReactionThermo& thermo,
            const compressible::RASModel& turbulence,
            const volScalarField& Su
        );

        //- Disallow default bitwise copy construction
        XiGModel(const XiGModel&);


        // Selectors

            //- Return a reference to the selected XiG model
        static autoPtr<XiGModel> New
        (
            const dictionary& XiGProperties,
            const psiuReactionThermo& thermo,
            const compressible::RASModel& turbulence,
            const volScalarField& Su
        );


        //- Destructor
        virtual ~XiGModel();


        // Member Functions

            //- Return the flame-wrinking generation rate
        virtual tmp<volScalarField> G() const = 0;

        //- Return the flame diffusivity
        virtual tmp<volScalarField> Db() const
        {
            return turbulence_.muEff();
        }

        //- Update properties from given dictionary
        virtual bool read(const dictionary& XiGProperties) = 0;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const XiGModel&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_XiGModel_Header
