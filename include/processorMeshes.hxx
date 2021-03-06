#pragma once
#ifndef _processorMeshes_Header
#define _processorMeshes_Header

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
	tnbLib::processorMeshes

Description
	Container for processor mesh addressing.

SourceFiles
	processorMeshes.C

\*---------------------------------------------------------------------------*/

#include <PtrList.hxx>
#include <fvMesh.hxx>
#include <IOobjectList.hxx>
#include <labelIOList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{


	/*---------------------------------------------------------------------------*\
						 Class processorMeshes Declaration
	\*---------------------------------------------------------------------------*/

	class processorMeshes
	{
		// Private Data

		const word meshName_;

		//- Processor databases
		PtrList<Time>& databases_;

		//- List of processor meshes
		PtrList<fvMesh> meshes_;

		//- List of processor point addressing lists
		PtrList<labelIOList> pointProcAddressing_;

		//- List of processor face addressing lists
		PtrList<labelIOList> faceProcAddressing_;

		//- List of processor cell addressing lists
		PtrList<labelIOList> cellProcAddressing_;

		//- List of processor boundary addressing lists
		PtrList<labelIOList> boundaryProcAddressing_;


		// Private Member Functions

			//- Read all meshes
		FoamParallel_EXPORT void read();


	public:

		// Constructors

			//- Construct from components
		FoamParallel_EXPORT processorMeshes(PtrList<Time>& databases, const word& meshName);

		//- Disallow default bitwise copy construction
		FoamParallel_EXPORT processorMeshes(const processorMeshes&) = delete;


		// Member Functions

			//- Update the meshes based on the mesh files saved in time directories
		FoamParallel_EXPORT fvMesh::readUpdateState readUpdate();

		//- Reconstruct point position after motion in parallel
		FoamParallel_EXPORT void reconstructPoints(fvMesh&);

		PtrList<fvMesh>& meshes()
		{
			return meshes_;
		}

		const PtrList<labelIOList>& pointProcAddressing() const
		{
			return pointProcAddressing_;
		}

		PtrList<labelIOList>& faceProcAddressing()
		{
			return faceProcAddressing_;
		}

		const PtrList<labelIOList>& cellProcAddressing() const
		{
			return cellProcAddressing_;
		}

		const PtrList<labelIOList>& boundaryProcAddressing() const
		{
			return boundaryProcAddressing_;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamParallel_EXPORT void operator=(const processorMeshes&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_processorMeshes_Header
