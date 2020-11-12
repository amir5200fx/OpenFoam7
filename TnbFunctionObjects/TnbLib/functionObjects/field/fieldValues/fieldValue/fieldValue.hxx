#pragma once
#ifndef _fieldValue_Header
#define _fieldValue_Header

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
	tnbLib::functionObjects::fieldValue

Description
	Base class for field value -based function objects.

See also
	tnbLib::functionObject
	tnbLib::functionObjects::fvMeshFunctionObject
	tnbLib::functionObjects::logFiles

SourceFiles
	fieldValue.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <logFiles.hxx>
#include <Switch.hxx>
#include <Field.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class fvMesh;

	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							   Class fieldValue Declaration
		\*---------------------------------------------------------------------------*/

		class fieldValue
			:
			public fvMeshFunctionObject,
			public logFiles
		{

		protected:

			// Protected data

				//- Construction dictionary
			dictionary dict_;

			//- Name of region (patch, zone, etc.)
			word regionName_;

			//- List of field names to operate on
			wordList fields_;

			//- Output field values flag
			Switch writeFields_;

			//- Results dictionary for external access of results
			dictionary resultDict_;


			// Protected Member Functions

				//- Combine fields from all processor domains into single field
			template<class Type>
			void combineFields(Field<Type>& field);

			//- Combine fields from all processor domains into single field
			template<class Type>
			void combineFields(tmp<Field<Type>>&);


		public:

			//- Run-time type information
			//TypeName("fieldValue");
			static const char* typeName_() { return "fieldValue"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			// Declare runtime constructor selection table

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				fieldValue,
				dictionary,
				(
					const word& name,
					const objectRegistry& obr,
					const dictionary& dict
					),
					(name, obr, dict)
			);*/

			typedef autoPtr<fieldValue> (*dictionaryConstructorPtr)(const word& name, const objectRegistry& obr,
			                                                        const dictionary& dict);
			typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
			static FoamFunctionObjects_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
			static FoamFunctionObjects_EXPORT void constructdictionaryConstructorTables();
			static FoamFunctionObjects_EXPORT void destroydictionaryConstructorTables();

			template <class fieldValueType>
			class adddictionaryConstructorToTable
			{
			public:
				static autoPtr<fieldValue> New(const word& name, const objectRegistry& obr, const dictionary& dict)
				{
					return autoPtr<fieldValue>(new fieldValueType(name, obr, dict));
				}

				adddictionaryConstructorToTable(const word& lookup = fieldValueType::typeName)
				{
					constructdictionaryConstructorTables();
					if (!dictionaryConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "fieldValue" <<
							std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
			};

			template <class fieldValueType>
			class addRemovabledictionaryConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<fieldValue> New(const word& name, const objectRegistry& obr, const dictionary& dict)
				{
					return autoPtr<fieldValue>(new fieldValueType(name, obr, dict));
				}

				addRemovabledictionaryConstructorToTable(const word& lookup = fieldValueType::typeName) : lookup_(
					lookup)
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

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT fieldValue
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict,
				const word& valueType
			);

			//- Construct from objectRegistry and dictionary
			FoamFunctionObjects_EXPORT fieldValue
			(
				const word& name,
				const objectRegistry& obr,
				const dictionary& dict,
				const word& valueType
			);

			//- Return a reference to the selected fieldValue
			static FoamFunctionObjects_EXPORT autoPtr<fieldValue> New
			(
				const word& name,
				const objectRegistry& obr,
				const dictionary& dict,
				const bool output = true
			);


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~fieldValue();


			// Member Functions

				//- Return the reference to the construction dictionary
			inline const dictionary& dict() const;

			//- Return the region name
			inline const word& regionName() const;

			//- Return the list of field names
			inline const wordList& fields() const;

			//- Return the output field values flag
			inline const Switch& writeFields() const;

			//- Return access to the latest set of results
			inline const dictionary& resultDict() const;

			//- Read from dictionary
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary& dict);

			//- Execute
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write
			FoamFunctionObjects_EXPORT virtual bool write();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fieldValueI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
//#include <fieldValueTemplates.cxx>
#endif

#include <fieldValueTemplates.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fieldValue_Header
