#pragma once
#ifndef _GAMGProcAgglomeration_Header
#define _GAMGProcAgglomeration_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::GAMGProcAgglomeration

Description
	Processor agglomeration of GAMGAgglomerations.

SourceFiles
	GAMGProcAgglomeration.C

\*---------------------------------------------------------------------------*/

#include <runTimeSelectionTables.hxx>
#include <labelList.hxx>

#include <typeInfo.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class GAMGAgglomeration;
	class lduMesh;

	/*---------------------------------------------------------------------------*\
						Class GAMGProcAgglomeration Declaration
	\*---------------------------------------------------------------------------*/

	class GAMGProcAgglomeration
	{

	protected:

		// Protected data

			//- Reference to agglomeration
		GAMGAgglomeration& agglom_;

		// Protected Member Functions

			//- Debug: write agglomeration info
		FoamBase_EXPORT void printStats(Ostream& os, GAMGAgglomeration& agglom) const;

		//- Agglomerate a level. Return true if anything has changed
		FoamBase_EXPORT bool agglomerate
		(
			const label fineLevelIndex,
			const labelList& procAgglomMap,
			const labelList& masterProcs,
			const List<label>& agglomProcIDs,
			const label procAgglomComm
		);

		//- Debug: calculate global cell-cells
		static FoamBase_EXPORT labelListList globalCellCells(const lduMesh&);


	public:

		//- Runtime type information
		//TypeName("GAMGProcAgglomeration");
		static const char* typeName_() { return "GAMGProcAgglomeration"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

			//- Runtime selection table for pure geometric agglomerators
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			GAMGProcAgglomeration,
			GAMGAgglomeration,
			(
				GAMGAgglomeration& agglom,
				const dictionary& controlDict
				),
				(
					agglom,
					controlDict
					)
		);*/

		typedef autoPtr<GAMGProcAgglomeration> (*GAMGAgglomerationConstructorPtr)(
			GAMGAgglomeration& agglom, const dictionary& controlDict);
		typedef HashTable<GAMGAgglomerationConstructorPtr, word, string::hash> GAMGAgglomerationConstructorTable;
		static FoamBase_EXPORT GAMGAgglomerationConstructorTable* GAMGAgglomerationConstructorTablePtr_;
		static FoamBase_EXPORT void constructGAMGAgglomerationConstructorTables();
		static FoamBase_EXPORT void destroyGAMGAgglomerationConstructorTables();

		template <class GAMGProcAgglomerationType>
		class addGAMGAgglomerationConstructorToTable
		{
		public:
			static autoPtr<GAMGProcAgglomeration> New(GAMGAgglomeration& agglom, const dictionary& controlDict)
			{
				return autoPtr<GAMGProcAgglomeration>(new GAMGProcAgglomerationType(agglom, controlDict));
			}

			addGAMGAgglomerationConstructorToTable(const word& lookup = GAMGProcAgglomerationType::typeName)
			{
				constructGAMGAgglomerationConstructorTables();
				if (!GAMGAgglomerationConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "GAMGProcAgglomeration" << std::
						endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addGAMGAgglomerationConstructorToTable() { destroyGAMGAgglomerationConstructorTables(); }
		};

		template <class GAMGProcAgglomerationType>
		class addRemovableGAMGAgglomerationConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<GAMGProcAgglomeration> New(GAMGAgglomeration& agglom, const dictionary& controlDict)
			{
				return autoPtr<GAMGProcAgglomeration>(new GAMGProcAgglomerationType(agglom, controlDict));
			}

			addRemovableGAMGAgglomerationConstructorToTable(const word& lookup = GAMGProcAgglomerationType::typeName) : lookup_(
				lookup)
			{
				constructGAMGAgglomerationConstructorTables();
				GAMGAgglomerationConstructorTablePtr_->set(lookup, New);
			}

			~addRemovableGAMGAgglomerationConstructorToTable()
			{
				if (GAMGAgglomerationConstructorTablePtr_) { GAMGAgglomerationConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct given agglomerator and controls
		FoamBase_EXPORT GAMGProcAgglomeration
		(
			GAMGAgglomeration& agglom,
			const dictionary& controlDict
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT GAMGProcAgglomeration(const GAMGProcAgglomeration&) = delete;


		// Selectors

			//- Return the selected agglomerator
		static FoamBase_EXPORT autoPtr<GAMGProcAgglomeration> New
		(
			const word& type,
			GAMGAgglomeration& agglom,
			const dictionary& controlDict
		);


		//- Destructor
		FoamBase_EXPORT virtual ~GAMGProcAgglomeration();


		// Member Functions

			//- Modify agglomeration. Return true if modified
		FoamBase_EXPORT virtual bool agglomerate() = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const GAMGProcAgglomeration&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_GAMGProcAgglomeration_Header
