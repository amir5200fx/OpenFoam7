#pragma once
#ifndef _TwoResistanceHeatTransferPhaseSystem_Header
#define _TwoResistanceHeatTransferPhaseSystem_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2015-2018 OpenFOAM Foundation
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
    tnbLib::TwoResistanceHeatTransferPhaseSystem

Description
    Class which models interfacial heat transfer between a number of phases.
    Two heat transfer models are stored at each interface, one for each phase.
    This permits definition of an interface temperature with which heat transfer
    occurs. It also allows derived systems to define other thermodynamic
    properties at the interface and therefore represent phase changes.

See also
    OneResistanceHeatTransferPhaseSystem

SourceFiles
    TwoResistanceHeatTransferPhaseSystem.C

\*---------------------------------------------------------------------------*/

#include <phaseSystem.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    template<class modelType>
    class BlendedInterfacialModel;

    class blendingMethod;
    class heatTransferModel;

    /*---------------------------------------------------------------------------*\
             Class TwoResistanceHeatTransferPhaseSystem Declaration
    \*---------------------------------------------------------------------------*/

    template<class BasePhaseSystem>
    class TwoResistanceHeatTransferPhaseSystem
        :
        public BasePhaseSystem
    {
    protected:

        // Protected typedefs

        typedef HashTable
            <
            Pair<autoPtr<BlendedInterfacialModel<heatTransferModel>>>,
            phasePairKey,
            phasePairKey::hash
            > heatTransferModelTable;


        // Protected data

            //- Interface temperatures
        HashPtrTable<volScalarField, phasePairKey, phasePairKey::hash> Tf_;

        // Sub Models

            //- Heat transfer models
        heatTransferModelTable heatTransferModels_;


    public:

        // Constructors

            //- Construct from fvMesh
        TwoResistanceHeatTransferPhaseSystem(const fvMesh&);


        //- Destructor
        virtual ~TwoResistanceHeatTransferPhaseSystem();


        // Member Functions

            //- Return the heat transfer matrices
        virtual autoPtr<phaseSystem::heatTransferTable> heatTransfer() const;

        //- Correct the energy transport e.g. alphat and Tf
        virtual void correctEnergyTransport();

        //- Correct the interface thermodynamics
        virtual void correctInterfaceThermo();

        //- Read base phaseProperties dictionary
        virtual bool read();
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include "TwoResistanceHeatTransferPhaseSystem.C"
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_TwoResistanceHeatTransferPhaseSystem_Header
