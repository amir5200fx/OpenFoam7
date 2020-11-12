#pragma once
#ifndef _NoStochasticCollision_Header
#define _NoStochasticCollision_Header

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
	tnbLib::NoStochasticCollision

Description
	Dummy collision model for 'none'

\*---------------------------------------------------------------------------*/

#include <StochasticCollisionModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamNoStochasticCollision_EXPORT __declspec(dllexport)
#else
#ifdef FoamNoStochasticCollision_EXPORT_DEFINE
#define FoamNoStochasticCollision_EXPORT __declspec(dllexport)
#else
#define FoamNoStochasticCollision_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						Class NoStochasticCollision Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class NoStochasticCollision
		:
		public StochasticCollisionModel<CloudType>
	{
	protected:

		// Protected Member Functions

			//- Update the model
		virtual void collide
		(
			typename CloudType::parcelType::trackingData& td,
			const scalar dt
		);


	public:

		//- Runtime type information
		//TypeName("none");
		static const char* typeName_() { return "none"; }
		static FoamNoStochasticCollision_EXPORT const ::tnbLib::word typeName;
		static FoamNoStochasticCollision_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		NoStochasticCollision(const dictionary& dict, CloudType& owner);

		//- Construct copy
		NoStochasticCollision(const NoStochasticCollision<CloudType>& cm);

		//- Construct and return a clone
		virtual autoPtr<StochasticCollisionModel<CloudType>> clone() const
		{
			return autoPtr<StochasticCollisionModel<CloudType>>
				(
					new NoStochasticCollision<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~NoStochasticCollision();


		// Member Functions

			//- Flag to indicate whether model activates collision model
		virtual bool active() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <NoStochasticCollisionI.hxx>

//#ifdef NoRepository
//#include <NoStochasticCollision.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NoStochasticCollision_Header
