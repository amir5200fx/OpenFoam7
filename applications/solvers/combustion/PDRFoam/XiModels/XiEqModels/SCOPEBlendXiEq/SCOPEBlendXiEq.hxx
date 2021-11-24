#pragma once
#ifndef _SCOPEBlendXiEq_Header
#define _SCOPEBlendXiEq_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpentnbLib: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://opentnbLib.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpentnbLib Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpentnbLib.

    OpentnbLib is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpentnbLib is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpentnbLib.  If not, see <http://www.gnu.org/licenses/>.

Class
    tnbLib::XiEqModels::SCOPEBlend

Description
    Simple SCOPEBlendXiEq model for XiEq based on SCOPEXiEqs correlation
    with a linear correction function to give a plausible profile for XiEq.
    See @link SCOPELaminarFlameSpeed.H @endlink for details on the SCOPE
    laminar flame speed model.

SourceFiles
    SCOPEBlend.C

\*---------------------------------------------------------------------------*/

#include <XiEqModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace XiEqModels
    {

        /*---------------------------------------------------------------------------*\
                                  Class SCOPEBlend Declaration
        \*---------------------------------------------------------------------------*/

        class SCOPEBlend
            :
            public XiEqModel
        {
            // Private Data

                //- Low turbulence intensity equilibrium Xi model
            autoPtr<XiEqModel> XiEqModelL_;

            //- High turbulence intensity equilibrium Xi model
            autoPtr<XiEqModel> XiEqModelH_;


        public:

            //- Runtime type information
            TypeName("SCOPEBlend");


            // Constructors

                //- Construct from components
            SCOPEBlend
            (
                const dictionary& XiEqProperties,
                const psiuReactionThermo& thermo,
                const compressible::RASModel& turbulence,
                const volScalarField& Su
            );

            //- Disallow default bitwise copy construction
            SCOPEBlend(const SCOPEBlend&);


            //- Destructor
            virtual ~SCOPEBlend();


            // Member Functions

                //- Return the flame-wrinking XiEq
            virtual tmp<volScalarField> XiEq() const;

            //- Update properties from given dictionary
            virtual bool read(const dictionary& XiEqProperties)
            {
                return true;
            }


            // Member Operators

                //- Disallow default bitwise assignment
            void operator=(const SCOPEBlend&) = delete;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace XiEqModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SCOPEBlendXiEq_Header
