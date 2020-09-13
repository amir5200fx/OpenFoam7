#pragma once
#ifndef _NoCollision_Header
#define _NoCollision_Header

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
	tnbLib::NoCollision

Description
	Place holder for 'none' option

SourceFiles
	NoCollision.C

\*---------------------------------------------------------------------------*/

#include <CollisionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class NoCollision Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class NoCollision
		:
		public CollisionModel<CloudType>
	{

	public:

		//- Runtime type information
		TypeName("none");


		// Constructors

			//- Construct from components
		NoCollision(const dictionary& dict, CloudType& owner);

		//- Construct copy
		NoCollision(const NoCollision<CloudType>& cm);

		//- Construct and return a clone
		virtual autoPtr<CollisionModel<CloudType>> clone() const
		{
			return autoPtr<CollisionModel<CloudType>>
				(
					new NoCollision<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~NoCollision();


		// Member Functions

			//- Return the number of times to subcycle the current
			//  timestep to meet the criteria of the collision model.  For
			//  this model this will always be 1.
		virtual label nSubCycles() const;

		//- Flag to indicate whether model activates collision model
		virtual bool active() const;

		// Collision function
		virtual void collide();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <NoCollisionI.hxx>

//#ifdef NoRepository
//#include <NoCollision.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NoCollision_Header
