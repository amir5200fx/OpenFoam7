#pragma once
#ifndef _cyclicAMIPolyPatch_Header
#define _cyclicAMIPolyPatch_Header

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
	tnbLib::cyclicAMIPolyPatch

Description
	Cyclic patch for Arbitrary Mesh Interface (AMI)

SourceFiles
	cyclicAMIPolyPatch.C

\*---------------------------------------------------------------------------*/

#include <coupledPolyPatch.hxx>
#include <AMIInterpolation.hxx>
#include <polyBoundaryMesh.hxx>
#include <coupleGroupIdentifier.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class cyclicAMIPolyPatch Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicAMIPolyPatch
		:
		public coupledPolyPatch
	{
		// Private Member Functions

			//- Return normal of face at max distance from rotation axis
		FoamFvMesh_EXPORT vector findFaceNormalMaxRadius(const pointField& faceCentres) const;

		FoamFvMesh_EXPORT void calcTransforms
		(
			const primitivePatch& half0,
			const pointField& half0Ctrs,
			const vectorField& half0Areas,
			const pointField& half1Ctrs,
			const vectorField& half1Areas
		);


	protected:

		// Protected data

			//- Name of other half
		mutable word nbrPatchName_;

		//- Optional patchGroup to find neighbPatch
		const coupleGroupIdentifier coupleGroup_;

		//- Index of other half
		mutable label nbrPatchID_;


		// Transformations

			// For rotation

				//- Axis of rotation for rotational cyclics
		vector rotationAxis_;

		//- Point on axis of rotation for rotational cyclics
		point rotationCentre_;

		//- Flag to show whether the rotation angle is defined
		bool rotationAngleDefined_;

		//- Rotation angle
		scalar rotationAngle_;


		// For translation

			//- Translation vector
		vector separationVector_;


		//- AMI interpolation classes
		mutable PtrList<AMIInterpolation> AMIs_;

		//- AMI transforms (from source to target)
		mutable List<vectorTensorTransform> AMITransforms_;

		//- Flag to indicate that slave patch should be reversed for AMI
		const bool AMIReverse_;

		//- Flag to indicate that patches should match/overlap
		const bool AMIRequireMatch_;

		//- Low weight correction threshold for AMI
		const scalar AMILowWeightCorrection_;

		//- AMI Method
		const AMIInterpolation::interpolationMethod AMIMethod_;

		//- Projection surface
		mutable autoPtr<searchableSurface> surfPtr_;

		//- Dictionary used during projection surface construction
		const dictionary surfDict_;


		// Protected Member Functions

			//- Reset the AMI interpolator
		FoamFvMesh_EXPORT virtual void resetAMI() const;

		//- Recalculate the transformation tensors
		FoamFvMesh_EXPORT virtual void calcTransforms();

		//- Initialise the calculation of the patch geometry
		FoamFvMesh_EXPORT virtual void initGeometry(PstreamBuffers&);

		//- Calculate the patch geometry
		FoamFvMesh_EXPORT virtual void calcGeometry(PstreamBuffers&);

		//- Initialise the patches for moving points
		FoamFvMesh_EXPORT virtual void initMovePoints(PstreamBuffers& pBufs, const pointField&);

		//- Correct patches after moving points
		FoamFvMesh_EXPORT virtual void movePoints(PstreamBuffers& pBufs, const pointField&);

		//- Initialise the update of the patch topology
		FoamFvMesh_EXPORT virtual void initUpdateMesh(PstreamBuffers&);

		//- Update of the patch topology
		FoamFvMesh_EXPORT virtual void updateMesh(PstreamBuffers&);

		//- Clear geometry
		FoamFvMesh_EXPORT virtual void clearGeom();


	public:

		//- Runtime type information
		//TypeName("cyclicAMI");
		static const char* typeName_() { return "cyclicAMI"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from (base couped patch) components
		FoamFvMesh_EXPORT cyclicAMIPolyPatch
		(
			const word& name,
			const label size,
			const label start,
			const label index,
			const polyBoundaryMesh& bm,
			const word& patchType,
			const transformType transform = UNKNOWN,
			const bool AMIRequireMatch = true,
			const AMIInterpolation::interpolationMethod AMIMethod =
			AMIInterpolation::imFaceAreaWeight
		);

		//- Construct from dictionary
		FoamFvMesh_EXPORT cyclicAMIPolyPatch
		(
			const word& name,
			const dictionary& dict,
			const label index,
			const polyBoundaryMesh& bm,
			const word& patchType,
			const bool AMIRequireMatch = true,
			const AMIInterpolation::interpolationMethod AMIMethod =
			AMIInterpolation::imFaceAreaWeight
		);

		//- Construct as copy, resetting the boundary mesh
		FoamFvMesh_EXPORT cyclicAMIPolyPatch(const cyclicAMIPolyPatch&, const polyBoundaryMesh&);

		//- Construct given the original patch and resetting the
		//  face list and boundary mesh information
		FoamFvMesh_EXPORT cyclicAMIPolyPatch
		(
			const cyclicAMIPolyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart,
			const word& nbrPatchName
		);

		//- Construct given the original patch and a map
		FoamFvMesh_EXPORT cyclicAMIPolyPatch
		(
			const cyclicAMIPolyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const labelUList& mapAddressing,
			const label newStart
		);


		//- Construct and return a clone, resetting the boundary mesh
		virtual autoPtr<polyPatch> clone(const polyBoundaryMesh& bm) const
		{
			return autoPtr<polyPatch>(new cyclicAMIPolyPatch(*this, bm));
		}

		//- Construct and return a clone, resetting the face list
		//  and boundary mesh
		virtual autoPtr<polyPatch> clone
		(
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart
		) const
		{
			return autoPtr<polyPatch>
				(
					new cyclicAMIPolyPatch
					(
						*this,
						bm,
						index,
						newSize,
						newStart,
						nbrPatchName_
					)
					);
		}

		//- Construct and return a clone, resetting the face list
		//  and boundary mesh
		virtual autoPtr<polyPatch> clone
		(
			const polyBoundaryMesh& bm,
			const label index,
			const labelUList& mapAddressing,
			const label newStart
		) const
		{
			return autoPtr<polyPatch>
				(
					new cyclicAMIPolyPatch
					(
						*this,
						bm,
						index,
						mapAddressing,
						newStart
					)
					);
		}


		//- Destructor
		FoamFvMesh_EXPORT virtual ~cyclicAMIPolyPatch();


		// Member Functions

			// Access

				//- Is patch 'coupled'. Note that on AMI the geometry is not
				//  coupled but the fields are!
		virtual bool coupled() const
		{
			return false;
		}

		//- Neighbour patch name
		inline const word& neighbPatchName() const;

		//- Neighbour patch ID
		FoamFvMesh_EXPORT virtual label neighbPatchID() const;

		//- Does this side own the patch?
		FoamFvMesh_EXPORT virtual bool owner() const;

		//- Return a reference to the neighbour patch
		FoamFvMesh_EXPORT virtual const cyclicAMIPolyPatch& neighbPatch() const;

		//- Return a reference to the projection surface
		FoamFvMesh_EXPORT const autoPtr<searchableSurface>& surfPtr() const;

		//- Return a reference to the AMI interpolators
		FoamFvMesh_EXPORT const PtrList<AMIInterpolation>& AMIs() const;

		//- Return a reference to the AMI transforms
		FoamFvMesh_EXPORT const List<vectorTensorTransform>& AMITransforms() const;

		//- Return true if applying the low weight correction
		FoamFvMesh_EXPORT bool applyLowWeightCorrection() const;

		//- Return the weights sum for this patch
		FoamFvMesh_EXPORT virtual const scalarField& weightsSum() const;

		//- Return the weights sum for the neighbour patch
		FoamFvMesh_EXPORT virtual const scalarField& neighbWeightsSum() const;



		// Transformations

			//- Axis of rotation for rotational cyclic AMI
		inline const vector& rotationAxis() const;

		//- Point on axis of rotation for rotational cyclic AMI
		inline const point& rotationCentre() const;

		//- Translation vector for translational cyclic AMI
		inline const vector& separationVector() const;

		//- Transform patch-based positions from nbr side to this side
		virtual void transformPosition(pointField&) const;

		//- Transform a patch-based position from nbr side to this side
		FoamFvMesh_EXPORT virtual void transformPosition
		(
			point& l,
			const label facei
		) const;

		//- Transform a patch-based direction from nbr side to this side
		FoamFvMesh_EXPORT virtual void transformDirection
		(
			vector& d,
			const label facei
		) const;

		//- Transform a patch-based position from this side to nbr side
		FoamFvMesh_EXPORT virtual void reverseTransformPosition
		(
			point& l,
			const label facei
		) const;

		//- Transform a patch-based direction from this side to nbr side
		FoamFvMesh_EXPORT virtual void reverseTransformDirection
		(
			vector& d,
			const label facei
		) const;


		// Interpolations

			//- Interpolate field
		template<class Type>
		tmp<Field<Type>> interpolate
		(
			const Field<Type>& fld,
			const UList<Type>& defaultValues = UList<Type>()
		) const;

		//- Interpolate tmp field
		template<class Type>
		tmp<Field<Type>> interpolate
		(
			const tmp<Field<Type>>& tFld,
			const UList<Type>& defaultValues = UList<Type>()
		) const;

		//- Interpolate field component
		FoamFvMesh_EXPORT tmp<scalarField> interpolate
		(
			const scalarField& field,
			const direction cmpt,
			const direction rank,
			const scalarUList& defaultValues = scalarUList()
		) const;


		//- Calculate the patch geometry
		FoamFvMesh_EXPORT virtual void calcGeometry
		(
			const primitivePatch& referPatch,
			const pointField& thisCtrs,
			const vectorField& thisAreas,
			const pointField& thisCc,
			const pointField& nbrCtrs,
			const vectorField& nbrAreas,
			const pointField& nbrCc
		);

		//- Initialize ordering for primitivePatch. Does not
		//  refer to *this (except for name() and type() etc.)
		FoamFvMesh_EXPORT virtual void initOrder
		(
			PstreamBuffers&,
			const primitivePatch&
		) const;

		//- Return new ordering for primitivePatch.
		//  Ordering is -faceMap: for every face
		//  index of the new face -rotation:for every new face the clockwise
		//  shift of the original face. Return false if nothing changes
		//  (faceMap is identity, rotation is 0), true otherwise.
		FoamFvMesh_EXPORT virtual bool order
		(
			PstreamBuffers&,
			const primitivePatch&,
			labelList& faceMap,
			labelList& rotation
		) const;

		//- Return the transform and face indices on neighbour patch which
		//  shares point p following trajectory vector n
		FoamFvMesh_EXPORT labelPair pointAMIAndFace
		(
			const label facei,
			const vector& n,
			point& p
		) const;

		//- Index of processor that holds all of both sides, or -1 if
		//  distributed
		FoamFvMesh_EXPORT label singlePatchProc() const;

		//- Write the polyPatch data as a dictionary
		FoamFvMesh_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <cyclicAMIPolyPatchI.hxx>
#include <cyclicAMIPolyPatchTemplatesI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include <cyclicAMIPolyPatchTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicAMIPolyPatch_Header
