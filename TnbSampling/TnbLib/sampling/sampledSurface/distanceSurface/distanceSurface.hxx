#pragma once
#ifndef _distanceSurface_Header
#define _distanceSurface_Header

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
	 tnbLib::sampledSurfaces::distanceSurface

Description
	A sampledSurface defined by a distance to a surface.

SourceFiles
	distanceSurface.C

\*---------------------------------------------------------------------------*/

#include <sampledSurface.hxx>
#include <searchableSurface.hxx>
#include <isoSurface.hxx>

#include <Switch.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSurfaces
	{

		/*---------------------------------------------------------------------------*\
							   Class distanceSurface Declaration
		\*---------------------------------------------------------------------------*/

		class distanceSurface
			:
			public sampledSurface
		{
			// Private Data

				//- Surface
			const autoPtr<searchableSurface> surfPtr_;

			//- Distance value
			const scalar distance_;

			//- Signed distance
			const bool signed_;

			//- Whether to coarsen
			const Switch regularise_;

			//- Whether to recalculate cell values as average of point values
			const Switch average_;

			//- If restricted to zones, name of this zone or a regular expression
			keyType zoneKey_;

			//- Track if the surface needs an update
			mutable bool needsUpdate_;


			//- Distance to cell centres
			autoPtr<volScalarField> cellDistancePtr_;

			//- Distance to points
			scalarField pointDistance_;

			//- Constructed iso surface
			autoPtr<isoSurface> isoSurfPtr_;


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
			//TypeName("distanceSurface");
			static const char* typeName_() { return "distanceSurface"; }
			static FoamSampling_EXPORT const ::tnbLib::word typeName;
			static FoamSampling_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from dictionary
			FoamSampling_EXPORT distanceSurface
			(
				const word& name,
				const polyMesh& mesh,
				const dictionary& dict
			);

			//- Construct from components
			FoamSampling_EXPORT distanceSurface
			(
				const word& name,
				const polyMesh& mesh,
				const bool interpolate,
				const word& surfaceType,
				const word& surfaceName,
				const scalar distance,
				const bool signedDistance,
				const Switch regularise,
				const Switch average
			);


			//- Destructor
			FoamSampling_EXPORT virtual ~distanceSurface();


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

#include <distanceSurfaceI.hxx>

//#ifdef NoRepository
//#include <distanceSurfaceTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_distanceSurface_Header
