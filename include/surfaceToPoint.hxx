#pragma once
#ifndef _surfaceToPoint_Header
#define _surfaceToPoint_Header

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
	tnbLib::surfaceToPoint

Description
	A topoSetSource to selects points based on relation to surface.

	Select based on:
	- distance to surface
	- inside/outside status to surface
	  (Uses normal of nearest surface triangle so requires valid surface
	  topology!)

SourceFiles
	surfaceToPoint.C

\*---------------------------------------------------------------------------*/

#include <topoSetSource.hxx>
#include <Map.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	class triSurfaceSearch;

	/*---------------------------------------------------------------------------*\
							   Class surfaceToPoint Declaration
	\*---------------------------------------------------------------------------*/

	class surfaceToPoint
		:
		public topoSetSource
	{

		// Private Data

			//- Add usage string
		static FoamFvMesh_EXPORT addToUsageTable usage_;

		//- Name of surface file
		fileName surfName_;

		//- If > 0 : include points with distance to surface less than nearDist.
		scalar nearDist_;

		//- Include all points on opposite sign of normal on nearest surface.
		bool includeInside_;

		//- Include all points on this sign of normal on nearest surface.
		bool includeOutside_;


		// Private Member Functions

			//- Depending on surface add to or delete from pointSet.
		FoamFvMesh_EXPORT void combine(topoSet& set, const bool add) const;

		//- Check settings at construction time.
		FoamFvMesh_EXPORT void checkSettings() const;

	public:

		//- Runtime type information
		/*TypeName("surfaceToPoint");*/
		static const char* typeName_() { return "surfaceToPoint"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT surfaceToPoint
		(
			const polyMesh& mesh,
			const fileName& surfName,
			const scalar nearDist,
			const bool includeInside,
			const bool includeOutside
		);

		//- Construct from dictionary
		FoamFvMesh_EXPORT surfaceToPoint
		(
			const polyMesh& mesh,
			const dictionary& dict
		);

		//- Construct from Istream
		FoamFvMesh_EXPORT surfaceToPoint
		(
			const polyMesh& mesh,
			Istream&
		);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~surfaceToPoint();


		// Member Functions

		virtual sourceType setType() const
		{
			return POINTSETSOURCE;
		}

		FoamFvMesh_EXPORT virtual void applyToSet
		(
			const topoSetSource::setAction action,
			topoSet&
		) const;

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceToPoint_Header
