#pragma once
#ifndef _leastSquaresGrad_Header
#define _leastSquaresGrad_Header

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
	tnbLib::fv::leastSquaresGrad

Description
	Second-order gradient scheme using least-squares.

SourceFiles
	leastSquaresGrad.C

\*---------------------------------------------------------------------------*/

#include <gradScheme.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamLeastSquaresGrad_EXPORT __declspec(dllexport)
#else
#ifdef FoamLeastSquaresGrad_EXPORT_DEFINE
#define FoamLeastSquaresGrad_EXPORT __declspec(dllexport)
#else
#define FoamLeastSquaresGrad_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							  Class leastSquaresGrad Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class leastSquaresGrad
			:
			public fv::gradScheme<Type>
		{
		public:

			//- Runtime type information
			/*TypeName("leastSquares");*/
			static const char* typeName_() { return "leastSquares"; }
			static FoamLeastSquaresGrad_EXPORT const ::tnbLib::word typeName;
			static FoamLeastSquaresGrad_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from mesh
			leastSquaresGrad(const fvMesh& mesh)
				:
				gradScheme<Type>(mesh)
			{}

			//- Construct from Istream
			leastSquaresGrad(const fvMesh& mesh, Istream&)
				:
				gradScheme<Type>(mesh)
			{}

			//- Disallow default bitwise copy construction
			leastSquaresGrad(const leastSquaresGrad&) = delete;


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
			void operator=(const leastSquaresGrad&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <leastSquaresGradI.hxx>

//#ifdef NoRepository
//#include <leastSquaresGrad.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_leastSquaresGrad_Header
