#pragma once
#ifndef _cylindricalCS_Header
#define _cylindricalCS_Header

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
	tnbLib::cylindricalCS

Description
	Cylindrical coordinate system

SourceFiles
	cylindricalCS.C

\*---------------------------------------------------------------------------*/

#include <coordinateSystem.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class cylindricalCS Declaration
	\*---------------------------------------------------------------------------*/

	class cylindricalCS
		:
		public coordinateSystem
	{
		// Private Data members

			//- Are angles in degrees? (default = true)
		bool inDegrees_;


	protected:

		// Protected Member Functions


			//- Convert from local coordinate system to the global Cartesian system
			//  with optional translation for the origin
		FoamFvMesh_EXPORT virtual vector localToGlobal(const vector&, bool translate) const;

		//- Convert from local coordinate system to the global Cartesian system
		//  with optional translation for the origin
		FoamFvMesh_EXPORT virtual tmp<vectorField> localToGlobal
		(
			const vectorField&,
			bool translate
		) const;

		//- Convert from global Cartesian system to the local coordinate system
		//  with optional translation for the origin
		FoamFvMesh_EXPORT virtual vector globalToLocal(const vector&, bool translate) const;

		//- Convert from global Cartesian system to the local coordinate system
		//  with optional translation for the origin
		FoamFvMesh_EXPORT virtual tmp<vectorField> globalToLocal
		(
			const vectorField&,
			bool translate
		) const;


	public:


		// Constructors

			//- Construct null
		FoamFvMesh_EXPORT cylindricalCS(const bool inDegrees = true);

		//- Construct copy
		FoamFvMesh_EXPORT cylindricalCS
		(
			const coordinateSystem&,
			const bool inDegrees = true
		);

		//- Construct copy with a different name
		FoamFvMesh_EXPORT cylindricalCS
		(
			const word& name,
			const coordinateSystem&,
			const bool inDegrees = true
		);

		//- Construct from origin and rotation
		FoamFvMesh_EXPORT cylindricalCS
		(
			const word& name,
			const point& origin,
			const coordinateRotation&,
			const bool inDegrees = true
		);

		//- Construct from origin and 2 axes
		FoamFvMesh_EXPORT cylindricalCS
		(
			const word& name,
			const point& origin,
			const vector& axis,
			const vector& dirn,
			const bool inDegrees = true
		);

		//- Construct from dictionary and name
		FoamFvMesh_EXPORT cylindricalCS(const word&, const dictionary&);

		//- Construct from dictionary and objectRegistry
		FoamFvMesh_EXPORT cylindricalCS(const objectRegistry&, const dictionary&);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~cylindricalCS();


		// Member Functions

			//- Are angles in degrees?
		FoamFvMesh_EXPORT bool  inDegrees() const;

		//- Non-const access to inDegrees
		FoamFvMesh_EXPORT bool& inDegrees();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cylindricalCS_Header
