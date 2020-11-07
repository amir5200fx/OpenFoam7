#pragma once
#ifndef _outletStabilised_Header
#define _outletStabilised_Header

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
	tnbLib::outletStabilised

Description
	Outlet-stabilised interpolation scheme which applies upwind differencing
	to the faces of the cells adjacent to outlets.

	This is particularly useful to stabilise the velocity at entrainment
	boundaries for LES cases using linear or other centred differencing
	schemes.

SourceFiles
	outletStabilised.C

\*---------------------------------------------------------------------------*/

#include <surfaceInterpolationScheme.hxx>
#include <skewCorrectionVectors.hxx>
#include <linear.hxx>
#include <gaussGrad.hxx>
#include <zeroGradientFvPatchField.hxx>
#include <mixedFvPatchField.hxx>
#include <directionMixedFvPatchField.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamOutletStabilised_EXPORT __declspec(dllexport)
#else
#ifdef FoamOutletStabilised_EXPORT_DEFINE
#define FoamOutletStabilised_EXPORT __declspec(dllexport)
#else
#define FoamOutletStabilised_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class outletStabilised Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class outletStabilised
		:
		public surfaceInterpolationScheme<Type>
	{
		// Private member data

		const surfaceScalarField& faceFlux_;
		tmp<surfaceInterpolationScheme<Type>> tScheme_;


	public:

		//- Runtime type information
		/*TypeName("outletStabilised");*/
		static const char* typeName_() { return "outletStabilised"; }
		static FoamOutletStabilised_EXPORT const ::tnbLib::word typeName;
		static FoamOutletStabilised_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh and Istream
		outletStabilised
		(
			const fvMesh& mesh,
			Istream& is
		)
			:
			surfaceInterpolationScheme<Type>(mesh),
			faceFlux_
			(
				mesh.lookupObject<surfaceScalarField>
				(
					word(is)
					)
			),
			tScheme_
			(
				surfaceInterpolationScheme<Type>::New(mesh, faceFlux_, is)
			)
		{}


		//- Construct from mesh, faceFlux and Istream
		outletStabilised
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux,
			Istream& is
		)
			:
			surfaceInterpolationScheme<Type>(mesh),
			faceFlux_(faceFlux),
			tScheme_
			(
				surfaceInterpolationScheme<Type>::New(mesh, faceFlux, is)
			)
		{}

		//- Disallow default bitwise copy construction
		outletStabilised(const outletStabilised&) = delete;


		// Member Functions

			//- Return the interpolation weighting factors
		tmp<surfaceScalarField> weights
		(
			const GeometricField<Type, fvPatchField, volMesh>& vf
		) const
		{
			tmp<surfaceScalarField> tw = tScheme_().weights(vf);
			surfaceScalarField& w = tw.ref();

			const fvMesh& mesh_ = this->mesh();
			const cellList& cells = mesh_.cells();

			forAll(vf.boundaryField(), patchi)
			{
				if
					(
						isA<zeroGradientFvPatchField<Type>>
						(vf.boundaryField()[patchi])
						|| isA<mixedFvPatchField<Type>>(vf.boundaryField()[patchi])
						|| isA<directionMixedFvPatchField<Type>>
						(vf.boundaryField()[patchi])
						)
				{
					const labelList& pFaceCells =
						mesh_.boundary()[patchi].faceCells();

					forAll(pFaceCells, pFacei)
					{
						const cell& pFaceCell = cells[pFaceCells[pFacei]];

						forAll(pFaceCell, fi)
						{
							label facei = pFaceCell[fi];

							if (mesh_.isInternalFace(facei))
							{
								// Apply upwind differencing
								w[facei] = pos0(faceFlux_[facei]);
							}
						}
					}
				}
			}

			return tw;
		}

		//- Return true if this scheme uses an explicit correction
		virtual bool corrected() const
		{
			return tScheme_().corrected();
		}

		//- Return the explicit correction to the face-interpolate
		//  set to zero on the near-boundary faces where upwind is applied
		virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			correction
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			if (tScheme_().corrected())
			{
				tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tcorr =
					tScheme_().correction(vf);

				GeometricField<Type, fvsPatchField, surfaceMesh>& corr =
					tcorr.ref();

				const fvMesh& mesh_ = this->mesh();
				const cellList& cells = mesh_.cells();

				forAll(vf.boundaryField(), patchi)
				{
					if
						(
							isA<zeroGradientFvPatchField<Type>>
							(vf.boundaryField()[patchi])
							|| isA<mixedFvPatchField<Type>>
							(vf.boundaryField()[patchi])
							)
					{
						const labelList& pFaceCells =
							mesh_.boundary()[patchi].faceCells();

						forAll(pFaceCells, pFacei)
						{
							const cell& pFaceCell = cells[pFaceCells[pFacei]];

							forAll(pFaceCell, fi)
							{
								label facei = pFaceCell[fi];

								if (mesh_.isInternalFace(facei))
								{
									// Remove correction
									corr[facei] = Zero;
								}
							}
						}
					}
				}

				return tcorr;
			}
			else
			{
				return tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
					(
						nullptr
						);
			}
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const outletStabilised&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_outletStabilised_Header
