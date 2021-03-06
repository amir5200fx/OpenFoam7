#pragma once
#ifndef _LeastSquaresGradTemplate_Header
#define _LeastSquaresGradTemplate_Header

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
	tnbLib::fv::LeastSquaresGrad

Description
	Gradient calculated using weighted least-squares on an arbitrary stencil.
	The stencil type is provided via a template argument and any cell-based
	stencil is supported:

	\table
		Stencil                     | Connections     | Scheme name
		centredCFCCellToCellStencil | cell-face-cell  | Not Instantiated
		centredCPCCellToCellStencil | cell-point-cell | pointCellsLeastSquares
		centredCECCellToCellStencil | cell-edge-cell  | edgeCellsLeastSquares
	\endtable

	The first of these is not instantiated by default as the standard
	leastSquaresGrad is equivalent and more efficient.

Usage
	Example of the gradient specification:
	\verbatim
	gradSchemes
	{
		default         pointCellsLeastSquares;
	}
	\endverbatim

See also
	tnbLib::fv::LeastSquaresVectors
	tnbLib::fv::leastSquaresGrad

SourceFiles
	LeastSquaresGrad.C
	LeastSquaresVectors.H
	LeastSquaresVectors.C

\*---------------------------------------------------------------------------*/

#include <gradScheme.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamLeastSquaresGradStencil_EXPORT __declspec(dllexport)
#else
#ifdef FoamLeastSquaresGradStencil_EXPORT_DEFINE
#define FoamLeastSquaresGradStencil_EXPORT __declspec(dllexport)
#else
#define FoamLeastSquaresGradStencil_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							  Class LeastSquaresGrad Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type, class Stencil>
		class LeastSquaresGrad
			:
			public fv::gradScheme<Type>
		{
			// Private Data

				//- Minimum determinant criterion to choose extra cells
			scalar minDet_;


		public:

			//- Runtime type information
			/*TypeName("LeastSquares");*/
			static const char* typeName_() { return "LeastSquares"; }
			static FoamLeastSquaresGradStencil_EXPORT const ::tnbLib::word typeName;
			static FoamLeastSquaresGradStencil_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Istream
			LeastSquaresGrad(const fvMesh& mesh, Istream& schemeData)
				:
				gradScheme<Type>(mesh)
			{}

			//- Disallow default bitwise copy construction
			LeastSquaresGrad(const LeastSquaresGrad&) = delete;


			// Member Functions

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


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const LeastSquaresGrad&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makeLeastSquaresGradTypeScheme(SS, STENCIL, TYPE)                      \
    typedef tnbLib::fv::LeastSquaresGrad<tnbLib::TYPE, tnbLib::STENCIL>              \
        LeastSquaresGrad##TYPE##STENCIL##_;                                    \
                                                                               \
    defineTemplateTypeNameAndDebugWithName                                     \
        (LeastSquaresGrad##TYPE##STENCIL##_, #SS, 0);                          \
                                                                               \
    namespace tnbLib                                                             \
    {                                                                          \
        namespace fv                                                           \
        {                                                                      \
            typedef LeastSquaresGrad<tnbLib::TYPE, tnbLib::STENCIL>                \
                LeastSquaresGrad##TYPE##STENCIL##_;                            \
                                                                               \
            gradScheme<tnbLib::TYPE>::addIstreamConstructorToTable               \
                <LeastSquaresGrad<tnbLib::TYPE, tnbLib::STENCIL>>                  \
                add##SS##STENCIL##TYPE##IstreamConstructorToTable_;            \
        }                                                                      \
    }

#define makeLeastSquaresGradScheme(SS, STENCIL)                                \
    typedef tnbLib::fv::LeastSquaresVectors<tnbLib::STENCIL>                       \
        LeastSquaresVectors##STENCIL##_;                                       \
                                                                               \
    defineTemplateTypeNameAndDebugWithName                                     \
        (LeastSquaresVectors##STENCIL##_, #SS, 0);                             \
                                                                               \
    makeLeastSquaresGradTypeScheme(SS,STENCIL,scalar)                          \
    makeLeastSquaresGradTypeScheme(SS,STENCIL,vector)

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <LeastSquaresGradTemplateI.hxx>

//#ifdef NoRepository
//#include <LeastSquaresGradTemplate.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_LeastSquaresGradTemplate_Header
