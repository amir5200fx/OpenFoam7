#pragma once
#ifndef _TolubinskiKostanchuk_Header
#define _TolubinskiKostanchuk_Header

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
    tnbLib::wallBoilingModels::departureDiameterModels::TolubinskiKostanchuk

Description
    Tolubinski-Kostanchuk correlation for bubble departure diameter.

    Reference:
    \verbatim
        Tolubinsky, V. I., & Kostanchuk, D. M. (1970).
        Vapour bubbles growth rate and heat transfer intensity at subcooled
        water boiling.
        In International Heat Transfer Conference 4 (Vol. 23). Begel House Inc.
    \endverbatim

SourceFiles
    TolubinskiKostanchuk.C

\*---------------------------------------------------------------------------*/

#include <departureDiameterModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace wallBoilingModels
    {
        namespace departureDiameterModels
        {

            /*---------------------------------------------------------------------------*\
                                     Class TolubinskiKostanchuk Declaration
            \*---------------------------------------------------------------------------*/

            class TolubinskiKostanchuk
                :
                public departureDiameterModel
            {

                // Private Data:

                    //- Coefficient of the temperature term
                scalar dRef_;

                //- Maximum diameter
                scalar dMax_;

                //- Minimum diameter
                scalar dMin_;

            public:

                //- Runtime type information
                TypeName("TolubinskiKostanchuk");


                // Constructors

                    //- Construct from a dictionary
                TolubinskiKostanchuk(const dictionary& dict);


                //- Destructor
                virtual ~TolubinskiKostanchuk();


                // Member Functions

                    //- Calculate and return the departure diameter field
                virtual tmp<scalarField> dDeparture
                (
                    const phaseModel& liquid,
                    const phaseModel& vapor,
                    const label patchi,
                    const scalarField& Tl,
                    const scalarField& Tsatw,
                    const scalarField& L
                ) const;

                virtual void write(Ostream& os) const;
            };


            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        } // End namespace departureDiameterModels
    } // End namespace wallBoilingModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_TolubinskiKostanchuk_Header
