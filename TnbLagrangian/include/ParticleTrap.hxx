#pragma once
#ifndef _ParticleTrap_Header
#define _ParticleTrap_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2018 OpenFOAM Foundation
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
	tnbLib::ParticleTrap

Description
	Traps particles within a given phase fraction for multi-phase cases.

	Model is activated using:
	\verbatim
	particleTrap1
	{
		type        particleTrap;
		alpha       alpha;      // name of the volume fraction field
		threshold   0.95;       // alpha value below which model is active
	}
	\endverbatim


SourceFiles
	ParticleTrap.C

\*---------------------------------------------------------------------------*/

#include <CloudFunctionObject.hxx>
#include <volFields.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamParticleTrap_EXPORT __declspec(dllexport)
#else
#ifdef FoamParticleTrap_EXPORT_DEFINE
#define FoamParticleTrap_EXPORT __declspec(dllexport)
#else
#define FoamParticleTrap_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class ParticleTrap Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class ParticleTrap
		:
		public CloudFunctionObject<CloudType>
	{
		// Private Data

			// Typedefs

				//- Convenience typedef for parcel type
		typedef typename CloudType::parcelType parcelType;


		//- Name of vol fraction field
		const word alphaName_;

		//- Pointer to the volume fraction field
		const volScalarField* alphaPtr_;

		//- Gradient of the volume fraction field
		autoPtr<volVectorField> gradAlphaPtr_;

		//- Threshold beyond which model is active
		scalar threshold_;


	public:

		//- Runtime type information
		//TypeName("particleTrap");
		static const char* typeName_() { return "particleTrap"; }
		static FoamParticleTrap_EXPORT const ::tnbLib::word typeName;
		static FoamParticleTrap_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		ParticleTrap
		(
			const dictionary& dict,
			CloudType& owner,
			const word& modelName
		);

		//- Construct copy
		ParticleTrap(const ParticleTrap<CloudType>& pe);

		//- Construct and return a clone
		virtual autoPtr<CloudFunctionObject<CloudType>> clone() const
		{
			return autoPtr<CloudFunctionObject<CloudType>>
				(
					new ParticleTrap<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~ParticleTrap();


		// Member Functions

			// Evaluation

				//- Pre-evolve hook
		virtual void preEvolve();

		//- Post-evolve hook
		virtual void postEvolve();

		//- Post-move hook
		virtual void postMove
		(
			typename CloudType::parcelType& p,
			const scalar dt,
			const point& position0,
			bool& keepParticle
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <ParticleTrapI.hxx>

//#ifdef NoRepository
//#include <ParticleTrap.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ParticleTrap_Header
