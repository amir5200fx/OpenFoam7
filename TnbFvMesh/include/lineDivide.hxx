#pragma once
#ifndef _lineDivide_Header
#define _lineDivide_Header

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
	tnbLib::lineDivide

Description
	Divides a line into segments

SourceFiles
	lineDivide.C

\*---------------------------------------------------------------------------*/

#include <pointField.hxx>
#include <scalarList.hxx>
#include <gradingDescriptors.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class blockEdge;

	/*---------------------------------------------------------------------------*\
							 Class lineDivide Declaration
	\*---------------------------------------------------------------------------*/

	class lineDivide
	{
		// Private Data

		pointField points_;

		scalarList divisions_;

	public:

		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT lineDivide
		(
			const blockEdge&,
			const label ndiv,
			const gradingDescriptors& gd = gradingDescriptors()
		);


		// Member Functions

			//- Return the points
		FoamFvMesh_EXPORT const pointField& points() const;

		//- Return the list of lambda values
		FoamFvMesh_EXPORT const scalarList& lambdaDivisions() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_lineDivide_Header
