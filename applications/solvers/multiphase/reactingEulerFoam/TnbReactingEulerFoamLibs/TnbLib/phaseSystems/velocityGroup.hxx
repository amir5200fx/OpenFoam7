#pragma once
#ifndef _velocityGroup_Header
#define _velocityGroup_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
    tnbLib::diameterModels::velocityGroup

Description
    This diameterModel is intended for use with a populationBalanceModel in
    order to simulate polydispersed bubbly or particulate flows. It can hold any
    number of sizeGroups from which the Sauter mean diameter is calculated. It
    can also be used as a diameterModel without a populationBalance and would
    then behave like a constantDiameter model. In this case, some arbitrary name
    must be entered for the populationBalance keyword.

Usage
    \table
        Property          | Description
        populationBalance | Name of the corresponding populationBalance
        formFactor        | Form factor for converting diameter into volume
        sizeGroups        | List of sizeGroups
    \endtable

    Example
    \verbatim
    diameterModel   velocityGroup;
    velocityGroupCoeffs
    {
        populationBalance    bubbles;

        formFactor      0.5235987756;

        sizeGroups
        (
            f0{d  1.00e-3; value 0;}
            f1{d  1.08e-3; value 0;}
            f2{d  1.16e-3; value 0.25;}
            f3{d  1.25e-3; value 0.5;}
            f4{d  1.36e-3; value 0.25;}
            f5{d  1.46e-3; value 0;}
            ...
        );
    }
    \endverbatim

See also
    tnbLib::diameterModels::sizeGroup
    tnbLib::diameterModels::populationBalanceModel

SourceFiles
    velocityGroup.C

\*---------------------------------------------------------------------------*/

#include <diameterModel.hxx>
#include <multivariateScheme.hxx>
#include <convectionScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {

        class sizeGroup;

        /*---------------------------------------------------------------------------*\
                                Class velocityGroup Declaration
        \*---------------------------------------------------------------------------*/

        class velocityGroup
            :
            public diameterModel
        {
            // Private Data

                //- Name of the populationBalance this velocityGroup belongs to
            word popBalName_;

            //- Reference field from which the sizeGroup fields are derived
            volScalarField f_;

            //- Form factor relating diameter and volume
            dimensionedScalar formFactor_;

            //- sizeGroups belonging to this velocityGroup
            PtrList<sizeGroup> sizeGroups_;

            //- Sum of sizeGroup volume fractions
            volScalarField fSum_;

            //- Number-based Sauter-mean diameter of the phase
            volScalarField d_;

            //- Multivariate convection scheme
            tmp<fv::convectionScheme<scalar>> mvConvection_;

            //- Table of fields for multivariate convection
            multivariateSurfaceInterpolationScheme<scalar>::fieldTable fields_;

            //- Mass transfer rate
            volScalarField dmdt_;


            // Private Member Functions

            FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> dsm() const;

            FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> fSum() const;

            vFoamReactingEulerFoamLibs_EXPORT oid renormalize();

            FoamReactingEulerFoamLibs_EXPORT tmp<tnbLib::fv::convectionScheme<tnbLib::scalar>> mvconvection() const;


        public:

            //- Runtime type information
            TypeName("velocityGroup");


            // Constructors

                //- Construct from components
            FoamReactingEulerFoamLibs_EXPORT velocityGroup
            (
                const dictionary& diameterProperties,
                const phaseModel& phase
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~velocityGroup();


            // Member Functions

                //- Return name of populationBalance this velocityGroup belongs to
            inline const word& popBalName() const;

            //- Return reference field for sizeGroup's
            inline const volScalarField& f() const;

            //- Return the form factor
            inline const dimensionedScalar& formFactor() const;

            //- Return sizeGroups belonging to this velocityGroup
            inline const PtrList<sizeGroup>& sizeGroups() const;

            //- Return const-reference to multivariate convectionScheme
            inline const tmp<fv::convectionScheme<scalar>>& mvConvection() const;

            //- Return const-reference to the mass transfer rate
            inline const volScalarField& dmdt() const;

            //- Return reference to the mass transfer rate
            inline volScalarField& dmdtRef();

            //- Corrections before populationBalanceModel::solve()
            FoamReactingEulerFoamLibs_EXPORT void preSolve();

            //- Corrections after populationBalanceModel::solve()
            FoamReactingEulerFoamLibs_EXPORT void postSolve();

            //- Read diameterProperties dictionary
            FoamReactingEulerFoamLibs_EXPORT virtual bool read(const dictionary& diameterProperties);

            //- Return the Sauter-mean diameter
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> d() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace diameterModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <velocityGroupI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_velocityGroup_Header
