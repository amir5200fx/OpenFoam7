#pragma once
#ifndef _AMIMethod_Header
#define _AMIMethod_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::AMIMethod

Description
	Base class for Arbitrary Mesh Interface (AMI) methods

SourceFiles
	AMIMethod.C

\*---------------------------------------------------------------------------*/

#include <className.hxx>
#include <DynamicList.hxx>
#include <faceAreaIntersect.hxx>
#include <indexedOctree.hxx>
#include <treeDataPrimitivePatch.hxx>
#include <treeBoundBoxList.hxx>
#include <primitivePatch.hxx>
#include <runTimeSelectionTables.hxx>

#include <PtrList.hxx> //added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class AMIInterpolation;  //added by amir

	/*---------------------------------------------------------------------------*\
							  Class AMIMethod Declaration
	\*---------------------------------------------------------------------------*/

	class AMIMethod
	{
	protected:

		//- Local typedef to octree tree-type
		typedef treeDataPrimitivePatch<primitivePatch> treeType;


		// Protected data

			//- Reference to source patch
		const primitivePatch& srcPatch_;

		//- Reference to target patch
		const primitivePatch& tgtPatch_;

		//- Flag to indicate that the two patches are co-directional and
		//  that the orientation of the target patch should be reversed
		const bool reverseTarget_;

		//- Flag to indicate that the two patches must be matched/an overlap
		//  exists between them
		const bool requireMatch_;

		//- Source face areas
		const scalarField& srcMagSf_;

		//- Target face areas
		const scalarField& tgtMagSf_;

		//- Labels of faces that are not overlapped by any target faces
		//  (should be empty for correct functioning)
		labelList srcNonOverlap_;

		//- Octree used to find face seeds
		autoPtr<indexedOctree<treeType>> treePtr_;

		//- Face triangulation mode
		const faceAreaIntersect::triangulationMode triMode_;


		// Protected Member Functions

			// Helper functions

				//- Check AMI patch coupling
		FoamFvMesh_EXPORT void checkPatches() const;

		//- Initialise and return true if all ok
		FoamFvMesh_EXPORT bool initialise
		(
			labelListList& srcAddress,
			scalarListList& srcWeights,
			labelListList& tgtAddress,
			scalarListList& tgtWeights,
			label& srcFacei,
			label& tgtFacei
		);

		//- Write triangle intersection to OBJ file
		FoamFvMesh_EXPORT void writeIntersectionOBJ
		(
			const scalar area,
			const face& f1,
			const face& f2,
			const pointField& f1Points,
			const pointField& f2Points
		) const;


		// Common AMI method functions

			//- Reset the octree for the target patch face search
		FoamFvMesh_EXPORT void resetTree();

		//- Find face on target patch that overlaps source face
		FoamFvMesh_EXPORT label findTargetFace(const label srcFacei) const;

		//- Add faces neighbouring facei to the ID list
		FoamFvMesh_EXPORT void appendNbrFaces
		(
			const label facei,
			const primitivePatch& patch,
			const DynamicList<label>& visitedFaces,
			DynamicList<label>& faceIDs
		) const;

		//- The maximum edge angle that the walk will cross
		FoamFvMesh_EXPORT virtual scalar maxWalkAngle() const;


	public:

		//- Runtime type information
		//TypeName("AMIMethod");
		static const char* typeName_() { return "AMIMethod"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			AMIMethod,
			components,
			(
				const primitivePatch& srcPatch,
				const primitivePatch& tgtPatch,
				const scalarField& srcMagSf,
				const scalarField& tgtMagSf,
				const faceAreaIntersect::triangulationMode& triMode,
				const bool reverseTarget,
				const bool requireMatch
				),
				(
					srcPatch,
					tgtPatch,
					srcMagSf,
					tgtMagSf,
					triMode,
					reverseTarget,
					requireMatch
					)
		);*/

		typedef autoPtr<AMIMethod> (*componentsConstructorPtr)(const primitivePatch& srcPatch, const primitivePatch& tgtPatch,
		                                                       const scalarField& srcMagSf, const scalarField& tgtMagSf,
		                                                       const faceAreaIntersect::triangulationMode& triMode,
		                                                       const bool reverseTarget, const bool requireMatch);
		typedef HashTable<componentsConstructorPtr, word, string::hash> componentsConstructorTable;
		static FoamFvMesh_EXPORT componentsConstructorTable* componentsConstructorTablePtr_;
		static FoamFvMesh_EXPORT void constructcomponentsConstructorTables();
		static FoamFvMesh_EXPORT void destroycomponentsConstructorTables();

		template <class AMIMethodType>
		class addcomponentsConstructorToTable
		{
		public:
			static autoPtr<AMIMethod> New(const primitivePatch& srcPatch, const primitivePatch& tgtPatch,
			                              const scalarField& srcMagSf, const scalarField& tgtMagSf,
			                              const faceAreaIntersect::triangulationMode& triMode, const bool reverseTarget,
			                              const bool requireMatch)
			{
				return autoPtr<AMIMethod>(new AMIMethodType(srcPatch, tgtPatch, srcMagSf, tgtMagSf, triMode, reverseTarget,
				                                            requireMatch));
			}

			addcomponentsConstructorToTable(const word& lookup = AMIMethodType::typeName)
			{
				constructcomponentsConstructorTables();
				if (!componentsConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "AMIMethod" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addcomponentsConstructorToTable() { destroycomponentsConstructorTables(); }
		};

		template <class AMIMethodType>
		class addRemovablecomponentsConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<AMIMethod> New(const primitivePatch& srcPatch, const primitivePatch& tgtPatch,
			                              const scalarField& srcMagSf, const scalarField& tgtMagSf,
			                              const faceAreaIntersect::triangulationMode& triMode, const bool reverseTarget,
			                              const bool requireMatch)
			{
				return autoPtr<AMIMethod>(new AMIMethodType(srcPatch, tgtPatch, srcMagSf, tgtMagSf, triMode, reverseTarget,
				                                            requireMatch));
			}

			addRemovablecomponentsConstructorToTable(const word& lookup = AMIMethodType::typeName) : lookup_(lookup)
			{
				constructcomponentsConstructorTables();
				componentsConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablecomponentsConstructorToTable()
			{
				if (componentsConstructorTablePtr_) { componentsConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT AMIMethod
		(
			const primitivePatch& srcPatch,
			const primitivePatch& tgtPatch,
			const scalarField& srcMagSf,
			const scalarField& tgtMagSf,
			const faceAreaIntersect::triangulationMode& triMode,
			const bool reverseTarget,
			const bool requireMatch
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT AMIMethod(const AMIMethod&) = delete;


		//- Selector
		static FoamFvMesh_EXPORT autoPtr<AMIMethod> New
		(
			const word& methodName,
			const primitivePatch& srcPatch,
			const primitivePatch& tgtPatch,
			const scalarField& srcMagSf,
			const scalarField& tgtMagSf,
			const faceAreaIntersect::triangulationMode& triMode,
			const bool reverseTarget,
			const bool requireMatch
		);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~AMIMethod();


		// Member Functions

			// Access

				//- Labels of faces that are not overlapped by any target faces
				//  Note: this should be empty for correct functioning
		inline const labelList& srcNonOverlap() const;

		//- Flag to indicate that interpolation patches are conformal
		FoamFvMesh_EXPORT virtual bool conformal() const;


		// Manipulation

			//- Update addressing and weights
		FoamFvMesh_EXPORT virtual void calculate
		(
			labelListList& srcAddress,
			scalarListList& srcWeights,
			labelListList& tgtAddress,
			scalarListList& tgtWeights,
			label srcFacei = -1,
			label tgtFacei = -1
		) = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const AMIMethod&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <AMIMethodI.hxx>

#endif // !_AMIMethod_Header
