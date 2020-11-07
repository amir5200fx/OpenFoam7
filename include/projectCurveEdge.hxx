#pragma once
#ifndef _projectCurveEdge_Header
#define _projectCurveEdge_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::projectCurveEdge

Description
	Defines the edge from the projection onto a surface (single surface)
	or intersection of two surfaces.

SourceFiles
	projectCurveEdge.C

\*---------------------------------------------------------------------------*/

#include <blockEdge.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class pointConstraint;

	/*---------------------------------------------------------------------------*\
						  Class projectCurveEdge Declaration
	\*---------------------------------------------------------------------------*/

	class projectCurveEdge
		:
		public blockEdge
	{
		// Private Data

		const searchableSurfaces& geometry_;

		//- The indices of surfaces onto which the points are projected
		labelList surfaces_;


	public:

		//- Runtime type information
		//TypeName("projectCurve");
		static const char* typeName_() { return "projectCurve"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from Istream setting pointsList
		FoamFvMesh_EXPORT projectCurveEdge
		(
			const dictionary& dict,
			const label index,
			const searchableSurfaces& geometry,
			const pointField& points,
			Istream&
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT projectCurveEdge(const projectCurveEdge&) = delete;


		//- Destructor
		virtual ~projectCurveEdge()
		{}


		// Member Functions

			//- Return the point positions corresponding to the curve parameters
			//  0 <= lambda <= 1
		FoamFvMesh_EXPORT virtual point position(const scalar) const
		{
			NotImplemented;
			return point::max;
		}

		//- Return the point positions corresponding to the curve parameters
		//  0 <= lambda <= 1
		FoamFvMesh_EXPORT virtual tmp<pointField> position(const scalarList&) const;

		//- Return the length of the curve
		virtual scalar length() const
		{
			NotImplemented;
			return 1;
		}


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const projectCurveEdge&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_projectCurveEdge_Header
