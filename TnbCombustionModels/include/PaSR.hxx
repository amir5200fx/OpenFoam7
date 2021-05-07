#pragma once
#ifndef _PaSR_Header
#define _PaSR_Header

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
	tnbLib::combustionModels::PaSR

Description
	Partially stirred reactor turbulent combustion model.

	This model calculates a finite rate, based on both turbulence and chemistry
	time scales.  Depending on mesh resolution, the Cmix parameter can be used
	to scale the turbulence mixing time scale.

SourceFiles
	PaSR.C

\*---------------------------------------------------------------------------*/

#include <laminarTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef FoamCombustionModels_EXPORT_DEFINE
#define FoamPaSR_EXPORT __declspec(dllexport)
#else
#ifdef FoamPaSR_EXPORT_DEFINE
#define FoamPaSR_EXPORT __declspec(dllexport)
#else
#define FoamPaSR_EXPORT __declspec(dllimport)
#endif
#endif

namespace tnbLib
{
	namespace combustionModels
	{

		/*---------------------------------------------------------------------------*\
									Class PaSR Declaration
		\*---------------------------------------------------------------------------*/

		template<class ReactionThermo>
		class PaSR
			:
			public laminar<ReactionThermo>
		{
			// Private Data

				//- Mixing constant
			scalar Cmix_;

			//- Mixing parameter
			volScalarField kappa_;


		public:

			//- Runtime type information
			//TypeName("PaSR");
			static const char* typeName_() { return "PaSR"; }
			static FoamPaSR_EXPORT const ::tnbLib::word typeName;
			static FoamPaSR_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			PaSR
			(
				const word& modelType,
				ReactionThermo& thermo,
				const compressibleTurbulenceModel& turb,
				const word& combustionProperties
			);

			//- Disallow default bitwise copy construction
			PaSR(const PaSR&);


			//- Destructor
			virtual ~PaSR();


			// Member Functions

				//- Correct combustion rate
			virtual void correct();

			//- Fuel consumption rate matrix.
			virtual tmp<fvScalarMatrix> R(volScalarField& Y) const;

			//- Heat release rate [kg/m/s^3]
			virtual tmp<volScalarField> Qdot() const;

			//- Update properties from given dictionary
			virtual bool read();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const PaSR&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace combustionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <PaSRI.hxx>

//#ifdef NoRepository
//#include "PaSR.cxx"
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_PaSR_Header