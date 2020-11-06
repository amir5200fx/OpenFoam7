#pragma once
#ifndef _searchableSurfaceToFaceZone_Header
#define _searchableSurfaceToFaceZone_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::searchableSurfaceToFaceZone

Description
	A topoSetSource to select faces based on intersection (of cell-cell
	vector) with a surface.

SourceFiles
	searchableSurfaceToFaceZone.C

\*---------------------------------------------------------------------------*/

#include <topoSetSource.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class searchableSurface;

	/*---------------------------------------------------------------------------*\
					   Class searchableSurfaceToFaceZone Declaration
	\*---------------------------------------------------------------------------*/

	class searchableSurfaceToFaceZone
		:
		public topoSetSource
	{
		// Private Data

			//- Add usage string
		static FoamFvMesh_EXPORT addToUsageTable usage_;

		//- Surface
		autoPtr<searchableSurface> surfacePtr_;

	public:

		//- Runtime type information
		/*TypeName("searchableSurfaceToFaceZone");*/
		static const char* typeName_() { return "searchableSurfaceToFaceZone"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from dictionary
		FoamFvMesh_EXPORT searchableSurfaceToFaceZone
		(
			const polyMesh& mesh,
			const dictionary& dict
		);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~searchableSurfaceToFaceZone();


		// Member Functions

		virtual sourceType setType() const
		{
			return FACEZONESOURCE;
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

#endif // !_searchableSurfaceToFaceZone_Header
