#pragma once
#ifndef _meanVelocityForce_Header
#define _meanVelocityForce_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
	tnbLib::fv::meanVelocityForce

Description
	Calculates and applies the force necessary to maintain the specified mean
	velocity.

	Note: Currently only handles kinematic pressure (incompressible solvers).

Usage
	Example usage:
	\verbatim
	selectionMode   all;                    // Apply force to all cells
	fields          (U);                    // Name of velocity field
	Ubar            (10.0 0 0);             // Desired mean velocity
	relaxation      0.2;                    // Optional relaxation factor
	\endverbatim

SourceFiles
	meanVelocityForce.C

\*---------------------------------------------------------------------------*/

#include <autoPtr.hxx>
#include <topoSetSource.hxx>
#include <cellSet.hxx>
#include <fvMesh.hxx>
#include <volFields.hxx>
#include <cellSetOption.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
					   Class meanVelocityForce Declaration
		\*---------------------------------------------------------------------------*/

		class meanVelocityForce
			:
			public cellSetOption
		{
		protected:

			// Protected data

				//- Average velocity
			vector Ubar_;

			//- Pressure gradient before correction
			scalar gradP0_;

			//- Change in pressure gradient
			scalar dGradP_;

			//- Flow direction
			vector flowDir_;

			//- Relaxation factor
			scalar relaxation_;

			//- Matrix 1/A coefficients field pointer
			autoPtr<volScalarField> rAPtr_;


			// Protected Member Functions

				//- Calculate and return the magnitude of the mean velocity
				//  averaged over the selected cellSet
			FoamFvOptions_EXPORT virtual scalar magUbarAve(const volVectorField& U) const;

			//- Write the pressure gradient to file (for restarts etc)
			FoamFvOptions_EXPORT void writeProps(const scalar gradP) const;

			//- Correct driving force for a constant mass flow rate
			FoamFvOptions_EXPORT void update(fvMatrix<vector>& eqn);


		public:

			//- Runtime type information
			//TypeName("meanVelocityForce");
			static const char* typeName_() { return "meanVelocityForce"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from explicit source name and mesh
			FoamFvOptions_EXPORT meanVelocityForce
			(
				const word& sourceName,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);

			//- Disallow default bitwise copy construction
			meanVelocityForce(const meanVelocityForce&) = delete;


			// Member Functions

				// Evaluate

					//- Correct the pressure gradient
			FoamFvOptions_EXPORT virtual void correct(volVectorField& U);

			//- Add explicit contribution to momentum equation
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

			//- Set 1/A coefficient
			FoamFvOptions_EXPORT virtual void constrain
			(
				fvMatrix<vector>& eqn,
				const label fieldi
			);


			// IO

				//- Read source dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const meanVelocityForce&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_meanVelocityForce_Header
