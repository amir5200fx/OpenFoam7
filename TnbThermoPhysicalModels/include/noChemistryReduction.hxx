#pragma once
#ifndef _noChemistryReduction_Header
#define _noChemistryReduction_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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
	tnbLib::chemistryReductionMethods::none

Description

SourceFiles
	noChemistryReduction.C

\*---------------------------------------------------------------------------*/

#include <chemistryReductionMethod.hxx>  // added by amir
#include <IOdictionary.hxx>  // added by amir
#include <scalarField.hxx> // added by amir

#ifdef FoamThermophysicalModels_EXPORT_DEFINE
#define FoamnoChemistryReduction_EXPORT __declspec(dllexport)
#else
#ifdef FoamnoChemistryReduction_EXPORT_DEFINE
#define FoamnoChemistryReduction_EXPORT __declspec(dllexport)
#else
#define FoamnoChemistryReduction_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<class ReactionThermo, class ThermoType>
	class TDACChemistryModel;  // added by amir

	namespace chemistryReductionMethods
	{

		/*---------------------------------------------------------------------------*\
							   Class none Declaration
		\*---------------------------------------------------------------------------*/

		template<class CompType, class ThermoType>
		class none
			:
			public chemistryReductionMethod<CompType, ThermoType>
		{

		public:

			//- Runtime type information
			//TypeName("none");
			static const char* typeName_() { return "none"; }
			static FoamnoChemistryReduction_EXPORT const ::tnbLib::word typeName;
			static FoamnoChemistryReduction_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			none
			(
				const IOdictionary& dict,
				TDACChemistryModel<CompType, ThermoType>& chemistry
			);


			//- Destructor
			virtual ~none();


			// Member Functions

				//- Reduce the mechanism
			virtual void reduceMechanism
			(
				const scalarField &c,
				const scalar T,
				const scalar p
			);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace chemistryReductionMethods
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <noChemistryReductionI.hxx>

//#ifdef NoRepository
//#include <noChemistryReduction.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noChemistryReduction_Header
