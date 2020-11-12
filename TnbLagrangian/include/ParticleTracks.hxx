#pragma once
#ifndef _ParticleTracks_Header
#define _ParticleTracks_Header

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
	tnbLib::ParticleTracks

Description
	Records particle state (all variables) on each call to postFace

SourceFiles
	ParticleTracks.C

\*---------------------------------------------------------------------------*/

#include <CloudFunctionObject.hxx>

#include <Switch.hxx>  // added by amir
#include <HashTable.hxx>  // added by amir
#include <labelPair.hxx>  // added by amir
#include <CloudTemplate.hxx>  // added by amir

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamParticleTracks_EXPORT __declspec(dllexport)
#else
#ifdef FoamParticleTracks_EXPORT_DEFINE
#define FoamParticleTracks_EXPORT __declspec(dllexport)
#else
#define FoamParticleTracks_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class ParticleTracks Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class ParticleTracks
		:
		public CloudFunctionObject<CloudType>
	{
		// Private Data

			// Typedefs

				//- Convenience typedef for parcel type
		typedef typename CloudType::parcelType parcelType;

		//- Convenience typedef for hash hit-table
		typedef HashTable<label, labelPair, typename labelPair::Hash<>>
			hitTableType;

		//- Number of face-hit intervals between storing parcel data
		label trackInterval_;

		//- Maximum number of particles to store per track
		label maxSamples_;

		//- Flag to indicate whether data should be reset/cleared on writing
		Switch resetOnWrite_;

		//- Table of number of times a particle has hit a face
		hitTableType faceHitCounter_;

		//- Pointer to the cloud storage
		autoPtr<Cloud<parcelType>> cloudPtr_;


	protected:

		// Protected member functions

			//- Write post-processing info
		void write();


	public:

		//- Runtime type information
		//TypeName("particleTracks");
		static const char* typeName_() { return "particleTracks"; }
		static FoamParticleTracks_EXPORT const ::tnbLib::word typeName;
		static FoamParticleTracks_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		ParticleTracks
		(
			const dictionary& dict,
			CloudType& owner,
			const word& modelName
		);

		//- Construct copy
		ParticleTracks(const ParticleTracks<CloudType>& ppm);

		//- Construct and return a clone
		virtual autoPtr<CloudFunctionObject<CloudType>> clone() const
		{
			return autoPtr<CloudFunctionObject<CloudType>>
				(
					new ParticleTracks<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~ParticleTracks();


		// Member Functions

			// Access

				//- Return const access to the track interval
		inline label trackInterval() const;

		//- Return const access to the max samples
		inline label maxSamples() const;

		//- Return const access to the reset on write flag
		inline const Switch& resetOnWrite() const;

		//- Return the table of number of times a particle has hit a face
		inline const hitTableType& faceHitCounter() const;

		//- Return const access to the cloud
		inline const Cloud<parcelType>& cloud() const;


		// Evaluation

			//- Pre-evolve hook
		virtual void preEvolve();

		//- Post-face hook
		virtual void postFace(const parcelType& p, bool& keepParticle);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <ParticleTracksI.hxx>
#include <ParticleTracks_Imp.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include <ParticleTracks.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ParticleTracks_Header
