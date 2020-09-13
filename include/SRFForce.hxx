#pragma once
#ifndef _SRFForce_Header
#define _SRFForce_Header

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
	tnbLib::SRFForce

Description
	Calculates particle SRF reference frame force

SourceFiles
	SRFForce.C

\*---------------------------------------------------------------------------*/

#include <ParticleForce.hxx>
#include <SRFModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;

	/*---------------------------------------------------------------------------*\
						   Class SRFForce Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class SRFForce
		:
		public ParticleForce<CloudType>
	{
		// Private Data

			//- Pointer to the SRF model
		const typename SRF::SRFModel* srfPtr_;


	public:

		//- Runtime type information
		TypeName("SRF");


		// Constructors

			//- Construct from mesh
		SRFForce
		(
			CloudType& owner,
			const fvMesh& mesh,
			const dictionary& dict
		);

		//- Construct copy
		SRFForce(const SRFForce& srff);

		//- Construct and return a clone
		virtual autoPtr<ParticleForce<CloudType>> clone() const
		{
			return autoPtr<ParticleForce<CloudType>>
				(
					new ParticleForce<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~SRFForce();


		// Member Functions

			// Evaluation

				//- Cache fields
		virtual void cacheFields(const bool store);

		//- Calculate the non-coupled force
		virtual forceSuSp calcNonCoupled
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

#include <SRFForceI.hxx>

//#ifdef NoRepository
//#include <SRFForce.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SRFForce_Header
