#pragma once
#ifndef _NoInteractionTemplate_Header
#define _NoInteractionTemplate_Header

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
	tnbLib::NoInteraction

Description
	Dummy class for 'none' option - will raise an error if any functions are
	called that require return values.

\*---------------------------------------------------------------------------*/

#include <PatchInteractionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						   Class NoInteraction Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class NoInteraction
		:
		public PatchInteractionModel<CloudType>
	{
	public:

		//- Runtime type information
		TypeName("none");


		// Constructors

			//- Construct from dictionary
		NoInteraction(const dictionary& dict, CloudType& cloud);

		//- Construct copy
		NoInteraction(const NoInteraction<CloudType>& pim);

		//- Construct and return a clone
		virtual autoPtr<PatchInteractionModel<CloudType>> clone() const
		{
			return autoPtr<PatchInteractionModel<CloudType>>
				(
					new NoInteraction<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~NoInteraction();


		// Member Functions

			//- Flag to indicate whether model activates patch interaction model
		virtual bool active() const;

		//- Apply velocity correction
		//  Returns true if particle remains in same cell
		virtual bool correct
		(
			typename CloudType::parcelType& p,
			const polyPatch& pp,
			bool& keepParticle
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <NoInteractionTemplate.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NoInteractionTemplate_Header
