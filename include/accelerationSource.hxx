#pragma once
#ifndef _accelerationSource_Header
#define _accelerationSource_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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
	tnbLib::fv::accelerationSource

Description
	This fvOption applies an explicit acceleration force to components of the
	velocity field.

Usage
	Example usage:
	\verbatim
	accelerationSource
	{
		type        accelerationSource;
		active      on;
		selectionMode all;
		U           U;
		velocity    scale;
		value       (-2.572 0 0);
		scale
		{
			type        halfCosineRamp;
			start       0;
			duration    10;
		}
	}
	\endverbatim

SourceFiles
	accelerationSource.C

\*---------------------------------------------------------------------------*/

#include <cellSetOption.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							   Class accelerationSource Declaration
		\*---------------------------------------------------------------------------*/

		class accelerationSource
			:
			public cellSetOption
		{
			// Private Data

				//- Time-varying velocity
			autoPtr<Function1<vector>> velocity_;


			// Private Member Functions

				//- Source term to momentum equation
			template<class AlphaRhoFieldType>
			void add
			(
				const AlphaRhoFieldType& rho,
				fvMatrix<vector>& eqn,
				const label fieldi
			);


		public:

			//- Runtime type information
			//TypeName("accelerationSource");
			static const char* typeName_() { return "accelerationSource"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvOptions_EXPORT accelerationSource
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);


			//- Destructor
			virtual ~accelerationSource()
			{}


			// Member Functions

				 // Add explicit and implicit contributions

					//- Source term to momentum equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				fvMatrix<vector>& eqn,
				const label fieldi
			);

			//- Source term to compressible momentum equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				const volScalarField& rho,
				fvMatrix<vector>& eqn,
				const label fieldi
			);

			//- Source term to phase momentum equation
			FoamFvOptions_EXPORT virtual void addSup
			(
				const volScalarField& alpha,
				const volScalarField& rho,
				fvMatrix<vector>& eqn,
				const label fieldi
			);


			// IO

				//- Read dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include <accelerationSourceTemplates.cxx>
//#endif

#include <accelerationSourceTemplatesI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_accelerationSource_Header
