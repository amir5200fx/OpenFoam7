#pragma once
#ifndef _gaussGrad_Header
#define _gaussGrad_Header

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
	tnbLib::fv::gaussGrad

Description
	Basic second-order gradient scheme using face-interpolation
	and Gauss' theorem.

SourceFiles
	gaussGrad.C

\*---------------------------------------------------------------------------*/

#include <gradScheme.hxx>
#include <surfaceInterpolationScheme.hxx>
#include <linear.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamGaussGrad_EXPORT __declspec(dllexport)
#else
#ifdef FoamGaussGrad_EXPORT_DEFINE
#define FoamGaussGrad_EXPORT __declspec(dllexport)
#else
#define FoamGaussGrad_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							   Class gaussGrad Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class gaussGrad
			:
			public fv::gradScheme<Type>
		{
			// Private Data

			tmp<surfaceInterpolationScheme<Type>> tinterpScheme_;


		public:

			//- Runtime type information
			/*TypeName("Gauss");*/
			static const char* typeName_() { return "Gauss"; }
			static FoamGaussGrad_EXPORT const ::tnbLib::word typeName;
			static FoamGaussGrad_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from mesh
			gaussGrad(const fvMesh& mesh)
				:
				gradScheme<Type>(mesh),
				tinterpScheme_(new linear<Type>(mesh))
			{}

			//- Construct from mesh and Istream
			gaussGrad(const fvMesh& mesh, Istream& is)
				:
				gradScheme<Type>(mesh),
				tinterpScheme_(nullptr)
			{
				if (is.eof())
				{
					tinterpScheme_ =
						tmp<surfaceInterpolationScheme<Type>>
						(
							new linear<Type>(mesh)
							);
				}
				else
				{
					tinterpScheme_ =
						tmp<surfaceInterpolationScheme<Type>>
						(
							surfaceInterpolationScheme<Type>::New(mesh, is)
							);
				}
			}

			//- Disallow default bitwise copy construction
			gaussGrad(const gaussGrad&) = delete;


			// Member Functions

				//- Return the gradient of the given field
				//  calculated using Gauss' theorem on the given surface field
			static
				tmp
				<
				GeometricField
				<typename outerProduct<vector, Type>::type, fvPatchField, volMesh>
				> gradf
				(
					const GeometricField<Type, fvsPatchField, surfaceMesh>&,
					const word& name
				);

			//- Return the gradient of the given field to the gradScheme::grad
			//  for optional caching
			virtual tmp
				<
				GeometricField
				<typename outerProduct<vector, Type>::type, fvPatchField, volMesh>
				> calcGrad
				(
					const GeometricField<Type, fvPatchField, volMesh>& vsf,
					const word& name
				) const;

			//- Correct the boundary values of the gradient using the patchField
			// snGrad functions
			static void correctBoundaryConditions
			(
				const GeometricField<Type, fvPatchField, volMesh>&,
				GeometricField
				<typename outerProduct<vector, Type>::type, fvPatchField, volMesh>&
			);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const gaussGrad&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <gaussGradI.hxx>

//#ifdef NoRepository
//#include <gaussGrad.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_gaussGrad_Header
