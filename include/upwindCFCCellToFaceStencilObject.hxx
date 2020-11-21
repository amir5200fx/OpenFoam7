#pragma once
#ifndef _upwindCFCCellToFaceStencilObject_Header
#define _upwindCFCCellToFaceStencilObject_Header

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
	tnbLib::upwindCFCCellToFaceStencilObject

Description

SourceFiles

\*---------------------------------------------------------------------------*/

#include <extendedUpwindCellToFaceStencil.hxx>
#include <CFCCellToFaceStencil.hxx>
#include <MeshObject.hxx>

#include <fvMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				  Class upwindCFCCellToFaceStencilObject Declaration
	\*---------------------------------------------------------------------------*/

	class upwindCFCCellToFaceStencilObject
		:
		public MeshObject
		<
		fvMesh,
		TopologicalMeshObject,
		upwindCFCCellToFaceStencilObject
		>,
		public extendedUpwindCellToFaceStencil
	{

	public:

		/*TypeName("upwindCFCCellToFaceStencil");*/
		static const char* typeName_() { return "upwindCFCCellToFaceStencil"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from uncompacted face stencil
		upwindCFCCellToFaceStencilObject
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
			upwindCFCCellToFaceStencilObject
			>(mesh),
			extendedUpwindCellToFaceStencil
			(
				CFCCellToFaceStencil(mesh),
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


		//- added by amir (quadraticLinearPureUpwindFit.cxx wouldn't compile without this constructor)
		upwindCFCCellToFaceStencilObject
		(
			const fvMesh& mesh
		)
			:
			MeshObject
			<
			fvMesh,
			tnbLib::TopologicalMeshObject,
			upwindCFCCellToFaceStencilObject
			>(mesh),
			extendedUpwindCellToFaceStencil
			(
				CFCCellToFaceStencil(mesh)
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
		virtual ~upwindCFCCellToFaceStencilObject()
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_upwindCFCCellToFaceStencilObject_Header
