#pragma once
#ifndef _basicMultiComponentMixture_Header
#define _basicMultiComponentMixture_Header

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
	tnbLib::basicMultiComponentMixture

Description
	Multi-component mixture.

	Provides a list of mass fraction fields and helper functions to
	query mixture composition.

SourceFiles
	basicMultiComponentMixture.C

\*---------------------------------------------------------------------------*/

#include <volFields.hxx>
#include <PtrList.hxx>
#include <basicMixture.hxx>
#include <typeInfo.hxx>

#include <speciesTable.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class basicMultiComponentMixture Declaration
	\*---------------------------------------------------------------------------*/

	class basicMultiComponentMixture
		:
		public basicMixture
	{

	protected:

		// Protected data

			//- Table of specie names
		speciesTable species_;

		//- List of specie active flags
		List<bool> active_;

		//- Species mass fractions
		PtrList<volScalarField> Y_;


	public:

		//- Run time type information
		//TypeName("basicMultiComponentMixture");
		static const char* typeName_() { return "basicMultiComponentMixture"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		//- The base class of the mixture
		typedef basicMultiComponentMixture basicMixtureType;


		// Constructors

			//- Construct from dictionary, species names, mesh and phase name
		FoamThermophysicalModels_EXPORT basicMultiComponentMixture
		(
			const dictionary&,
			const wordList& specieNames,
			const fvMesh&,
			const word&
		);


		//- Destructor
		virtual ~basicMultiComponentMixture()
		{}


		// Member Functions

			//- Return the table of species
		inline const speciesTable& species() const;

		//- Does the mixture include this specie?
		inline bool contains(const word& specieName) const;

		//- Return true for active species
		inline bool active(label speciei) const;

		//- Return the bool list of active species
		inline const List<bool>& active() const;

		//- Set speciei active
		inline void setActive(label speciei);

		//- Set speciei inactive
		inline void setInactive(label speciei);

		//- Return the mass-fraction fields
		inline PtrList<volScalarField>& Y();

		//- Return the const mass-fraction fields
		inline const PtrList<volScalarField>& Y() const;

		//- Return the mass-fraction field for a specie given by index
		inline volScalarField& Y(const label i);

		//- Return the const mass-fraction field for a specie given by index
		inline const volScalarField& Y(const label i) const;

		//- Return the mass-fraction field for a specie given by name
		inline volScalarField& Y(const word& specieName);

		//- Return the const mass-fraction field for a specie given by name
		inline const volScalarField& Y(const word& specieName) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <basicMultiComponentMixtureI.hxx>

#endif // !_basicMultiComponentMixture_Headeer
