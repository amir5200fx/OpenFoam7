#pragma once
#ifndef _mixtureFraction_Header
#define _mixtureFraction_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::radiationModels::sootModels::mixtureFraction

Description
	This soot model is purely an state model. The amount of soot produced is
	determined by a single step chemistry as :

		nuf Fuel + nuOx Ox = nuP P + nuSoot soot

	nuSoot is prescribed by the user.

	The single step chemistry used is read from the combustion.
	The soot is not considered into the thermodynamics of the system and it
	is not considered as an extra specie in the solver.

	The spacial distribution is given by the normalization of the first product
	on the rhs of the reaction by default or it can be added as input.

	The input dictionary reads like in the radiationProperties dictionary:

	sootModel mixtureFraction<gasHThermoPhysics>;

	mixtureFractionSootCoeffs
	{
		nuSoot              0.015;
		Wsoot               12;
		mappingField        P;
	}

SourceFiles
	mixtureFraction.C

\*---------------------------------------------------------------------------*/

#include <interpolationLookUpTable.hxx>
#include <sootModel.hxx>
#include <HashTable.hxx>

#include <fluidThermo.hxx>
#include <singleStepReactingMixture.hxx>

#ifdef FoamRadiationModels_EXPORT_DEFINE
#define FoammixtureFraction_EXPORT __declspec(dllexport)
#else
#ifdef FoammixtureFraction_EXPORT_DEFINE
#define FoammixtureFraction_EXPORT __declspec(dllexport)
#else
#define FoammixtureFraction_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace sootModels
		{

			/*---------------------------------------------------------------------------*\
								 Class mixtureFraction Declaration
			\*---------------------------------------------------------------------------*/

			template<class ThermoType>
			class mixtureFraction
				:
				public sootModel
			{
				// Static functions

					//- Check mixture in thermo
				static const singleStepReactingMixture<ThermoType>& checkThermo
				(
					const fluidThermo&
				);


				// Private Data

					 //- Soot mass fraction
				volScalarField soot_;

				//- Soot model dictionary
				dictionary coeffsDict_;

				//- Soot yield
				scalar nuSoot_;

				//- Soot molecular weight
				scalar Wsoot_;

				//- Maximum soot mass concentration at stoichiometric
				scalar sootMax_;

				//- Name of the field mapping the soot
				word mappingFieldName_;

				//- Maximum value of the map field
				scalar mapFieldMax_;

				//- Thermo package
				const fluidThermo& thermo_;

				//- Auto Ptr to singleStepReactingMixture
				const singleStepReactingMixture<ThermoType>& mixture_;


			public:

				//- Runtime type information
				//TypeName("mixtureFraction");
				static const char* typeName_() { return "mixtureFraction"; }
				static FoammixtureFraction_EXPORT const ::tnbLib::word typeName;
				static FoammixtureFraction_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from components
				mixtureFraction
				(
					const dictionary& dict,
					const fvMesh& mesh,
					const word& modelType
				);


				//- Destructor
				virtual ~mixtureFraction();


				// Member Functions

					// Edit

						//- Main update/correction routine
				virtual void correct();


				// Access

					//- Return Ysoot
				const volScalarField& soot() const
				{
					return soot_;
				}

			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace sootModels
	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <mixtureFractionI.hxx>

//#ifdef NoRepository
//#include <mixtureFraction.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_mixtureFraction_Header
