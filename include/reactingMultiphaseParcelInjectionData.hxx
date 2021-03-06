#pragma once
#ifndef _reactingMultiphaseParcelInjectionData_Header
#define _reactingMultiphaseParcelInjectionData_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::reactingMultiphaseParcelInjectionData

Description
	Container class to provide injection data for reacting multiphase parcels

SourceFiles
	reactingMultiphaseParcelInjectionData.C

\*---------------------------------------------------------------------------*/

#include <reactingParcelInjectionData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class reactingMultiphaseParcelInjectionData;

	// Forward declaration of friend functions

	FoamLagrangian_EXPORT Ostream& operator<<
		(
			Ostream&,
			const reactingMultiphaseParcelInjectionData&
			);

	FoamLagrangian_EXPORT Istream& operator>>
		(
			Istream&,
			reactingMultiphaseParcelInjectionData&
			);

	/*---------------------------------------------------------------------------*\
				Class reactingMultiphaseParcelInjectionData Declaration
	\*---------------------------------------------------------------------------*/

	class reactingMultiphaseParcelInjectionData
		:
		public reactingParcelInjectionData
	{
	protected:

		// Parcel properties

			//- List of gaseous mass fractions
		scalarList YGas_;

		//- List of liquid mass fractions
		scalarList YLiquid_;

		//- List of solid mass fractions
		scalarList YSolid_;


	public:

		//- Runtime type information
		//TypeName("reactingMultiphaseParcelInjectionData");
		static const char* typeName_() { return "reactingMultiphaseParcelInjectionData"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Null constructor
		FoamLagrangian_EXPORT reactingMultiphaseParcelInjectionData();

		//- Construct from dictionary
		FoamLagrangian_EXPORT reactingMultiphaseParcelInjectionData(const dictionary& dict);

		//- Construct from Istream
		FoamLagrangian_EXPORT reactingMultiphaseParcelInjectionData(Istream& is);


		//-Destructor
		FoamLagrangian_EXPORT virtual ~reactingMultiphaseParcelInjectionData();


		// Access

			//- Return const access to the list of gaseous mass fractions
		inline const scalarList& YGas() const;

		//- Return const access to the list of liquid mass fractions
		inline const scalarList& YLiquid() const;

		//- Return const access to the list of solid mass fractions
		inline const scalarList& YSolid() const;


		// Edit

			//- Return access to the gaseous mass fractions
		inline scalarList& YGas();

		//- Return access to the liquid mass fractions
		inline scalarList& YLiquid();

		//- Return access to the solid mass fractions
		inline scalarList& YSolid();


		// I-O

			//- Ostream operator
		friend FoamLagrangian_EXPORT Ostream& operator<<
			(
				Ostream& os,
				const reactingMultiphaseParcelInjectionData& data
				);

		//- Istream operator
		friend FoamLagrangian_EXPORT Istream& operator>>
			(
				Istream& is,
				reactingMultiphaseParcelInjectionData& data
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <reactingMultiphaseParcelInjectionDataI.hxx>

#endif // !_reactingMultiphaseParcelInjectionData_Header
