#pragma once
#ifndef _LaakkonenAlopaeusAittamaaDsd_Header
#define _LaakkonenAlopaeusAittamaaDsd_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2018 OpenFOAM Foundation
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
    tnbLib::diameterModels::daughterSizeDistributionModels::
    LaakkonenAlopaeusAittamaaDsd

Description
    Daughter size distribution model used by Laakkonen et al. (2006). Note that
    it must be multiplied by the number of daughter particles (2). Also, the
    coefficient C4 needs to be set to the value of 2 as to ensure number and
    mass conservation following Kumar and Ramkrishna (1996). Also the internal
    coordinate was changed to particle volume, which gives

    \f[
        \frac{60}{v_j} \left(\frac{v_i}{v_j}\right)^{2}
        \left(1 - \frac{v_i}{v_j}\right)^{2}
    \f]

    where

    \vartable
        v_i         |  Volume of daughter bubble i [m]
        v_j         |  Volume of mother bubble j [m]
    \endvartable

    References:
    \verbatim
        Laakkonen, M., Alopaeus, V., & Aittamaa, J. (2006).
        Validation of bubble breakage, coalescence and mass transfer models for
        gas-liquid dispersion in agitated vessel.
        Chemical engineering science, 61(1), 218-228.
        Eq. 3, p. 220.
    \endverbatim

    \verbatim
        Kumar, S., & Ramkrishna, D. (1996).
        On the solution of population balance equations by discretization-I.
        A fixed pivot technique.
        Chemical Engineering Science, 51(8), 1311-1332.
        Eq. 33, p. 1318.
    \endverbatim

Usage
    \table
        Property     | Description             | Required    | Default value
        C1           | Coefficient C1          | no          | 6.0
        C2           | Coefficient C2          | no          | 0.04
        C3           | Coefficient C3          | no          | 0.01
    \endtable

SourceFiles
    LaakkonenAlopaeusAittamaaBinaryBreakup.C

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
                                  Class LaakkonenAlopaeusAittamaaDsd Declaration
            \*---------------------------------------------------------------------------*/

            class LaakkonenAlopaeusAittamaaDsd
                :
                public daughterSizeDistributionModel
            {
            public:

                //- Runtime type information
                TypeName("LaakkonenAlopaeusAittamaa");


                // Constructor

                FoamReactingEulerFoamLibs_EXPORT LaakkonenAlopaeusAittamaaDsd
                (
                    const breakupModel& breakup,
                    const dictionary& dict
                );


                //- Destructor
                FoamReactingEulerFoamLibs_EXPORT virtual ~LaakkonenAlopaeusAittamaaDsd();


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

#endif // !_LaakkonenAlopaeusAittamaaDsd_Header
