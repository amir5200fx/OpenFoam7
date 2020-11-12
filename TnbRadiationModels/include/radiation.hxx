#pragma once
#ifndef _radiation_Header
#define _radiation_Header

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
	tnbLib::fv::radiation

Description
	Calculates and applies the radiation source to the energy equation.

Usage
	Example usage:
	\verbatim
	radiationCoeffs
	{
		fields          (h);                    // Name of energy field
	}
	\endverbatim

SourceFiles
	radiation.C

\*---------------------------------------------------------------------------*/

#include <fvOption.hxx>
#include <uniformDimensionedFields.hxx>
#include <radiationModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
					   Class radiation Declaration
		\*---------------------------------------------------------------------------*/

		class radiation
			:
			public option
		{
			// Private Data

				//- The radiation model pointer
			autoPtr<radiationModel> radiation_;


		public:

			//- Runtime type information
			//TypeName("radiation");
			static const char* typeName_() { return "radiation"; }
			static FoamRadiationModels_EXPORT const ::tnbLib::word typeName;
			static FoamRadiationModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from explicit source name and mesh
			FoamRadiationModels_EXPORT radiation
			(
				const word& sourceName,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);

			//- Disallow default bitwise copy construction
			FoamRadiationModels_EXPORT radiation(const radiation&) = delete;


			// Member Functions

				// Evaluate

					//- Add explicit contribution to compressible momentum equation
			FoamRadiationModels_EXPORT virtual void addSup
			(
				const volScalarField& rho,
				fvMatrix<scalar>& eqn,
				const label fieldi
			);


			// IO

				//- Read source dictionary
			FoamRadiationModels_EXPORT virtual bool read(const dictionary& dict);


			// Member Operators

				//- Disallow default bitwise assignment
			FoamRadiationModels_EXPORT void operator=(const radiation&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_radiation_Header
