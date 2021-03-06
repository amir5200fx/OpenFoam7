#pragma once
#ifndef _phaseProperties_Header
#define _phaseProperties_Header

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
	tnbLib::phaseProperties

Description
	Helper class to manage multi-specie phase properties

SourceFiles
	phaseProperties.C
	phasePropertiesIO.C

\*---------------------------------------------------------------------------*/

#include <NamedEnum.hxx>
#include <Tuple2.hxx>
#include <PtrList.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class phaseProperties;

	FoamLagrangian_EXPORT Istream& operator>>(Istream&, phaseProperties&);
	FoamLagrangian_EXPORT Ostream& operator<<(Ostream&, const phaseProperties&);


	/*---------------------------------------------------------------------------*\
						  Class phaseProperties Declaration
	\*---------------------------------------------------------------------------*/

	class phaseProperties
	{
	public:

		// Public data

			//- Phase type enumeration
		enum phaseType
		{
			GAS,
			LIQUID,
			SOLID,
			UNKNOWN
		};

		//- Corresponding word representations for phase type enumerations
		static FoamLagrangian_EXPORT const NamedEnum<phaseType, 4> phaseTypeNames;


	private:

		// Private Data

			 //- Phase type
		phaseType phase_;

		//- State label (s), (l), (g) etc.
		word stateLabel_;

		//- List of specie names
		List<word> names_;

		//- List of specie mass fractions
		scalarField Y_;

		//- Map to carrier id
		labelList carrierIds_;


		// Private Member Functions

			//- Reorder species to be consistent with the given specie name list
		FoamLagrangian_EXPORT void reorder(const wordList& specieNames);

		//- Set carrier ids
		FoamLagrangian_EXPORT void setCarrierIds(const wordList& carrierNames);

		//- Check the total mass fraction
		FoamLagrangian_EXPORT void checkTotalMassFraction() const;

		//- Set the state label
		FoamLagrangian_EXPORT word phaseToStateLabel(const phaseType pt) const;


	public:

		// Constructors

			//- Null constructor
		FoamLagrangian_EXPORT phaseProperties();

		//- Construct from Istream
		FoamLagrangian_EXPORT phaseProperties(Istream&);


		//- Destructor
		FoamLagrangian_EXPORT ~phaseProperties();


		// Public Member Functions

			//- Reorder species to be consistent with the corresponding
			//  phase specie name list
		FoamLagrangian_EXPORT void reorder
		(
			const wordList& gasNames,
			const wordList& liquidNames,
			const wordList& solidNames
		);


		// Access

			//- Return const access to the phase type
		FoamLagrangian_EXPORT phaseType phase() const;

		//- Return const access to the phase state label
		FoamLagrangian_EXPORT const word& stateLabel() const;

		//- Return word representation of the phase type
		FoamLagrangian_EXPORT word phaseTypeName() const;

		//- Return the list of specie names
		FoamLagrangian_EXPORT const List<word>& names() const;

		//- Return const access to a specie name
		FoamLagrangian_EXPORT const word& name(const label speciei) const;

		//- Return const access to all specie mass fractions
		FoamLagrangian_EXPORT const scalarField& Y() const;

		//- Return non-const access to a specie mass fraction
		FoamLagrangian_EXPORT scalar& Y(const label speciei);

		//- Return const access to the map to the carrier ids
		FoamLagrangian_EXPORT const labelList& carrierIds() const;

		//- Return the id of a specie in the local list by name
		//  Returns -1 if not found
		FoamLagrangian_EXPORT label id(const word& specieName) const;

		
		FoamLagrangian_EXPORT bool operator==(const phaseProperties&) const; //- added by amir
		FoamLagrangian_EXPORT bool operator!=(const phaseProperties&) const; //- added by amir


		// IOstream Operators

		friend FoamLagrangian_EXPORT Istream& operator>>(Istream&, phaseProperties&);
		friend FoamLagrangian_EXPORT Ostream& operator<<(Ostream&, const phaseProperties&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_phaseProperties_Header
