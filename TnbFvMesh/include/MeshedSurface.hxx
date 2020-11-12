#pragma once
#ifndef _MeshedSurface_Header
#define _MeshedSurface_Header

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
	tnbLib::MeshedSurface

Description
	A surface geometry mesh with zone information, not to be confused with
	the similarly named surfaceMesh, which actually refers to the cell faces
	of a volume mesh.

	A MeshedSurface can have zero or more surface zones (roughly equivalent
	to faceZones for a polyMesh). If surface zones are defined, they must
	be contiguous and cover all of the faces.

	The MeshedSurface is intended for surfaces from a variety of sources.
	- A set of points and faces without any surface zone information.
	- A set of points and faces with randomly ordered zone information.
	  This could arise, for example, from reading external file formats
	  such as STL, etc.

SourceFiles
	MeshedSurface.C

\*---------------------------------------------------------------------------*/

#include <PrimitivePatchTemplate.hxx>
#include <PatchTools.hxx>
#include <pointField.hxx>
#include <face.hxx>
#include <triFace.hxx>

#include <surfZoneList.hxx>
#include <surfaceFormatsCore.hxx>
#include <memberFunctionSelectionTables.hxx>
#include <HashSet.hxx>

#ifdef FoamFvMesh_EXPORT_DEFINE
#define FoamMeshedSurface_EXPORT __declspec(dllexport)
#else
#ifdef FoamMeshedSurface_EXPORT_DEFINE
#define FoamMeshedSurface_EXPORT __declspec(dllexport)
#else
#define FoamMeshedSurface_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class Time;
	class surfMesh;
	class polyBoundaryMesh;

	template<class Face> class MeshedSurface;
	template<class Face> class MeshedSurfaceProxy;
	template<class Face> class UnsortedMeshedSurface;

	/*---------------------------------------------------------------------------*\
						  Class MeshedSurface Declaration
	\*---------------------------------------------------------------------------*/

	template<class Face>
	class MeshedSurface
		:
		public PrimitivePatch<::tnbLib::List<Face>, pointField>,
		public fileFormats::surfaceFormatsCore
	{
		// friends - despite different face representationsx
		template<class Face2> friend class MeshedSurface;
		template<class Face2> friend class UnsortedMeshedSurface;
		friend class surfMesh;

		// Private Typedefs for convenience

		typedef PrimitivePatch<::tnbLib::List<Face>, pointField> ParentType;

		typedef UnsortedMeshedSurface<Face>  FriendType;
		typedef MeshedSurfaceProxy<Face>     ProxyType;


		// Private Member Data

			//- Zone information
			// (face ordering nFaces/startFace only used during reading/writing)
		List<surfZone> zones_;


	protected:

		// Protected Member functions

			//- Transfer points/zones and transcribe face -> triFace
		void transcribe(MeshedSurface<face>&);

		//- Basic sanity check on zones
		void checkZones();

		//- Non-const access to global points
		pointField& storedPoints()
		{
			return const_cast<pointField&>(ParentType::points());
		}

		//- Non-const access to the faces
		List<Face>& storedFaces()
		{
			return static_cast<List<Face> &>(*this);
		}

		//- Non-const access to the zones
		surfZoneList& storedZones()
		{
			return zones_;
		}

		//- Sort faces by zones and store sorted faces
		void sortFacesAndStore
		(
			List<Face>&& unsortedFaces,
			List<label>&& zoneIds,
			const bool sorted
		);

		//- Set new zones from faceMap
		virtual void remapFaces(const labelUList& faceMap);


	public:

		// Public Typedefs

			//- Face type used
		typedef Face FaceType;

		//- Runtime type information
		/*ClassName("MeshedSurface");*/
		static const char* typeName_() { return "MeshedSurface"; } 
		static FoamMeshedSurface_EXPORT const ::tnbLib::word typeName;
		static FoamMeshedSurface_EXPORT int debug;


		// Static

			//- Face storage only handles triangulated faces
		inline static bool isTri();

		//- Can we read this file format?
		static bool canRead(const fileName&, const bool verbose = false);

		//- Can we read this file format?
		static bool canReadType(const word& ext, const bool verbose = false);

		//- Can we write this file format?
		static bool canWriteType(const word& ext, const bool verbose = false);

		static wordHashSet readTypes();
		static wordHashSet writeTypes();


		// Constructors

			//- Construct null
		MeshedSurface();

		//- Construct by transferring components (points, faces, zones).
		MeshedSurface
		(
			pointField&&,
			List<Face>&&,
			surfZoneList&&
		);

		//- Construct by transferring components (points, faces).
		//  Use zone information if available
		MeshedSurface
		(
			pointField&&,
			List<Face>&&,
			const labelUList& zoneSizes = labelUList(),
			const UList<word>& zoneNames = UList<word>()
		);

		//- Copy constructor
		MeshedSurface(const MeshedSurface&);

		//- Construct from a UnsortedMeshedSurface
		MeshedSurface(const UnsortedMeshedSurface<Face>&);

		//- Construct from a boundary mesh with local points/faces
		MeshedSurface
		(
			const polyBoundaryMesh&,
			const bool globalPoints = false
		);

		//- Construct from a surfMesh
		MeshedSurface(const surfMesh&);

		//- Construct by transferring the contents from a UnsortedMeshedSurface
		MeshedSurface(UnsortedMeshedSurface<Face>&&)
		{
			NotImplemented;
		}// Commented by Amin

		//- Construct by transferring the contents from a MeshedSurface
		/*MeshedSurface(MeshedSurface<Face>&&)
		{
			NotImplemented;
		}*/// Commented by Amin

		//- Construct from file name (uses extension to determine type)
		MeshedSurface(const fileName&);

		//- Construct from file name (uses extension to determine type)
		MeshedSurface(const fileName&, const word& ext);

		//- Construct from database
		MeshedSurface(const Time&, const word& surfName = "");


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			MeshedSurface,
			fileExtension,
			(
				const fileName& name
				),
				(name)
		);*/

		typedef autoPtr<MeshedSurface> (*fileExtensionConstructorPtr)(const fileName& name);
		typedef HashTable<fileExtensionConstructorPtr, word, string::hash> fileExtensionConstructorTable;
		static FoamMeshedSurface_EXPORT fileExtensionConstructorTable* fileExtensionConstructorTablePtr_;
		static FoamMeshedSurface_EXPORT void constructfileExtensionConstructorTables();
		static FoamMeshedSurface_EXPORT void destroyfileExtensionConstructorTables();

		template <class MeshedSurfaceType>
		class addfileExtensionConstructorToTable
		{
		public:
			static autoPtr<MeshedSurface> New(const fileName& name)
			{
				return autoPtr<MeshedSurface>(new MeshedSurfaceType(name));
			}

			addfileExtensionConstructorToTable(const word& lookup = MeshedSurfaceType::typeName)
			{
				constructfileExtensionConstructorTables();
				if (!fileExtensionConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "MeshedSurface" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addfileExtensionConstructorToTable() { destroyfileExtensionConstructorTables(); }
		};

		template <class MeshedSurfaceType>
		class addRemovablefileExtensionConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<MeshedSurface> New(const fileName& name)
			{
				return autoPtr<MeshedSurface>(new MeshedSurfaceType(name));
			}

			addRemovablefileExtensionConstructorToTable(const word& lookup = MeshedSurfaceType::typeName) : lookup_(
				lookup)
			{
				constructfileExtensionConstructorTables();
				fileExtensionConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablefileExtensionConstructorToTable()
			{
				if (fileExtensionConstructorTablePtr_) { fileExtensionConstructorTablePtr_->erase(lookup_); }
			}
		};


		// Selectors

			//- Select constructed from filename (explicit extension)
		static autoPtr<MeshedSurface> New
		(
			const fileName&,
			const word& ext
		);

		//- Select constructed from filename (implicit extension)
		static autoPtr<MeshedSurface> New(const fileName&);


		//- Destructor
		virtual ~MeshedSurface();


		// Member Function Selectors

		/*declareMemberFunctionSelectionTable
		(
			void,
			UnsortedMeshedSurface,
			write,
			fileExtension,
			(
				const fileName& name,
				const MeshedSurface<Face>& surf
				),
				(name, surf)
		);*/

		typedef void (*writefileExtensionMemberFunctionPtr)(const fileName& name, const MeshedSurface<Face>& surf);
		typedef HashTable<writefileExtensionMemberFunctionPtr, word, string::hash>
		writefileExtensionMemberFunctionTable;
		static FoamMeshedSurface_EXPORT writefileExtensionMemberFunctionTable* writefileExtensionMemberFunctionTablePtr_;

		template <class UnsortedMeshedSurfaceType>
		class addwritefileExtensionMemberFunctionToTable
		{
		public:
			addwritefileExtensionMemberFunctionToTable(const word& lookup = UnsortedMeshedSurfaceType::typeName)
			{
				constructwritefileExtensionMemberFunctionTables();
				writefileExtensionMemberFunctionTablePtr_->insert(lookup, UnsortedMeshedSurfaceType::write);
			}

			~addwritefileExtensionMemberFunctionToTable() { destroywritefileExtensionMemberFunctionTables(); }
		};

		static FoamMeshedSurface_EXPORT void constructwritefileExtensionMemberFunctionTables();
		static FoamMeshedSurface_EXPORT void destroywritefileExtensionMemberFunctionTables();

		//- Write to file
		static void write(const fileName&, const MeshedSurface<Face>&);


		// Member Functions

			// Access

				//- The surface size is the number of faces
		label size() const
		{
			return ParentType::size();
		}

		//- Return const access to the faces
		inline const List<Face>& faces() const
		{
			return static_cast<const List<Face> &>(*this);
		}

		//- Const access to the surface zones.
		//  If zones are defined, they must be contiguous and cover the
		//  entire surface
		const List<surfZone>& surfZones() const
		{
			return zones_;
		}

		//- Add surface zones
		virtual void addZones
		(
			const UList<surfZone>&,
			const bool cullEmpty = false
		);

		//- Add surface zones
		virtual void addZones
		(
			const labelUList& sizes,
			const UList<word>& names,
			const bool cullEmpty = false
		);

		//- Add surface zones
		virtual void addZones
		(
			const labelUList& sizes,
			const bool cullEmpty = false
		);

		//- Remove surface zones
		virtual void removeZones();


		// Edit

			//- Clear all storage
		virtual void clear();

		//- Move points
		virtual void movePoints(const pointField&);

		//- Scale points. A non-positive factor is ignored
		virtual void scalePoints(const scalar);

		//- Reset primitive data (points, faces and zones)
		//  Note, optimized to avoid overwriting data (with null)
		virtual void reset
		(
			pointField&& points,
			List<Face>&& faces,
			surfZoneList&& zones
		);

		//- Reset primitive data (points, faces and zones)
		//  Note, optimized to avoid overwriting data (with null)
		virtual void reset
		(
			List<point>&& points,
			List<Face>&& faces,
			surfZoneList&& zones
		);

		//- Remove invalid faces
		virtual void cleanup(const bool verbose);

		virtual bool stitchFaces
		(
			const scalar tol = small,
			const bool verbose = false
		);

		virtual bool checkFaces
		(
			const bool verbose = false
		);

		//- Triangulate in-place, returning the number of triangles added
		virtual label triangulate();

		//- Triangulate in-place, returning the number of triangles added
		//  and setting a map of original face Ids.
		//  The faceMap is zero-sized when no triangulation was done.
		virtual label triangulate(List<label>& faceMap);


		//- Return new surface.
		//  Returns return pointMap, faceMap from subsetMeshMap
		MeshedSurface subsetMesh
		(
			const labelHashSet& include,
			labelList& pointMap,
			labelList& faceMap
		) const;

		//- Return new surface.
		MeshedSurface subsetMesh
		(
			const labelHashSet& include
		) const;

		//- Transfer the contents of the argument and annul the argument
		void transfer(MeshedSurface<Face>&);

		//- Transfer the contents of the argument and annul the argument
		void transfer(UnsortedMeshedSurface<Face>&);


		// Read

			//- Read from file. Chooses reader based on explicit extension
		bool read(const fileName&, const word& ext);

		//- Read from file. Chooses reader based on detected extension
		virtual bool read(const fileName&);


		// Write

		void writeStats(Ostream& os) const;

		//- Generic write routine. Chooses writer based on extension.
		virtual void write(const fileName& name) const
		{
			write(name, *this);
		}

		//- Write to database
		void write(const Time&, const word& surfName = "") const;


		// Member Operators

		void operator=(const MeshedSurface<Face>&);

		//- Conversion operator to MeshedSurfaceProxy
		operator MeshedSurfaceProxy<Face>() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	//- Specialization for holding triangulated information
	template<>
	inline bool MeshedSurface<triFace>::isTri()
	{
		return true;
	}


	//- Specialization for holding triangulated information
	template<>
	inline label MeshedSurface<triFace>::triangulate()
	{
		return 0;
	}


	//- Specialization for holding triangulated information
	template<>
	inline label MeshedSurface<triFace>::triangulate(List<label>& faceMap)
	{
		if (notNull(faceMap))
		{
			faceMap.clear();
		}

		return 0;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <MeshedSurfaceI.hxx>
#include <MeshedSurfaceZonesI.hxx>
#include <MeshedSurfaceIOI.hxx>
#include <MeshedSurfaceNewI.hxx>

//#ifdef NoRepository
//#include <MeshedSurface.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_MeshedSurface_Header
