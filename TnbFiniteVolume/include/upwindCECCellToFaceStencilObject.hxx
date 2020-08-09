#pragma once
#ifndef _upwindCECCellToFaceStencilObject_Header
#define _upwindCECCellToFaceStencilObject_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::upwindCECCellToFaceStencilObject

Description

SourceFiles

\*---------------------------------------------------------------------------*/

#include <extendedUpwindCellToFaceStencil.hxx>
#include <CECCellToFaceStencil.hxx>
#include <MeshObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				  Class upwindCECCellToFaceStencilObject Declaration
	\*---------------------------------------------------------------------------*/

	class upwindCECCellToFaceStencilObject
		:
		public MeshObject
		<
		fvMesh,
		TopologicalMeshObject,
		upwindCECCellToFaceStencilObject
		>,
		public extendedUpwindCellToFaceStencil
	{

	public:

		TypeName("upwindCECCellToFaceStencil");

		// Constructors

			//- Construct from uncompacted face stencil
		upwindCECCellToFaceStencilObject
		(
			const fvMesh& mesh,
			const bool pureUpwind,
			const scalar minOpposedness
		)
			:
			MeshObject
			<
			fvMesh,
			tnbLib::TopologicalMeshObject,
			upwindCECCellToFaceStencilObject
			>(mesh),
			extendedUpwindCellToFaceStencil
			(
				CECCellToFaceStencil(mesh),
				pureUpwind,
				minOpposedness
			)
		{
			if (extendedCellToFaceStencil::debug)
			{
				Info << "Generated off-centred stencil " << type()
					<< nl << endl;
				writeStencilStats(Info, ownStencil(), ownMap());
			}
		}


		//- Destructor
		virtual ~upwindCECCellToFaceStencilObject()
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_upwindCECCellToFaceStencilObject_Header
