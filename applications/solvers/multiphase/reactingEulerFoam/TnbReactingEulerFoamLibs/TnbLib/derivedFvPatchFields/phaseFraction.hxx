#pragma once
#ifndef _phaseFraction_Header
#define _phaseFraction_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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
    tnbLib::wallBoilingModels::partitioningModels::phaseFraction

Description
    Wall heat-flux partitioned according to the phase volume fraction.

SourceFiles
    phaseFraction.C

\*---------------------------------------------------------------------------*/

#include <partitioningModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace wallBoilingModels
    {
        namespace partitioningModels
        {

            /*---------------------------------------------------------------------------*\
                                     Class phaseFraction Declaration
            \*---------------------------------------------------------------------------*/

            class phaseFraction
                :
                public partitioningModel
            {

            public:

                //- Runtime type information
                TypeName("phaseFraction");


                // Constructors

                    //- Construct from a dictionary
                phaseFraction(const dictionary& dict);


                //- Destructor
                virtual ~phaseFraction();


                // Member Functions

                    //- Calculate and return the wall heat-flux partitioning
                virtual tmp<scalarField> fLiquid(const scalarField& alphaLiquid) const;
            };


            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        } // End namespace partitioningModels
    } // End namespace wallBoilingModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_phaseFraction_Header
