#pragma once
#ifndef _pointPatchDist_Header
#define _pointPatchDist_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::pointPatchDist

Description
	Calculation of distance to nearest patch for all points

SourceFiles
	pointPatchDist.C

\*---------------------------------------------------------------------------*/

#include <pointFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class pointMesh;

	/*---------------------------------------------------------------------------*\
							  Class pointPatchDist Declaration
	\*---------------------------------------------------------------------------*/

	class pointPatchDist
		:
		public pointScalarField
	{
		// Private Member Data

			//- Reference to pointField
		const pointField& points_;

		//- Set of patch IDs
		const labelHashSet patchIDs_;

		//- Number of unset points
		label nUnset_;


	public:

		// Constructors

			//- Construct from mesh and set of patches
		FoamDynamicMesh_EXPORT pointPatchDist
		(
			const pointMesh& pMesh,
			const labelHashSet& patchIDs,
			const pointField& points
		);

		//- Disallow default bitwise copy construction
		pointPatchDist(const pointPatchDist&) = delete;


		//- Destructor
		FoamDynamicMesh_EXPORT virtual ~pointPatchDist();


		// Member Functions

		const pointScalarField& y() const
		{
			return *this;
		}

		label nUnset() const
		{
			return nUnset_;
		}

		//- Correct for mesh geom/topo changes
		FoamDynamicMesh_EXPORT void correct();


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const pointPatchDist&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pointPatchDist_Header
