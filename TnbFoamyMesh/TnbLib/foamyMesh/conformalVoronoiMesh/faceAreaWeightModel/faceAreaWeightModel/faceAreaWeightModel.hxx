#pragma once
#ifndef _faceAreaWeightModel_Header
#define _faceAreaWeightModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
    tnbLib::faceAreaWeightModel

Description
    Abstract base class for providing faceAreaWeight values to the cell motion
    controller based on an argument faceAreaFraction value, typically the ratio
    of the area of the face in question to the area of a square face with a side
    length of the local target cell size.

SourceFiles
    faceAreaWeightModel.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>

#include <point.hxx>
#include <dictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                           Class faceAreaWeightModel Declaration
    \*---------------------------------------------------------------------------*/

    class faceAreaWeightModel
        :
        public dictionary
    {

    protected:

        // Protected data

            //- Method coeffs dictionary
        dictionary coeffDict_;


    public:

        //- Runtime type information
        TypeName("faceAreaWeightModel");


        // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            faceAreaWeightModel,
            dictionary,
            (
                const dictionary& faceAreaWeightDict
                ),
            (faceAreaWeightDict)
        );


        // Constructors

            //- Construct from components
        FoamFoamyMesh_EXPORT faceAreaWeightModel
        (
            const word& type,
            const dictionary& faceAreaWeightDict
        );

        //- Disallow default bitwise copy construction
        faceAreaWeightModel(const faceAreaWeightModel&) = delete;


        // Selectors

            //- Return a reference to the selected faceAreaWeightModel
        static autoPtr<faceAreaWeightModel> New
        (
            const dictionary& faceAreaWeightDict
        );


        //- Destructor
        FoamFoamyMesh_EXPORT virtual ~faceAreaWeightModel();


        // Member Functions

            //- Const access to the coeffs dictionary
        const dictionary& coeffDict() const
        {
            return coeffDict_;
        }

        //- Return the current faceAreaWeight coefficient
        virtual scalar faceAreaWeight(scalar faceAreaFraction) const = 0;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const faceAreaWeightModel&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_faceAreaWeightModel_Header
