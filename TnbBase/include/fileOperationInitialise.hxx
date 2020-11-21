#pragma once
#ifndef _fileOperationInitialise_Header
#define _fileOperationInitialise_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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
	tnbLib::fileOperations::fileOperationInitialise

\*---------------------------------------------------------------------------*/

#include <runTimeSelectionTables.hxx>
#include <typeInfo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileOperations
	{

		/*---------------------------------------------------------------------------*\
						   Class fileOperationInitialise Declaration
		\*---------------------------------------------------------------------------*/

		class fileOperationInitialise
		{
		public:

			//- Runtime type information
			//TypeName("fileOperationInitialise");
			static const char* typeName_() { return "fileOperationInitialise"; }
			static FoamBase_EXPORT const ::tnbLib::word typeName;
			static FoamBase_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct components
			FoamBase_EXPORT fileOperationInitialise(int& argc, char**& argv);


			// Declare run-time constructor selection table

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				fileOperationInitialise,
				word,
				(
					int& argc, char**& argv
					),
					(argc, argv)
			);*/

			typedef autoPtr<fileOperationInitialise> (*wordConstructorPtr)(int& argc, char**& argv);
			typedef HashTable<wordConstructorPtr, word, string::hash> wordConstructorTable;
			static FoamBase_EXPORT wordConstructorTable* wordConstructorTablePtr_;
			static FoamBase_EXPORT void constructwordConstructorTables();
			static FoamBase_EXPORT void destroywordConstructorTables();

			template <class fileOperationInitialiseType>
			class addwordConstructorToTable
			{
			public:
				static autoPtr<fileOperationInitialise> New(int& argc, char**& argv)
				{
					return autoPtr<fileOperationInitialise>(new fileOperationInitialiseType(argc, argv));
				}

				addwordConstructorToTable(const word& lookup = fileOperationInitialiseType::typeName)
				{
					constructwordConstructorTables();
					if (!wordConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "fileOperationInitialise" << std::
							endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addwordConstructorToTable() { destroywordConstructorTables(); }
			};

			template <class fileOperationInitialiseType>
			class addRemovablewordConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<fileOperationInitialise> New(int& argc, char**& argv)
				{
					return autoPtr<fileOperationInitialise>(new fileOperationInitialiseType(argc, argv));
				}

				addRemovablewordConstructorToTable(const word& lookup = fileOperationInitialiseType::typeName) : lookup_(lookup)
				{
					constructwordConstructorTables();
					wordConstructorTablePtr_->set(lookup, New);
				}

				~addRemovablewordConstructorToTable()
				{
					if (wordConstructorTablePtr_) { wordConstructorTablePtr_->erase(lookup_); }
				}
			};;


			// Selectors

				//- Select type
			static FoamBase_EXPORT autoPtr<fileOperationInitialise> New
			(
				const word& type, int& argc, char**& argv
			);


			//- Destructor
			FoamBase_EXPORT virtual ~fileOperationInitialise();


			// Member Functions

				//- Needs threading
			FoamBase_EXPORT virtual bool needsThreading() const = 0;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileOperations
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fileOperationInitialise_Header
