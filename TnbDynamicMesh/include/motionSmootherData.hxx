#pragma once
#ifndef _motionSmootherData_Header
#define _motionSmootherData_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::motionSmootherData

Description

SourceFiles
	motionSmootherData.C

\*---------------------------------------------------------------------------*/

#include <pointFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class motionSmootherData Declaration
	\*---------------------------------------------------------------------------*/

	class motionSmootherData
	{
	protected:

		// Private Data

			//- Displacement field
		pointVectorField displacement_;

		//- Scale factor for displacement
		pointScalarField scale_;

		//- Starting mesh position
		pointField oldPoints_;


	public:

		// Constructors

			//- Construct read
		FoamDynamicMesh_EXPORT motionSmootherData
		(
			const pointMesh&
		);

		//- Construct from pointDisplacement
		FoamDynamicMesh_EXPORT motionSmootherData
		(
			const pointVectorField&
		);


		// Member Functions

			//- Reference to displacement field
		FoamDynamicMesh_EXPORT pointVectorField& displacement();

		//- Reference to displacement field
		FoamDynamicMesh_EXPORT const pointVectorField& displacement() const;

		//- Reference to scale field
		FoamDynamicMesh_EXPORT const pointScalarField& scale() const;

		//- Starting mesh position
		FoamDynamicMesh_EXPORT const pointField& oldPoints() const;

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_motionSmootherData_Header
