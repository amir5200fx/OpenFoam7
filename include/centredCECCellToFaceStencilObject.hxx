#pragma once
#ifndef _centredCECCellToFaceStencilObject_Header
#define _centredCECCellToFaceStencilObject_Header

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
	tnbLib::centredCECCellToFaceStencilObject

Description

SourceFiles

\*---------------------------------------------------------------------------*/

#include <extendedCentredCellToFaceStencil.hxx>
#include <CECCellToFaceStencil.hxx>
#include <MeshObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				  Class centredCECCellToFaceStencilObject Declaration
	\*---------------------------------------------------------------------------*/

	class centredCECCellToFaceStencilObject
		:
		public MeshObject
		<
		fvMesh,
		TopologicalMeshObject,
		centredCECCellToFaceStencilObject
		>,
		public extendedCentredCellToFaceStencil
	{

	public:

		/*TypeName("centredCECCellToFaceStencil");*/
		static const char* typeName_() { return "centredCECCellToFaceStencil"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from uncompacted face stencil
		explicit centredCECCellToFaceStencilObject
		(
			const fvMesh& mesh
		)
			:
			MeshObject
			<
			fvMesh,
			tnbLib::TopologicalMeshObject,
			centredCECCellToFaceStencilObject
			>(mesh),
			extendedCentredCellToFaceStencil(CECCellToFaceStencil(mesh))
		{
			if (extendedCellToFaceStencil::debug)
			{
				Info << "Generated centred stencil " << type()
					<< nl << endl;
				writeStencilStats(Info, stencil(), map());
			}
		}


		//- Destructor
		virtual ~centredCECCellToFaceStencilObject()
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_centredCECCellToFaceStencilObject_Header
