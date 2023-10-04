#pragma once
#ifndef _WellekTwoPhase_Header
#define _WellekTwoPhase_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2014-2018 OpenFOAM Foundation
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
    tnbLib::aspectRatioModels::Wellek

Description
    Aspect ratio model of Wellek et al.

    References:
    \verbatim
        "Implementation and Comparison of Correlations for interfacial Forces
         in a Gas-Liquid System within an Euler-Euler Framework"
        Otromke, M.,
        PhD Thesis, April 2013
    \endverbatim

    \verbatim
        "Shape of liquid drops moving in liquid media"
        Wellek, R.M., Agrawal, A.K., Skelland, A.H.P.,
        International Journal of Multiphase Flow
        Volume 12, Issue 5, September 1966, pp. 854-862
    \endverbatim

SourceFiles
    Wellek.C

\*---------------------------------------------------------------------------*/

#include "aspectRatioModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace aspectRatioModels
    {

        /*---------------------------------------------------------------------------*\
                               Class Wellek Declaration
        \*---------------------------------------------------------------------------*/

        class Wellek
            :
            public aspectRatioModel
        {
        public:

            //- Runtime type information
            TypeName("Wellek");


            // Constructors

                //- Construct from a dictionary and an ordered phase pair
            Wellek
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            virtual ~Wellek();


            // Member Functions

                //- Aspect ratio
            virtual tmp<volScalarField> E() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace aspectRatioModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_WellekTwoPhase_Header