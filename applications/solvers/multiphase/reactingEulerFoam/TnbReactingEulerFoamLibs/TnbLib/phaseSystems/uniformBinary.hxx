#pragma once
#ifndef _uniformBinary_Header
#define _uniformBinary_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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
    tnbLib::diameterModels::daughterSizeDistributionModels::uniformBinary

Description
    Uniform binary daughter size distribution. Used for verification and
    validation of the breakup formulation implemented in the
    populationBalanceModel class.

SourceFiles
    uniformBinary.C

\*---------------------------------------------------------------------------*/

#include <daughterSizeDistributionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {
        namespace daughterSizeDistributionModels
        {

            /*---------------------------------------------------------------------------*\
                                  Class uniformBinary Declaration
            \*---------------------------------------------------------------------------*/

            class uniformBinary
                :
                public daughterSizeDistributionModel
            {
            public:

                //- Runtime type information
                TypeName("uniformBinary");


                // Constructor

                FoamReactingEulerFoamLibs_EXPORT uniformBinary
                (
                    const breakupModel& breakup,
                    const dictionary& dict
                );


                //- Destructor
                FoamReactingEulerFoamLibs_EXPORT virtual ~uniformBinary();


                // Member Functions

                    //- Return total number of particles assigned to class i when a particle
                    //  of class k breaks
                FoamReactingEulerFoamLibs_EXPORT virtual dimensionedScalar calcNik(const label i, const label k) const;
            };


            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        } // End namespace daughterSizeDistributionModels
    } // End namespace diameterModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_uniformBinary_Header
