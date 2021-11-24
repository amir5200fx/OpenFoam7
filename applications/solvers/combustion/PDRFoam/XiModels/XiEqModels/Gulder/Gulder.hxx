#pragma once
#ifndef _Gulder_Header
#define _Gulder_Header

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
    tnbLib::XiEqModels::Gulder

Description
    Simple Gulder model for XiEq based on Gulders correlation
    with a linear correction function to give a plausible profile for XiEq.

SourceFiles
    Gulder.C

\*---------------------------------------------------------------------------*/

#include <XiEqModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace XiEqModels
    {

        /*---------------------------------------------------------------------------*\
                                  Class Gulder Declaration
        \*---------------------------------------------------------------------------*/

        class Gulder
            :
            public XiEqModel
        {
            // Private Data

                //- Model constant
            scalar XiEqCoef_;

            //- Minimum laminar burning velocity
            const dimensionedScalar SuMin_;

            //- Schelkin effect Model constant
            scalar uPrimeCoef_;

            //- Use sub-grid Schelkin effect
            bool subGridSchelkin_;


        public:

            //- Runtime type information
            TypeName("Gulder");


            // Constructors

                //- Construct from components
            Gulder
            (
                const dictionary& XiEqProperties,
                const psiuReactionThermo& thermo,
                const compressible::RASModel& turbulence,
                const volScalarField& Su
            );

            //- Disallow default bitwise copy construction
            Gulder(const Gulder&);


            //- Destructor
            virtual ~Gulder();


            // Member Functions

                //- Return the flame-wrinking XiEq
            virtual tmp<volScalarField> XiEq() const;

            //- Update properties from given dictionary
            virtual bool read(const dictionary& XiEqProperties);


            // Member Operators

                //- Disallow default bitwise assignment
            void operator=(const Gulder&) = delete;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace XiEqModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Gulder_Header
