#pragma once
#ifndef _fvBoundaryMeshMapper_Header
#define _fvBoundaryMeshMapper_Header

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
	tnbLib::fvBoundaryMeshMapper

Description
	tnbLib::fvBoundaryMeshMapper

\*---------------------------------------------------------------------------*/

#include <PtrList.hxx>
#include <fvPatchMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class fvBoundaryMeshMapper Declaration
	\*---------------------------------------------------------------------------*/

	class fvBoundaryMeshMapper
		:
		public PtrList<fvPatchMapper>
	{
	public:

		// Constructors

			//- Construct from components
		fvBoundaryMeshMapper
		(
			const fvMesh& mesh,
			const faceMapper& faceMap
		)
			:
			PtrList<fvPatchMapper>(mesh.boundary().size())
		{
			const fvBoundaryMesh& patches = mesh.boundary();

			forAll(patches, patchi)
			{
				set
				(
					patchi,
					new fvPatchMapper
					(
						patches[patchi],
						faceMap
					)
				);
			}
		}

		//- Disallow default bitwise copy construction
		FoamFiniteVolume_EXPORT fvBoundaryMeshMapper(const fvBoundaryMeshMapper&) = delete;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFiniteVolume_EXPORT void operator=(const fvBoundaryMeshMapper&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvBoundaryMeshMapper_Header
