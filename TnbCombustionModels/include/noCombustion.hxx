#pragma once
#ifndef _noCombustion_Header
#define _noCombustion_Header

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
	tnbLib::combustionModels::noCombustion

Description
	Dummy combustion model for 'no combustion'

SourceFiles
	noCombustion.C

\*---------------------------------------------------------------------------*/

#include <ThermoCombustionTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef FoamCombustionModels_EXPORT_DEFINE
#define FoamNoCombustion_EXPORT __declspec(dllexport)
#else
#ifdef FoamNoCombustion_EXPORT_DEFINE
#define FoamNoCombustion_EXPORT __declspec(dllexport)
#else
#define FoamNoCombustion_EXPORT __declspec(dllimport)
#endif
#endif

namespace tnbLib
{
	namespace combustionModels
	{

		/*---------------------------------------------------------------------------*\
								Class noCombustion Declaration
		\*---------------------------------------------------------------------------*/

		template<class ReactionThermo>
		class noCombustion
			:
			public ThermoCombustion<ReactionThermo>
		{
		public:

			//- Runtime type information
			//TypeName("none");
			static const char* typeName_() { return "none"; }
			static FoamNoCombustion_EXPORT const ::tnbLib::word typeName;
			static FoamNoCombustion_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			noCombustion
			(
				const word& modelType,
				ReactionThermo& thermo,
				const compressibleTurbulenceModel& turb,
				const word& combustionProperties
			);

			//- Disallow default bitwise copy construction
			noCombustion(const noCombustion&);


			//- Destructor
			virtual ~noCombustion();


			// Member Functions

				//- Correct combustion rate
			virtual void correct();

			//- Fuel consumption rate matrix
			virtual tmp<fvScalarMatrix> R(volScalarField& Y) const;

			//- Heat release rate [kg/m/s^3]
			virtual tmp<volScalarField> Qdot() const;

			//- Update properties from given dictionary
			virtual bool read();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const noCombustion&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace combustionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <noCombustionI.hxx>

//#ifdef NoRepository
//#include "noCombustion.cxx"
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noCombustion_Header
