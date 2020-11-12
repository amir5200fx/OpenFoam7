#pragma once
#ifndef _sampledPatchInternalField_Header
#define _sampledPatchInternalField_Header

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
	tnbLib::sampledSurfaces::patchInternalField

Description
	Variation of sampledPatch that samples the internalField (at a given
	normal distance from the patch) instead of the patchField.
	Note:
	- interpolate=false : get cell value on faces
	- interpolate=true  : interpolate inside cell and interpolate to points
	There is no option to get interpolated value inside the cell on the faces.

SourceFiles
	sampledPatchInternalField.C

\*---------------------------------------------------------------------------*/

#include <sampledPatch.hxx>
#include <mappedPatchBase.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSurfaces
	{

		/*---------------------------------------------------------------------------*\
						  Class patchInternalField Declaration
		\*---------------------------------------------------------------------------*/

		class patchInternalField
			:
			public patch
		{
			// Private Data

				//- Mapping engines
			PtrList<mappedPatchBase> mappers_;


			// Private Member Functions

				//- Sample field on faces
			template<class Type>
			tmp<Field<Type>> sampleField
			(
				const GeometricField<Type, fvPatchField, volMesh>& vField
			) const;

			template<class Type>
			tmp<Field<Type>> interpolateField(const interpolation<Type>&) const;


		public:

			//- Runtime type information
			//TypeName("patchInternalField");
			static const char* typeName_() { return "patchInternalField"; }
			static FoamSampling_EXPORT const ::tnbLib::word typeName;
			static FoamSampling_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary
			FoamSampling_EXPORT patchInternalField
			(
				const word& name,
				const polyMesh& mesh,
				const dictionary& dict
			);


			//- Destructor
			FoamSampling_EXPORT virtual ~patchInternalField();


			// Member Functions

				// Sample

					//- Sample field on surface
			FoamSampling_EXPORT virtual tmp<scalarField> sample
			(
				const volScalarField&
			) const;

			//- Sample field on surface
			FoamSampling_EXPORT virtual tmp<vectorField> sample
			(
				const volVectorField&
			) const;

			//- Sample field on surface
			FoamSampling_EXPORT virtual tmp<sphericalTensorField> sample
			(
				const volSphericalTensorField&
			) const;

			//- Sample field on surface
			FoamSampling_EXPORT virtual tmp<symmTensorField> sample
			(
				const volSymmTensorField&
			) const;

			//- Sample field on surface
			FoamSampling_EXPORT virtual tmp<tensorField> sample
			(
				const volTensorField&
			) const;


			// Interpolate

				//- Interpolate field on surface
			FoamSampling_EXPORT virtual tmp<scalarField> interpolate
			(
				const interpolation<scalar>&
			) const;

			//- Interpolate field on surface
			FoamSampling_EXPORT virtual tmp<vectorField> interpolate
			(
				const interpolation<vector>&
			) const;

			//- Interpolate field on surface
			FoamSampling_EXPORT virtual tmp<sphericalTensorField> interpolate
			(
				const interpolation<sphericalTensor>&
			) const;

			//- Interpolate field on surface
			FoamSampling_EXPORT virtual tmp<symmTensorField> interpolate
			(
				const interpolation<symmTensor>&
			) const;

			//- Interpolate field on surface
			FoamSampling_EXPORT virtual tmp<tensorField> interpolate
			(
				const interpolation<tensor>&
			) const;


			//- Write
			FoamSampling_EXPORT virtual void print(Ostream&) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace sampledSurfaces
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <sampledPatchInternalFieldI.hxx>

//#ifdef NoRepository
//#include <sampledPatchInternalFieldTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sampledPatchInternalField_Header
