#pragma once
#ifndef _gaussLaplacianScheme_Header
#define _gaussLaplacianScheme_Header

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
	tnbLib::fv::gaussLaplacianScheme

Description
	Basic second-order laplacian using face-gradients and Gauss' theorem.

SourceFiles
	gaussLaplacianScheme.C

\*---------------------------------------------------------------------------*/

#include <laplacianScheme.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamGaussLaplacianScheme_EXPORT __declspec(dllexport)
#else
#ifdef FoamGaussLaplacianScheme_EXPORT_DEFINE
#define FoamGaussLaplacianScheme_EXPORT __declspec(dllexport)
#else
#define FoamGaussLaplacianScheme_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							   Class gaussLaplacianScheme Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type, class GType>
		class gaussLaplacianScheme
			:
			public fv::laplacianScheme<Type, GType>
		{
			// Private Member Functions

			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> gammaSnGradCorr
			(
				const surfaceVectorField& SfGammaCorr,
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			//- Disallow default bitwise copy construction
			gaussLaplacianScheme(const gaussLaplacianScheme&) = delete;

			//- Disallow default bitwise assignment
			void operator=(const gaussLaplacianScheme&) = delete;


		public:

			//- Runtime type information
			/*TypeName("Gauss");*/
			static const char* typeName_() { return "Gauss"; }
			static FoamGaussLaplacianScheme_EXPORT const ::tnbLib::word typeName;
			static FoamGaussLaplacianScheme_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct null
			gaussLaplacianScheme(const fvMesh& mesh)
				:
				laplacianScheme<Type, GType>(mesh)
			{}

			//- Construct from Istream
			gaussLaplacianScheme(const fvMesh& mesh, Istream& is)
				:
				laplacianScheme<Type, GType>(mesh, is)
			{}

			//- Construct from mesh, interpolation and snGradScheme schemes
			gaussLaplacianScheme
			(
				const fvMesh& mesh,
				const tmp<surfaceInterpolationScheme<GType>>& igs,
				const tmp<snGradScheme<Type>>& sngs
			)
				:
				laplacianScheme<Type, GType>(mesh, igs, sngs)
			{}


			//- Destructor
			virtual ~gaussLaplacianScheme()
			{}


			// Member Functions

			static tmp<fvMatrix<Type>> fvmLaplacianUncorrected
			(
				const surfaceScalarField& gammaMagSf,
				const surfaceScalarField& deltaCoeffs,
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			tmp<GeometricField<Type, fvPatchField, volMesh>> fvcLaplacian
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			tmp<fvMatrix<Type>> fvmLaplacian
			(
				const GeometricField<GType, fvsPatchField, surfaceMesh>&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			tmp<GeometricField<Type, fvPatchField, volMesh>> fvcLaplacian
			(
				const GeometricField<GType, fvsPatchField, surfaceMesh>&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);
		};


		// Use macros to emulate partial-specialisation of the Laplacian functions
		// for scalar diffusivity gamma

#define defineFvmLaplacianScalarGamma(Type)                                    \
                                                                               \
template<>                                                                     \
tmp<fvMatrix<Type>> gaussLaplacianScheme<Type, scalar>::fvmLaplacian           \
(                                                                              \
    const GeometricField<scalar, fvsPatchField, surfaceMesh>&,                 \
    const GeometricField<Type, fvPatchField, volMesh>&                         \
);                                                                             \
                                                                               \
template<>                                                                     \
tmp<GeometricField<Type, fvPatchField, volMesh>>                               \
gaussLaplacianScheme<Type, scalar>::fvcLaplacian                               \
(                                                                              \
    const GeometricField<scalar, fvsPatchField, surfaceMesh>&,                 \
    const GeometricField<Type, fvPatchField, volMesh>&                         \
);


		defineFvmLaplacianScalarGamma(scalar);
		defineFvmLaplacianScalarGamma(vector);
		defineFvmLaplacianScalarGamma(sphericalTensor);
		defineFvmLaplacianScalarGamma(symmTensor);
		defineFvmLaplacianScalarGamma(tensor);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <gaussLaplacianSchemeI.hxx>

//#ifdef NoRepository
//#include <gaussLaplacianScheme.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_gaussLaplacianScheme_Header
