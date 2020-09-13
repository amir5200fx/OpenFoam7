#pragma once
#ifndef _ErgunWenYuDragForce_Header
#define _ErgunWenYuDragForce_Header

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
	tnbLib::ErgunWenYuDragForce

Description
	Ergun-Wen-Yu drag model for solid spheres.

	Reference:
	\verbatim
		Gidaspow, D. (1994).
		Multiphase flow and fluidization: continuum and kinetic theory
		descriptions.
		Academic press.
	\endverbatim

\*---------------------------------------------------------------------------*/

#include <WenYuDragForce.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class ErgunWenYuDragForce Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class ErgunWenYuDragForce
		:
		public WenYuDragForce<CloudType>
	{
	public:

		//- Runtime type information
		TypeName("ErgunWenYuDrag");


		// Constructors

			//- Construct from mesh
		ErgunWenYuDragForce
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict
		);

		//- Construct copy
		ErgunWenYuDragForce(const ErgunWenYuDragForce<CloudType>& df);

		//- Construct and return a clone
		virtual autoPtr<ParticleForce<CloudType>> clone() const
		{
			return autoPtr<ParticleForce<CloudType>>
				(
					new ErgunWenYuDragForce<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~ErgunWenYuDragForce();


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

#include <ErgunWenYuDragForceI.hxx>

//#ifdef NoRepository
//#include <ErgunWenYuDragForce.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ErgunWenYuDragForce_Header
