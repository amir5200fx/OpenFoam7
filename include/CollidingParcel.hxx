#pragma once
#ifndef _CollidingParcel_Header
#define _CollidingParcel_Header

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
	tnbLib::CollidingParcel

Description
	Wrapper around kinematic parcel types to add collision modelling

SourceFiles
	CollidingParcelI.H
	CollidingParcel.C
	CollidingParcelIO.C

\*---------------------------------------------------------------------------*/

#include <particle.hxx>
#include <CollisionRecordList.hxx>
#include <labelFieldIOField.hxx>
#include <vectorFieldIOField.hxx>

#include <demandDrivenEntry.hxx>  // added by amir

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamCollidingParcel_EXPORT __declspec(dllexport)
#else
#ifdef FoamCollidingParcel_EXPORT_DEFINE
#define FoamCollidingParcel_EXPORT __declspec(dllexport)
#else
#define FoamCollidingParcel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	typedef CollisionRecordList<vector, vector> collisionRecordList;
	typedef vectorFieldCompactIOField pairDataFieldCompactIOField;
	typedef vectorFieldCompactIOField wallDataFieldCompactIOField;

	template<class ParcelType>
	class CollidingParcel;

	// Forward declaration of friend functions

	template<class ParcelType>
	Ostream& operator<<
		(
			Ostream&,
			const CollidingParcel<ParcelType>&
			);

	/*---------------------------------------------------------------------------*\
						   Class CollidingParcel Declaration
	\*---------------------------------------------------------------------------*/

	template<class ParcelType>
	class CollidingParcel
		:
		public ParcelType
	{
		// Private member data

			//- Size in bytes of the fields
		static const std::size_t sizeofFields_;


	public:

		//- Class to hold thermo particle constant properties
		class constantProperties
			:
			public ParcelType::constantProperties
		{

			// Private Data

				//- Young's modulus [N/m^2]
			demandDrivenEntry<scalar> youngsModulus_;

			//- Poisson's ratio
			demandDrivenEntry<scalar> poissonsRatio_;


		public:

			// Constructors

				//- Null constructor
			constantProperties();

			//- Copy constructor
			constantProperties(const constantProperties& cp);

			//- Construct from dictionary
			constantProperties(const dictionary& parentDict);


			// Member Functions

				//- Return const access to Young's Modulus
			inline scalar youngsModulus() const;

			//- Return const access to Poisson's ratio
			inline scalar poissonsRatio() const;
		};


		//- Use base tracking data
		typedef typename ParcelType::trackingData trackingData;


	protected:

		// Protected data

			//- Force on particle due to collisions [N]
		vector f_;

		//- Angular momentum of Parcel in global reference frame [kg m2/s]
		vector angularMomentum_;

		//- Torque on particle due to collisions in global
		//  reference frame [Nm]
		vector torque_;

		//- Particle collision records
		collisionRecordList collisionRecords_;


	public:

		// Static Data Members

			//- Runtime type information
		//TypeName("CollidingParcel");
		static const char* typeName_() { return "CollidingParcel"; }
		static FoamCollidingParcel_EXPORT const ::tnbLib::word typeName;
		static FoamCollidingParcel_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- String representation of properties
		/*AddToPropertyList
		(
			ParcelType,
			" (fx fy fz)"
			+ " (angularMomentumx angularMomentumy angularMomentumz)"
			+ " (torquex torquey torquez)"
			+ " collisionRecordsPairAccessed"
			+ " collisionRecordsPairOrigProcOfOther"
			+ " collisionRecordsPairOrigIdOfOther"
			+ " (collisionRecordsPairData)"
			+ " collisionRecordsWallAccessed"
			+ " collisionRecordsWallPRel"
			+ " (collisionRecordsWallData)"
		);*/
		
		static string propertyList_;

		static string propertyList()
		{
			return ParcelType::propertyList() + " (fx fy fz)" + " (angularMomentumx angularMomentumy angularMomentumz)"
				+ " (torquex torquey torquez)" + " collisionRecordsPairAccessed" +
				" collisionRecordsPairOrigProcOfOther" + " collisionRecordsPairOrigIdOfOther" +
				" (collisionRecordsPairData)" + " collisionRecordsWallAccessed" + " collisionRecordsWallPRel" +
				" (collisionRecordsWallData)";
		};


		// Constructors

			//- Construct from mesh, coordinates and topology
			//  Other properties initialised as null
		inline CollidingParcel
		(
			const polyMesh& mesh,
			const barycentric& coordinates,
			const label celli,
			const label tetFacei,
			const label tetPti
		);

		//- Construct from a position and a cell, searching for the rest of the
		//  required topology. Other properties are initialised as null.
		inline CollidingParcel
		(
			const polyMesh& mesh,
			const vector& position,
			const label celli
		);

		//- Construct from components
		inline CollidingParcel
		(
			const polyMesh& mesh,
			const barycentric& coordinates,
			const label celli,
			const label tetFacei,
			const label tetPti,
			const label typeId,
			const scalar nParticle0,
			const scalar d0,
			const scalar dTarget0,
			const vector& U0,
			const vector& f0,
			const vector& angularMomentum0,
			const vector& torque0,
			const typename ParcelType::constantProperties& constProps
		);

		//- Construct from Istream
		CollidingParcel
		(
			const polyMesh& mesh,
			Istream& is,
			bool readFields = true
		);

		//- Construct as a copy
		CollidingParcel(const CollidingParcel& p);

		//- Construct as a copy
		CollidingParcel(const CollidingParcel& p, const polyMesh& mesh);

		//- Construct and return a (basic particle) clone
		virtual autoPtr<particle> clone() const
		{
			return autoPtr<particle>(new CollidingParcel(*this));
		}

		//- Construct and return a (basic particle) clone
		virtual autoPtr<particle> clone(const polyMesh& mesh) const
		{
			return autoPtr<particle>(new CollidingParcel(*this, mesh));
		}

		//- Factory class to read-construct particles used for
		//  parallel transfer
		class iNew
		{
			const polyMesh& mesh_;

		public:

			iNew(const polyMesh& mesh)
				:
				mesh_(mesh)
			{}

			autoPtr<CollidingParcel<ParcelType>> operator()(Istream& is) const
			{
				return autoPtr<CollidingParcel<ParcelType>>
					(
						new CollidingParcel<ParcelType>(mesh_, is, true)
						);
			}
		};


		// Member Functions

			// Access

				//- Return const access to force
		inline const vector& f() const;

		//- Return const access to angular momentum
		inline const vector& angularMomentum() const;

		//- Return const access to torque
		inline const vector& torque() const;

		//- Return const access to the collision records
		inline const collisionRecordList& collisionRecords() const;

		//- Return access to force
		inline vector& f();

		//- Return access to angular momentum
		inline vector& angularMomentum();

		//- Return access to torque
		inline vector& torque();

		//- Return access to collision records
		inline collisionRecordList& collisionRecords();

		//- Particle angular velocity
		inline vector omega() const;


		// Tracking

			//- Move the parcel
		template<class TrackCloudType>
		bool move
		(
			TrackCloudType& cloud,
			trackingData& td,
			const scalar trackTime
		);

		//- Transform the physical properties of the particle
		//  according to the given transformation tensor
		virtual void transformProperties(const tensor& T);

		//- Transform the physical properties of the particle
		//  according to the given separation vector
		virtual void transformProperties(const vector& separation);


		// I-O

			 //- Read
		template<class CloudType>
		static void readFields(CloudType& c);

		//- Write
		template<class CloudType>
		static void writeFields(const CloudType& c);


		// Ostream Operator

		friend Ostream& operator<< <ParcelType>
			(
				Ostream&,
				const CollidingParcel<ParcelType>&
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <CollidingParcelI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
//#include <CollidingParcel.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CollidingParcel_Header
