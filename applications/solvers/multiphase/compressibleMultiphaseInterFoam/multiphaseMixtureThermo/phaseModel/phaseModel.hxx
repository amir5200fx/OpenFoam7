#pragma once
#ifndef _phaseModel_Header
#define _phaseModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
    tnbLib::phaseModel

Description
    Single incompressible phase derived from the phase-fraction.
    Used as part of the multiPhaseMixture for interface-capturing multi-phase
    simulations.

SourceFiles
    phaseModel.C

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <rhoThermo.hxx>
#include <volFields.hxx>
#include <dictionaryEntry.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                               Class phaseModel Declaration
    \*---------------------------------------------------------------------------*/

    class phaseModel
        :
        public volScalarField
    {
        // Private Data

        word name_;
        const volScalarField& p_;
        const volScalarField& T_;
        autoPtr<rhoThermo> thermo_;
        volScalarField dgdt_;


    public:

        // Constructors

            //- Construct from components
        phaseModel
        (
            const word& phaseName,
            const volScalarField& p,
            const volScalarField& T
        );

        //- Return clone
        autoPtr<phaseModel> clone() const;

        //- Return a pointer to a new phaseModel created on freestore
        //  from Istream
        class iNew
        {
            const volScalarField& p_;
            const volScalarField& T_;

        public:

            iNew
            (
                const volScalarField& p,
                const volScalarField& T
            )
                :
                p_(p),
                T_(T)
            {}

            autoPtr<phaseModel> operator()(Istream& is) const
            {
                return autoPtr<phaseModel>(new phaseModel(is, p_, T_));
            }
        };


        // Member Functions

        const word& name() const
        {
            return name_;
        }

        const word& keyword() const
        {
            return name();
        }

        //- Return const-access to phase rhoThermo
        const rhoThermo& thermo() const
        {
            return thermo_();
        }

        //- Return access to phase rhoThermo
        rhoThermo& thermo()
        {
            return thermo_();
        }

        //- Return const-access to phase divergence
        const volScalarField& dgdt() const
        {
            return dgdt_;
        }

        //- Return access to phase divergence
        volScalarField& dgdt()
        {
            return dgdt_;
        }

        void correct();
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_phaseModel_Header
