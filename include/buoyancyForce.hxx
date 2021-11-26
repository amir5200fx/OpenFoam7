#pragma once
#ifndef _buoyancyForce_Header
#define _buoyancyForce_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
	tnbLib::fv::buoyancyForce

Description
	Calculates and applies the buoyancy force rho*g to the momentum equation
	corresponding to the specified velocity field.

Usage
	Example usage:
	\verbatim
	fields          (U);                    // Name of velocity field
	\endverbatim

SourceFiles
	buoyancyForce.C

\*---------------------------------------------------------------------------*/

#include <fvOption.hxx>
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
					   Class buoyancyForce Declaration
		\*---------------------------------------------------------------------------*/

		class buoyancyForce
			:
			public option
		{
			// Private Data

			uniformDimensionedVectorField g_;


		public:

			//- Runtime type information
			//TypeName("buoyancyForce");
			static const char* typeName_() { return "buoyancyForce"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from explicit source name and mesh
			FoamFvOptions_EXPORT buoyancyForce
			(
				const word& sourceName,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);

			//- Disallow default bitwise copy construction
			buoyancyForce(const buoyancyForce&) = delete;


			// Member Functions

				// Evaluate

					//- Add explicit contribution to incompressible momentum equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				fvMatrix<vector>& eqn,
				const label fieldi
			);

			//- Add explicit contribution to compressible momentum equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				const volScalarField& rho,
				fvMatrix<vector>& eqn,
				const label fieldi
			);


			// IO

				//- Read source dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const buoyancyForce&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_buoyancyForce_Header
