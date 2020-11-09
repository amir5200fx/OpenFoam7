#pragma once
#ifndef _SLGThermo_Header
#define _SLGThermo_Header

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
	tnbLib::SLGThermo

Description
	Thermo package for (S)olids (L)iquids and (G)ases
	Takes reference to thermo package, and provides:
	- carrier : components of thermo - access to elemental properties
	- liquids : liquid components - access  to elemental properties
	- solids  : solid components - access  to elemental properties

	If thermo is not a multi-component thermo package, carrier is nullptr.
	Similarly, if no liquids or solids are specified, their respective
	pointers will also be nullptr.

	Registered to the mesh so that it can be looked-up

SourceFiles
	SLGThermo.C

\*---------------------------------------------------------------------------*/

#include <regIOobject.hxx>
#include <fluidThermo.hxx>
#include <basicSpecieMixture.hxx>
#include <liquidMixtureProperties.hxx>
#include <solidMixtureProperties.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class SLGThermo Declaration
	\*---------------------------------------------------------------------------*/

	class SLGThermo
		:
		public regIOobject
	{
		// Private Data

			//- Thermo package
		fluidThermo& thermo_;

		//- Reference to the multi-component carrier phase thermo
		basicSpecieMixture* carrier_;

		//- Additional liquid properties data
		autoPtr<liquidMixtureProperties> liquids_;

		//- Additional solid properties data
		autoPtr<solidMixtureProperties> solids_;


	public:

		//- Runtime type information
		//TypeName("SLGThermo");
		static const char* typeName_() { return "SLGThermo"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from mesh
		FoamThermophysicalModels_EXPORT SLGThermo(const fvMesh& mesh, fluidThermo& thermo);


		//- Destructor
		FoamThermophysicalModels_EXPORT virtual ~SLGThermo();


		// Member Functions

			// Access

				//- Return reference to the thermo database
		FoamThermophysicalModels_EXPORT const fluidThermo& thermo() const;

		//- Return reference to the gaseous components
		FoamThermophysicalModels_EXPORT const basicSpecieMixture& carrier() const;

		//- Return reference to the global (additional) liquids
		FoamThermophysicalModels_EXPORT const liquidMixtureProperties& liquids() const;

		//- Return reference to the global (additional) solids
		FoamThermophysicalModels_EXPORT const solidMixtureProperties& solids() const;


		// Index retrieval

			//- Index of carrier component
		FoamThermophysicalModels_EXPORT label carrierId
		(
			const word& cmptName,
			bool allowNotFound = false
		) const;

		//- Index of liquid component
		FoamThermophysicalModels_EXPORT label liquidId
		(
			const word& cmptName,
			bool allowNotFound = false
		) const;

		//- Index of solid component
		FoamThermophysicalModels_EXPORT label solidId
		(
			const word& cmptName,
			bool allowNotFound = false
		) const;


		// Checks

			//- Thermo database has multi-component carrier flag
		FoamThermophysicalModels_EXPORT bool hasMultiComponentCarrier() const;

		//- Thermo database has liquid components flag
		FoamThermophysicalModels_EXPORT bool hasLiquids() const;

		//- Thermo database has solid components flag
		FoamThermophysicalModels_EXPORT bool hasSolids() const;


		// IO

		bool writeData(tnbLib::Ostream&) const
		{
			return true;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SLGThermo_Header
