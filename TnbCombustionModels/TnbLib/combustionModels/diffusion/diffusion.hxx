#pragma once
#ifndef _diffusion_Header
#define _diffusion_Header

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
	tnbLib::combustionModels::diffusion

Description
	Simple diffusion-based combustion model based on the principle mixed is
	burnt. Additional parameter C is used to distribute the heat release rate
	in time.

SourceFiles
	diffusion.C

\*---------------------------------------------------------------------------*/

#include <singleStepCombustion.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef FoamCombustionModels_EXPORT_DEFINE
#define FoamDiffusion_EXPORT __declspec(dllexport)
#else
#ifdef FoamDiffusion_EXPORT_DEFINE
#define FoamDiffusion_EXPORT __declspec(dllexport)
#else
#define FoamDiffusion_EXPORT __declspec(dllimport)
#endif
#endif

namespace tnbLib
{
	namespace combustionModels
	{

		/*---------------------------------------------------------------------------*\
								 Class diffusion Declaration
		\*---------------------------------------------------------------------------*/

		template<class ReactionThermo, class ThermoType>
		class diffusion
			:
			public singleStepCombustion<ReactionThermo, ThermoType>
		{
			// Private Data

				//- Model constant
			scalar C_;

			//- Name of oxidant - default is "O2"
			word oxidantName_;


		public:

			//- Runtime type information
			//TypeName("diffusion");
			static const char* typeName_() { return "diffusion"; }
			static FoamDiffusion_EXPORT const ::tnbLib::word typeName;
			static FoamDiffusion_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			diffusion
			(
				const word& modelType,
				ReactionThermo& thermo,
				const compressibleTurbulenceModel& turb,
				const word& combustionProperties
			);

			//- Disallow default bitwise copy construction
			diffusion(const diffusion&);


			//- Destructor
			virtual ~diffusion();


			// Member Functions

				//- Correct combustion rate
			virtual void correct();

			//- Update properties
			virtual bool read();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const diffusion&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace combustionModels
} // End namespace tnbLib


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <diffusionI.hxx>

//#ifdef NoRepository
//#include "diffusion.cxx"
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_diffusion_Header
