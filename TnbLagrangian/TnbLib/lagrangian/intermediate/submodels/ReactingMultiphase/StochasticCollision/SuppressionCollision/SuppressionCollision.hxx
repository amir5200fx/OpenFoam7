#pragma once
#ifndef _SuppressionCollision_Header
#define _SuppressionCollision_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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
	tnbLib::SuppressionCollision

Description
	Inter-cloud collision model, whereby the \c canReact flag can be used
	to inhibit devolatilisation and surface reactions

\*---------------------------------------------------------------------------*/

#include <StochasticCollisionModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamSuppressionCollision_EXPORT __declspec(dllexport)
#else
#ifdef FoamSuppressionCollision_EXPORT_DEFINE
#define FoamSuppressionCollision_EXPORT __declspec(dllexport)
#else
#define FoamSuppressionCollision_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						Class SuppressionCollision Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class SuppressionCollision
		:
		public StochasticCollisionModel<CloudType>
	{
	protected:

		// Protected data

			//- Name of cloud used for suppression
		const word suppressionCloud_;

		//- Suppressed parcel type - optional
		const label suppressedParcelType_;


		// Protected Member Functions

			 //- Update the model
		virtual void collide
		(
			typename CloudType::parcelType::trackingData& td,
			const scalar dt
		);


	public:

		//- Runtime type information
		//TypeName("suppressionCollision");
		static const char* typeName_() { return "suppressionCollision"; }
		static FoamSuppressionCollision_EXPORT const ::tnbLib::word typeName;
		static FoamSuppressionCollision_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		SuppressionCollision(const dictionary& dict, CloudType& owner);

		//- Construct copy
		SuppressionCollision(const SuppressionCollision<CloudType>& cm);

		//- Construct and return a clone
		virtual autoPtr<StochasticCollisionModel<CloudType>> clone() const
		{
			return autoPtr<StochasticCollisionModel<CloudType>>
				(
					new SuppressionCollision<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~SuppressionCollision();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <SuppressionCollisionI.hxx>

//#ifdef NoRepository
//#include <SuppressionCollision.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SuppressionCollision_Header
