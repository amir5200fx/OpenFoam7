#pragma once
#ifndef _thermoParcelInjectionData_Header
#define _thermoParcelInjectionData_Header

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
	tnbLib::thermoParcelInjectionData

Description
	Container class to provide injection data for thermodynamic parcels

SourceFiles
	thermoParcelInjectionData.C

\*---------------------------------------------------------------------------*/

#include <kinematicParcelInjectionData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class thermoParcelInjectionData;

	// Forward declaration of friend functions

	FoamLagrangian_EXPORT Ostream& operator<<
		(
			Ostream&,
			const thermoParcelInjectionData&
			);

	FoamLagrangian_EXPORT Istream& operator>>
		(
			Istream&,
			thermoParcelInjectionData&
			);

	/*---------------------------------------------------------------------------*\
					 Class thermoParcelInjectionData Declaration
	\*---------------------------------------------------------------------------*/

	class thermoParcelInjectionData
		:
		public kinematicParcelInjectionData
	{
	protected:

		// Parcel properties

			//- Temperature [K]
		scalar T_;

		//- Specific heat capacity [J/kg/K]
		scalar Cp_;


	public:

		//- Runtime type information
		//TypeName("thermoParcelInjectionData");
		static const char* typeName_() { return "thermoParcelInjectionData"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Null constructor
		FoamLagrangian_EXPORT thermoParcelInjectionData();

		//- Construct from dictionary
		FoamLagrangian_EXPORT thermoParcelInjectionData(const dictionary& dict);

		//- Construct from Istream
		FoamLagrangian_EXPORT thermoParcelInjectionData(Istream& is);


		//-Destructor
		FoamLagrangian_EXPORT virtual ~thermoParcelInjectionData();


		// Access

			//- Return const access to the temperature
		inline scalar T() const;

		//- Return const access to the specific heat capacity
		inline scalar Cp() const;


		// Edit

			//- Return access to the temperature
		inline scalar& T();

		//- Return access to the specific heat capacity
		inline scalar& Cp();


		// I-O

			//- Ostream operator
		friend FoamLagrangian_EXPORT Ostream& operator<<
			(
				Ostream& os,
				const thermoParcelInjectionData& data
				);

		//- Istream operator
		friend FoamLagrangian_EXPORT Istream& operator>>
			(
				Istream& is,
				thermoParcelInjectionData& data
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <thermoParcelInjectionDataI.hxx>

#endif // !_thermoParcelInjectionData_Header
