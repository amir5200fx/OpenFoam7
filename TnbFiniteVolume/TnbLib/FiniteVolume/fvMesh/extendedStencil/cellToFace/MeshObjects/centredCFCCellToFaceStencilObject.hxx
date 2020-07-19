#pragma once
#ifndef _centredCFCCellToFaceStencilObject_Header
#define _centredCFCCellToFaceStencilObject_Header

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
	tnbLib::centredCFCCellToFaceStencilObject

Description

SourceFiles

\*---------------------------------------------------------------------------*/

#include <extendedCentredCellToFaceStencil.hxx>
#include <CFCCellToFaceStencil.hxx>
#include <MeshObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				  Class centredCFCCellToFaceStencilObject Declaration
	\*---------------------------------------------------------------------------*/

	class centredCFCCellToFaceStencilObject
		:
		public MeshObject
		<
		fvMesh,
		TopologicalMeshObject,
		centredCFCCellToFaceStencilObject
		>,
		public extendedCentredCellToFaceStencil
	{

	public:

		TypeName("centredCFCCellToFaceStencil");

		// Constructors

			//- Construct from uncompacted face stencil
		explicit centredCFCCellToFaceStencilObject
		(
			const fvMesh& mesh
		)
			:
			MeshObject
			<
			fvMesh,
			tnbLib::TopologicalMeshObject,
			centredCFCCellToFaceStencilObject
			>(mesh),
			extendedCentredCellToFaceStencil(CFCCellToFaceStencil(mesh))
		{
			if (extendedCellToFaceStencil::debug)
			{
				Info << "Generated centred stencil " << type()
					<< nl << endl;
				writeStencilStats(Info, stencil(), map());
			}
		}


		//- Destructor
		virtual ~centredCFCCellToFaceStencilObject()
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_centredCFCCellToFaceStencilObject_Header
