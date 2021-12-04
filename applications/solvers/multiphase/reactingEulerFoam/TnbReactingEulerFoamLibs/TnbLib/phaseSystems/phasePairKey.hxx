#pragma once
#ifndef _phasePairKey_Header
#define _phasePairKey_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2014-2019 OpenFOAM Foundation
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
    tnbLib::phasePairKey

Description

SourceFiles

\*---------------------------------------------------------------------------*/

#include <reactingEulerFoamLibs_Module.hxx>

#include <Pair.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    // Forward declaration of friend functions and operators

    class phasePairKey;

    FoamReactingEulerFoamLibs_EXPORT bool operator==(const phasePairKey&, const phasePairKey&);
    FoamReactingEulerFoamLibs_EXPORT bool operator!=(const phasePairKey&, const phasePairKey&);

    FoamReactingEulerFoamLibs_EXPORT Istream& operator>>(Istream&, phasePairKey&);
    FoamReactingEulerFoamLibs_EXPORT Ostream& operator<<(Ostream&, const phasePairKey&);


    /*---------------------------------------------------------------------------*\
                             Class phasePairKey Declaration
    \*---------------------------------------------------------------------------*/

    class phasePairKey
        :
        public Pair<word>
    {
    public:

        class hash
            :
            public Hash<phasePairKey>
        {
        public:

            // Constructors

                // Construct null
            hash();


            // Member Operators

                // Generate a hash from a phase pair key
            label operator()(const phasePairKey& key) const;
        };


    private:

        // Private Data

            //- Flag to indicate whether ordering is important
        bool ordered_;


    public:

        // Constructors

            //- Construct null
        FoamReactingEulerFoamLibs_EXPORT phasePairKey();

        //- Construct from names and the ordering flag
        FoamReactingEulerFoamLibs_EXPORT phasePairKey
        (
            const word& name1,
            const word& name2,
            const bool ordered = false
        );


        // Destructor
        FoamReactingEulerFoamLibs_EXPORT virtual ~phasePairKey();


        // Access

            //- Return the ordered flag
        FoamReactingEulerFoamLibs_EXPORT bool ordered() const;


        // Friend Operators

            //- Test if keys are equal
        friend FoamReactingEulerFoamLibs_EXPORT bool operator==(const phasePairKey& a, const phasePairKey& b);

        //- Test if keys are unequal
        friend FoamReactingEulerFoamLibs_EXPORT bool operator!=(const phasePairKey& a, const phasePairKey& b);

        //- Read from stdin
        friend FoamReactingEulerFoamLibs_EXPORT Istream& operator>>(Istream& is, phasePairKey& key);

        //- Write to stdout
        friend FoamReactingEulerFoamLibs_EXPORT Ostream& operator<<(Ostream& os, const phasePairKey& key);
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_phasePairKey_Header