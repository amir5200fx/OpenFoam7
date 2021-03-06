#pragma once
#ifndef _sampledThresholdCellFaces_Header
#define _sampledThresholdCellFaces_Header

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
	tnbLib::sampledSurfaces::thresholdCellFaces

Description
	A sampledSurface defined by the cell faces corresponding to a threshold
	value.

SourceFiles
	sampledThresholdCellFaces.C

\*---------------------------------------------------------------------------*/

#include <sampledSurface.hxx>
#include <MeshedSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSurfaces
	{

		/*---------------------------------------------------------------------------*\
							Class thresholdCellFaces Declaration
		\*---------------------------------------------------------------------------*/

		class thresholdCellFaces
			:
			public sampledSurface,
			public MeshedSurface<face>
		{
			// Private Typedefs

			typedef MeshedSurface<face> MeshStorage;


			// Private Data

				//- Field to get isoSurface of
			const word fieldName_;

			//- Threshold value
			const scalar lowerThreshold_;

			//- Threshold value
			const scalar upperThreshold_;

			//- If restricted to zones, name of this zone or a regular expression
			keyType zoneKey_;

			//- Triangulated faces or keep faces as is
			bool triangulate_;

			// Recreated for every time-step

			//- Time at last call, also track it surface needs an update
			mutable label prevTimeIndex_;

			//- For every face the original cell in mesh
			mutable labelList meshCells_;


			// Private Member Functions

				//- Create surface (if time has changed)
				//  Do nothing (and return false) if no update was needed
			FoamSampling_EXPORT bool updateGeometry() const;

			//- Sample field on faces
			template<class Type>
			tmp<Field<Type>> sampleField
			(
				const GeometricField<Type, fvPatchField, volMesh>& vField
			) const;


			template<class Type>
			tmp<Field<Type>>
				interpolateField(const interpolation<Type>&) const;


		public:

			//- Runtime type information
			//TypeName("thresholdCellFaces");
			static const char* typeName_() { return "thresholdCellFaces"; }
			static FoamSampling_EXPORT const ::tnbLib::word typeName;
			static FoamSampling_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary
			FoamSampling_EXPORT thresholdCellFaces
			(
				const word& name,
				const polyMesh&,
				const dictionary&
			);


			//- Destructor
			FoamSampling_EXPORT virtual ~thresholdCellFaces();


			// Member Functions

				//- Does the surface need an update?
			FoamSampling_EXPORT virtual bool needsUpdate() const;

			//- Mark the surface as needing an update.
			//  May also free up unneeded data.
			//  Return false if surface was already marked as expired.
			FoamSampling_EXPORT virtual bool expire();

			//- Update the surface as required.
			//  Do nothing (and return false) if no update was needed
			FoamSampling_EXPORT virtual bool update();

			//- Points of surface
			virtual const pointField& points() const
			{
				return MeshStorage::points();
			}

			//- Faces of surface
			virtual const faceList& faces() const
			{
				return MeshStorage::faces();
			}

			//- Sample field on surface
			FoamSampling_EXPORT virtual tmp<scalarField> sample(const volScalarField&) const;

			//- Sample field on surface
			FoamSampling_EXPORT virtual tmp<vectorField> sample(const volVectorField&) const;

			//- Sample field on surface
			FoamSampling_EXPORT virtual tmp<sphericalTensorField> sample
			(
				const volSphericalTensorField&
			) const;

			//- Sample field on surface
			FoamSampling_EXPORT virtual tmp<symmTensorField> sample(const volSymmTensorField&) const;

			//- Sample field on surface
			FoamSampling_EXPORT virtual tmp<tensorField> sample
			(
				const volTensorField&
			) const;

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

#include <sampledThresholdCellFacesI.hxx>

//#ifdef NoRepository
//#include <sampledThresholdCellFacesTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sampledThresholdCellFaces_Header
