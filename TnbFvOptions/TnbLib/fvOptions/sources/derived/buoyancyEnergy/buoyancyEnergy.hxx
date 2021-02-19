#pragma once
#ifndef _buoyancyEnergy_Header
#define _buoyancyEnergy_Header

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
	tnbLib::fv::buoyancyEnergy

Description
	Calculates and applies the buoyancy energy source rho*(U&g) to the energy
	equation.

Usage
	Example usage:
	\verbatim
	fields          (h);                    // Name of energy field
	\endverbatim

SourceFiles
	buoyancyEnergy.C

\*---------------------------------------------------------------------------*/

#include <fvOptions.hxx>
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
					   Class buoyancyEnergy Declaration
		\*---------------------------------------------------------------------------*/

		class buoyancyEnergy
			:
			public option
		{
			// Private Data

				//- Name of velocity field; default = U
			word UName_;


		public:

			//- Runtime type information
			//TypeName("buoyancyEnergy");
			static const char* typeName_() { return "buoyancyEnergy"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from explicit source name and mesh
			FoamFvOptions_EXPORT buoyancyEnergy
			(
				const word& sourceName,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);

			//- Disallow default bitwise copy construction
			buoyancyEnergy(const buoyancyEnergy&) = delete;


			// Member Functions

				// Evaluate

					//- Add explicit contribution to compressible momentum equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				const volScalarField& rho,
				fvMatrix<scalar>& eqn,
				const label fieldi
			);


			// IO

				//- Read source dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const buoyancyEnergy&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_buoyancyEnergy_Header
