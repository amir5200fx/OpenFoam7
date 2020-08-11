#pragma once
#ifndef _ReactionList_Header
#define _ReactionList_Header

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
	tnbLib::ReactionList

Description
	List of templated reactions

SourceFiles
	ReactionList.C

\*---------------------------------------------------------------------------*/

#include <PtrList.hxx>
#include <SLPtrList.hxx>
#include <speciesTable.hxx>
#include <HashPtrTable.hxx>
#include <Reaction.hxx>
#include <fileName.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class ReactionList Declaration
	\*---------------------------------------------------------------------------*/

	template<class ThermoType>
	class ReactionList
		:
		public SLPtrList<Reaction<ThermoType>>
	{
		// Private Data

			//- Reference to the table of species
		const speciesTable& species_;

		//- Reference to the thermo database
		const HashPtrTable<ThermoType>& thermoDb_;

		//- The dictionary used for construction
		const dictionary dict_;


	public:

		// Constructors

			//- Construct null
		ReactionList
		(
			const speciesTable& species,
			const HashPtrTable<ThermoType>& thermoDatabase
		);

		//- Construct from dictionary
		ReactionList
		(
			const speciesTable& species,
			const HashPtrTable<ThermoType>& thermoDatabase,
			const dictionary& dict
		);

		//- Construct copy
		ReactionList(const ReactionList<ThermoType>& reactions);


		//- Destructor
		~ReactionList();


		// Public Member Functions

			//- Read reactions from dictionary
		bool readReactionDict();

		//- Write
		void write(Ostream& os) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const ReactionList&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <ReactionList.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ReactionList_Header
