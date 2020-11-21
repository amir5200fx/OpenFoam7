#pragma once
#ifndef _regionToFace_Header
#define _regionToFace_Header

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
	tnbLib::regionToFace

Description
	A topoSetSource to select faces belonging to topological connected region
	(that contains given point)

SourceFiles
	regionToFace.C

\*---------------------------------------------------------------------------*/

#include <topoSetSource.hxx>
#include <PackedBoolList.hxx>
#include <indirectPrimitivePatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class regionToFace Declaration
	\*---------------------------------------------------------------------------*/

	class regionToFace
		:
		public topoSetSource
	{
		// Private Data

			//- Add usage string
		static FoamFvMesh_EXPORT addToUsageTable usage_;

		//- Name of set to use
		word setName_;

		//- Coordinate that is nearest/on connected region
		point nearPoint_;

		// Private Member Functions

			//- Walk edge-face-edge
		FoamFvMesh_EXPORT void markZone
		(
			const indirectPrimitivePatch& patch,
			const label proci,
			const label facei,
			const label zoneI,
			labelList& faceZone
		) const;

		FoamFvMesh_EXPORT void combine(topoSet& set, const bool add) const;

	public:

		//- Runtime type information
		/*TypeName("regionToFace");*/
		static const char* typeName_() { return "regionToFace"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT regionToFace
		(
			const polyMesh& mesh,
			const word& setName,
			const point& nearPoint
		);

		//- Construct from dictionary
		FoamFvMesh_EXPORT regionToFace
		(
			const polyMesh& mesh,
			const dictionary& dict
		);

		//- Construct from Istream
		FoamFvMesh_EXPORT regionToFace
		(
			const polyMesh& mesh,
			Istream&
		);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~regionToFace();


		// Member Functions

		virtual sourceType setType() const
		{
			return FACESETSOURCE;
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

#endif // !_regionToFace_Header
