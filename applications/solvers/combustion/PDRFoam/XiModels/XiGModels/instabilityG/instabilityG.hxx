#pragma once
#ifndef _instabilityG_Header
#define _instabilityG_Header

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
    tnbLib::XiGModels::instabilityG

Description
    Flame-surface instabilityG flame-wrinking generation rate coefficient model
    used in \link XiModel.H \endlink.

    See Technical Report SH/RE/01R for details on the PDR modelling.

SourceFiles
    instabilityG.C

\*---------------------------------------------------------------------------*/

#include <XiGModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace XiGModels
    {

        /*---------------------------------------------------------------------------*\
                                  Class instabilityG Declaration
        \*---------------------------------------------------------------------------*/

        class instabilityG
            :
            public XiGModel
        {
            // Private Data

                //- Flame instabilityG wrinling generation rate coefficient
            dimensionedScalar GIn_;

            //- InstabilityG length-scale
            dimensionedScalar lambdaIn_;

            //- Xi generation rate model due to all other processes
            autoPtr<XiGModel> XiGModel_;


        public:

            //- Runtime type information
            TypeName("instabilityG");


            // Constructors

                //- Construct from components
            instabilityG
            (
                const dictionary& XiGProperties,
                const psiuReactionThermo& thermo,
                const compressible::RASModel& turbulence,
                const volScalarField& Su
            );

            //- Disallow default bitwise copy construction
            instabilityG(const instabilityG&);


            //- Destructor
            virtual ~instabilityG();


            // Member Functions

                //- Return the flame-wrinking generation rate
            virtual tmp<volScalarField> G() const;

            //- Return the flame diffusivity
            virtual tmp<volScalarField> Db() const;

            //- Update properties from given dictionary
            virtual bool read(const dictionary& XiGProperties);


            // Member Operators

                //- Disallow default bitwise assignment
            void operator=(const instabilityG&) = delete;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace XiGModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_instabilityG_Header
