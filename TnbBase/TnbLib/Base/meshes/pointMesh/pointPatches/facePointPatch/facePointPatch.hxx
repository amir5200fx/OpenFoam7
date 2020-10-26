#pragma once
#ifndef _facePointPatch_Header
#define _facePointPatch_Header

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
	tnbLib::facePointPatch

Description
	A pointPatch based on a polyPatch

SourceFiles
	facePointPatch.C
	newPointPatch.C

\*---------------------------------------------------------------------------*/

#include <pointPatch.hxx>
#include <polyPatch.hxx>
#include <autoPtr.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class processorPointPatch;
	class cyclicPointPatch;

	/*---------------------------------------------------------------------------*\
					  Class facePointPatch Declaration
	\*---------------------------------------------------------------------------*/

	class facePointPatch
		:
		public pointPatch
	{
	protected:

		// Protected data

			//- Reference to the underlying polyPatch
		const polyPatch& polyPatch_;


		// Protected Member Functions

			//- Initialise the calculation of the patch geometry
		FoamBase_EXPORT virtual void initGeometry(PstreamBuffers&);

		//- Calculate the patch geometry
		FoamBase_EXPORT virtual void calcGeometry(PstreamBuffers&);

		//- Initialise the patches for moving points
		FoamBase_EXPORT virtual void initMovePoints(PstreamBuffers&, const pointField&);

		//- Correct patches after moving points
		FoamBase_EXPORT virtual void movePoints(PstreamBuffers&, const pointField&);

		//- Initialise the update of the patch topology
		FoamBase_EXPORT virtual void initUpdateMesh(PstreamBuffers&);

		//- Update of the patch topology
		FoamBase_EXPORT virtual void updateMesh(PstreamBuffers&);


	public:

		// Declare friendship with the coupledPointPatches to allow them to extend
		// the set of points with those not associated with faces
		friend class processorPointPatch;
		friend class cyclicPointPatch;


		//- Runtime type information
		//TypeName(polyPatch::typeName_());
		static const char* typeName_() { return polyPatch::typeName_(); }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			facePointPatch,
			polyPatch,
			(const polyPatch& patch, const pointBoundaryMesh& bm),
			(patch, bm)
		);*/

		typedef autoPtr<facePointPatch> (*polyPatchConstructorPtr)(const polyPatch& patch, const pointBoundaryMesh& bm);
		typedef HashTable<polyPatchConstructorPtr, word, string::hash> polyPatchConstructorTable;
		static FoamBase_EXPORT polyPatchConstructorTable* polyPatchConstructorTablePtr_;
		static FoamBase_EXPORT void constructpolyPatchConstructorTables();
		static FoamBase_EXPORT void destroypolyPatchConstructorTables();

		template <class facePointPatchType>
		class addpolyPatchConstructorToTable
		{
		public:
			static autoPtr<facePointPatch> New(const polyPatch& patch, const pointBoundaryMesh& bm)
			{
				return autoPtr<facePointPatch>(new facePointPatchType(patch, bm));
			}

			addpolyPatchConstructorToTable(const word& lookup = facePointPatchType::typeName)
			{
				constructpolyPatchConstructorTables();
				if (!polyPatchConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "facePointPatch" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addpolyPatchConstructorToTable() { destroypolyPatchConstructorTables(); }
		};

		template <class facePointPatchType>
		class addRemovablepolyPatchConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<facePointPatch> New(const polyPatch& patch, const pointBoundaryMesh& bm)
			{
				return autoPtr<facePointPatch>(new facePointPatchType(patch, bm));
			}

			addRemovablepolyPatchConstructorToTable(const word& lookup = facePointPatchType::typeName) : lookup_(lookup)
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

			//- Construct from polyPatch
		FoamBase_EXPORT facePointPatch
		(
			const polyPatch&,
			const pointBoundaryMesh&
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT facePointPatch(const facePointPatch&) = delete;


		// Selectors

			//- Return a pointer to a new patch created on freestore from polyPatch
		static FoamBase_EXPORT autoPtr<facePointPatch> New
		(
			const polyPatch&,
			const pointBoundaryMesh&
		);


		//- Destructor
		virtual ~facePointPatch()
		{}


		// Member Functions

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

		//- Return size
		virtual label size() const
		{
			return meshPoints().size();
		}

		//- Return the index of this patch in the pointBoundaryMesh
		virtual label index() const
		{
			return polyPatch_.index();
		}

		//- Return true if this patch field is coupled
		virtual bool coupled() const
		{
			return polyPatch_.coupled();
		}

		//- Return mesh points
		virtual const labelList& meshPoints() const
		{
			return polyPatch_.meshPoints();
		}


		//- Return pointField of points in patch
		virtual const pointField& localPoints() const
		{
			return polyPatch_.localPoints();
		}


		//- Return point unit normals
		virtual const vectorField& pointNormals() const
		{
			return polyPatch_.pointNormals();
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const facePointPatch&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_facePointPatch_Header
