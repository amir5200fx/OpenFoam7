#pragma once
#ifndef _Tenneti_Header
#define _Tenneti_Header

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
    tnbLib::dragModels::Tenneti

Description
    Drag model of Tenneti et al. for monodisperse gas-particle flows obtained
    with particle-resolved direct numerical simulations and accounting for the
    effect of particle ensembles.

    Reference:
    \verbatim
        Tenneti, S., Garg, R., & Subramaniam, S. (2011).
        Drag law for monodisperse gas�solid systems using particle-resolved
        direct numerical simulation of flow past fixed assemblies of spheres.
        International Journal of Multiphase Flow, 37(9), 1072�1092.
    \endverbatim

SourceFiles
    Tenneti.C

\*---------------------------------------------------------------------------*/

#include <dragModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace dragModels
    {

        class SchillerNaumann;

        /*---------------------------------------------------------------------------*\
                                   Class Tenneti Declaration
        \*---------------------------------------------------------------------------*/

        class Tenneti
            :
            public dragModel
        {
            // Private Data

                //- Residual Reynolds Number
            const dimensionedScalar residualRe_;


        public:

            //- Runtime type information
            TypeName("Tenneti");


            // Constructors

                //- Construct from a dictionary and a phase pair
            FoamReactingEulerFoamLibs_EXPORT Tenneti
            (
                const dictionary& dict,
                const phasePair& pair,
                const bool registerObject
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~Tenneti();


            // Member Functions

                //- Drag coefficient
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> CdRe() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace dragModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_Tenneti_Header
