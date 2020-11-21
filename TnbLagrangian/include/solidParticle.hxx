#pragma once
#ifndef _solidParticle_Header
#define _solidParticle_Header

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
	tnbLib::solidParticle

Description
	Simple solid spherical particle class with one-way coupling with the
	continuous phase.

SourceFiles
	solidParticleI.H
	solidParticle.C
	solidParticleIO.C

\*---------------------------------------------------------------------------*/

#include <particle.hxx>
#include <IOstream.hxx>
#include <autoPtr.hxx>
#include <interpolationCellPoint.hxx>
#include <contiguous.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class solidParticleCloud;


	// Forward declaration of friend functions and operators

	class solidParticle;

	FoamLagrangian_EXPORT Ostream& operator<<(Ostream&, const solidParticle&);


	/*---------------------------------------------------------------------------*\
							   Class solidParticle Declaration
	\*---------------------------------------------------------------------------*/

	class solidParticle
		:
		public particle
	{
		// Private Data

			//- Size in bytes of the fields
		static FoamLagrangian_EXPORT const std::size_t sizeofFields_;

		//- Diameter
		scalar d_;

		//- Velocity of parcel
		vector U_;


	public:

		friend class Cloud<solidParticle>;

		//- Class used to pass tracking data to the trackToFace function
		class trackingData
			:
			public particle::trackingData
		{
			// Interpolators for continuous phase fields

			const interpolationCellPoint<scalar>& rhoInterp_;
			const interpolationCellPoint<vector>& UInterp_;
			const interpolationCellPoint<scalar>& nuInterp_;

			//- Local gravitational or other body-force acceleration
			const vector& g_;


		public:

			// Constructors

			inline trackingData
			(
				const solidParticleCloud& spc,
				const interpolationCellPoint<scalar>& rhoInterp,
				const interpolationCellPoint<vector>& UInterp,
				const interpolationCellPoint<scalar>& nuInterp,
				const vector& g
			);


			// Member Functions

			inline const interpolationCellPoint<scalar>& rhoInterp() const;

			inline const interpolationCellPoint<vector>& UInterp() const;

			inline const interpolationCellPoint<scalar>& nuInterp() const;

			inline const vector& g() const;
		};


		// Constructors

			//- Construct from components
		inline solidParticle
		(
			const polyMesh& mesh,
			const barycentric& coordinates,
			const label celli,
			const label tetFacei,
			const label tetPti,
			const scalar d,
			const vector& U
		);

		//- Construct from Istream
		FoamLagrangian_EXPORT solidParticle
		(
			const polyMesh& mesh,
			Istream& is,
			bool readFields = true
		);

		//- Construct and return a clone
		virtual autoPtr<particle> clone() const
		{
			return autoPtr<particle>(new solidParticle(*this));
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

			autoPtr<solidParticle> operator()(Istream& is) const
			{
				return autoPtr<solidParticle>
					(
						new solidParticle(mesh_, is, true)
						);
			}
		};


		// Member Functions

			// Access

				//- Return diameter
		inline scalar d() const;

		//- Return velocity
		inline const vector& U() const;


		// Tracking

			//- Move
		FoamLagrangian_EXPORT bool move(solidParticleCloud&, trackingData&, const scalar);


		// Patch interactions

			//- Overridable function to handle the particle hitting a patch
			//  Executed before other patch-hitting functions
		FoamLagrangian_EXPORT bool hitPatch(solidParticleCloud& cloud, trackingData& td);

		//- Overridable function to handle the particle hitting a
		//  processorPatch
		FoamLagrangian_EXPORT void hitProcessorPatch(solidParticleCloud& cloud, trackingData& td);

		//- Overridable function to handle the particle hitting a wallPatch
		FoamLagrangian_EXPORT void hitWallPatch(solidParticleCloud& cloud, trackingData& td);

		//- Transform the physical properties of the particle
		//  according to the given transformation tensor
		FoamLagrangian_EXPORT virtual void transformProperties(const tensor& T);

		//- Transform the physical properties of the particle
		//  according to the given separation vector
		FoamLagrangian_EXPORT virtual void transformProperties(const vector& separation);


		// I-O

		static FoamLagrangian_EXPORT void readFields(Cloud<solidParticle>& c);

		static FoamLagrangian_EXPORT void writeFields(const Cloud<solidParticle>& c);


		// Ostream Operator

		friend FoamLagrangian_EXPORT Ostream& operator<<(Ostream&, const solidParticle&);
	};


	template<>
	inline bool contiguous<solidParticle>()
	{
		return true;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <solidParticleI.hxx>

#endif // !_solidParticle_Header
