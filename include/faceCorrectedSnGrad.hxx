#pragma once
#ifndef _faceCorrectedSnGrad_Header
#define _faceCorrectedSnGrad_Header

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
	tnbLib::fv::faceCorrectedSnGrad

Description
	Simple central-difference snGrad scheme with non-orthogonal correction.

SourceFiles
	faceCorrectedSnGrad.C

\*---------------------------------------------------------------------------*/

#include <snGradScheme.hxx>

#include <surfaceMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
						 Class faceCorrectedSnGrad Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class faceCorrectedSnGrad
			:
			public snGradScheme<Type>
		{
			// Private Member Functions

				//- Disallow default bitwise assignment
			void operator=(const faceCorrectedSnGrad&) = delete;


		public:

			//- Runtime type information
			TypeName("faceCorrected");


			// Constructors

				//- Construct from mesh
			faceCorrectedSnGrad(const fvMesh& mesh)
				:
				snGradScheme<Type>(mesh)
			{}


			//- Construct from mesh and data stream
			faceCorrectedSnGrad(const fvMesh& mesh, Istream&)
				:
				snGradScheme<Type>(mesh)
			{}


			//- Destructor
			virtual ~faceCorrectedSnGrad();


			// Member Functions

				//- Return the interpolation weighting factors for the given field
			virtual tmp<surfaceScalarField> deltaCoeffs
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			) const
			{
				return this->mesh().nonOrthDeltaCoeffs();
			}

			//- Return true if this scheme uses an explicit correction
			virtual bool corrected() const
			{
				return true;
			}

			//- Return the explicit correction to the faceCorrectedSnGrad
			//  for the given field using the gradient of the field
			tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
				fullGradCorrection
				(
					const GeometricField<Type, fvPatchField, volMesh>&
				) const;

			//- Return the explicit correction to the faceCorrectedSnGrad
			//  for the given field using the gradients of the field components
			virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
				correction(const GeometricField<Type, fvPatchField, volMesh>&) const;
		};


		// * * * * * * * * Template Member Function Specialisations  * * * * * * * * //

		template<>
		tmp<surfaceScalarField> faceCorrectedSnGrad<scalar>::correction
		(
			const volScalarField& vsf
		) const;


		template<>
		tmp<surfaceVectorField> faceCorrectedSnGrad<vector>::correction
		(
			const volVectorField& vvf
		) const;


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <faceCorrectedSnGradI.hxx>

//#ifdef NoRepository
//#include <faceCorrectedSnGrad.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_faceCorrectedSnGrad_Header