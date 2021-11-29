#pragma once
#ifndef _AttouFerschneider_Header
#define _AttouFerschneider_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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
    tnbLib::dragModels::AttouFerschneider

Description
    Attou and Ferschneider's Drag model for film flow through packed beds. The
    implementation follows the description of Gunjal and Ranade, who, in the
    reference below, formulate the model in more convenient terms.

    Reference:
    \verbatim
        Gunjal, P. R., & Ranade, V. V. (2007).
        Modeling of laboratory and commercial scale hydro-processing reactors
        using CFD.
        Chemical Engineering Science, 62(18-20), 5512-5526.
    \endverbatim

SourceFiles
    AttouFerschneider.C

\*---------------------------------------------------------------------------*/

#include <dragModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;
    class phaseModel;

    namespace dragModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class AttouFerschneider Declaration
        \*---------------------------------------------------------------------------*/

        class AttouFerschneider
            :
            public dragModel
        {
            // Private Data

                //- Name of the gaseous phase
            const word gasName_;

            //- Name of the liquidphase
            const word liquidName_;

            //- Name of the solid phase
            const word solidName_;

            //- Ergun constant 1
            const dimensionedScalar E1_;

            //- Ergun constant 2
            const dimensionedScalar E2_;


            // Private Member Functions

                //- Return the momentum transfer coefficient between gas and liquid
            virtual tmp<volScalarField> KGasLiquid
            (
                const phaseModel& gas,
                const phaseModel& liquid
            ) const;

            //- Return the momentum transfer coefficient between gas and solid
            virtual tmp<volScalarField> KGasSolid
            (
                const phaseModel& gas,
                const phaseModel& solid
            ) const;

            //- Return the momentum transfer coefficient between liquid and solid
            virtual tmp<volScalarField> KLiquidSolid
            (
                const phaseModel& liquid,
                const phaseModel& solid
            ) const;


        public:

            //- Runtime type information
            TypeName("AttouFerschneider");


            // Constructors

                //- Construct from a dictionary and a phase pair
            AttouFerschneider
            (
                const dictionary& dict,
                const phasePair& pair,
                const bool registerObject
            );


            //- Destructor
            virtual ~AttouFerschneider();


            // Member Functions

                //- Drag coefficient
            virtual tmp<volScalarField> CdRe() const;

            //- The drag coefficient used in the momentum equation
            virtual tmp<volScalarField> K() const;

            //- The drag coefficient used in the face-momentum equations
            virtual tmp<surfaceScalarField> Kf() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace dragModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_AttouFerschneider_Header
