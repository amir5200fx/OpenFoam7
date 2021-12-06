#pragma once
#ifndef _turbulentBreakUpTwoPhase_Header
#define _turbulentBreakUpTwoPhase_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
    tnbLib::diameterModels::IATEsources::turbulentBreakUp

Description
    Turbulence-induced break-up IATE source as defined in paper:

    \verbatim
        "Development of Interfacial Area Transport Equation"
        Ishii, M., Kim, S. and Kelly, J.,
        Nuclear Engineering and Technology, Vol.37 No.6 December 2005
    \endverbatim

SourceFiles
    turbulentBreakUpTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "IATEsourceTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {
        namespace IATEsources
        {

            /*---------------------------------------------------------------------------*\
                                       Class turbulentBreakUp Declaration
            \*---------------------------------------------------------------------------*/

            class turbulentBreakUp
                :
                public IATEsource
            {
                // Private Data

                dimensionedScalar Cti_;
                dimensionedScalar WeCr_;


            public:

                //- Runtime type information
                TypeName("turbulentBreakUp");

                // Constructors

                turbulentBreakUp
                (
                    const IATE& iate,
                    const dictionary& dict
                );


                //- Destructor
                virtual ~turbulentBreakUp()
                {}


                // Member Functions

                virtual tmp<volScalarField> R() const;
            };


            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        } // End namespace IATEsources
    } // End namespace diameterModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_turbulentBreakUpTwoPhase_Header
