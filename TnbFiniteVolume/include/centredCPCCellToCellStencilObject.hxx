#pragma once
#ifndef _centredCPCCellToCellStencilObject_Header
#define _centredCPCCellToCellStencilObject_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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
	tnbLib::centredCPCCellToCellStencilObject

Description

SourceFiles

\*---------------------------------------------------------------------------*/

#include <extendedCentredCellToCellStencil.hxx>
#include <CPCCellToCellStencil.hxx>
#include <MeshObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				  Class centredCPCCellToCellStencilObject Declaration
	\*---------------------------------------------------------------------------*/

	class centredCPCCellToCellStencilObject
		:
		public MeshObject
		<
		fvMesh,
		TopologicalMeshObject,
		centredCPCCellToCellStencilObject
		>,
		public extendedCentredCellToCellStencil
	{

	public:

		TypeName("centredCPCCellToCellStencil");

		// Constructors

			//- Construct from uncompacted cell stencil
		explicit centredCPCCellToCellStencilObject
		(
			const fvMesh& mesh
		)
			:
			MeshObject
			<
			fvMesh,
			tnbLib::TopologicalMeshObject,
			centredCPCCellToCellStencilObject
			>(mesh),
			extendedCentredCellToCellStencil(CPCCellToCellStencil(mesh))
		{}


		//- Destructor
		virtual ~centredCPCCellToCellStencilObject()
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_centredCPCCellToCellStencilObject_Header
