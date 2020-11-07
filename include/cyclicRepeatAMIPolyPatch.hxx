#pragma once
#ifndef _cyclicRepeatAMIPolyPatch_Header
#define _cyclicRepeatAMIPolyPatch_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018 OpenFOAM Foundation
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
	tnbLib::cyclicRepeatAMIPolyPatch

Description
	Repeat patch for Arbitrary Mesh Interface (AMI)

SourceFiles
	cyclicRepeatAMIPolyPatch.C

\*---------------------------------------------------------------------------*/

#include <cyclicAMIPolyPatch.hxx>
#include <AMIInterpolation.hxx>
#include <polyBoundaryMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class cyclicRepeatAMIPolyPatch Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicRepeatAMIPolyPatch
		:
		public cyclicAMIPolyPatch
	{
	protected:

		// Protected data

			//- Name of the transform patch
		mutable word transformPatchName_;

		//- Index of the transform patch
		mutable label transformPatchID_;


		// Protected Member Functions

			//- Reset the AMI interpolator
		FoamFvMesh_EXPORT virtual void resetAMI() const;


	public:

		//- Runtime type information
		//TypeName("cyclicRepeatAMI");
		static const char* typeName_() { return "cyclicRepeatAMI"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from (base couped patch) components
		FoamFvMesh_EXPORT cyclicRepeatAMIPolyPatch
		(
			const word& name,
			const label size,
			const label start,
			const label index,
			const polyBoundaryMesh& bm,
			const word& patchType,
			const transformType transform = UNKNOWN
		);

		//- Construct from dictionary
		FoamFvMesh_EXPORT cyclicRepeatAMIPolyPatch
		(
			const word& name,
			const dictionary& dict,
			const label index,
			const polyBoundaryMesh& bm,
			const word& patchType
		);

		//- Construct as copy, resetting the boundary mesh
		FoamFvMesh_EXPORT cyclicRepeatAMIPolyPatch
		(
			const cyclicRepeatAMIPolyPatch&,
			const polyBoundaryMesh&
		);

		//- Construct given the original patch and resetting the
		//  face list and boundary mesh information
		FoamFvMesh_EXPORT cyclicRepeatAMIPolyPatch
		(
			const cyclicRepeatAMIPolyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart,
			const word& nbrPatchName
		);

		//- Construct given the original patch and a map
		FoamFvMesh_EXPORT cyclicRepeatAMIPolyPatch
		(
			const cyclicRepeatAMIPolyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const labelUList& mapAddressing,
			const label newStart
		);


		//- Construct and return a clone, resetting the boundary mesh
		virtual autoPtr<polyPatch> clone(const polyBoundaryMesh& bm) const
		{
			return autoPtr<polyPatch>(new cyclicRepeatAMIPolyPatch(*this, bm));
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
					new cyclicRepeatAMIPolyPatch
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
					new cyclicRepeatAMIPolyPatch
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
		FoamFvMesh_EXPORT virtual ~cyclicRepeatAMIPolyPatch();


		// Member Functions

			// Access

				//- Return a reference to the neighbour patch
		FoamFvMesh_EXPORT virtual const cyclicRepeatAMIPolyPatch& neighbPatch() const;

		//- Neighbour patch name
		inline const word& transformPatchName() const;

		//- Neighbour patch ID
		FoamFvMesh_EXPORT virtual label transformPatchID() const;

		//- Return a reference to the transform patch
		FoamFvMesh_EXPORT virtual const coupledPolyPatch& transformPatch() const;

		//- Return the weights sum for this patch
		FoamFvMesh_EXPORT virtual const scalarField& weightsSum() const;

		//- Return the weights sum for the neighbour patch
		FoamFvMesh_EXPORT virtual const scalarField& neighbWeightsSum() const;


		//- Write the polyPatch data as a dictionary
		FoamFvMesh_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <cyclicRepeatAMIPolyPatchI.hxx>

#endif // !_cyclicRepeatAMIPolyPatch_Header
