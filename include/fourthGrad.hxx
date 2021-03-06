#pragma once
#ifndef _fourthGrad_Header
#define _fourthGrad_Header

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
	tnbLib::fv::fourthGrad

Description
	Second-order gradient scheme using least-squares.

SourceFiles
	fourthGrad.C

\*---------------------------------------------------------------------------*/

#include <gradScheme.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamFourthGrad_EXPORT __declspec(dllexport)
#else
#ifdef FoamFourthGrad_EXPORT_DEFINE
#define FoamFourthGrad_EXPORT __declspec(dllexport)
#else
#define FoamFourthGrad_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							  Class fourthGrad Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class fourthGrad
			:
			public fv::gradScheme<Type>
		{
		public:

			//- Runtime type information
			/*TypeName("fourth");*/
			static const char* typeName_() { return "fourth"; }
			static FoamFourthGrad_EXPORT const ::tnbLib::word typeName;
			static FoamFourthGrad_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Istream
			fourthGrad(const fvMesh& mesh, Istream&)
				:
				gradScheme<Type>(mesh)
			{}

			//- Disallow default bitwise copy construction
			fourthGrad(const fourthGrad&) = delete;


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
			void operator=(const fourthGrad&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fourthGradI.hxx>

//#ifdef NoRepository
//#include <fourthGrad.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fourthGrad_Header
