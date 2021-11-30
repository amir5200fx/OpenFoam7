#pragma once
#ifndef _phasePair_Header
#define _phasePair_Header

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
    tnbLib::phasePair

Description

SourceFiles
    phasePair.C

\*---------------------------------------------------------------------------*/

#include <phaseModel.hxx>
#include <phasePairKey.hxx>
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                             Class phasePair Declaration
    \*---------------------------------------------------------------------------*/

    class phasePair
        :
        public phasePairKey
    {
    public:

        // Hash table types

            //- Dictionary hash table
        typedef HashTable<dictionary, phasePairKey, phasePairKey::hash>
            dictTable;

        //- Scalar hash table
        typedef HashTable<scalar, phasePairKey, phasePairKey::hash>
            scalarTable;


    private:

        // Private Data

            //- Phase 1
        const phaseModel& phase1_;

        //- Phase 2
        const phaseModel& phase2_;

        //- Gravitational acceleration
        const uniformDimensionedVectorField& g_;


        // Private Member Functions

            // Etvos number for given diameter
        FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> EoH(const volScalarField& d) const;


    public:

        // Constructors

            //- Construct from two phases and gravity
        FoamReactingEulerFoamLibs_EXPORT phasePair
        (
            const phaseModel& phase1,
            const phaseModel& phase2,
            const bool ordered = false
        );


        //- Destructor
        FoamReactingEulerFoamLibs_EXPORT virtual ~phasePair();


        // Member Functions

            //- Dispersed phase
        FoamReactingEulerFoamLibs_EXPORT virtual const phaseModel& dispersed() const;

        //- Continuous phase
        FoamReactingEulerFoamLibs_EXPORT virtual const phaseModel& continuous() const;

        //- Pair name
        FoamReactingEulerFoamLibs_EXPORT virtual word name() const;

        //- Other pair name
        FoamReactingEulerFoamLibs_EXPORT virtual word otherName() const;

        //- Average density
        FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> rho() const;

        //- Relative velocity magnitude
        FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> magUr() const;

        //- Relative velocity
        FoamReactingEulerFoamLibs_EXPORT tmp<volVectorField> Ur() const;

        //- Reynolds number
        FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> Re() const;

        //- Prandtl number
        FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> Pr() const;

        //- Eotvos number
        FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> Eo() const;

        //- Eotvos number based on hydraulic diameter type 1
        FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> EoH1() const;

        //- Eotvos number based on hydraulic diameter type 2
        FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> EoH2() const;

        //- Surface tension coefficient
        FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> sigma() const;

        //- Morton Number
        FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> Mo() const;

        //- Takahashi Number
        FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> Ta() const;

        //- Aspect ratio
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> E() const;

        // Access

            //- Return phase 1
        inline const phaseModel& phase1() const;

        //- Return phase 2
        inline const phaseModel& phase2() const;

        //- Return true if this phasePair contains the given phase
        inline bool contains(const phaseModel& phase) const;

        //- Return the other phase relative to the given phase
        //  Generates a FatalError if this phasePair does not contain
        //  the given phase
        inline const phaseModel& otherPhase(const phaseModel& phase) const;

        //- Return the index of the given phase. Generates a FatalError if
        //  this phasePair does not contain the given phase
        inline label index(const phaseModel& phase) const;

        //- Return gravitation acceleration
        inline const uniformDimensionedVectorField& g() const;


        //- STL const_iterator
        class const_iterator
        {
            // Private Data

                //- Reference to the pair for which this is an iterator
            const phasePair& pair_;

            //- Current index
            label index_;

            //- Construct an iterator with the given index
            inline const_iterator(const phasePair&, const label index);

        public:

            friend class phasePair;

            // Constructors

                //- Construct from pair, moving to its 'begin' position
            inline explicit const_iterator(const phasePair&);


            // Access

                //- Return the current index
            inline label index() const;


            // Member Operators

            inline bool operator==(const const_iterator&) const;

            inline bool operator!=(const const_iterator&) const;

            inline const phaseModel& operator*() const;
            inline const phaseModel& operator()() const;

            inline const phaseModel& otherPhase() const;

            inline const_iterator& operator++();
            inline const_iterator operator++(int);
        };


        //- const_iterator set to the beginning of the pair
        inline const_iterator cbegin() const;

        //- const_iterator set to beyond the end of the pair
        inline const_iterator cend() const;

        //- const_iterator set to the beginning of the pair
        inline const_iterator begin() const;

        //- const_iterator set to beyond the end of the pair
        inline const_iterator end() const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_phasePair_Header
