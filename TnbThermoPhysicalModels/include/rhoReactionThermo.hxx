#pragma once
#ifndef _rhoReactionThermo_Header
#define _rhoReactionThermo_Header

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
	tnbLib::rhoReactionThermo

Description
	tnbLib::rhoReactionThermo

SourceFiles
	rhoReactionThermo.C

\*---------------------------------------------------------------------------*/

#include <rhoThermo.hxx>
#include <basicSpecieMixture.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class rhoReactionThermo Declaration
	\*---------------------------------------------------------------------------*/

	class rhoReactionThermo
		:
		public rhoThermo
	{

	public:

		//- Runtime type information
		//TypeName("rhoReactionThermo");
		static const char* typeName_() { return "rhoReactionThermo"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		//- Declare run-time constructor selection tables
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			rhoReactionThermo,
			fvMesh,
			(const fvMesh& mesh, const word& phaseName),
			(mesh, phaseName)
		);*/
		
		typedef autoPtr<rhoReactionThermo> (*fvMeshConstructorPtr)(const fvMesh& mesh, const word& phaseName);
		typedef HashTable<fvMeshConstructorPtr, word, string::hash> fvMeshConstructorTable;
		static FoamThermophysicalModels_EXPORT fvMeshConstructorTable* fvMeshConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructfvMeshConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroyfvMeshConstructorTables();

		template <class rhoReactionThermoType>
		class addfvMeshConstructorToTable
		{
		public:
			static autoPtr<rhoReactionThermo> New(const fvMesh& mesh, const word& phaseName)
			{
				return autoPtr<rhoReactionThermo>(new rhoReactionThermoType(mesh, phaseName));
			}

			addfvMeshConstructorToTable(const word& lookup = rhoReactionThermoType::typeName)
			{
				constructfvMeshConstructorTables();
				if (!fvMeshConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "rhoReactionThermo"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addfvMeshConstructorToTable() { destroyfvMeshConstructorTables(); }
		};

		template <class rhoReactionThermoType>
		class addRemovablefvMeshConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<rhoReactionThermo> New(const fvMesh& mesh, const word& phaseName)
			{
				return autoPtr<rhoReactionThermo>(new rhoReactionThermoType(mesh, phaseName));
			}

			addRemovablefvMeshConstructorToTable(const word& lookup = rhoReactionThermoType::typeName) : lookup_(lookup)
			{
				constructfvMeshConstructorTables();
				fvMeshConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablefvMeshConstructorToTable()
			{
				if (fvMeshConstructorTablePtr_) { fvMeshConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct from mesh and phase name
		FoamThermophysicalModels_EXPORT rhoReactionThermo
		(
			const fvMesh&,
			const word& phaseName
		);


		// Selectors

			//- Standard selection based on fvMesh
		static FoamThermophysicalModels_EXPORT autoPtr<rhoReactionThermo> New
		(
			const fvMesh&,
			const word& phaseName = word::null
		);


		//- Destructor
		FoamThermophysicalModels_EXPORT virtual ~rhoReactionThermo();


		// Member Functions

			//- Return the composition of the multi-component mixture
		FoamThermophysicalModels_EXPORT virtual basicSpecieMixture& composition() = 0;

		//- Return the composition of the multi-component mixture
		FoamThermophysicalModels_EXPORT virtual const basicSpecieMixture& composition() const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_rhoReactionThermo_Header
