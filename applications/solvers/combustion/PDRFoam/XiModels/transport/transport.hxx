#pragma once
#ifndef _transport_Header
#define _transport_Header

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
    tnbLib::XiModels::transport

Description
    Simple transport model for Xi based on Gulders correlation
    with a linear correction function to give a plausible profile for Xi.
    See report TR/HGW/10 for details on the Weller two equations model.
    See \link XiModel.H \endlink for more details on flame wrinkling modelling.

SourceFiles
    transport.C

\*---------------------------------------------------------------------------*/

#include <XiModel.hxx>
#include <XiEqModel.hxx>
#include <XiGModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace XiModels
    {

        /*---------------------------------------------------------------------------*\
                                  Class transport Declaration
        \*---------------------------------------------------------------------------*/

        class transport
            :
            public XiModel
        {
            // Private Data

            scalar XiShapeCoef;

            autoPtr<XiEqModel> XiEqModel_;
            autoPtr<XiGModel> XiGModel_;


        public:

            //- Runtime type information
            TypeName("transport");


            // Constructors

                //- Construct from components
            transport
            (
                const dictionary& XiProperties,
                const psiuReactionThermo& thermo,
                const compressible::RASModel& turbulence,
                const volScalarField& Su,
                const volScalarField& rho,
                const volScalarField& b,
                const surfaceScalarField& phi
            );

            //- Disallow default bitwise copy construction
            transport(const transport&);


            //- Destructor
            virtual ~transport();


            // Member Functions

                //- Return the flame diffusivity
            virtual tmp<volScalarField> Db() const;

            //- Add Xi to the multivariateSurfaceInterpolationScheme table
            virtual void addXi
            (
                multivariateSurfaceInterpolationScheme<scalar>::fieldTable& fields
            )
            {
                fields.add(Xi_);
            }

            //- Correct the flame-wrinking Xi
            virtual void correct()
            {
                NotImplemented;
            }

            //- Correct the flame-wrinking Xi using the given convection scheme
            virtual void correct(const fv::convectionScheme<scalar>& mvConvection);

            //- Update properties from given dictionary
            virtual bool read(const dictionary& XiProperties);

            //- Write fields of the XiEq model
            virtual void writeFields()
            {
                XiEqModel_().writeFields();
            }


            // Member Operators

                //- Disallow default bitwise assignment
            void operator=(const transport&) = delete;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace XiModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_transport_Header
