#pragma once
#ifndef _lineEdge_Header
#define _lineEdge_Header

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
	tnbLib::blockEdges::lineEdge

Description
	A straight edge between the start point and the end point.

SourceFiles
	lineEdge.C

\*---------------------------------------------------------------------------*/

#include <blockEdge.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blockEdges
	{

		/*---------------------------------------------------------------------------*\
								  Class lineEdge Declaration
		\*---------------------------------------------------------------------------*/


		class lineEdge
			:
			public blockEdge
		{

		public:

			//- Runtime type information
			//TypeName("line");
			static const char* typeName_() { return "line"; }
			static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
			static FoamFvMesh_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvMesh_EXPORT lineEdge(const pointField&, const label start, const label end);

			//- Construct from Istream with a pointField
			FoamFvMesh_EXPORT lineEdge
			(
				const dictionary& dict,
				const label index,
				const searchableSurfaces& geometry,
				const pointField&,
				Istream&
			);


			//- Destructor
			FoamFvMesh_EXPORT virtual ~lineEdge();


			// Member Functions

				//- Return the point position corresponding to the curve parameter
				//  0 <= lambda <= 1
			FoamFvMesh_EXPORT point position(const scalar) const;

			//- Return the length of the curve
			FoamFvMesh_EXPORT scalar length() const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End of namespace blockEdges
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_lineEdge_Header
