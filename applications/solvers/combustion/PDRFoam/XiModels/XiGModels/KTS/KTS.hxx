#pragma once
#ifndef _KTS_Header
#define _KTS_Header

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
    tnbLib::XiGModels::KTS

Description
    Simple Kolmogorov time-scale (KTS) model for the flame-wrinling generation
    rate.

SourceFiles
    KTS.C

\*---------------------------------------------------------------------------*/

#include <XiGModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace XiGModels
    {

        /*---------------------------------------------------------------------------*\
                                  Class KTS Declaration
        \*---------------------------------------------------------------------------*/

        class KTS
            :
            public XiGModel
        {
            // Private Data

            scalar GEtaCoef_;


        public:

            //- Runtime type information
            TypeName("KTS");


            // Constructors

                //- Construct from components
            KTS
            (
                const dictionary& XiGProperties,
                const psiuReactionThermo& thermo,
                const compressible::RASModel& turbulence,
                const volScalarField& Su
            );

            //- Disallow default bitwise copy construction
            KTS(const KTS&);


            //- Destructor
            virtual ~KTS();


            // Member Functions

                //- Return the flame-wrinking generation rate
            virtual tmp<volScalarField> G() const;

            //- Update properties from given dictionary
            virtual bool read(const dictionary& XiGProperties);


            // Member Operators

                //- Disallow default bitwise assignment
            void operator=(const KTS&) = delete;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace XiGModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_KTS_Header
