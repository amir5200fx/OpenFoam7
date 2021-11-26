#pragma once
#ifndef _isotropicDamping_Header
#define _isotropicDamping_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2019 OpenFOAM Foundation
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
	tnbLib::fv::isotropicDamping

Description

	This fvOption applies an implicit damping force to all components of the
	vector field to relax the field towards a specified uniform value.  Its
	intended purpose is to damp the motions of an interface in the region
	approaching an outlet so that no reflections are generated.

	The damping force coefficient \f$\lambda\f$ should be set based on the
	desired level of damping and the residence time of a perturbation through
	the damping zone.  For example, if waves moving at 2 [m/s] are travelling
	through a damping zone 8 [m] in length, then the residence time is 4 [s]. If
	it is deemed necessary to damp for 5 time-scales, then \f$\lambda\f$ should
	be set to equal 5/(4 [s]) = 1.2 [1/s].

Usage
	Example usage:
	\verbatim
	isotropicDamping1
	{
		type            isotropicDamping;

		selectionMode   cellZone;
		cellZone        nearOutlet;

		value           (2 0 0);   // Value towards which the field it relaxed
		lambda          [0 0 -1 0 0 0 0] 1; // Damping coefficient

		timeStart       0;
		duration        1e6;
	}
	\endverbatim

	Example usage with graduated onset:
	\verbatim
	isotropicDamping1
	{
		type            isotropicDamping;

		selectionMode   all;

		// Define the line along which to apply the graduation
		origin          (1200 0 0);
		direction       (1 0 0);

		// Or, define multiple lines
		// origins         ((1200 0 0) (1200 -300 0) (1200 300 0));
		// directions      ((1 0 0) (0 -1 0) (0 1 0));

		scale
		{
			type        halfCosineRamp;
			start       0;
			duration    600;
		}

		value           (2 0 0);   // Value towards which the field it relaxed
		lambda          [0 0 -1 0 0 0 0] 1; // Damping coefficient

		timeStart       0;
		duration        1e6;
	}
	\endverbatim

See also
	tnbLib::fv::damping
	tnbLib::fv::verticalDamping

SourceFiles
	isotropicDamping.C

\*---------------------------------------------------------------------------*/

#include <damping.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
						   Class isotropicDamping Declaration
		\*---------------------------------------------------------------------------*/

		class isotropicDamping
			:
			public damping
		{
			// Private Data

				//- Reference value
			dimensionedVector value_;


			// Private Member Functions

				//- Source term to momentum equation
			FoamFvOptions_EXPORT void add
			(
				const volScalarField::Internal& forceCoeff,
				fvMatrix<vector>& eqn
			);


		public:

			//- Runtime type information
			//TypeName("isotropicDamping");
			static const char* typeName_() { return "isotropicDamping"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvOptions_EXPORT isotropicDamping
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);


			//- Destructor
			virtual ~isotropicDamping()
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

#endif // !_isotropicDamping_Header
