#pragma once
#ifndef _fvPatchMapper_Header
#define _fvPatchMapper_Header

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
	tnbLib::fvPatchMapper

Description
	Mapping class for a fvPatchField.

SourceFiles
	fvPatchMapper.C

\*---------------------------------------------------------------------------*/

#include <fvPatchFieldMapper.hxx>
#include <faceMapper.hxx>
#include <fvPatch.hxx>
#include <primitiveFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class fvPatch;
	class mapPolyMesh;

	/*---------------------------------------------------------------------------*\
						   Class fvPatchMapper Declaration
	\*---------------------------------------------------------------------------*/

	class fvPatchMapper
		:
		public generalFvPatchFieldMapper
	{
		// Private Data

			//- Reference to patch
		const fvPatch& patch_;

		//- Reference to face mapper
		const faceMapper& faceMap_;

		//- Size before mapping
		const label sizeBeforeMapping_;


		// Demand-driven private data

		mutable bool hasUnmapped_;

		//- Direct addressing (only one for of addressing is used)
		mutable labelList* directAddrPtr_;

		//- Interpolated addressing (only one for of addressing is used)
		mutable labelListList* interpolationAddrPtr_;

		//- Interpolation weights
		mutable scalarListList* weightsPtr_;


		// Private Member Functions

			//- Calculate addressing for mapping with inserted cells
		void calcAddressing() const;

		//- Clear out local storage
		void clearOut();


	public:

		// Static Data Members

		// Constructors

		//- Construct from mappers
		FoamFiniteVolume_EXPORT fvPatchMapper
		(
			const fvPatch& patch,
			const faceMapper& faceMap
		);

		//- Disallow default bitwise copy construction
		FoamFiniteVolume_EXPORT fvPatchMapper
		(
			const fvPatchMapper&
		);


		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~fvPatchMapper();


		// Member Functions

			//- Return size of field before mapping
		virtual label sizeBeforeMapping() const
		{
			return sizeBeforeMapping_;
		}

		//- Is the mapping direct
		virtual bool direct() const
		{
			return faceMap_.direct();
		}

		virtual bool hasUnmapped() const
		{
			return hasUnmapped_;
		}

		//- Return direct addressing
		FoamFiniteVolume_EXPORT virtual const labelUList& directAddressing() const;

		//- Return interpolated addressing
		FoamFiniteVolume_EXPORT virtual const labelListList& addressing() const;

		//- Return interpolaion weights
		FoamFiniteVolume_EXPORT virtual const scalarListList& weights() const;


		// Member Operators

		//- Disallow default bitwise assignment
		FoamFiniteVolume_EXPORT void operator=(const fvPatchMapper&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvPatchMapper_Header
