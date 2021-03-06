#pragma once
#ifndef _surfMesh_Header
#define _surfMesh_Header

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
	tnbLib::surfMesh

Description
	A surface mesh consisting of general polygon faces.

SourceFiles
	surfMesh.C
	surfMeshClear.C
	surfMeshIO.C

\*---------------------------------------------------------------------------*/

#include <surfaceRegistry.hxx>
#include <MeshedSurfaceIOAllocator.hxx>
#include <PrimitivePatchTemplate.hxx>
#include <SubField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<class Face> class MeshedSurface;

	/*---------------------------------------------------------------------------*\
							  Class surfMesh Declaration
	\*---------------------------------------------------------------------------*/

	class surfMesh
		:
		public  surfaceRegistry,
		private MeshedSurfaceIOAllocator,
		public  PrimitivePatch<::tnbLib::UList<face>, ::tnbLib::SubField<point>>
	{
		// friends
		template<class Face> friend class MeshedSurface;
		template<class Face> friend class UnsortedMeshedSurface;

	public:

		// Public data types

			//- Enumeration defining the state of the mesh after a read update.
			//  Used for post-processing applications, where the mesh
			//  needs to update based on the files written in time directories
		enum readUpdateState
		{
			UNCHANGED,
			POINTS_MOVED,
			TOPO_CHANGE,
			TOPO_PATCH_CHANGE
		};


	private:

		// Private Typedefs

		typedef MeshedSurfaceIOAllocator Allocator;

		typedef PrimitivePatch<::tnbLib::UList<face>, ::tnbLib::SubField<point>>
			MeshReference;


	protected:

		// Protected Member Functions

			//- Non-const access to global points
		pointField& storedPoints()
		{
			return Allocator::storedIOPoints();
		}

		//- Non-const access to the faces
		faceList& storedFaces()
		{
			return Allocator::storedIOFaces();
		}

		//- Non-const access to the zones
		surfZoneList& storedZones()
		{
			return Allocator::storedIOZones();
		}

		//- Update references to storedFaces
		FoamFvMesh_EXPORT virtual void updateFacesRef();

		//- Update references to storedPoints
		FoamFvMesh_EXPORT virtual void updatePointsRef();

		//- Update references to storedPoints/storedFaces
		FoamFvMesh_EXPORT virtual void updateRefs();


	public:

		// Public Typedefs

		typedef surfMesh Mesh;

		//- Placeholder only, but do not remove - it is needed for GeoMesh
		typedef bool BoundaryMesh;


		//- Runtime type information
		/*TypeName("surfMesh");*/
		static const char* typeName_() { return "surfMesh"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Return the mesh sub-directory name (normally "surfMesh")
		static FoamFvMesh_EXPORT word meshSubDir;

		// Constructors

			//- Construct from IOobject, with alternative surface name
		FoamFvMesh_EXPORT explicit surfMesh(const IOobject&, const word& surfName = "");

		//- Construct by transferring components (points, faces) without zones.
		//  surfZones are added using addZones() member function
		FoamFvMesh_EXPORT surfMesh
		(
			const IOobject&,
			pointField&&,
			faceList&&,
			const word& surfName = ""
		);

		//- Construct copy/move from MeshedSurface
		FoamFvMesh_EXPORT surfMesh
		(
			const IOobject&,
			MeshedSurface<face>&& surf,
			const word& surfName = ""
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT surfMesh(const surfMesh&);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~surfMesh();


		// Member Functions

			// Database

				//- Return the local mesh directory (dbDir()/meshSubDir)
		FoamFvMesh_EXPORT fileName meshDir() const;

		//- Return the current instance directory for points
		//  Used in the consruction of geometric mesh data dependent
		//  on points
		FoamFvMesh_EXPORT const fileName& pointsInstance() const;

		//- Return the current instance directory for faces
		FoamFvMesh_EXPORT const fileName& facesInstance() const;

		//- Set the instance for mesh files
		FoamFvMesh_EXPORT void setInstance(const fileName&);


		// Access

			//- Return the number of raw points
		FoamFvMesh_EXPORT virtual label nPoints() const;

		//- Return the number of raw faces
		FoamFvMesh_EXPORT virtual label nFaces() const;

		//- Return number of faces
		virtual label size() const
		{
			return nFaces();
		}


		//- Return points
		FoamFvMesh_EXPORT virtual const pointField& points() const;

		//- Return faces
		FoamFvMesh_EXPORT virtual const faceList& faces() const;

		//- Return surface zones
		virtual const surfZoneList& surfZones() const
		{
			return Allocator::storedIOZones();
		}

		//- Check the surface zone definitions
		FoamFvMesh_EXPORT void checkZones();

		//- Add surface zones
		FoamFvMesh_EXPORT void addZones
		(
			const List<surfZone>&,
			const bool validate = true
		);

		//- Update the mesh based on the mesh files saved in
		//  time directories
		FoamFvMesh_EXPORT virtual readUpdateState readUpdate();

		//- Update the mesh corresponding to given map

		//- Remove surface zones
		FoamFvMesh_EXPORT void removeZones();

		//- Reset mesh primitive data.
		FoamFvMesh_EXPORT void resetPrimitives
		(
			pointField&& points,
			faceList&& faces,
			surfZoneList&& zones,
			const bool validate = true
		);


		//- Transfer the contents of the argument and annul the argument
		FoamFvMesh_EXPORT void transfer(MeshedSurface<face>&);


		//- Avoid masking the normal objectRegistry write
		using surfaceRegistry::write;

		//- Write to file
		static FoamFvMesh_EXPORT void write(const fileName&, const surfMesh&);

		//- Write to file
		FoamFvMesh_EXPORT void write(const fileName&);

		//  Storage management

			//- Clear geometry
		FoamFvMesh_EXPORT void clearGeom();

		//- Clear addressing
		FoamFvMesh_EXPORT void clearAddressing();

		//- Clear all geometry and addressing unnecessary for CFD
		FoamFvMesh_EXPORT void clearOut();

		//- Clear primitive data (points, faces and cells)
		FoamFvMesh_EXPORT void clearPrimitives();

		//- Remove all files from mesh instance
		FoamFvMesh_EXPORT void removeFiles(const fileName& instanceDir) const;

		//- Remove all files from mesh instance()
		FoamFvMesh_EXPORT void removeFiles() const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const surfMesh&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfMesh_Header
