#pragma once
#ifndef _piecewiseLinearRamp_Header
#define _piecewiseLinearRamp_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
    tnbLib::piecewiseLinearRamp

Description
    A linear ramp between 0 and 1 with definable start and end points.

SourceFiles
    piecewiseLinearRamp.C

\*---------------------------------------------------------------------------*/

#include <faceAreaWeightModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                               Class piecewiseLinearRamp Declaration
    \*---------------------------------------------------------------------------*/

    class piecewiseLinearRamp
        :
        public faceAreaWeightModel
    {

    private:

        // Private Data

            //- Face area fraction below which a weight of 0 is returned
        scalar lAF_;

        //- Face area fraction above which a which of 1 is returned
        scalar uAF_;

    public:

        //- Runtime type information
        /*TypeName("piecewiseLinearRamp");*/
        static const char* typeName_() { return "piecewiseLinearRamp"; }
        static FoamFoamyMesh_EXPORT const ::tnbLib::word typeName;
        static FoamFoamyMesh_EXPORT int debug;
        virtual const word& type() const { return typeName; };

        // Constructors

            //- Construct from components
        FoamFoamyMesh_EXPORT piecewiseLinearRamp
        (
            const dictionary& faceAreaWeightDict
        );


        //- Destructor
        FoamFoamyMesh_EXPORT virtual ~piecewiseLinearRamp()
        {}


        // Member Functions

            //- Return the faceAreaWeight
        FoamFoamyMesh_EXPORT virtual scalar faceAreaWeight(scalar faceAreaFraction) const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_piecewiseLinearRamp_Header
