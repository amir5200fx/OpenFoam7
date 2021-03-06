#pragma once
#ifndef _EFA_Header
#define _EFA_Header

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
	tnbLib::chemistryReductionMethods::EFA

Description

SourceFiles
	EFA.C

\*---------------------------------------------------------------------------*/

#include <chemistryReductionMethod.hxx>  // added by amir
#include <labelList.hxx>  // added by amir
#include <scalar.hxx> // added by amir
#include <typeInfo.hxx>  // added by amir

#ifdef FoamThermophysicalModels_EXPORT_DEFINE
#define FoamEFA_EXPORT __declspec(dllexport)
#else
#ifdef FoamEFA_EXPORT_DEFINE
#define FoamEFA_EXPORT __declspec(dllexport)
#else
#define FoamEFA_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace chemistryReductionMethods
	{

		/*---------------------------------------------------------------------------*\
								   Class ode Declaration
		\*---------------------------------------------------------------------------*/

		template<class CompType, class ThermoType>
		class EFA
			:
			public chemistryReductionMethod<CompType, ThermoType>
		{
			// Private Data

			List<label> sC_, sH_, sO_, sN_;
			scalar  sortPart_;

		public:

			//- Runtime type information
			//TypeName("EFA");
			static const char* typeName_() { return "EFA"; }
			static FoamEFA_EXPORT const ::tnbLib::word typeName;
			static FoamEFA_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			EFA
			(
				const IOdictionary& dict,
				TDACChemistryModel<CompType, ThermoType>& chemistry
			);


			//- Destructor
			virtual ~EFA();


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

#include <EFAI.hxx>

//#ifdef NoRepository
//#include <EFA.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_EFA_Header
