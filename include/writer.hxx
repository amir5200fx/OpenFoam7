#pragma once
#ifndef _writer_Header
#define _writer_Header

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
	tnbLib::writer

Description
	Base class for graphics format writing. Entry points are
	- write(..). \n
	  Write to an Ostream a table of points with corresponding values.
	- write(scalar/vector/sphericalTensor/symmTensor/tensor). \n
	  Write single scalar/vector/sphericalTensor/symmTensor/tensor.
	  Default is to write space separated components.

	Example:
	\verbatim
		// Construct writer of xmgr type
		autoPtr<writer<scalar>> scalarFormatter(writer<scalar>::New("xmgr"));

		// Output list of points and corresponding values
		scalarFormatter().write
		(
			coordSet(...)
			"U.component(0)",   // name of values
			vals                // values
		);
	\endverbatim

SourceFiles
	writer.C

\*---------------------------------------------------------------------------*/

#include <fileName.hxx>
#include <wordList.hxx>
#include <vector.hxx>
#include <tensor.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>
#include <autoPtr.hxx>
#include <Field.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class coordSet;

	/*---------------------------------------------------------------------------*\
							   Class writer Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class writer
	{

	protected:

		//- Generates filename from coordSet and sampled fields
		fileName getBaseName(const coordSet&, const wordList&) const;

		void writeCoord(const coordSet&, const label sampleI, Ostream&) const;

		//- Writes single-column ascii write. Column 1 is coordSet coordinate,
		//  columns 2 is the value. Uses write() function
		//  to write coordinate in correct format.
		void writeTable(const coordSet&, const List<Type>&, Ostream&) const;

		//- Writes multi-column ascii write. Column 1 is coordSet coordinate,
		//  columns 2..n are the values. Uses write() function
		//  to write coordinate in correct format.
		void writeTable
		(
			const coordSet&,
			const List<const List<Type>*>&,
			Ostream& os
		) const;

		//- Writes a separator. Used by write functions.
		virtual void writeSeparator(Ostream& os) const;


	public:

		//- Runtime type information
		//TypeName("writer");
		static const char* typeName_() { return "writer"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			writer,
			word,
			(),
			()
		);*/

		typedef autoPtr<writer> (*wordConstructorPtr)();
		typedef HashTable<wordConstructorPtr, word, string::hash> wordConstructorTable;
		static FoamFvMesh_EXPORT wordConstructorTable* wordConstructorTablePtr_;
		static FoamFvMesh_EXPORT void constructwordConstructorTables();
		static FoamFvMesh_EXPORT void destroywordConstructorTables();

		template <class writerType>
		class addwordConstructorToTable
		{
		public:
			static autoPtr<writer> New() { return autoPtr<writer>(new writerType()); }

			addwordConstructorToTable(const word& lookup = writerType::typeName)
			{
				constructwordConstructorTables();
				if (!wordConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "writer" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addwordConstructorToTable() { destroywordConstructorTables(); }
		};

		template <class writerType>
		class addRemovablewordConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<writer> New() { return autoPtr<writer>(new writerType()); }

			addRemovablewordConstructorToTable(const word& lookup = writerType::typeName) : lookup_(lookup)
			{
				constructwordConstructorTables();
				wordConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablewordConstructorToTable() { if (wordConstructorTablePtr_) { wordConstructorTablePtr_->erase(lookup_); } }
		};;


		// Selectors

			//- Return a reference to the selected writer
		static autoPtr<writer> New(const word& writeFormat);


		// Constructors

			//- Construct null
		writer();


		//- Destructor
		virtual ~writer() = 0;


		// Member Functions

			//- Generate file name with correct extension
		virtual fileName getFileName
		(
			const coordSet&,
			const wordList&
		) const = 0;

		//- General entry point for writing.
		//  The data is organized in a set of point with one or more values
		//  per point
		virtual void write
		(
			const coordSet&,
			const wordList&,
			const List<const Field<Type>*>&,
			Ostream&
		) const = 0;

		//- General entry point for writing.
		//  The data is organized in a set of point with one or more values
		//  per point
		virtual void write
		(
			const coordSet&,
			const wordList&,
			const List<Field<Type>>&,
			Ostream&
		) const;

		//- General entry point for writing of multiple coordSets.
		//  Each coordSet (track) has same data variables.
		//  The data is per variable, per track, per point of track.
		//  If writeTracks adds connecting lines (wherever applicable)
		virtual void write
		(
			const bool writeTracks,
			const PtrList<coordSet>&,
			const wordList& valueSetNames,
			const List<List<Field<Type>>>&,
			Ostream&
		) const = 0;

		//- Write scalar as ascii
		virtual Ostream& write(const scalar, Ostream&) const;

		template<class VSType>
		Ostream& writeVS(const VSType&, Ostream&) const;

		//- Write vector. Tab separated ascii
		virtual Ostream& write(const vector&, Ostream&) const;

		//- Write sphericalTensor. Tab separated ascii
		virtual Ostream& write(const sphericalTensor&, Ostream&) const;

		//- Write symmTensor. Tab separated ascii
		virtual Ostream& write(const symmTensor&, Ostream&) const;

		//- Write tensor. Tab separated ascii
		virtual Ostream& write(const tensor&, Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <writerI.hxx>

//#ifdef NoRepository
//#include <writer.cxx>
//#endif


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_writer_Header
