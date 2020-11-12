#pragma once
#ifndef _solidReactionThermo_Header
#define _solidReactionThermo_Header

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
	tnbLib::solidReactionThermo

Description
	tnbLib::solidReactionThermo

SourceFiles
	solidReactionThermo.C

\*---------------------------------------------------------------------------*/

#include <basicSpecieMixture.hxx>
#include <solidThermo.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class solidReactionThermo Declaration
	\*---------------------------------------------------------------------------*/


	class solidReactionThermo
		:
		public solidThermo
	{

	public:

		//- Runtime type information
		//TypeName("solidReactionThermo");
		static const char* typeName_() { return "solidReactionThermo"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		//- Declare run-time constructor selection tables
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			solidReactionThermo,
			fvMesh,
			(const fvMesh& mesh, const word& phaseName),
			(mesh, phaseName)
		);*/
		
		typedef autoPtr<solidReactionThermo> (*fvMeshConstructorPtr)(const fvMesh& mesh, const word& phaseName);
		typedef HashTable<fvMeshConstructorPtr, word, string::hash> fvMeshConstructorTable;
		static FoamThermophysicalModels_EXPORT fvMeshConstructorTable* fvMeshConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructfvMeshConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroyfvMeshConstructorTables();

		template <class solidReactionThermoType>
		class addfvMeshConstructorToTable
		{
		public:
			static autoPtr<solidReactionThermo> New(const fvMesh& mesh, const word& phaseName)
			{
				return autoPtr<solidReactionThermo>(new solidReactionThermoType(mesh, phaseName));
			}

			addfvMeshConstructorToTable(const word& lookup = solidReactionThermoType::typeName)
			{
				constructfvMeshConstructorTables();
				if (!fvMeshConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "solidReactionThermo"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addfvMeshConstructorToTable() { destroyfvMeshConstructorTables(); }
		};

		template <class solidReactionThermoType>
		class addRemovablefvMeshConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<solidReactionThermo> New(const fvMesh& mesh, const word& phaseName)
			{
				return autoPtr<solidReactionThermo>(new solidReactionThermoType(mesh, phaseName));
			}

			addRemovablefvMeshConstructorToTable(const word& lookup = solidReactionThermoType::typeName) : lookup_(
				lookup)
			{
				constructfvMeshConstructorTables();
				fvMeshConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablefvMeshConstructorToTable()
			{
				if (fvMeshConstructorTablePtr_) { fvMeshConstructorTablePtr_->erase(lookup_); }
			}
		};;

		// Declare run-time constructor selection tables
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			solidReactionThermo,
			dictionary,
			(const fvMesh& mesh, const dictionary& dict, const word& phaseName),
			(mesh, dict, phaseName)
		);*/
		
		typedef autoPtr<solidReactionThermo> (*dictionaryConstructorPtr)(
			const fvMesh& mesh, const dictionary& dict, const word& phaseName);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamThermophysicalModels_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructdictionaryConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroydictionaryConstructorTables();

		template <class solidReactionThermoType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<solidReactionThermo> New(const fvMesh& mesh, const dictionary& dict, const word& phaseName)
			{
				return autoPtr<solidReactionThermo>(new solidReactionThermoType(mesh, dict, phaseName));
			}

			adddictionaryConstructorToTable(const word& lookup = solidReactionThermoType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "solidReactionThermo"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class solidReactionThermoType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<solidReactionThermo> New(const fvMesh& mesh, const dictionary& dict, const word& phaseName)
			{
				return autoPtr<solidReactionThermo>(new solidReactionThermoType(mesh, dict, phaseName));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = solidReactionThermoType::typeName) : lookup_(
				lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};;

		// Constructors

			//- Construct from mesh and phase name
		FoamThermophysicalModels_EXPORT solidReactionThermo
		(
			const fvMesh&,
			const word& phaseName
		);

		//- Construct from mesh, dictionary and phase name
		FoamThermophysicalModels_EXPORT solidReactionThermo
		(
			const fvMesh&,
			const dictionary&,
			const word& phaseName
		);


		// Selectors

			//- Standard selection based on fvMesh
		static FoamThermophysicalModels_EXPORT autoPtr<solidReactionThermo> New
		(
			const fvMesh&,
			const word& phaseName = word::null
		);

		//- Standard selection based on fvMesh amd dictionary
		static FoamThermophysicalModels_EXPORT autoPtr<solidReactionThermo> New
		(
			const fvMesh&,
			const dictionary&,
			const word& phaseName = word::null
		);


		//- Destructor
		FoamThermophysicalModels_EXPORT virtual ~solidReactionThermo();


		// Member Functions

			//- Return the composition of the multi-component mixture
		FoamThermophysicalModels_EXPORT virtual basicSpecieMixture& composition() = 0;

		//- Return the composition of the multi-component mixture
		FoamThermophysicalModels_EXPORT virtual const basicSpecieMixture& composition() const = 0;

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_solidReactionThermo_Header
