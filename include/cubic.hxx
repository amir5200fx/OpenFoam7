#pragma once
#ifndef _cubic_Header
#define _cubic_Header

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
	tnbLib::cubic

Description
	Cubic interpolation scheme class derived from linear and returns
	linear weighting factors but also applies an explicit correction.

SourceFiles
	cubic.C

\*---------------------------------------------------------------------------*/

#include <linear.hxx>
#include <gaussGrad.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamCubic_EXPORT __declspec(dllexport)
#else
#ifdef FoamCubic_EXPORT_DEFINE
#define FoamCubic_EXPORT __declspec(dllexport)
#else
#define FoamCubic_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class cubic Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class cubic
		:
		public linear<Type>
	{

	public:

		//- Runtime type information
		/*TypeName("cubic");*/
		static const char* typeName_() { return "cubic"; }
		static FoamCubic_EXPORT const ::tnbLib::word typeName;
		static FoamCubic_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh
		cubic(const fvMesh& mesh)
			:
			linear<Type>(mesh)
		{}

		//- Construct from mesh and Istream
		cubic
		(
			const fvMesh& mesh,
			Istream&
		)
			:
			linear<Type>(mesh)
		{}

		//- Construct from mesh, faceFlux and Istream
		cubic
		(
			const fvMesh& mesh,
			const surfaceScalarField&,
			Istream&
		)
			:
			linear<Type>(mesh)
		{}

		//- Disallow default bitwise copy construction
		cubic(const cubic&) = delete;


		// Member Functions

			//- Return true if this scheme uses an explicit correction
		virtual bool corrected() const
		{
			return true;
		}

		//- Return the explicit correction to the face-interpolate
		virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
			correction
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			const fvMesh& mesh = this->mesh();

			// calculate the appropriate interpolation factors
			const surfaceScalarField& lambda = mesh.weights();

			const surfaceScalarField kSc
			(
				lambda*(scalar(1) - lambda * (scalar(3) - scalar(2)*lambda))
			);

			const surfaceScalarField kVecP(sqr(scalar(1) - lambda)*lambda);
			const surfaceScalarField kVecN(sqr(lambda)*(lambda - scalar(1)));

			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tsfCorr
			(
				new GeometricField<Type, fvsPatchField, surfaceMesh>
				(
					IOobject
					(
						"cubic::correction(" + vf.name() + ')',
						mesh.time().timeName(),
						mesh,
						IOobject::NO_READ,
						IOobject::NO_WRITE,
						false
					),
					surfaceInterpolationScheme<Type>::interpolate(vf, kSc, -kSc)
					)
			);
			GeometricField<Type, fvsPatchField, surfaceMesh>& sfCorr =
				tsfCorr.ref();

			for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
			{
				sfCorr.replace
				(
					cmpt,
					sfCorr.component(cmpt)
					+ (
						surfaceInterpolationScheme
						<
						typename outerProduct
						<
						vector,
						typename pTraits<Type>::cmptType
						>::type
						>::interpolate
						(
							fv::gaussGrad
							<typename pTraits<Type>::cmptType>(mesh)
							.grad(vf.component(cmpt)),
							kVecP,
							kVecN
						) & mesh.Sf()
						) / mesh.magSf() / mesh.surfaceInterpolation::deltaCoeffs()
				);
			}

			typename GeometricField<Type, fvsPatchField, surfaceMesh>::
				Boundary& sfCorrbf = sfCorr.boundaryFieldRef();

			forAll(sfCorrbf, pi)
			{
				if (!sfCorrbf[pi].coupled())
				{
					sfCorrbf[pi] = Zero;
				}
			}

			return tsfCorr;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const cubic&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cubic_Header
