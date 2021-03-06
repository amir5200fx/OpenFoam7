#pragma once
#ifndef _SphereDragForce_Header
#define _SphereDragForce_Header

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
	tnbLib::SphereDragForce

Description
	Drag model for spheres.

	Reference:
	\verbatim
		Amsden, A. A., Butler, T. D., & O'Rourke, P. J. (1987).
		The KIVA-II computer program for transient multidimensional chemically
		reactive flows with sprays
		SAE Technical Paper.
	\endverbatim

\*---------------------------------------------------------------------------*/

#include <ParticleForce.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamSphereDragForce_EXPORT __declspec(dllexport)
#else
#ifdef FoamSphereDragForce_EXPORT_DEFINE
#define FoamSphereDragForce_EXPORT __declspec(dllexport)
#else
#define FoamSphereDragForce_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class SphereDragForce Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class SphereDragForce
		:
		public ParticleForce<CloudType>
	{
	public:

		// Static Member Functions

			//- Drag coefficient multiplied by Reynolds number
		static scalar CdRe(const scalar Re);


		//- Runtime type information
		//TypeName("sphereDrag");
		static const char* typeName_() { return "sphereDrag"; }
		static FoamSphereDragForce_EXPORT const ::tnbLib::word typeName;
		static FoamSphereDragForce_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh
		SphereDragForce
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict
		);

		//- Construct copy
		SphereDragForce(const SphereDragForce<CloudType>& df);

		//- Construct and return a clone
		virtual autoPtr<ParticleForce<CloudType>> clone() const
		{
			return autoPtr<ParticleForce<CloudType>>
				(
					new SphereDragForce<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~SphereDragForce();


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

#include <SphereDragForceI.hxx>

//#ifdef NoRepository
//#include <SphereDragForce.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SphereDragForce_Header
