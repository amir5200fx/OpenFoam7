#pragma once
#ifndef _solidEqulibriumEnergySource_Header
#define _solidEqulibriumEnergySource_Header

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
	tnbLib::fv::solidEqulibriumEnergySource

Description
	This option adds the thermal inertia of a solid phase into the energy
	equation. It assumes that the solid is in thermal equilibrium with the
	surrounding fluid phase.

	The volume fraction of the solid phase is read from constant/alpha.<phase>,
	and the associated thermophysical properties are specified in
	constant/thermophysicalProperties.<phase>.

Usage
	\table
		Property    | Description                            | Req'd? | Default
		phase       | Name of the solid phase                | yes    |
		field       | Name of the energy field to apply the option to \\
															 | yes    |
	\endtable

	Example specification:
	\verbatim
	<fvOptionName>
	{
		type        solidEqulibriumEnergySource;
		phase       solid;
		field       e;
	}
	\endverbatim

\*---------------------------------------------------------------------------*/

#include <fvOption.hxx>
#include <volFields.hxx>
#include <solidThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
								 Class solidEqulibriumEnergySource Declaration
		\*---------------------------------------------------------------------------*/

		class solidEqulibriumEnergySource
			:
			public option
		{
			// Private Member Data

				//- The name of the phase
			const word phaseName_;

			//- Get the volume fraction field
			FoamFvOptions_EXPORT const volScalarField& alpha() const;

			//- Get the thermo
			FoamFvOptions_EXPORT const solidThermo& thermo() const;


		public:

			//- Runtime type information
			//TypeName("solidEqulibriumEnergySource");
			static const char* typeName_() { return "solidEqulibriumEnergySource"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvOptions_EXPORT solidEqulibriumEnergySource
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);

			//- Disallow default bitwise copy construction
			solidEqulibriumEnergySource
			(
				const solidEqulibriumEnergySource&
			) = delete;


			//- Destructor
			FoamFvOptions_EXPORT virtual ~solidEqulibriumEnergySource();


			// Member Functions

				// Evaluation

					//- Explicit and implicit sources for compressible equations
			FoamFvOptions_EXPORT virtual void addSup
			(
				const volScalarField&,
				fvMatrix<scalar>&,
				const label
			);

			//- Explicit and implicit sources for phase equations
			FoamFvOptions_EXPORT virtual void addSup
			(
				const volScalarField&,
				const volScalarField&,
				fvMatrix<scalar>&,
				const label
			);


			// IO

				//- Read dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const solidEqulibriumEnergySource&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_solidEqulibriumEnergySource_Header
