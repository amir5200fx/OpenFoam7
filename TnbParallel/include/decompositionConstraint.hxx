#pragma once
#ifndef _decompositionConstraint_Header
#define _decompositionConstraint_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
	tnbLib::decompositionConstraint

Description

SourceFiles
	decompositionConstraint.C

\*---------------------------------------------------------------------------*/

#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>
#include <boolList.hxx>
#include <labelList.hxx>
#include <labelPair.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class polyMesh;

	/*---------------------------------------------------------------------------*\
					Class decompositionConstraint Declaration
	\*---------------------------------------------------------------------------*/

	class decompositionConstraint
	{
	protected:

		// Protected data

			//- Model coefficients dictionary
		dictionary coeffDict_;


	public:

		//- Runtime type information
		//TypeName("decompositionConstraint");
		static const char* typeName_() { return "decompositionConstraint"; }
		static FoamParallel_EXPORT const ::tnbLib::word typeName;
		static FoamParallel_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			decompositionConstraint,
			dictionary,
			(
				const dictionary& constraintsDict,
				const word& type
				),
				(constraintsDict, type)
		);*/

		typedef autoPtr<decompositionConstraint> (*dictionaryConstructorPtr)(
			const dictionary& constraintsDict, const word& type);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamParallel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamParallel_EXPORT void constructdictionaryConstructorTables();
		static FoamParallel_EXPORT void destroydictionaryConstructorTables();

		template <class decompositionConstraintType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<decompositionConstraint> New(const dictionary& constraintsDict, const word& type)
			{
				return autoPtr<decompositionConstraint>(new decompositionConstraintType(constraintsDict, type));
			}

			adddictionaryConstructorToTable(const word& lookup = decompositionConstraintType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"decompositionConstraint" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class decompositionConstraintType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<decompositionConstraint> New(const dictionary& constraintsDict, const word& type)
			{
				return autoPtr<decompositionConstraint>(new decompositionConstraintType(constraintsDict, type));
			}

			addRemovabledictionaryConstructorToTable(
				const word& lookup = decompositionConstraintType::typeName) : lookup_(lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};


		// Constructors

			//- Construct with generic dictionary with optional entry for type
		FoamParallel_EXPORT decompositionConstraint
		(
			const dictionary& constraintsDict,
			const word& type
		);

		//- Disallow default bitwise copy construction
		FoamParallel_EXPORT decompositionConstraint(const decompositionConstraint&) = delete;


		// Selectors

			//- Return a reference to the selected decompositionConstraint
		static FoamParallel_EXPORT autoPtr<decompositionConstraint> New
		(
			const dictionary& constraintsDict,
			const word& type
		);


		//- Destructor
		FoamParallel_EXPORT virtual ~decompositionConstraint();


		// Member Functions

			//- Add my constraints to list of constraints
		FoamParallel_EXPORT virtual void add
		(
			const polyMesh& mesh,
			boolList& blockedFace,
			PtrList<labelList>& specifiedProcessorFaces,
			labelList& specifiedProcessor,
			List<labelPair>& explicitConnections
		) const = 0;

		//- Apply any additional post-decomposition constraints. Usually no
		//  need to do anything since decomposition method should have already
		//  obeyed the constraints
		virtual void apply
		(
			const polyMesh& mesh,
			const boolList& blockedFace,
			const PtrList<labelList>& specifiedProcessorFaces,
			const labelList& specifiedProcessor,
			const List<labelPair>& explicitConnections,
			labelList& decomposition
		) const
		{}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamParallel_EXPORT void operator=(const decompositionConstraint&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_decompositionConstraint_Header
