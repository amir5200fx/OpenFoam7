#pragma once
#ifndef _MoragaTwoPhase_Header
#define _MoragaTwoPhase_Header

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
    tnbLib::liftModels::Moraga

Description
    Lift model of Moraga et al.

    References:
    \verbatim
        "Implementation and Comparison of Correlations for interfacial Forces
         in a Gas-Liquid System within an Euler-Euler Framework"
        Otromke, M.,
        PhD Thesis, April 2013
    \endverbatim

    \verbatim
        "Lateral forces on spheres in turbulent uniform shear flow"
        Moraga, F.J., Bonetto, F.J., Lahey, R.T.,
        International Journal of Multiphase Flow
        Volume 25, Issues 6-7, September 1999, pp. 1321-1372
    \endverbatim

SourceFiles
    MoragaTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "liftModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace liftModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class Moraga Declaration
        \*---------------------------------------------------------------------------*/

        class Moraga
            :
            public liftModel
        {
        public:

            //- Runtime type information
            TypeName("Moraga");


            // Constructors

                //- Construct from a dictionary and a phase pair
            Moraga
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            virtual ~Moraga();


            // Member Functions

                //- Lift coefficient
            virtual tmp<volScalarField> Cl() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace liftModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_MoragaTwoPhase_Header
