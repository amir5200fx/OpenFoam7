#pragma once
#ifndef _cyclicACMIFvPatch_Header
#define _cyclicACMIFvPatch_Header

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
	tnbLib::cyclicACMIFvPatch

Description
	Cyclic patch for Arbitrarily Coupled Mesh Interface (ACMI)

SourceFiles
	cyclicACMIFvPatch.C

\*---------------------------------------------------------------------------*/

#include <cyclicAMIFvPatch.hxx>
#include <cyclicACMIPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class cyclicACMIFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicACMIFvPatch
		:
		public cyclicAMIFvPatch
	{
		// Private Member Functions

			//- Update the patch areas after AMI update
		void updateAreas() const;


	protected:

		// Protected Member functions

			//- Make patch weighting factors
		FoamFiniteVolume_EXPORT virtual void makeWeights(scalarField&) const;


	public:

		//- Runtime type information
		/*TypeName(cyclicACMIPolyPatch::typeName_());*/
		static const char* typeName_() { return cyclicACMIPolyPatch::typeName_(); }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from polyPatch
		cyclicACMIFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
			:
			cyclicAMIFvPatch(patch, bm)
		{}


		// Member Functions

			// Access

				//- Return a reference to the AMI interpolators
		virtual const PtrList<AMIInterpolation>& AMIs() const
		{
			const PtrList<AMIInterpolation>& AMIs =
				cyclicAMIFvPatch::AMIs();

			updateAreas();

			return AMIs;
		}

		//- Return a reference to the AMI transformations
		virtual const List<vectorTensorTransform>& AMITransforms() const
		{
			const List<vectorTensorTransform>& AMITransforms =
				cyclicAMIFvPatch::AMITransforms();

			updateAreas();

			return AMITransforms;
		}

		//- Return the poly patch
		const cyclicACMIPolyPatch& cyclicACMIPatch() const
		{
			return refCast<const cyclicACMIPolyPatch>(this->patch());
		}

		//- Return the neighbour patch
		const cyclicACMIFvPatch& neighbFvPatch() const
		{
			return refCast<const cyclicACMIFvPatch>
				(
					this->boundaryMesh()[this->cyclicAMIPatch().neighbPatchID()]
					);
		}

		//- Return the non-overlap patch
		const fvPatch& nonOverlapFvPatch() const
		{
			return this->boundaryMesh()
				[
					cyclicACMIPatch().nonOverlapPatchID()
				];
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_cyclicACMIFvPatch_Header
