#pragma once
#ifndef _cosine_Header
#define _cosine_Header

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
    tnbLib::wallBoilingModels::partitioningModels::cosine

Description
    Cosine wall heat flux partitioning model.

    Proposed threshold liquid fractions:
      - alphaLiquid1 0.1
      - alphaLiquid0 0.05

    \verbatim
        Tentner, A., Lo, S., & Kozlov, V. (2006).
        Advances in computational fluid dynamics modeling
        of two-phase flow in boiling water reactor fuel assemblies.
        In International Conference of Nuclear Engineering,
        Miami, Florida, USA.
    \endverbatim

SourceFiles
    cosine.C

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
                                     Class cosine Declaration
            \*---------------------------------------------------------------------------*/

            class cosine
                :
                public partitioningModel
            {
                // Private Data

                    // Model parameters, threshold liquid phase fractions
                scalar alphaLiquid1_;
                scalar alphaLiquid0_;


            public:

                //- Runtime type information
                TypeName("cosine");


                // Constructors

                    //- Construct from a dictionary
                cosine(const dictionary& dict);


                //- Destructor
                virtual ~cosine();


                // Member Functions

                    //- Calculate and return the wall heat-flux partitioning
                virtual tmp<scalarField> fLiquid(const scalarField& alphaLiquid) const;

                virtual void write(Ostream& os) const;
            };


            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        } // End namespace partitioningModels
    } // End namespace wallBoilingModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cosine_Header