#pragma once
#ifndef _findCellParticle_Header
#define _findCellParticle_Header

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
	tnbLib::findCellParticle

Description
	Particle class that finds cells by tracking

SourceFiles
	findCellParticle.C

\*---------------------------------------------------------------------------*/

#include <particle.hxx>
#include <autoPtr.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class findCellParticleCloud;


	// Forward declaration of friend functions and operators

	class findCellParticle;

	FoamFunctionObjects_EXPORT Ostream& operator<<(Ostream&, const findCellParticle&);


	/*---------------------------------------------------------------------------*\
						 Class findCellParticle Declaration
	\*---------------------------------------------------------------------------*/

	class findCellParticle
		:
		public particle
	{
		// Private Data

			//- Displacement over which to track
		vector displacement_;

		//- Passive data
		label data_;


	public:

		friend class Cloud<findCellParticle>;

		//- Class used to pass tracking data to the trackToFace function
		class trackingData
			:
			public particle::trackingData
		{
			labelListList& cellToData_;
			List<List<point>>& cellToEnd_;

		public:

			// Constructors

			trackingData
			(
				Cloud<findCellParticle>& cloud,
				labelListList& cellToData,
				List<List<point>>& cellToEnd
			)
				:
				particle::trackingData(cloud),
				cellToData_(cellToData),
				cellToEnd_(cellToEnd)
			{}


			// Member Functions

			labelListList& cellToData()
			{
				return cellToData_;
			}

			List<List<point>>& cellToEnd()
			{
				return cellToEnd_;
			}
		};


		// Constructors

			//- Construct from components
		FoamFunctionObjects_EXPORT findCellParticle
		(
			const polyMesh& mesh,
			const barycentric& coordinates,
			const label celli,
			const label tetFacei,
			const label tetPtI,
			const vector& displacement,
			const label data
		);

		//- Construct from a position and a cell, searching for the rest of the
		//  required topology
		FoamFunctionObjects_EXPORT findCellParticle
		(
			const polyMesh& mesh,
			const vector& position,
			const label celli,
			const vector& displacement,
			const label data
		);

		//- Construct from Istream
		FoamFunctionObjects_EXPORT findCellParticle
		(
			const polyMesh& mesh,
			Istream& is,
			bool readFields = true
		);

		//- Construct and return a clone
		autoPtr<particle> clone() const
		{
			return autoPtr<particle>(new findCellParticle(*this));
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

			autoPtr<findCellParticle> operator()(Istream& is) const
			{
				return autoPtr<findCellParticle>
					(
						new findCellParticle(mesh_, is, true)
						);
			}
		};


		// Member Functions

			//- Displacement over which to track
		const vector& displacement() const
		{
			return displacement_;
		}

		//- Displacement over which to track
		vector& displacement()
		{
			return displacement_;
		}

		//- Transported label
		label data() const
		{
			return data_;
		}

		//- Transported label
		label& data()
		{
			return data_;
		}


		// Tracking

			//- Track all particles to their end point
		FoamFunctionObjects_EXPORT bool move(Cloud<findCellParticle>&, trackingData&, const scalar);

		//- Overridable function to handle the particle hitting a patch
		//  Executed before other patch-hitting functions
		FoamFunctionObjects_EXPORT bool hitPatch(Cloud<findCellParticle>&, trackingData&);

		//- Overridable function to handle the particle hitting a wedge
		FoamFunctionObjects_EXPORT void hitWedgePatch(Cloud<findCellParticle>&, trackingData&);

		//- Overridable function to handle the particle hitting a
		//  symmetry plane
		FoamFunctionObjects_EXPORT void hitSymmetryPlanePatch(Cloud<findCellParticle>&, trackingData&);

		//- Overridable function to handle the particle hitting a
		//  symmetry patch
		FoamFunctionObjects_EXPORT void hitSymmetryPatch(Cloud<findCellParticle>&, trackingData&);

		//- Overridable function to handle the particle hitting a cyclic
		FoamFunctionObjects_EXPORT void hitCyclicPatch(Cloud<findCellParticle>&, trackingData&);

		//- Overridable function to handle the particle hitting a cyclicAMI
		FoamFunctionObjects_EXPORT void hitCyclicAMIPatch
		(
			const vector&,
			const scalar,
			Cloud<findCellParticle>&,
			trackingData&
		);

		//- Overridable function to handle the particle hitting a cyclicACMI
		FoamFunctionObjects_EXPORT void hitCyclicACMIPatch
		(
			const vector&,
			const scalar,
			Cloud<findCellParticle>&,
			trackingData&
		);

		//- Overridable function to handle the particle hitting a
		//cyclicRepeatAMI
		FoamFunctionObjects_EXPORT void hitCyclicRepeatAMIPatch
		(
			const vector&,
			const scalar,
			Cloud<findCellParticle>&,
			trackingData&
		);

		//- Overridable function to handle the particle hitting a
		//- processorPatch
		FoamFunctionObjects_EXPORT void hitProcessorPatch(Cloud<findCellParticle>&, trackingData&);

		//- Overridable function to handle the particle hitting a wallPatch
		FoamFunctionObjects_EXPORT void hitWallPatch(Cloud<findCellParticle>&, trackingData&);


		// Ostream Operator

		friend FoamFunctionObjects_EXPORT Ostream& operator<<(Ostream&, const findCellParticle&);
	};


	template<>
	inline bool contiguous<findCellParticle>()
	{
		return true;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_findCellParticle_Header
