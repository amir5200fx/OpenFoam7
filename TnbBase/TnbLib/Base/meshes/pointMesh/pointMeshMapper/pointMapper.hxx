#pragma once
#ifndef _pointMapper_Header
#define _pointMapper_Header

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
	tnbLib::pointMapper

Description
	This object provides mapping and fill-in information for point data
	between the two meshes after the topological change.  It is
	constructed from mapPolyMesh.

SourceFiles
	pointMapper.C

\*---------------------------------------------------------------------------*/

#include <morphFieldMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class pointMesh;
	class mapPolyMesh;
	class polyMesh;

	/*---------------------------------------------------------------------------*\
							   Class pointMapper Declaration
	\*---------------------------------------------------------------------------*/

	class pointMapper
		:
		public morphFieldMapper
	{
		// Private Data

			//- Reference to pointMesh
		const pointMesh& pMesh_;

		//- Reference to mapPolyMesh
		const mapPolyMesh& mpm_;

		//- Are there any inserted (unmapped) points
		bool insertedPoints_;

		//- Is the mapping direct
		bool direct_;


		// Demand-driven private data

			//- Direct addressing (only one for of addressing is used)
		mutable labelList* directAddrPtr_;

		//- Interpolated addressing (only one for of addressing is used)
		mutable labelListList* interpolationAddrPtr_;

		//- Interpolation weights
		mutable scalarListList* weightsPtr_;

		//- Inserted points
		mutable labelList* insertedPointLabelsPtr_;


		// Private Member Functions

			//- Calculate addressing for mapping with inserted points
		FoamBase_EXPORT void calcAddressing() const;

		//- Clear out local storage
		FoamBase_EXPORT void clearOut();


	public:

		// Constructors

			//- Construct from mapPolyMesh
		FoamBase_EXPORT pointMapper(const pointMesh&, const mapPolyMesh& mpm);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT pointMapper(const pointMapper&) = delete;


		//- Destructor
		FoamBase_EXPORT virtual ~pointMapper();


		// Member Functions

			//- Return size before mapping
		FoamBase_EXPORT virtual label sizeBeforeMapping() const;

		//- Is the mapping direct
		virtual bool direct() const
		{
			return direct_;
		}

		//- Are there unmapped values? I.e. do all size() elements get
		//  get value
		virtual bool hasUnmapped() const
		{
			return insertedObjects();
		}

		//- Return direct addressing
		FoamBase_EXPORT virtual const labelUList& directAddressing() const;

		//- Return interpolated addressing
		FoamBase_EXPORT virtual const labelListList& addressing() const;

		//- Return interpolaion weights
		FoamBase_EXPORT virtual const scalarListList& weights() const;

		//- Are there any inserted points
		bool insertedObjects() const
		{
			return insertedPoints_;
		}

		//- Return list of inserted points
		FoamBase_EXPORT const labelList& insertedObjectLabels() const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const pointMapper&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pointMapper_Header
