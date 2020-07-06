#include <PatchToPatchInterpolationTemplate.hxx>

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

Description
	Patch to patch interpolation functions

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class FromPatch, class ToPatch>
	template<class Type>
	tmp<Field<Type>>
		PatchToPatchInterpolation<FromPatch, ToPatch>::pointInterpolate
		(
			const Field<Type>& pf
		) const
	{
		if (pf.size() != fromPatch_.nPoints())
		{
			FatalErrorInFunction
				<< "given field does not correspond to patch. Patch size: "
				<< fromPatch_.nPoints() << " field size: " << pf.size()
				<< abort(FatalError);
		}

		tmp<Field<Type>> tresult
		(
			new Field<Type>(toPatch_.nPoints(), Zero)
		);

		Field<Type>& result = tresult.ref();

		const List<typename FromPatch::FaceType>& fromPatchLocalFaces =
			fromPatch_.localFaces();

		const FieldField<Field, scalar>& weights = pointWeights();

		const labelList& addr = pointAddr();

		forAll(result, pointi)
		{
			const scalarField& curWeights = weights[pointi];

			if (addr[pointi] > -1)
			{
				const labelList& hitFacePoints =
					fromPatchLocalFaces[addr[pointi]];

				forAll(curWeights, wI)
				{
					result[pointi] += curWeights[wI] * pf[hitFacePoints[wI]];
				}
			}
		}

		return tresult;
	}


	template<class FromPatch, class ToPatch>
	template<class Type>
	tmp<Field<Type>>
		PatchToPatchInterpolation<FromPatch, ToPatch>::pointInterpolate
		(
			const tmp<Field<Type>>& tpf
		) const
	{
		tmp<Field<Type>> tint = pointInterpolate<Type>(tpf());
		tpf.clear();
		return tint;
	}


	template<class FromPatch, class ToPatch>
	template<class Type>
	tmp<Field<Type>>
		PatchToPatchInterpolation<FromPatch, ToPatch>::faceInterpolate
		(
			const Field<Type>& ff
		) const
	{
		if (ff.size() != fromPatch_.size())
		{
			FatalErrorInFunction
				<< "given field does not correspond to patch. Patch size: "
				<< fromPatch_.size() << " field size: " << ff.size()
				<< abort(FatalError);
		}

		tmp<Field<Type>> tresult
		(
			new Field<Type>(toPatch_.size(), Zero)
		);

		Field<Type>& result = tresult.ref();

		const labelListList& fromPatchFaceFaces = fromPatch_.faceFaces();

		const FieldField<Field, scalar>& weights = faceWeights();

		const labelList& addr = faceAddr();

		forAll(result, facei)
		{
			const scalarField& curWeights = weights[facei];

			if (addr[facei] > -1)
			{
				const labelList& hitFaceFaces =
					fromPatchFaceFaces[addr[facei]];

				// first add the hit face
				result[facei] += ff[addr[facei]] * curWeights[0];

				for (label wI = 1; wI < curWeights.size(); wI++)
				{
					result[facei] += ff[hitFaceFaces[wI - 1]] * curWeights[wI];
				}
			}
		}

		return tresult;
	}


	template<class FromPatch, class ToPatch>
	template<class Type>
	tmp<Field<Type>>
		PatchToPatchInterpolation<FromPatch, ToPatch>::faceInterpolate
		(
			const tmp<Field<Type>>& tff
		) const
	{
		tmp<Field<Type>> tint = faceInterpolate(tff());
		tff.clear();
		return tint;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //