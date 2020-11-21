#pragma once
#ifndef _scalarTransport_Header
#define _scalarTransport_Header

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
	tnbLib::functionObjects::scalarTransport

Description
	Evolves a passive scalar transport equation.

	- To specify the field name set the \c field entry
	- To employ the same numerical schemes as another field set
	  the \c schemesField entry,
	- A constant diffusivity may be specified with the \c D entry,

	- Alternatively if a turbulence model is available a turbulent diffusivity
	  may be constructed from the laminar and turbulent viscosities using the
	  optional diffusivity coefficients \c alphaD and \c alphaDt (which default
	  to 1):
	  \verbatim
		  D = alphaD*nu + alphaDt*nut
	  \endverbatim

See also
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	scalarTransport.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <volFields.hxx>
#include <fvOptionList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							   Class scalarTransport Declaration
		\*---------------------------------------------------------------------------*/

		class scalarTransport
			:
			public fvMeshFunctionObject
		{
			// Private Data

				//- Name of field to process
			word fieldName_;

			//- Name of flux field (optional)
			word phiName_;

			//- Name of density field (optional)
			word rhoName_;

			//- Diffusion coefficient (optional)
			scalar D_;

			//- Flag to indicate whether a constant, uniform D_ is specified
			bool constantD_;

			//- Laminar diffusion coefficient (optional)
			scalar alphaD_;

			//- Turbulent diffusion coefficient (optional)
			scalar alphaDt_;

			//- Number of corrector iterations (optional)
			label nCorr_;

			//- Name of field whose schemes are used (optional)
			word schemesField_;

			//- Run-time selectable finite volume options, e.g. sources, constraints
			fv::optionList fvOptions_;

			//- The scalar field
			volScalarField s_;


			// Private Member Functions

				//- Return the diffusivity field
			FoamFunctionObjects_EXPORT tmp<volScalarField> D(const surfaceScalarField& phi) const;


		public:

			//- Runtime type information
			//TypeName("scalarTransport");
			static const char* typeName_() { return "scalarTransport"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT scalarTransport
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT scalarTransport(const scalarTransport&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~scalarTransport();


			// Member Functions

				//- Read the scalarTransport data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Calculate the scalarTransport
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Do nothing.
			//  The volScalarField is registered and written automatically
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const scalarTransport&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_scalarTransport_Header
