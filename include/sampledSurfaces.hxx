#pragma once
#ifndef _sampledSurfaces_Header
#define _sampledSurfaces_Header

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
	tnbLib::sampledSurfaces

Description
	Set of surfaces to sample.

	The write() method is used to sample and write files.

SourceFiles
	sampledSurfaces.C

\*---------------------------------------------------------------------------*/

#include <functionObject.hxx>
#include <sampledSurface.hxx>
#include <surfaceWriter.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <wordReList.hxx>
#include <IOobjectList.hxx>

#include <fvsPatchFields.hxx>
#include <fvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class Time;
	class fvMesh;
	class dictionary;

	/*---------------------------------------------------------------------------*\
						   Class sampledSurfaces Declaration
	\*---------------------------------------------------------------------------*/

	class sampledSurfaces
		:
		public functionObject,
		public PtrList<sampledSurface>
	{

		// Private classes

			//- Class used for surface merging information
		class mergeInfo
		{
		public:
			pointField points;
			faceList   faces;
			labelList  pointsMap;

			//- Clear all storage
			void clear()
			{
				points.clear();
				faces.clear();
				pointsMap.clear();
			}
		};


		// Static Data Members

			//- Output verbosity
		static FoamSampling_EXPORT bool verbose_;

		//- Tolerance for merging points (fraction of mesh bounding box)
		static FoamSampling_EXPORT scalar mergeTol_;


		// Private Data

			//- Const reference to fvMesh
		const fvMesh& mesh_;

		//- Load fields from files (not from objectRegistry)
		const bool loadFromFiles_;

		//- Output path
		fileName outputPath_;


		// Read from dictonary

			//- Names of fields to sample
		wordReList fieldSelection_;

		//- Interpolation scheme to use
		word interpolationScheme_;


		// surfaces

			//- Information for merging surfaces
		List<mergeInfo> mergeList_;


		// Calculated

			//- Surface formatter
		autoPtr<surfaceWriter> formatter_;


		// Private Member Functions


			//- Return number of fields
		FoamSampling_EXPORT label classifyFields();

		//- Write geometry only
		FoamSampling_EXPORT void writeGeometry() const;

		//- Write sampled fieldName on surface and on outputDir path		
		template<class Type>
		void writeSurface
		(
			const Field<Type>& values,
			const label surfI,
			const word& fieldName,
			const fileName& outputDir
		);

		//- Sample and write a particular volume field
		template<class Type>
		void sampleAndWrite
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		//- Sample and write a particular surface field
		template<class Type>
		void sampleAndWrite
		(
			const GeometricField<Type, fvsPatchField, surfaceMesh>&
		);

		//- Sample and write all sampled fields
		template<class GeoField> void sampleAndWriteGeoField(const IOobjectList& objects);  //- renamed by amir


	public:

		//- Runtime type information
		//TypeName("surfaces");
		static const char* typeName_() { return "surfaces"; }
		static FoamSampling_EXPORT const ::tnbLib::word typeName;
		static FoamSampling_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from Time and dictionary
		FoamSampling_EXPORT sampledSurfaces
		(
			const word& name,
			const Time& time,
			const dictionary& dict
		);

		//- Construct for given objectRegistry and dictionary
		//  allow the possibility to load fields from files
		FoamSampling_EXPORT sampledSurfaces
		(
			const word& name,
			const objectRegistry&,
			const dictionary&,
			const bool loadFromFiles = false
		);

		//- Disallow default bitwise copy construction
		FoamSampling_EXPORT sampledSurfaces(const sampledSurfaces&) = delete;


		//- Destructor
		FoamSampling_EXPORT virtual ~sampledSurfaces();


		// Member Functions

			//- Does any of the surfaces need an update?
		FoamSampling_EXPORT virtual bool needsUpdate() const;

		//- Mark the surfaces as needing an update.
		//  May also free up unneeded data.
		//  Return false if all surfaces were already marked as expired.
		FoamSampling_EXPORT virtual bool expire();

		//- Update the surfaces as required and merge surface points (parallel).
		//  Return false if no surfaces required an update.
		FoamSampling_EXPORT virtual bool update();

		//- Set verbosity level
		FoamSampling_EXPORT void verbose(const bool verbosity = true);

		//- Read the sampledSurfaces dictionary
		FoamSampling_EXPORT virtual bool read(const dictionary&);

		//- Execute, currently does nothing
		FoamSampling_EXPORT virtual bool execute();

		//- Sample and write
		FoamSampling_EXPORT virtual bool write();

		//- Update for changes of mesh - expires the surfaces
		FoamSampling_EXPORT virtual void updateMesh(const mapPolyMesh&);

		//- Update for mesh point-motion - expires the surfaces
		FoamSampling_EXPORT virtual void movePoints(const polyMesh&);

		//- Update for changes of mesh due to readUpdate - expires the surfaces
		FoamSampling_EXPORT virtual void readUpdate(const polyMesh::readUpdateState state);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamSampling_EXPORT void operator=(const sampledSurfaces&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <sampledSurfacesI.hxx>

//#ifdef NoRepository
//#include <sampledSurfacesTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sampledSurfaces_Header
