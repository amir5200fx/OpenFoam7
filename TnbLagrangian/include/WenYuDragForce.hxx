#pragma once
#ifndef _WenYuDragForce_Header
#define _WenYuDragForce_Header

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
	tnbLib::WenYuDragForce

Description
	Wen-Yu drag model for spheres.

	Reference:
	\verbatim
		Gidaspow, D. (1994).
		Multiphase flow and fluidization: continuum and kinetic theory
		descriptions.
		Academic press.
	\endverbatim

\*---------------------------------------------------------------------------*/

#include <DenseDragForce.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamWenYuDragForce_EXPORT __declspec(dllexport)
#else
#ifdef FoamWenYuDragForce_EXPORT_DEFINE
#define FoamWenYuDragForce_EXPORT __declspec(dllexport)
#else
#define FoamWenYuDragForce_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class WenYuDragForce Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class WenYuDragForce
		:
		public DenseDragForce<CloudType>
	{
	public:

		//- Runtime type information
		//TypeName("WenYuDrag");
		static const char* typeName_() { return "WenYuDrag"; }
		static FoamWenYuDragForce_EXPORT const ::tnbLib::word typeName;
		static FoamWenYuDragForce_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh
		WenYuDragForce
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict
		);

		//- Construct from mesh
		WenYuDragForce
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict,
			const word& typeName
		);

		//- Construct copy
		WenYuDragForce(const WenYuDragForce<CloudType>& df);

		//- Construct and return a clone
		virtual autoPtr<ParticleForce<CloudType>> clone() const
		{
			return autoPtr<ParticleForce<CloudType>>
				(
					new WenYuDragForce<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~WenYuDragForce();


		// Member Functions

			// Evaluation

				//- Calculate the coupled force
		virtual forceSuSp calcCoupled
		(
			const typename CloudType::parcelType& p,
			const typename CloudType::parcelType::trackingData& td,
			const scalar dt,
			const scalar mass,
			const scalar Re,
			const scalar muc
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <WenYuDragForceI.hxx>

//#ifdef NoRepository
//#include <WenYuDragForce.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_WenYuDragForce_Header
