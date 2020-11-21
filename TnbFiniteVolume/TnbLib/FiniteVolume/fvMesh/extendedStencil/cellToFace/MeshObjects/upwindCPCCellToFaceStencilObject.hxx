#pragma once
#ifndef _upwindCPCCellToFaceStencilObject_Header
#define _upwindCPCCellToFaceStencilObject_Header

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
	tnbLib::upwindCPCCellToFaceStencilObject

Description

SourceFiles

\*---------------------------------------------------------------------------*/

#include <extendedUpwindCellToFaceStencil.hxx>
#include <CPCCellToFaceStencil.hxx>
#include <MeshObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				  Class upwindCPCCellToFaceStencilObject Declaration
	\*---------------------------------------------------------------------------*/

	class upwindCPCCellToFaceStencilObject
		:
		public MeshObject
		<
		fvMesh,
		TopologicalMeshObject,
		upwindCPCCellToFaceStencilObject
		>,
		public extendedUpwindCellToFaceStencil
	{

	public:

		/*TypeName("upwindCPCCellToFaceStencil");*/
		static const char* typeName_() { return "upwindCPCCellToFaceStencil"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from uncompacted face stencil
		upwindCPCCellToFaceStencilObject
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
			upwindCPCCellToFaceStencilObject
			>(mesh),
			extendedUpwindCellToFaceStencil
			(
				CPCCellToFaceStencil(mesh),
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
		virtual ~upwindCPCCellToFaceStencilObject()
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_upwindCPCCellToFaceStencilObject_Header
