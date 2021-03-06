#pragma once
#ifndef _pointPatchFieldMapperPatchRef_Header
#define _pointPatchFieldMapperPatchRef_Header

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
	tnbLib::pointPatchFieldMapperPatchRef

Description
	tnbLib::pointPatchFieldMapperPatchRef

\*---------------------------------------------------------------------------*/

#include <pointPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class pointPatch; // added by amir

	/*---------------------------------------------------------------------------*\
					 Class pointPatchFieldMapperPatchRef Declaration
	\*---------------------------------------------------------------------------*/

	class pointPatchFieldMapperPatchRef
		:
		public generalPointPatchFieldMapper
	{
		// Private Data

		const pointPatch& sourcePatch_;
		const pointPatch& targetPatch_;


	public:

		// Constructors

			//- Construct from components
		pointPatchFieldMapperPatchRef
		(
			const pointPatch& source,
			const pointPatch& target
		)
			:
			sourcePatch_(source),
			targetPatch_(target)
		{}

		//- Disallow default bitwise copy construction
		pointPatchFieldMapperPatchRef
		(
			const pointPatchFieldMapperPatchRef&
		) = delete;


		// Member Functions

		const pointPatch& sourcePatch() const
		{
			return sourcePatch_;
		}

		const pointPatch& targetPatch() const
		{
			return targetPatch_;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const pointPatchFieldMapperPatchRef&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pointPatchFieldMapperPatchRef_Header
