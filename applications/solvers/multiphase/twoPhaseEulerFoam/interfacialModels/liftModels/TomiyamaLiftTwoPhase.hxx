#pragma once
#ifndef _TomiyamaLiftTwoPhase_Header
#define _TomiyamaLiftTwoPhase_Header

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
    tnbLib::liftModels::TomiyamaLift

Description
    Lift model of Tomiyama et al.

    Reference:
    \verbatim
        "Transverse migration of single bubbles in simple shear flows"
        Tomiyama, A., Tamai, H., Zun, I., Hosokawa, S.,
        Chemical Engineering Science
        Volume 57, Issue 11, June 2002, pp. 1849-1858
    \endverbatim

    The coefficient for pow3(EoH) proposed by Tomiyama (2002) has been modified
    to make the model continuous at EoH = 10.7 while maintaining the
    lift coefficient proposed by Tomiyama (2002) when EoH >= 10.7.

SourceFiles
    TomiyamaLiftTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "liftModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace liftModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class TomiyamaLift Declaration
        \*---------------------------------------------------------------------------*/

        class TomiyamaLift
            :
            public liftModel
        {
        public:

            //- Runtime type information
            TypeName("Tomiyama");


            // Constructors

                //- Construct from a dictionary and a phase pair
            TomiyamaLift
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            virtual ~TomiyamaLift();


            // Member Functions

                //- Lift coefficient
            virtual tmp<volScalarField> Cl() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace liftModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_TomiyamaLiftTwoPhase_Header
