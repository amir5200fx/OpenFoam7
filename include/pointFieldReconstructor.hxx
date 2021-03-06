#pragma once
#ifndef _pointFieldReconstructor_Header
#define _pointFieldReconstructor_Header

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
	tnbLib::pointFieldReconstructor

Description
	Point field reconstructor.

SourceFiles
	pointFieldReconstructor.C

\*---------------------------------------------------------------------------*/

#include <pointMesh.hxx>
#include <pointFields.hxx>
#include <pointPatchFieldMapper.hxx>
#include <setSizeFieldMapper.hxx>
#include <IOobjectList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class pointFieldReconstructor Declaration
	\*---------------------------------------------------------------------------*/

	class pointFieldReconstructor
	{
		// Private Data

			//- Reconstructed mesh reference
		const pointMesh& mesh_;

		//- List of processor meshes
		const PtrList<pointMesh>& procMeshes_;

		//- List of processor point addressing lists
		const PtrList<labelIOList>& pointProcAddressing_;

		//- List of processor boundary addressing lists
		const PtrList<labelIOList>& boundaryProcAddressing_;

		//- Point patch addressing
		labelListListList patchPointAddressing_;

		//- Number of fields reconstructed
		label nReconstructed_;


	public:

		//- Mapper for sizing only - does not do any actual mapping.
		class pointPatchFieldReconstructor
			:
			public pointPatchFieldMapper,
			public setSizeFieldMapper
		{
		public:

			// Constructors

				//- Construct given size
			pointPatchFieldReconstructor(const label size)
				:
				setSizeFieldMapper(size)
			{}
		};


		// Constructors

			//- Construct from components
		FoamParallel_EXPORT pointFieldReconstructor
		(
			const pointMesh& mesh,
			const PtrList<pointMesh>& procMeshes,
			const PtrList<labelIOList>& pointProcAddressing,
			const PtrList<labelIOList>& boundaryProcAddressing
		);

		//- Disallow default bitwise copy construction
		FoamParallel_EXPORT pointFieldReconstructor(const pointFieldReconstructor&) = delete;


		// Member Functions

			//- Return number of fields reconstructed
		label nReconstructed() const
		{
			return nReconstructed_;
		}

		//- Reconstruct field
		template<class Type>
		tmp<GeometricField<Type, pointPatchField, pointMesh>>
			reconstructField(const IOobject& fieldIoObject);

		//- Reconstruct and write all fields
		template<class Type>
		void reconstructFields
		(
			const IOobjectList& objects,
			const HashSet<word>& selectedFields
		);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamParallel_EXPORT void operator=(const pointFieldReconstructor&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <pointFieldReconstructorReconstructFieldsI.hxx>

//#ifdef NoRepository
//#include <pointFieldReconstructorReconstructFields.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pointFieldReconstructor_Header
