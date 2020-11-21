#pragma once
#ifndef _sampledCuttingPlane_Header
#define _sampledCuttingPlane_Header

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
	tnbLib::sampledSurfaces::cuttingPlane

Description
	A sampledSurface defined by a plane using the iso-surface algorithm
	to 'cut' the mesh.

SourceFiles
	sampledCuttingPlane.C

\*---------------------------------------------------------------------------*/

#include <sampledSurface.hxx>
#include <isoSurface.hxx>
#include <plane.hxx>
#include <ZoneIDs.hxx>
#include <fvMeshSubset.hxx>

#include <Switch.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSurfaces
	{

		/*---------------------------------------------------------------------------*\
							   Class cuttingPlane Declaration
		\*---------------------------------------------------------------------------*/

		class cuttingPlane
			:
			public sampledSurface
		{
			// Private Data

				//- Plane
			const plane plane_;

			//- Whether to coarsen
			const Switch regularise_;

			//- Whether to recalculate cell values as average of point values
			const Switch average_;

			//- Zone name/index (if restricted to zones)
			mutable cellZoneID zoneID_;

			//- For zones: patch to put exposed faces into
			mutable word exposedPatchName_;

			//- Track if the surface needs an update
			mutable bool needsUpdate_;


			//- Optional subsetted mesh
			autoPtr<fvMeshSubset> subMeshPtr_;

			//- Distance to cell centres
			autoPtr<volScalarField> cellDistancePtr_;

			//- Distance to points
			scalarField pointDistance_;

			//- Constructed iso surface
			autoPtr<isoSurface> isoSurfPtr_;

			//- Triangles converted to faceList
			mutable autoPtr<faceList> facesPtr_;


			// Private Member Functions

				//- Create iso surface
			FoamSampling_EXPORT void createGeometry();

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
			//TypeName("cuttingPlane");
			static const char* typeName_() { return "cuttingPlane"; }
			static FoamSampling_EXPORT const ::tnbLib::word typeName;
			static FoamSampling_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary
			FoamSampling_EXPORT cuttingPlane
			(
				const word& name,
				const polyMesh& mesh,
				const dictionary& dict
			);


			//- Destructor
			FoamSampling_EXPORT virtual ~cuttingPlane();


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
				return surface().points();
			}

			//- Faces of surface
			virtual const faceList& faces() const
			{
				return surface().faces();
			}

			const isoSurface& surface() const
			{
				return isoSurfPtr_();
			}

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

#include <sampledCuttingPlaneI.hxx>

//#ifdef NoRepository
//#include <sampledCuttingPlaneTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sampledCuttingPlane_Header
