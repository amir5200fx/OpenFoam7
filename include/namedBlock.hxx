#pragma once
#ifndef _namedBlock_Header
#define _namedBlock_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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
	tnbLib::blocks::namedBlock

Description
	Gives name to a block.

SourceFiles
	namedBlock.C

\*---------------------------------------------------------------------------*/

#include <block.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blocks
	{

		/*---------------------------------------------------------------------------*\
								   Class namedBlock Declaration
		\*---------------------------------------------------------------------------*/

		class namedBlock
			:
			public word,
			public block
		{
		public:

			//- Runtime type information
			TypeName("name");


			// Constructors

				//- Construct from Istream setting pointsList
			namedBlock
			(
				const dictionary& dict,
				const label index,
				const pointField& vertices,
				const blockEdgeList& edges,
				const blockFaceList& faces,
				Istream& is
			);


			//- Destructor
			virtual ~namedBlock()
			{}
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace blocks
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_namedBlock_Header
