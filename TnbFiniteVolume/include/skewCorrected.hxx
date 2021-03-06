#pragma once
#ifndef _skewCorrected_Header
#define _skewCorrected_Header

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
	tnbLib::skewCorrected

Description
	Skewness-corrected interpolation scheme that applies an explicit
	correction to given scheme.

SourceFiles
	skewCorrected.C

\*---------------------------------------------------------------------------*/

#include <surfaceInterpolationScheme.hxx>
#include <skewCorrectionVectors.hxx>
#include <linear.hxx>
#include <gaussGrad.hxx>

#include <Time.hxx>  // added by amir

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamSkewCorrected_EXPORT __declspec(dllexport)
#else
#ifdef FoamSkewCorrected_EXPORT_DEFINE
#define FoamSkewCorrected_EXPORT __declspec(dllexport)
#else
#define FoamSkewCorrected_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class skewCorrected Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class skewCorrected
		:
		public surfaceInterpolationScheme<Type>
	{
		// Private member data

		tmp<surfaceInterpolationScheme<Type>> tScheme_;


	public:

		//- Runtime type information
		/*TypeName("skewCorrected");*/
		static const char* typeName_() { return "skewCorrected"; }
		static FoamSkewCorrected_EXPORT const ::tnbLib::word typeName;
		static FoamSkewCorrected_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh and Istream
		skewCorrected
		(
			const fvMesh& mesh,
			Istream& is
		)
			:
			surfaceInterpolationScheme<Type>(mesh),
			tScheme_
			(
				surfaceInterpolationScheme<Type>::New(mesh, is)
			)
		{}


		//- Construct from mesh, faceFlux and Istream
		skewCorrected
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux,
			Istream& is
		)
			:
			surfaceInterpolationScheme<Type>(mesh),
			tScheme_
			(
				surfaceInterpolationScheme<Type>::New(mesh, faceFlux, is)
			)
		{}

		//- Disallow default bitwise copy construction
		skewCorrected(const skewCorrected&) = delete;


		// Member Functions

			//- Return the interpolation weighting factors
		tmp<surfaceScalarField> weights
		(
			const GeometricField<Type, fvPatchField, volMesh>& vf
		) const
		{
			return tScheme_().weights(vf);
		}

		//- Return true if this scheme uses an explicit correction
		virtual bool corrected() const
		{
			return
				tScheme_().corrected()
				|| skewCorrectionVectors::New(this->mesh()).skew();
		}

		tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			skewCorrection
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			const fvMesh& mesh = this->mesh();

			const skewCorrectionVectors& scv = skewCorrectionVectors::New(mesh);

			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tsfCorr
			(
				new GeometricField<Type, fvsPatchField, surfaceMesh>
				(
					IOobject
					(
						"skewCorrected::skewCorrection(" + vf.name() + ')',
						mesh.time().timeName(),
						mesh
					),
					mesh,
					dimensioned<Type>
					(
						vf.name(),
						vf.dimensions(),
						Zero
						)
					)
			);

			for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
			{
				tsfCorr.ref().replace
				(
					cmpt,
					scv() & linear
					<
					typename outerProduct
					<
					vector,
					typename pTraits<Type>::cmptType
					>::type
					>(mesh).interpolate
					(
						fv::gaussGrad<typename pTraits<Type>::cmptType>
						(mesh).grad(vf.component(cmpt))
					)
				);
			}

			return tsfCorr;
		}


		//- Return the explicit correction to the face-interpolate
		virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			correction
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			if
				(
					tScheme_().corrected()
					&& skewCorrectionVectors::New(this->mesh()).skew()
					)
			{
				return tScheme_().correction(vf) + skewCorrection(vf);
			}
			else if (tScheme_().corrected())
			{
				return tScheme_().correction(vf);
			}
			else if (skewCorrectionVectors::New(this->mesh()).skew())
			{
				return skewCorrection(vf);
			}
			else
			{
				return
					tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
					(
						nullptr
						);
			}
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const skewCorrected&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_skewCorrected_Header
