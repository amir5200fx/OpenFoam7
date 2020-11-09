#pragma once
#ifndef _surfaceWriter_Header
#define _surfaceWriter_Header

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
	tnbLib::surfaceWriter

Description
	Base class for surface writers

SourceFiles
	surfaceWriter.C

\*---------------------------------------------------------------------------*/

#include <typeInfo.hxx>
#include <autoPtr.hxx>
#include <pointField.hxx>
#include <faceList.hxx>
#include <fileName.hxx>

#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class surfaceWriter Declaration
	\*---------------------------------------------------------------------------*/

	class surfaceWriter
	{
	public:

		//- Runtime type information
		//TypeName("surfaceWriter");
		static const char* typeName_() { return "surfaceWriter"; }
		static FoamConversion_EXPORT const ::tnbLib::word typeName;
		static FoamConversion_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			surfaceWriter,
			word,
			(),
			()
		);*/

		typedef autoPtr<surfaceWriter> (*wordConstructorPtr)();
		typedef HashTable<wordConstructorPtr, word, string::hash> wordConstructorTable;
		static FoamConversion_EXPORT wordConstructorTable* wordConstructorTablePtr_;
		static FoamConversion_EXPORT void constructwordConstructorTables();
		static FoamConversion_EXPORT void destroywordConstructorTables();

		template <class surfaceWriterType>
		class addwordConstructorToTable
		{
		public:
			static autoPtr<surfaceWriter> New() { return autoPtr<surfaceWriter>(new surfaceWriterType()); }

			addwordConstructorToTable(const word& lookup = surfaceWriterType::typeName)
			{
				constructwordConstructorTables();
				if (!wordConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "surfaceWriter" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addwordConstructorToTable() { destroywordConstructorTables(); }
		};

		template <class surfaceWriterType>
		class addRemovablewordConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<surfaceWriter> New() { return autoPtr<surfaceWriter>(new surfaceWriterType()); }

			addRemovablewordConstructorToTable(const word& lookup = surfaceWriterType::typeName) : lookup_(lookup)
			{
				constructwordConstructorTables();
				wordConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablewordConstructorToTable()
			{
				if (wordConstructorTablePtr_) { wordConstructorTablePtr_->erase(lookup_); }
			}
		};

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			surfaceWriter,
			wordDict,
			(
				const dictionary& optDict
				),
				(optDict)
		);*/

		typedef autoPtr<surfaceWriter> (*wordDictConstructorPtr)(const dictionary& optDict);
		typedef HashTable<wordDictConstructorPtr, word, string::hash> wordDictConstructorTable;
		static FoamConversion_EXPORT wordDictConstructorTable* wordDictConstructorTablePtr_;
		static FoamConversion_EXPORT void constructwordDictConstructorTables();
		static FoamConversion_EXPORT void destroywordDictConstructorTables();

		template <class surfaceWriterType>
		class addwordDictConstructorToTable
		{
		public:
			static autoPtr<surfaceWriter> New(const dictionary& optDict)
			{
				return autoPtr<surfaceWriter>(new surfaceWriterType(optDict));
			}

			addwordDictConstructorToTable(const word& lookup = surfaceWriterType::typeName)
			{
				constructwordDictConstructorTables();
				if (!wordDictConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "surfaceWriter" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addwordDictConstructorToTable() { destroywordDictConstructorTables(); }
		};

		template <class surfaceWriterType>
		class addRemovablewordDictConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<surfaceWriter> New(const dictionary& optDict)
			{
				return autoPtr<surfaceWriter>(new surfaceWriterType(optDict));
			}

			addRemovablewordDictConstructorToTable(const word& lookup = surfaceWriterType::typeName) : lookup_(lookup)
			{
				constructwordDictConstructorTables();
				wordDictConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablewordDictConstructorToTable()
			{
				if (wordDictConstructorTablePtr_) { wordDictConstructorTablePtr_->erase(lookup_); }
			}
		};


		// Selectors

			//- Return a reference to the selected surfaceWriter
		static FoamConversion_EXPORT autoPtr<surfaceWriter> New(const word& writeType);

		//- Return a reference to the selected surfaceWriter
		//  Select with extra write option
		static FoamConversion_EXPORT autoPtr<surfaceWriter> New
		(
			const word& writeType,
			const dictionary& writeOptions
		);


		// Constructors

			//- Construct null
		FoamConversion_EXPORT surfaceWriter();


		//- Destructor
		FoamConversion_EXPORT virtual ~surfaceWriter();


		// Member Functions

			//- True if the surface format supports geometry in a separate file.
			//  False if geometry and field must be in a single file
		virtual bool separateGeometry()
		{
			return false;
		}

		//- Write single surface geometry to file.
		FoamConversion_EXPORT virtual void write
		(
			const fileName& outputDir,      // <case>/surface/TIME
			const fileName& surfaceName,    // name of surface
			const pointField& points,
			const faceList& faces,
			const bool verbose = false
		) const = 0;

		//- Write scalarField for a single surface to file.
		//  One value per face or vertex (isNodeValues = true)
		FoamConversion_EXPORT virtual void write
		(
			const fileName& outputDir,      // <case>/surface/TIME
			const fileName& surfaceName,    // name of surface
			const pointField& points,
			const faceList& faces,
			const word& fieldName,          // name of field
			const Field<scalar>& values,
			const bool isNodeValues,
			const bool verbose = false
		) const = 0;

		//- Write vectorField for a single surface to file.
		//  One value per face or vertex (isNodeValues = true)
		FoamConversion_EXPORT virtual void write
		(
			const fileName& outputDir,      // <case>/surface/TIME
			const fileName& surfaceName,    // name of surface
			const pointField& points,
			const faceList& faces,
			const word& fieldName,          // name of field
			const Field<vector>& values,
			const bool isNodeValues,
			const bool verbose = false
		) const = 0;

		//- Write sphericalTensorField for a single surface to file.
		//  One value per face or vertex (isNodeValues = true)
		FoamConversion_EXPORT virtual void write
		(
			const fileName& outputDir,      // <case>/surface/TIME
			const fileName& surfaceName,    // name of surface
			const pointField& points,
			const faceList& faces,
			const word& fieldName,          // name of field
			const Field<sphericalTensor>& values,
			const bool isNodeValues,
			const bool verbose = false
		) const = 0;

		//- Write symmTensorField for a single surface to file.
		//  One value per face or vertex (isNodeValues = true)
		FoamConversion_EXPORT virtual void write
		(
			const fileName& outputDir,      // <case>/surface/TIME
			const fileName& surfaceName,    // name of surface
			const pointField& points,
			const faceList& faces,
			const word& fieldName,          // name of field
			const Field<symmTensor>& values,
			const bool isNodeValues,
			const bool verbose = false
		) const = 0;

		//- Write tensorField for a single surface to file.
		//  One value per face or vertex (isNodeValues = true)
		FoamConversion_EXPORT virtual void write
		(
			const fileName& outputDir,      // <case>/surface/TIME
			const fileName& surfaceName,    // name of surface
			const pointField& points,
			const faceList& faces,
			const word& fieldName,          // name of field
			const Field<tensor>& values,
			const bool isNodeValues,
			const bool verbose = false
		) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceWriter_Header
