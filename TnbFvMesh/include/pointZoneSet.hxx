#pragma once
#ifndef _pointZoneSet_Header
#define _pointZoneSet_Header

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
	tnbLib::pointZoneSet

Description
	Like pointSet but -reads data from pointZone -updates pointZone when
	writing.

SourceFiles
	pointZone.C

\*---------------------------------------------------------------------------*/

#include <pointSet.hxx>
#include <boolList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class pointZoneSet Declaration
	\*---------------------------------------------------------------------------*/

	class pointZoneSet
		:
		public pointSet
	{
		// Private Data

		const polyMesh& mesh_;

		labelList addressing_;

		// Private Member Functions


	public:

		//- Runtime type information
		/*TypeName("pointZoneSet");*/
		static const char* typeName_() { return "pointZoneSet"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from objectRegistry and name
		FoamFvMesh_EXPORT pointZoneSet
		(
			const polyMesh& mesh,
			const word& name,
			readOption r = MUST_READ,
			writeOption w = NO_WRITE
		);

		//- Construct from additional size of labelHashSet
		FoamFvMesh_EXPORT pointZoneSet
		(
			const polyMesh& mesh,
			const word& name,
			const label,
			writeOption w = NO_WRITE
		);

		//- Construct from existing set
		FoamFvMesh_EXPORT pointZoneSet
		(
			const polyMesh& mesh,
			const word& name,
			const topoSet&,
			writeOption w = NO_WRITE
		);



		//- Destructor
		FoamFvMesh_EXPORT virtual ~pointZoneSet();


		// Member Functions

		const labelList& addressing() const
		{
			return addressing_;
		}

		labelList& addressing()
		{
			return addressing_;
		}

		//- Sort addressing and make pointSet part consistent with addressing
		FoamFvMesh_EXPORT void updateSet();

		//- Invert contents. (insert all members 0..maxLen-1 which were not in
		//  set)
		FoamFvMesh_EXPORT virtual void invert(const label maxLen);

		//- Subset contents. Only elements present in both sets remain.
		FoamFvMesh_EXPORT virtual void subset(const topoSet& set);

		//- Add elements present in set.
		FoamFvMesh_EXPORT virtual void addSet(const topoSet& set);

		//- Delete elements present in set.
		FoamFvMesh_EXPORT virtual void deleteSet(const topoSet& set);

		//- Sync pointZoneSet across coupled patches.
		FoamFvMesh_EXPORT virtual void sync(const polyMesh& mesh);

		//- Write maxLen items with label and coordinates.
		FoamFvMesh_EXPORT virtual void writeDebug
		(
			Ostream& os,
			const primitiveMesh&,
			const label maxLen
		) const;

		//- Write pointZone
		FoamFvMesh_EXPORT virtual bool writeObject
		(
			IOstream::streamFormat,
			IOstream::versionNumber,
			IOstream::compressionType,
			const bool write = true
		) const;

		//- Update any stored data for new labels
		FoamFvMesh_EXPORT virtual void updateMesh(const mapPolyMesh& morphMap);

		//- Return max index+1.
		FoamFvMesh_EXPORT virtual label maxSize(const polyMesh& mesh) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pointZoneSet_Header
