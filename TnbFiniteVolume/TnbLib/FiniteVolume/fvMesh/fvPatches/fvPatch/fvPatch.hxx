#pragma once
#ifndef _fvPatch_Header
#define _fvPatch_Header

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
	tnbLib::fvPatch

Description
	A finiteVolume patch using a polyPatch and a fvBoundaryMesh

SourceFiles
	fvPatch.C
	fvPatchNew.C

\*---------------------------------------------------------------------------*/

#include <polyPatch.hxx>
#include <labelList.hxx>
#include <SubList.hxx>
#include <typeInfo.hxx>
#include <tmp.hxx>
#include <primitiveFieldsFwd.hxx>
#include <SubField.hxx>
#include <fvPatchFieldsFwd.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvBoundaryMesh;
	class surfaceInterpolation;

	/*---------------------------------------------------------------------------*\
							   Class fvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class fvPatch
	{
		// Private Data

			//- Reference to the underlying polyPatch
		const polyPatch& polyPatch_;

		//- Reference to boundary mesh
		const fvBoundaryMesh& boundaryMesh_;


	protected:

		// Protected Member Functions

			//- Make patch weighting factors
		FoamFiniteVolume_EXPORT virtual void makeWeights(scalarField&) const;

		//- Initialise the patches for moving points
		FoamFiniteVolume_EXPORT virtual void initMovePoints();

		//- Correct patches after moving points
		FoamFiniteVolume_EXPORT virtual void movePoints();


	public:

		typedef fvBoundaryMesh BoundaryMesh;

		friend class fvBoundaryMesh;
		friend class surfaceInterpolation;

		//- Runtime type information
		/*TypeName(polyPatch::typeName_());*/
		static const char* typeName_() { return polyPatch::typeName_(); }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			fvPatch,
			polyPatch,
			(const polyPatch& patch, const fvBoundaryMesh& bm),
			(patch, bm)
		);*/

		typedef autoPtr<fvPatch> (*polyPatchConstructorPtr)(const polyPatch& patch, const fvBoundaryMesh& bm);
		typedef HashTable<polyPatchConstructorPtr, word, string::hash> polyPatchConstructorTable;
		static FoamFiniteVolume_EXPORT polyPatchConstructorTable* polyPatchConstructorTablePtr_;
		static FoamFiniteVolume_EXPORT void constructpolyPatchConstructorTables();
		static FoamFiniteVolume_EXPORT void destroypolyPatchConstructorTables();

		template <class fvPatchType>
		class addpolyPatchConstructorToTable
		{
		public:
			static autoPtr<fvPatch> New(const polyPatch& patch, const fvBoundaryMesh& bm)
			{
				return autoPtr<fvPatch>(new fvPatchType(patch, bm));
			}

			addpolyPatchConstructorToTable(const word& lookup = fvPatchType::typeName)
			{
				constructpolyPatchConstructorTables();
				if (!polyPatchConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "fvPatch" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addpolyPatchConstructorToTable() { destroypolyPatchConstructorTables(); }
		};

		template <class fvPatchType>
		class addRemovablepolyPatchConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<fvPatch> New(const polyPatch& patch, const fvBoundaryMesh& bm)
			{
				return autoPtr<fvPatch>(new fvPatchType(patch, bm));
			}

			addRemovablepolyPatchConstructorToTable(const word& lookup = fvPatchType::typeName) : lookup_(lookup)
			{
				constructpolyPatchConstructorTables();
				polyPatchConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablepolyPatchConstructorToTable()
			{
				if (polyPatchConstructorTablePtr_) { polyPatchConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct from polyPatch and fvBoundaryMesh
		FoamFiniteVolume_EXPORT fvPatch(const polyPatch&, const fvBoundaryMesh&);

		//- Disallow default bitwise copy construction
		FoamFiniteVolume_EXPORT fvPatch(const fvPatch&);


		// Selectors

		//- Return a pointer to a new patch created on freestore from polyPatch
		static FoamFiniteVolume_EXPORT autoPtr<fvPatch> New
		(
			const polyPatch&,
			const fvBoundaryMesh&
		);


		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~fvPatch();


		// Member Functions

		// Access

		//- Return the polyPatch
		const polyPatch& patch() const
		{
			return polyPatch_;
		}

		//- Return name
		virtual const word& name() const
		{
			return polyPatch_.name();
		}

		//- Return start label of this patch in the polyMesh face list
		virtual label start() const
		{
			return polyPatch_.start();
		}

		//- Return size
		virtual label size() const
		{
			return polyPatch_.size();
		}

		//- Return true if this patch is coupled
		virtual bool coupled() const
		{
			return polyPatch_.coupled();
		}

		//- Return true if the given type is a constraint type
		static FoamFiniteVolume_EXPORT bool constraintType(const word& pt);

		//- Return a list of all the constraint patch types
		static FoamFiniteVolume_EXPORT wordList constraintTypes();

		//- Return the index of this patch in the fvBoundaryMesh
		label index() const
		{
			return polyPatch_.index();
		}

		//- Return boundaryMesh reference
		const fvBoundaryMesh& boundaryMesh() const
		{
			return boundaryMesh_;
		}

		//- Slice list to patch
		template<class T>
		const typename List<T>::subList patchSlice(const List<T>& l) const
		{
			return typename List<T>::subList(l, size(), start());
		}

		//- Return faceCells
		FoamFiniteVolume_EXPORT virtual const labelUList& faceCells() const;


		// Access functions for geometrical data

			//- Return face centres
		FoamFiniteVolume_EXPORT const vectorField& Cf() const;

		//- Return neighbour cell centres
		FoamFiniteVolume_EXPORT tmp<vectorField> Cn() const;

		//- Return face area vectors
		FoamFiniteVolume_EXPORT const vectorField& Sf() const;

		//- Return face area magnitudes
		FoamFiniteVolume_EXPORT const scalarField& magSf() const;

		//- Return face normals
		FoamFiniteVolume_EXPORT tmp<vectorField> nf() const;

		//- Return cell-centre to face-centre vector
		//  except for coupled patches for which the cell-centre
		//  to coupled-cell-centre vector is returned
		FoamFiniteVolume_EXPORT virtual tmp<vectorField> delta() const;


		// Access functions for demand driven data

		//- Return patch weighting factors
		FoamFiniteVolume_EXPORT const scalarField& weights() const;

		//- Return the face - cell distance coeffient
		//  except for coupled patches for which the cell-centre
		//  to coupled-cell-centre distance coeffient is returned
		FoamFiniteVolume_EXPORT const scalarField& deltaCoeffs() const;


		// Evaluation functions

		//- Return given internal field next to patch as patch field
		template<class Type>
		tmp<Field<Type>> patchInternalField(const UList<Type>&) const;

		//- Return given internal field next to patch as patch field
		template<class Type>
		void patchInternalField(const UList<Type>&, Field<Type>&) const;

		//- Return the corresponding patchField of the named field
		template<class GeometricField, class Type>
		const typename GeometricField::Patch& patchField
		(
			const GeometricField&
		) const;

		//- Return the corresponding patchField reference of the named field
		template<class GeometricField, class Type>
		typename GeometricField::Patch& patchField
		(
			GeometricField&
		) const;

		//- Lookup and return the patchField of the named field from the
		//  local objectRegistry.
		//  N.B.  The dummy pointer arguments are used if this function is
		//  instantiated within a templated function to avoid a bug in gcc.
		//  See inletOutletFvPatchField.C and outletInletFvPatchField.C
		template<class GeometricField, class Type>
		const typename GeometricField::Patch& lookupPatchField
		(
			const word& name,
			const GeometricField* = nullptr,
			const Type* = nullptr
		) const;


		// Member Operators

		//- Disallow default bitwise assignment
		FoamFiniteVolume_EXPORT void operator=(const fvPatch&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fvPatchFvMeshTemplates_Imp.hxx>
#include <fvPatchI.hxx>

//#ifdef NoRepository
//#include <fvPatchTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvPatch_Header
