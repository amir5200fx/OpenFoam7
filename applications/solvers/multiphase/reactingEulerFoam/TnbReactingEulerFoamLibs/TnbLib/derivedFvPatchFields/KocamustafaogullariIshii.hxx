#pragma once
#ifndef _KocamustafaogullariIshii_Header
#define _KocamustafaogullariIshii_Header

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
    tnbLib::wallBoilingModels::departureDiameterModels::KocamustafaogullariIshii

Description
    A correlation for bubble departure diameter.

    Requires model parameter 'phi': contact angle in degrees.

    Reference:
    \verbatim
        Kocamustafaogullari, G., & Ishii, M. (1983).
        Interfacial area and nucleation site density in boiling systems.
        International Journal of Heat and Mass Transfer, 26(9), 1377-1387.
    \endverbatim

SourceFiles
    KocamustafaogullariIshii.C

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
                                     Class KocamustafaogullariIshii Declaration
            \*---------------------------------------------------------------------------*/

            class KocamustafaogullariIshii
                :
                public departureDiameterModel
            {
                // Private Data

                    //- Contact angle
                scalar phi_;


            public:

                //- Runtime type information
                TypeName("KocamustafaogullariIshii");

                // Constructors

                    //- Construct from a dictionary
                KocamustafaogullariIshii(const dictionary& dict);


                //- Destructor
                virtual ~KocamustafaogullariIshii();


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

#endif // !_KocamustafaogullariIshii_Header
