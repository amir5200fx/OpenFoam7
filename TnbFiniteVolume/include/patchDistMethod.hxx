#pragma once
#ifndef _patchDistMethod_Header
#define _patchDistMethod_Header

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
	tnbLib::patchDistMethod

Description
	Specialisation of patchDist for wall distance calculation

SourceFiles
	patchDistMethod.C

\*---------------------------------------------------------------------------*/

#include <dictionary.hxx>
#include <HashSet.hxx>
#include <volFieldsFwd.hxx>
#include <mapPolyMesh.hxx>
#include <fixedValueFvPatchFields.hxx>
#include <zeroGradientFvPatchFields.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;

	/*---------------------------------------------------------------------------*\
							  Class patchDistMethod Declaration
	\*---------------------------------------------------------------------------*/

	class patchDistMethod
	{

	protected:

		// Protected Member Data

			//- Reference to the mesh
		const fvMesh& mesh_;

		//- Set of patch IDs
		const labelHashSet patchIDs_;


	public:

		//- Runtime type information
		/*TypeName("patchDistMethod");*/
		static const char* typeName_() { return "patchDistMethod"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare runtime construction

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			patchDistMethod,
			dictionary,
			(
				const dictionary& dict,
				const fvMesh& mesh,
				const labelHashSet& patchIDs
				),
				(dict, mesh, patchIDs)
		);*/

		typedef autoPtr<patchDistMethod> (*dictionaryConstructorPtr)(const dictionary& dict, const fvMesh& mesh,
		                                                             const labelHashSet& patchIDs);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamFiniteVolume_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamFiniteVolume_EXPORT void constructdictionaryConstructorTables();
		static FoamFiniteVolume_EXPORT void destroydictionaryConstructorTables();

		template <class patchDistMethodType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<patchDistMethod> New(const dictionary& dict, const fvMesh& mesh, const labelHashSet& patchIDs)
			{
				return autoPtr<patchDistMethod>(new patchDistMethodType(dict, mesh, patchIDs));
			}

			adddictionaryConstructorToTable(const word& lookup = patchDistMethodType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "patchDistMethod" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class patchDistMethodType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<patchDistMethod> New(const dictionary& dict, const fvMesh& mesh, const labelHashSet& patchIDs)
			{
				return autoPtr<patchDistMethod>(new patchDistMethodType(dict, mesh, patchIDs));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = patchDistMethodType::typeName) : lookup_(lookup)
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

		//- Construct from mesh and patch ID set
		FoamFiniteVolume_EXPORT patchDistMethod
		(
			const fvMesh& mesh,
			const labelHashSet& patchIDs
		);

		//- Disallow default bitwise copy construction
		FoamFiniteVolume_EXPORT patchDistMethod(const patchDistMethod&) = delete;


		// Selectors

		static FoamFiniteVolume_EXPORT autoPtr<patchDistMethod> New
		(
			const dictionary& dict,
			const fvMesh& mesh,
			const labelHashSet& patchIDs
		);


		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~patchDistMethod();


		// Static Functions

		//- Return the patch types for y and n
		//  These are fixedValue for the set provided otherwise zero-gradient
		template<class Type>
		static wordList patchTypes
		(
			const fvMesh& mesh,
			const labelHashSet& patchIDs
		);


		// Member Functions

		//- Return the patchIDs
		const labelHashSet& patchIDs() const
		{
			return patchIDs_;
		}

		//- Update cached geometry when the mesh moves
		virtual bool movePoints()
		{
			return true;
		}

		//- Update cached topology and geometry when the mesh changes
		virtual void updateMesh(const mapPolyMesh&)
		{}

		//- Correct the given distance-to-patch field
		FoamFiniteVolume_EXPORT virtual bool correct(volScalarField& y) = 0;

		//- Correct the given distance-to-patch and normal-to-patch fields
		FoamFiniteVolume_EXPORT virtual bool correct(volScalarField& y, volVectorField& n) = 0;


		// Member Operators

		//- Disallow default bitwise assignment
		FoamFiniteVolume_EXPORT void operator=(const patchDistMethod&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <patchDistMethodI.hxx>

//#ifdef NoRepository
//#include <patchDistMethodTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_patchDistMethod_Header
