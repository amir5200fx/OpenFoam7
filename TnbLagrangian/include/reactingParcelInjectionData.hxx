#pragma once
#ifndef _reactingParcelInjectionData_Header
#define _reactingParcelInjectionData_Header

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
	tnbLib::reactingParcelInjectionData

Description
	Container class to provide injection data for reacting parcels

SourceFiles
	reactingParcelInjectionData.C

\*---------------------------------------------------------------------------*/

#include <thermoParcelInjectionData.hxx>
#include <scalarList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class reactingParcelInjectionData;

	// Forward declaration of friend functions

	FoamLagrangian_EXPORT Ostream& operator<<
		(
			Ostream&,
			const reactingParcelInjectionData&
			);

	FoamLagrangian_EXPORT Istream& operator>>
		(
			Istream&,
			reactingParcelInjectionData&
			);

	/*---------------------------------------------------------------------------*\
				   Class reactingParcelInjectionData Declaration
	\*---------------------------------------------------------------------------*/

	class reactingParcelInjectionData
		:
		public thermoParcelInjectionData
	{
	protected:

		// Parcel properties

			//- List of mass fractions
		scalarList Y_;


	public:

		//- Runtime type information
		//TypeName("reactingParcelInjectionData");
		static const char* typeName_() { return "reactingParcelInjectionData"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Null constructor
		FoamLagrangian_EXPORT reactingParcelInjectionData();

		//- Construct from dictionary
		FoamLagrangian_EXPORT reactingParcelInjectionData(const dictionary& dict);

		//- Construct from Istream
		FoamLagrangian_EXPORT reactingParcelInjectionData(Istream& is);


		//-Destructor
		FoamLagrangian_EXPORT virtual ~reactingParcelInjectionData();


		// Access

			//- Return const access to the list of mass fractions
		inline const scalarList& Y() const;


		// Edit

			//- Return access to the mass fractions
		inline scalarList& Y();


		// I-O

			//- Ostream operator
		friend FoamLagrangian_EXPORT Ostream& operator<<
			(
				Ostream& os,
				const reactingParcelInjectionData& data
				);

		//- Istream operator
		friend FoamLagrangian_EXPORT Istream& operator>>
			(
				Istream& is,
				reactingParcelInjectionData& data
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <reactingParcelInjectionDataI.hxx>

#endif // !_reactingParcelInjectionData_Header
