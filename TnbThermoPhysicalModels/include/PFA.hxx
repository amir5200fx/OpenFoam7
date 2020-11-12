#pragma once
#ifndef _PFA_Header
#define _PFA_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::chemistryReductionMethods::PFA

Description
	Path flux analysis

SourceFiles
	PFA.C

\*---------------------------------------------------------------------------*/

#include <chemistryReductionMethod.hxx>  // added by amir
#include <labelList.hxx>  // added by amir
#include <IOdictionary.hxx>  // added by amir
#include <scalarField.hxx>  // added by amir

#ifdef FoamThermophysicalModels_EXPORT_DEFINE
#define FoamPFA_EXPORT __declspec(dllexport)
#else
#ifdef FoamPFA_EXPORT_DEFINE
#define FoamPFA_EXPORT __declspec(dllexport)
#else
#define FoamPFA_EXPORT __declspec(dllimport)
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
								   Class ode Declaration
		\*---------------------------------------------------------------------------*/

		template<class CompType, class ThermoType>
		class PFA
			:
			public chemistryReductionMethod<CompType, ThermoType>
		{
			// Private Data

				//- List of label for the search initiating set
			labelList searchInitSet_;


		public:

			//- Runtime type information
			//TypeName("PFA");
			static const char* typeName_() { return "PFA"; }
			static FoamPFA_EXPORT const ::tnbLib::word typeName;
			static FoamPFA_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			PFA
			(
				const IOdictionary& dict,
				TDACChemistryModel<CompType, ThermoType>& chemistry
			);


			//- Destructor
			virtual ~PFA();


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

#include <PFAI.hxx>

//#ifdef NoRepository
//#include <PFA.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_PFA_Header
