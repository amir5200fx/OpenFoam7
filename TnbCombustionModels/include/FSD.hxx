#pragma once
#ifndef _FSD_Header
#define _FSD_Header

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
	tnbLib::combustionModels::FSD

Description

	Flame Surface Dennsity (FDS) combustion model.

	The fuel source term is given by mgft*pc*omegaFuelBar.

	where:
		  mgft: filtered flame area.
		  pc:   probability of the combustion progress.
		  omegaFuelBar: filtered consumption speed per unit of flame area.

	pc is considered from the IFC solution.
	omegaFuelBar is calculated solving a relaxation equation which tends to
	omegaEq. This omegaEq is obtained from the flamelet solution for
	different strain rates and fit using a expential distribution.

	The spacial distribution of the consumption speed (omega) is obtained also
	from a strained flamelet solution and it is assumed to have a gaussian
	distribution.

	If the grid resolution is not enough to resolve the flame, the consumption
	speed distribution is linearly thickened conserving the overall heat
	release.

	If the turbulent fluctuation of the mixture fraction at the sub-grid level
	is large (>1e-04) then a beta pdf is used for filtering.

	At the moment the flame area combustion model is only fit to work in a LES
	frame work. In RAS the subgrid fluctuation has to be solved by an extra
	transport equation.

SourceFiles
	FSD.C

\*---------------------------------------------------------------------------*/

#include <singleStepCombustion.hxx>
#include <reactionRateFlameArea.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef FoamCombustionModels_EXPORT_DEFINE
#define FoamFSD_EXPORT __declspec(dllexport)
#else
#ifdef FoamFSD_EXPORT_DEFINE
#define FoamFSD_EXPORT __declspec(dllexport)
#else
#define FoamFSD_EXPORT __declspec(dllimport)
#endif
#endif

namespace tnbLib
{
	namespace combustionModels
	{

		/*---------------------------------------------------------------------------*\
								  Class FSD Declaration
		\*---------------------------------------------------------------------------*/

		template<class ReactionThermo, class ThermoType>
		class FSD
			:
			public singleStepCombustion <ReactionThermo, ThermoType>
		{
			// Private Data

				//- Auto pointer to consumption speed per unit of flame area model
			autoPtr<reactionRateFlameArea> reactionRateFlameArea_;

			//- Mixture fraction
			volScalarField ft_;

			//- Fuel mass concentration on the fuel stream
			dimensionedScalar YFuelFuelStream_;

			//- Oxygen mass concentration on the oxydizer stream
			dimensionedScalar YO2OxiStream_;

			//- Similarity constant for the sub-grid ft fluctuations
			scalar Cv_;

			//- Model constant
			scalar C_;

			//- Lower flammability limit
			scalar ftMin_;

			//- Upper flammability limit
			scalar ftMax_;

			//- Dimension of the ft space. Used to integrate the beta-pdf
			scalar ftDim_;

			//- Minimum mixture freaction variance to calculate pdf
			scalar ftVarMin_;


			// Private Member Functions

				//- Calculate the normalised fuel source term
			void calculateSourceNorm();


		public:

			//- Runtime type information
			//TypeName("FSD");
			static const char* typeName_() { return "FSD"; }
			static FoamFSD_EXPORT const ::tnbLib::word typeName;
			static FoamFSD_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FSD
			(
				const word& modelType,
				ReactionThermo& thermo,
				const compressibleTurbulenceModel& turb,
				const word& combustionProperties
			);

			//- Disallow default bitwise copy construction
			FSD(const FSD&);


			//- Destructor
			virtual ~FSD();


			// Member Functions

				//- Correct combustion rate
			virtual void correct();

			//- Update properties
			virtual bool read();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const FSD&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace combustionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <FSDI.hxx>

//#ifdef NoRepository
//#include "FSD.cxx"
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_FSD_Header
