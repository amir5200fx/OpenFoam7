#pragma once
#ifndef _sampledSet_Header
#define _sampledSet_Header

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
	tnbLib::sampledSet

Description
	Holds list of sampling points which is filled at construction time.
	Various implementations of this base class to e.g. get sampling points
	at uniform distance along a line (lineUniformSet) or directly specified
	(pointsSet)

	Each 'sampledSet' has a name and a specifier of how the axis should be
	write (x/y/z component or all 3 components)

SourceFiles
	sampledSet.C

\*---------------------------------------------------------------------------*/

#include <coordSet.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>
#include <autoPtr.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class polyMesh;
	class meshSearch;

	/*---------------------------------------------------------------------------*\
							 Class sampledSet Declaration
	\*---------------------------------------------------------------------------*/

	class sampledSet
		:
		public coordSet
	{
		// Private Data

			//- Reference to mesh
		const polyMesh& mesh_;

		//- Reference to mesh searching class
		const meshSearch& searchEngine_;


	protected:

		// Protected data

			//- Segment numbers
		labelList segments_;

		//- Cell numbers
		labelList cells_;

		//- Face numbers (-1 if not known)
		labelList faces_;


		// Protected Member Functions

			//- Sets sample data
		FoamSampling_EXPORT void setSamples
		(
			const List<point>& samplingPts,
			const labelList& samplingCells,
			const labelList& samplingFaces,
			const labelList& samplingSegments,
			const scalarList& samplingCurveDist
		);


	public:

		//- Runtime type information
		//TypeName("sampledSet");
		static const char* typeName_() { return "sampledSet"; }
		static FoamSampling_EXPORT const ::tnbLib::word typeName;
		static FoamSampling_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			sampledSet,
			word,
			(
				const word& name,
				const polyMesh& mesh,
				const meshSearch& searchEngine,
				const dictionary& dict
				),
				(name, mesh, searchEngine, dict)
		);*/

		typedef autoPtr<sampledSet> (*wordConstructorPtr)(const word& name, const polyMesh& mesh,
		                                                  const meshSearch& searchEngine, const dictionary& dict);
		typedef HashTable<wordConstructorPtr, word, string::hash> wordConstructorTable;
		static FoamSampling_EXPORT wordConstructorTable* wordConstructorTablePtr_;
		static FoamSampling_EXPORT void constructwordConstructorTables();
		static FoamSampling_EXPORT void destroywordConstructorTables();

		template <class sampledSetType>
		class addwordConstructorToTable
		{
		public:
			static autoPtr<sampledSet> New(const word& name, const polyMesh& mesh, const meshSearch& searchEngine,
			                               const dictionary& dict)
			{
				return autoPtr<sampledSet>(new sampledSetType(name, mesh, searchEngine, dict));
			}

			addwordConstructorToTable(const word& lookup = sampledSetType::typeName)
			{
				constructwordConstructorTables();
				if (!wordConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "sampledSet" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addwordConstructorToTable() { destroywordConstructorTables(); }
		};

		template <class sampledSetType>
		class addRemovablewordConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<sampledSet> New(const word& name, const polyMesh& mesh, const meshSearch& searchEngine,
			                               const dictionary& dict)
			{
				return autoPtr<sampledSet>(new sampledSetType(name, mesh, searchEngine, dict));
			}

			addRemovablewordConstructorToTable(const word& lookup = sampledSetType::typeName) : lookup_(lookup)
			{
				constructwordConstructorTables();
				wordConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablewordConstructorToTable()
			{
				if (wordConstructorTablePtr_) { wordConstructorTablePtr_->erase(lookup_); }
			}
		};


		//- Class used for the read-construction of
		//  PtrLists of sampledSet
		class iNew
		{
			const polyMesh& mesh_;
			const meshSearch& searchEngine_;

		public:

			iNew(const polyMesh& mesh, const meshSearch& searchEngine)
				:
				mesh_(mesh),
				searchEngine_(searchEngine)
			{}

			autoPtr<sampledSet> operator()(Istream& is) const
			{
				word name(is);
				dictionary dict(is);
				return sampledSet::New(name, mesh_, searchEngine_, dict);
			}
		};


		// Constructors

			//- Construct from components
		FoamSampling_EXPORT sampledSet
		(
			const word& name,
			const polyMesh& mesh,
			const meshSearch& searchEngine,
			const word& axis
		);

		//- Construct from dictionary
		FoamSampling_EXPORT sampledSet
		(
			const word& name,
			const polyMesh& mesh,
			const meshSearch& searchEngine,
			const dictionary& dict
		);

		//- Clone
		autoPtr<sampledSet> clone() const
		{
			NotImplemented;
			return autoPtr<sampledSet>(nullptr);
		}


		// Selectors

			//- Return a reference to the selected sampledSet
		static FoamSampling_EXPORT autoPtr<sampledSet> New
		(
			const word& name,
			const polyMesh& mesh,
			const meshSearch& searchEngine,
			const dictionary& dict
		);


		//- Destructor
		FoamSampling_EXPORT virtual ~sampledSet();


		// Member Functions

		const polyMesh& mesh() const
		{
			return mesh_;
		}

		const meshSearch& searchEngine() const
		{
			return searchEngine_;
		}

		const labelList& segments() const
		{
			return segments_;
		}

		const labelList& cells() const
		{
			return cells_;
		}

		const labelList& faces() const
		{
			return faces_;
		}

		//- Output for debugging
		FoamSampling_EXPORT Ostream& write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sampledSet_Header
