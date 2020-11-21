#pragma once
#ifndef _regionCoupledBase_Header
#define _regionCoupledBase_Header

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
	tnbLib::regionCoupledBase

Description
	Base class with common functinality for regionCoupled polyPatch.
	It includes AMI.


SourceFiles
	regionCoupledBase.C

\*---------------------------------------------------------------------------*/

#include <AMIInterpolation.hxx>
#include <polyBoundaryMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class regionCoupledBase Declaration
	\*---------------------------------------------------------------------------*/

	class regionCoupledBase
	{
		// Private Data

			//- Patch to sample
		const polyPatch& patch_;

		//- Name of other half
		const word nbrPatchName_;

		//- Index of other half
		mutable label nbrPatchID_;

		//- Name of other region
		const word nbrRegionName_;

		//- Same region
		const bool sameRegion_;

		//- AMI interpolation class
		mutable autoPtr<AMIInterpolation> AMIPtr_;

		//- Flag to indicate that slave patch should be reversed for AMI
		const bool AMIReverse_;

		//- Projection surface
		mutable autoPtr<searchableSurface> surfPtr_;

		//- Dictionary used during projection surface construction
		const dictionary surfDict_;


		// Private Member Functions

			//- Reset the AMI interpolator
		FoamFvMesh_EXPORT void resetAMI() const;


	protected:


		//- Clear geometry
		FoamFvMesh_EXPORT virtual void clearGeom();


	public:

		//- Runtime type information
		/*TypeName("regionCoupledBase");*/
		static const char* typeName_() { return "regionCoupledBase"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch
		FoamFvMesh_EXPORT regionCoupledBase(const polyPatch&);

		//- Construct from dictionary
		FoamFvMesh_EXPORT regionCoupledBase(const polyPatch&, const dictionary&);

		//- Construct as copy, resetting patch
		FoamFvMesh_EXPORT regionCoupledBase(const polyPatch&, const regionCoupledBase&);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~regionCoupledBase();


		// Member Functions


			// Access

				//- Neighbour patch name
		const word& nbrPatchName() const
		{
			return nbrPatchName_;
		}

		//- Neighbour region name
		const word& nbrRegionName() const
		{
			return nbrRegionName_;
		}

		//- Cached sampleRegion != mesh.name()
		bool sameRegion() const
		{
			return sameRegion_;
		}

		//- Neighbour patch ID
		FoamFvMesh_EXPORT label neighbPatchID() const;

		//- Does this side own the patch?
		FoamFvMesh_EXPORT bool owner() const;

		//- Return a reference to the neighbour patch
		FoamFvMesh_EXPORT const regionCoupledBase& neighbPatch() const;

		//- Return a reference to the projection surface
		FoamFvMesh_EXPORT const autoPtr<searchableSurface>& surfPtr() const;

		//- Return a reference to the AMI interpolator
		FoamFvMesh_EXPORT const AMIInterpolation& AMI() const;


		// Interpolations

			//- Interpolate field
		template<class Type>
		tmp<Field<Type>> interpolate(const Field<Type>& fld) const;

		//- Interpolate tmp field
		template<class Type>
		tmp<Field<Type>> interpolate
		(
			const tmp<Field<Type>>& tFld
		) const;

		//- Low-level interpolate List
		template<class Type, class BinaryOp>
		void interpolate
		(
			const UList<Type>& fld,
			const BinaryOp& bop,
			List<Type>& result
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


		//- Return the type
		FoamFvMesh_EXPORT virtual const word& regionCoupleType() const = 0;

		//- Write the polyPatch data as a dictionary
		FoamFvMesh_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <regionCoupledBaseI.hxx>

//#ifdef NoRepository
//#include <regionCoupledBaseTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_regionCoupledBase_Header
