#pragma once
#ifndef _splineEdge_Header
#define _splineEdge_Header

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
	tnbLib::blockEdges::splineEdge

Description
	A blockEdge interface for Catmull-Rom splines.

SourceFiles
	splineEdge.C

\*---------------------------------------------------------------------------*/

#include <blockEdge.hxx>
#include <CatmullRomSpline.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blockEdges
	{

		/*---------------------------------------------------------------------------*\
							  Class splineEdge Declaration
		\*---------------------------------------------------------------------------*/

		class splineEdge
			:
			public blockEdge,
			public CatmullRomSpline
		{
		public:

			//- Runtime type information
			//TypeName("spline");
			static const char* typeName_() { return "spline"; }
			static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
			static FoamFvMesh_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvMesh_EXPORT splineEdge
			(
				const pointField&,
				const label start,
				const label end,
				const pointField& internalPoints
			);

			//- Construct from Istream, setting pointsList
			FoamFvMesh_EXPORT splineEdge
			(
				const dictionary& dict,
				const label index,
				const searchableSurfaces& geometry,
				const pointField&,
				Istream&
			);

			//- Disallow default bitwise copy construction
			FoamFvMesh_EXPORT splineEdge(const splineEdge&) = delete;


			//- Destructor
			FoamFvMesh_EXPORT virtual ~splineEdge();


			// Member Functions

				//- Return the point position corresponding to the curve parameter
				//  0 <= lambda <= 1
			FoamFvMesh_EXPORT virtual point position(const scalar) const;

			//- Return the length of the spline curve (not implemented)
			FoamFvMesh_EXPORT virtual scalar length() const;


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFvMesh_EXPORT void operator=(const splineEdge&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End of namespace blockEdges
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_splineEdge_Header
