#pragma once
#ifndef _SchillerNaumannDragForce_Header
#define _SchillerNaumannDragForce_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2019 OpenFOAM Foundation
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
	tnbLib::SchillerNaumannDragForce

Description
	Schiller-Naumann drag model for spheres.

	Reference:
	\verbatim
		Naumann, Z., & Schiller, L. (1935).
		A drag coefficient correlation.
		Z Ver Deutsch Ing, 77, 318-323.
	\endverbatim

\*---------------------------------------------------------------------------*/

#include <ParticleForce.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamSchillerNaumannDragForce_EXPORT __declspec(dllexport)
#else
#ifdef FoamSchillerNaumannDragForce_EXPORT_DEFINE
#define FoamSchillerNaumannDragForce_EXPORT __declspec(dllexport)
#else
#define FoamSchillerNaumannDragForce_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class SchillerNaumannDragForce Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class SchillerNaumannDragForce
		:
		public ParticleForce<CloudType>
	{
	public:

		// Static Member Functions

			//- Drag coefficient multiplied by Reynolds number
		static scalar CdRe(const scalar Re);


		//- Runtime type information
		//TypeName("SchillerNaumannDrag");
		static const char* typeName_() { return "SchillerNaumannDrag"; }
		static FoamSchillerNaumannDragForce_EXPORT const ::tnbLib::word typeName;
		static FoamSchillerNaumannDragForce_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh
		SchillerNaumannDragForce
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict
		);

		//- Construct copy
		SchillerNaumannDragForce(const SchillerNaumannDragForce<CloudType>& df);

		//- Construct and return a clone
		virtual autoPtr<ParticleForce<CloudType>> clone() const
		{
			return autoPtr<ParticleForce<CloudType>>
				(
					new SchillerNaumannDragForce<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~SchillerNaumannDragForce();


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

#include <SchillerNaumannDragForceI.hxx>

//#ifdef NoRepository
//#include <SchillerNaumannDragForce.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SchillerNaumannDragForce_Header
