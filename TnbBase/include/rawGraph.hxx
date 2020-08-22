#pragma once
#ifndef _rawGraph_Header
#define _rawGraph_Header

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
	tnbLib::rawGraph

Description
	A raw xy graph output

SourceFiles
	rawGraph.C

\*---------------------------------------------------------------------------*/

#include <graph.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class rawGraph Declaration
	\*---------------------------------------------------------------------------*/

	class rawGraph
		:
		public graph::writer
	{

	public:

		//- Runtime type information
		TypeName("raw");

		//- FileName extension  for this graph format
		static const word ext_;


		// Constructors

			//- Construct null
		rawGraph()
		{}


		//- Destructor
		~rawGraph()
		{}


		// Member Functions

			// Access

				//- Return the appropriate fileName extension
				//  for this graph format
		const word& ext() const
		{
			return ext_;
		}


		// Write

		void write(const graph&, Ostream& os) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_rawGraph_Header
