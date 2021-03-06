#pragma once
#ifndef _hexRef8Data_Header
#define _hexRef8Data_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
	tnbLib::hexRef8Data

Description
	Various for reading/decomposing/reconstructing/distributing refinement
	data.

SourceFiles
	hexRef8Data.C

\*---------------------------------------------------------------------------*/

#include <labelIOList.hxx>
#include <uniformDimensionedFields.hxx>
#include <UPtrList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class mapPolyMesh;
	class mapDistributePolyMesh;
	class refinementHistory;
	class fvMesh;

	/*---------------------------------------------------------------------------*\
							   Class hexRef8Data Declaration
	\*---------------------------------------------------------------------------*/

	class hexRef8Data
	{

	private:

		// Private Data

		autoPtr<labelIOList> cellLevelPtr_;

		autoPtr<labelIOList> pointLevelPtr_;

		autoPtr<uniformDimensionedScalarField> level0EdgePtr_;

		autoPtr<refinementHistory> refHistoryPtr_;


	public:

		// Constructors

			//- Construct read. Has special provision for only some processors
			//  having the files so can be used in redistribution.
		FoamDynamicMesh_EXPORT hexRef8Data(const IOobject& io);

		//- Construct as subset
		FoamDynamicMesh_EXPORT hexRef8Data
		(
			const IOobject& io,
			const hexRef8Data&,
			const labelList& cellMap,
			const labelList& pointMap
		);

		//- Construct from multiple hexRef8Data
		FoamDynamicMesh_EXPORT hexRef8Data
		(
			const IOobject& io,
			const UPtrList<const labelList>& cellMaps,
			const UPtrList<const labelList>& pointMaps,
			const UPtrList<const hexRef8Data>&
		);

		//- Disallow default bitwise copy construction
		hexRef8Data(const hexRef8Data&) = delete;


		//- Destructor
		FoamDynamicMesh_EXPORT ~hexRef8Data();


		// Member Functions

			//- Parallel synchronise. This enforces valid objects on all processors
			//  (even if they don't have a mesh). Used by redistributePar.
		FoamDynamicMesh_EXPORT void sync(const IOobject& io);

		//- In-place update for topology changes
		FoamDynamicMesh_EXPORT void updateMesh(const mapPolyMesh&);

		//- In-place distribute
		FoamDynamicMesh_EXPORT void distribute(const mapDistributePolyMesh&);

		//- Write
		FoamDynamicMesh_EXPORT bool write() const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const hexRef8Data&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_hexRef8Data_Header
