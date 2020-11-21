#pragma once
#ifndef _topoSet_Header
#define _topoSet_Header

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
	tnbLib::topoSet

Description
	General set of labels of mesh quantity (points, cells, faces).

	Contains various 'notImplemented' functions, but I do not want to make
	this class abstract since it is quite handy to work on topoSets.

SourceFiles
	topoSet.C

\*---------------------------------------------------------------------------*/

#include <HashSet.hxx>
#include <regIOobject.hxx>
#include <labelList.hxx>
#include <typeInfo.hxx>
#include <autoPtr.hxx>
#include <pointField.hxx>

#include <runTimeSelectionTables.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{


	class mapPolyMesh;
	class polyMesh;
	class primitiveMesh;

	/*---------------------------------------------------------------------------*\
							   Class topoSet Declaration
	\*---------------------------------------------------------------------------*/

	class topoSet
		:
		public regIOobject,
		public labelHashSet
	{

	protected:

		// Protected Member Functions

			//- Update map from map. Used to update cell/face labels
			//  after morphing
		FoamFvMesh_EXPORT void updateLabels(const labelList& map);

		//- Check validity of contents.
		FoamFvMesh_EXPORT void check(const label maxLabel);

		//- Write part of contents nicely formatted. Prints labels only.
		FoamFvMesh_EXPORT void writeDebug
		(
			Ostream& os,
			const label maxElem,
			topoSet::const_iterator& iter,
			label& elemI
		) const;

		//- Write part of contents nicely formatted. Prints label
		//  and corresponding coordinate.
		FoamFvMesh_EXPORT void writeDebug
		(
			Ostream& os,
			const pointField& coords,
			const label maxElem,
			topoSet::const_iterator& iter,
			label& elemI
		) const;

		//- Write labels and coordinates columnwise to os. Truncate to maxLen.
		FoamFvMesh_EXPORT void writeDebug
		(
			Ostream& os,
			const pointField& coords,
			const label maxLen
		) const;


	public:

		//- Runtime type information
		/*TypeName("topoSet");*/
		static const char* typeName_() { return "topoSet"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Static

			//- Name of file set will use.
		static FoamFvMesh_EXPORT fileName localPath(const polyMesh& mesh, const word& name);


		// Declare run-time constructor selection table

			// For the direct constructor
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			topoSet,
			word,
			(
				const polyMesh& mesh,
				const word& name,
				readOption r,
				writeOption w
				),
				(mesh, name, r, w)
		);*/

		typedef autoPtr<topoSet> (*wordConstructorPtr)(const polyMesh& mesh, const word& name, readOption r, writeOption w);
		typedef HashTable<wordConstructorPtr, word, string::hash> wordConstructorTable;
		static FoamFvMesh_EXPORT wordConstructorTable* wordConstructorTablePtr_;
		static FoamFvMesh_EXPORT void constructwordConstructorTables();
		static FoamFvMesh_EXPORT void destroywordConstructorTables();

		template <class topoSetType>
		class addwordConstructorToTable
		{
		public:
			static autoPtr<topoSet> New(const polyMesh& mesh, const word& name, readOption r, writeOption w)
			{
				return autoPtr<topoSet>(new topoSetType(mesh, name, r, w));
			}

			addwordConstructorToTable(const word& lookup = topoSetType::typeName)
			{
				constructwordConstructorTables();
				if (!wordConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "topoSet" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addwordConstructorToTable() { destroywordConstructorTables(); }
		};

		template <class topoSetType>
		class addRemovablewordConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<topoSet> New(const polyMesh& mesh, const word& name, readOption r, writeOption w)
			{
				return autoPtr<topoSet>(new topoSetType(mesh, name, r, w));
			}

			addRemovablewordConstructorToTable(const word& lookup = topoSetType::typeName) : lookup_(lookup)
			{
				constructwordConstructorTables();
				wordConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablewordConstructorToTable() { if (wordConstructorTablePtr_) { wordConstructorTablePtr_->erase(lookup_); } }
		};;

		// For the constructor from size
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			topoSet,
			size,
			(
				const polyMesh& mesh,
				const word& name,
				const label size,
				writeOption w
				),
				(mesh, name, size, w)
		);*/

		typedef autoPtr<topoSet> (*sizeConstructorPtr)(const polyMesh& mesh, const word& name, const label size,
		                                               writeOption w);
		typedef HashTable<sizeConstructorPtr, word, string::hash> sizeConstructorTable;
		static FoamFvMesh_EXPORT sizeConstructorTable* sizeConstructorTablePtr_;
		static FoamFvMesh_EXPORT void constructsizeConstructorTables();
		static FoamFvMesh_EXPORT void destroysizeConstructorTables();

		template <class topoSetType>
		class addsizeConstructorToTable
		{
		public:
			static autoPtr<topoSet> New(const polyMesh& mesh, const word& name, const label size, writeOption w)
			{
				return autoPtr<topoSet>(new topoSetType(mesh, name, size, w));
			}

			addsizeConstructorToTable(const word& lookup = topoSetType::typeName)
			{
				constructsizeConstructorTables();
				if (!sizeConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "topoSet" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addsizeConstructorToTable() { destroysizeConstructorTables(); }
		};

		template <class topoSetType>
		class addRemovablesizeConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<topoSet> New(const polyMesh& mesh, const word& name, const label size, writeOption w)
			{
				return autoPtr<topoSet>(new topoSetType(mesh, name, size, w));
			}

			addRemovablesizeConstructorToTable(const word& lookup = topoSetType::typeName) : lookup_(lookup)
			{
				constructsizeConstructorTables();
				sizeConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablesizeConstructorToTable() { if (sizeConstructorTablePtr_) { sizeConstructorTablePtr_->erase(lookup_); } }
		};;

		// For the constructor as copy
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			topoSet,
			set,
			(
				const polyMesh& mesh,
				const word& name,
				const topoSet& set,
				writeOption w
				),
				(mesh, name, set, w)
		);*/

		typedef autoPtr<topoSet> (*setConstructorPtr)(const polyMesh& mesh, const word& name, const topoSet& set,
		                                              writeOption w);
		typedef HashTable<setConstructorPtr, word, string::hash> setConstructorTable;
		static FoamFvMesh_EXPORT setConstructorTable* setConstructorTablePtr_;
		static FoamFvMesh_EXPORT void constructsetConstructorTables();
		static FoamFvMesh_EXPORT void destroysetConstructorTables();

		template <class topoSetType>
		class addsetConstructorToTable
		{
		public:
			static autoPtr<topoSet> New(const polyMesh& mesh, const word& name, const topoSet& set, writeOption w)
			{
				return autoPtr<topoSet>(new topoSetType(mesh, name, set, w));
			}

			addsetConstructorToTable(const word& lookup = topoSetType::typeName)
			{
				constructsetConstructorTables();
				if (!setConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "topoSet" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addsetConstructorToTable() { destroysetConstructorTables(); }
		};

		template <class topoSetType>
		class addRemovablesetConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<topoSet> New(const polyMesh& mesh, const word& name, const topoSet& set, writeOption w)
			{
				return autoPtr<topoSet>(new topoSetType(mesh, name, set, w));
			}

			addRemovablesetConstructorToTable(const word& lookup = topoSetType::typeName) : lookup_(lookup)
			{
				constructsetConstructorTables();
				setConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablesetConstructorToTable() { if (setConstructorTablePtr_) { setConstructorTablePtr_->erase(lookup_); } }
		};;


		// Constructors


			//- Construct from IOobject as explicitly passed type.
			//  Can't use typeName info here since subclasses not yet instantiated
		FoamFvMesh_EXPORT topoSet(const IOobject&, const word& wantedType);

		//- Construct from polyMesh and name. Searches for a polyMesh/sets
		//  directory but not beyond mesh.facesInstance.
		FoamFvMesh_EXPORT topoSet
		(
			const polyMesh& mesh,
			const word& wantedType,
			const word& name,
			readOption r = MUST_READ,
			writeOption w = NO_WRITE
		);

		//- Construct empty from additional size of labelHashSet.
		//  Searches for a polyMesh/sets
		//  directory but not beyond mesh.facesInstance.
		FoamFvMesh_EXPORT topoSet
		(
			const polyMesh& mesh,
			const word& name,
			const label,
			writeOption w = NO_WRITE
		);

		//- Construct empty from additional labelHashSet
		//  Searches for a polyMesh/sets
		//  directory but not beyond mesh.facesInstance.
		FoamFvMesh_EXPORT topoSet
		(
			const polyMesh& mesh,
			const word& name,
			const labelHashSet&,
			writeOption w = NO_WRITE
		);

		//- Construct empty from IOobject and size.
		FoamFvMesh_EXPORT topoSet(const IOobject&, const label size);

		//- Construct from IOobject and labelHashSet.
		FoamFvMesh_EXPORT topoSet(const IOobject&, const labelHashSet&);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT topoSet(const topoSet&) = delete;


		//- Clone
		autoPtr<topoSet> clone() const
		{
			NotImplemented;
			return autoPtr<topoSet>(nullptr);
		}


		// Selectors

			//- Return a pointer to a toposet read from file
		static FoamFvMesh_EXPORT autoPtr<topoSet> New
		(
			const word& setType,
			const polyMesh& mesh,
			const word& name,
			readOption r = MUST_READ,
			writeOption w = NO_WRITE
		);

		//- Return a pointer to a new toposet of given size
		static FoamFvMesh_EXPORT autoPtr<topoSet> New
		(
			const word& setType,
			const polyMesh& mesh,
			const word& name,
			const label size,
			writeOption w = NO_WRITE
		);

		//- Return a pointer to a new toposet as copy of another toposet
		static FoamFvMesh_EXPORT autoPtr<topoSet> New
		(
			const word& setType,
			const polyMesh& mesh,
			const word& name,
			const topoSet& set,
			writeOption w = NO_WRITE
		);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~topoSet();


		// Member Functions

			//- Invert contents. (insert all members 0..maxLen-1 which were not in
			//  set)
		FoamFvMesh_EXPORT virtual void invert(const label maxLen);

		//- Subset contents. Only elements present in both sets remain.
		FoamFvMesh_EXPORT virtual void subset(const topoSet& set);

		//- Add elements present in set.
		FoamFvMesh_EXPORT virtual void addSet(const topoSet& set);

		//- Delete elements present in set.
		FoamFvMesh_EXPORT virtual void deleteSet(const topoSet& set);

		//- Sync set across coupled patches.
		FoamFvMesh_EXPORT virtual void sync(const polyMesh& mesh);

		//- Write labels columnwise to os. Truncate to maxLen.
		FoamFvMesh_EXPORT virtual void writeDebug(Ostream& os, const label maxLen) const;

		//- Like above but also writes mesh related quantity
		//  (usually coordinate).
		FoamFvMesh_EXPORT virtual void writeDebug
		(
			Ostream& os,
			const primitiveMesh&,
			const label maxLen
		) const = 0;

		//- Write contents.
		FoamFvMesh_EXPORT virtual bool writeData(Ostream&) const;

		//- Update any stored data for new labels. Not implemented.
		FoamFvMesh_EXPORT virtual void updateMesh(const mapPolyMesh& morphMap);

		//- Return max allowable index (+1). Not implemented.
		FoamFvMesh_EXPORT virtual label maxSize(const polyMesh& mesh) const = 0;



		// Member Operators

			//- Copy labelHashSet part only
		FoamFvMesh_EXPORT void operator=(const topoSet&);

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_topoSet_Header
