#pragma once
#ifndef _algebraicPairGAMGAgglomeration_Header
#define _algebraicPairGAMGAgglomeration_Header

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
	tnbLib::algebraicPairGAMGAgglomeration

Description
	Agglomerate using the pair algorithm.

SourceFiles
	algebraicPairGAMGAgglomeration.C

\*---------------------------------------------------------------------------*/

#include <pairGAMGAgglomeration.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class algebraicPairGAMGAgglomeration Declaration
	\*---------------------------------------------------------------------------*/

	class algebraicPairGAMGAgglomeration
		:
		public pairGAMGAgglomeration
	{

	public:

		//- Runtime type information
		TypeName("algebraicPair");


		// Constructors

			//- Construct given mesh and controls
		algebraicPairGAMGAgglomeration
		(
			const lduMatrix& matrix,
			const dictionary& controlDict
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_algebraicPairGAMGAgglomeration_Header
