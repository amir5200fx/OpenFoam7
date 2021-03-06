#pragma once
#ifndef _MeshedSurfaceIOAllocator_Header
#define _MeshedSurfaceIOAllocator_Header

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
	tnbLib::MeshedSurfaceIOAllocator

Description
	A helper class for storing points, faces and zones with IO capabilities.

SourceFiles
	MeshedSurfaceIOAllocator.C

\*---------------------------------------------------------------------------*/

#include <pointIOField.hxx>
#include <faceIOList.hxx>
#include <surfZoneIOList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class MeshedSurfaceIOAllocator Declaration
	\*---------------------------------------------------------------------------*/

	class MeshedSurfaceIOAllocator
	{
		// Private Data

			//- Points
		pointIOField points_;

		//- Faces
		faceCompactIOList faces_;

		//- Surface zones
		surfZoneIOList zones_;


	public:

		// Constructors

			//- Read construct from IOobjects
		FoamFvMesh_EXPORT MeshedSurfaceIOAllocator
		(
			const IOobject& ioPoints,
			const IOobject& ioFaces,
			const IOobject& ioZones
		);

		//- Construct from IOobjects, copying components
		FoamFvMesh_EXPORT MeshedSurfaceIOAllocator
		(
			const IOobject& ioPoints,
			const pointField& points,
			const IOobject& ioFaces,
			const faceList& faces,
			const IOobject& ioZones,
			const surfZoneList& zones
		);

		//- Construct from IOobjects, possibly transferring components
		FoamFvMesh_EXPORT MeshedSurfaceIOAllocator
		(
			const IOobject& ioPoints,
			pointField&& points,
			const IOobject& ioFaces,
			faceList&& faces,
			const IOobject& ioZones,
			surfZoneList&& zones
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT MeshedSurfaceIOAllocator(const MeshedSurfaceIOAllocator&) = delete;


		// Member Functions

			// Access

				//- Non-const access to the points
		pointIOField& storedIOPoints()
		{
			return points_;
		}

		//- Non-const access to the faces
		faceCompactIOList& storedIOFaces()
		{
			return faces_;
		}

		//- Non-const access to the zones
		surfZoneIOList& storedIOZones()
		{
			return zones_;
		}

		//- Const access to the points
		const pointIOField& storedIOPoints() const
		{
			return points_;
		}

		//- Const access to the faces
		const faceCompactIOList& storedIOFaces() const
		{
			return faces_;
		}

		//- Const access to the zones
		const surfZoneIOList& storedIOZones() const
		{
			return zones_;
		}


		//  Storage management

			//- Clear primitive data (points, faces and zones)
		FoamFvMesh_EXPORT void clear();

		//- Reset primitive data (points, faces and zones)
		FoamFvMesh_EXPORT void resetFaces
		(
			faceList&& faces,
			surfZoneList&& zones
		);

		//- Reset primitive data (points, faces and zones)
		FoamFvMesh_EXPORT void reset
		(
			pointField&& points,
			faceList&& faces,
			surfZoneList&& zones
		);

		//- Reset primitive data (points, faces and zones)
		//  Note, optimized to avoid overwriting data (with null)
		FoamFvMesh_EXPORT void reset
		(
			List<point>&& points,
			faceList&& faces,
			surfZoneList&& zones
		);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const MeshedSurfaceIOAllocator&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_MeshedSurfaceIOAllocator_Header
