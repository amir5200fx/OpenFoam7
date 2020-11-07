#pragma once
#ifndef _orthogonalSnGrad_Header
#define _orthogonalSnGrad_Header

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
	tnbLib::fv::orthogonalSnGrad

Description
	Simple central-difference snGrad scheme using the cell-centre to cell-centre
	delta-coefficients.

SourceFiles
	orthogonalSnGrad.C

\*---------------------------------------------------------------------------*/

#include <snGradScheme.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamOrthogonalSnGrad_EXPORT __declspec(dllexport)
#else
#ifdef FoamOrthogonalSnGrad_EXPORT_DEFINE
#define FoamOrthogonalSnGrad_EXPORT __declspec(dllexport)
#else
#define FoamOrthogonalSnGrad_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
						 Class orthogonalSnGrad Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class orthogonalSnGrad
			:
			public snGradScheme<Type>
		{

		public:

			//- Runtime type information
			/*TypeName("orthogonal");*/
			static const char* typeName_() { return "orthogonal"; }
			static FoamOrthogonalSnGrad_EXPORT const ::tnbLib::word typeName;
			static FoamOrthogonalSnGrad_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from mesh
			orthogonalSnGrad(const fvMesh& mesh)
				:
				snGradScheme<Type>(mesh)
			{}


			//- Construct from mesh and data stream
			orthogonalSnGrad(const fvMesh& mesh, Istream&)
				:
				snGradScheme<Type>(mesh)
			{}


			//- Destructor
			virtual ~orthogonalSnGrad();


			// Member Functions

				//- Return the interpolation weighting factors for the given field
			virtual tmp<surfaceScalarField> deltaCoeffs
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			) const
			{
				return this->mesh().deltaCoeffs();
			}

			//- Return true if this scheme uses an explicit correction
			virtual bool corrected() const
			{
				return false;
			}

			//- Return the explicit correction to the orthogonalSnGrad
			//  for the given field
			virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
				correction(const GeometricField<Type, fvPatchField, volMesh>&) const;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const orthogonalSnGrad&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <orthogonalSnGradI.hxx>

//#ifdef NoRepository
//#include <orthogonalSnGrad.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_orthogonalSnGrad_Header
