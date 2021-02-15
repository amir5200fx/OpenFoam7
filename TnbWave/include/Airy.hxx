#pragma once
#ifndef _Airy_Header
#define _Airy_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::waveModels::Airy

Description
	First-order wave model.

	Reference:
	\verbatim
		Stokes, G.G. (1847)
		On the theory of oscillatory waves.
		Transactions of the Cambridge Philosophical Society, 8, 441.
	\endverbatim

	See the leading terms of equations 18 and 19.

SourceFiles
	Airy.C

\*---------------------------------------------------------------------------*/

#include <waveModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace waveModels
	{

		/*---------------------------------------------------------------------------*\
								   Class Airy Declaration
		\*---------------------------------------------------------------------------*/

		class Airy
			:
			public waveModel
		{
			// Private Data

				//- Peak-to-peak length [m]
			const scalar length_;

			//- Phase offset [rad]
			const scalar phase_;

			//- Depth [m]
			const scalar depth_;


		protected:

			// Protected Member Functions

				//- The angular wavenumber [rad/m]
			FoamWave_EXPORT scalar k() const;

			//- The wave celerity [m/s]
			FoamWave_EXPORT scalar celerity() const;

			//- Angle of the oscillation [rad]
			FoamWave_EXPORT tmp<scalarField> angle
			(
				const scalar t,
				const scalarField& x
			) const;

			//- Return whether shallow and intermdiate effects are to be omitted
			FoamWave_EXPORT bool deep() const;

			//- Return the non-dimensionalised i-th harmonic of the velocity
			FoamWave_EXPORT tmp<vector2DField> vi
			(
				const label i,
				const scalar t,
				const vector2DField& xz
			) const;


		public:
			
			//- Runtime type information
			//TypeName("Airy");
			static const char* typeName_() { return "Airy"; }

			static FoamWave_EXPORT const ::tnbLib::word typeName;
			static FoamWave_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct a copy
			FoamWave_EXPORT Airy(const Airy& wave);

			//- Construct from a database and a dictionary
			FoamWave_EXPORT Airy(const objectRegistry& db, const dictionary& dict);

			//- Construct a clone
			virtual autoPtr<waveModel> clone() const
			{
				return autoPtr<waveModel>(new Airy(*this));
			}


			//- Destructor
			FoamWave_EXPORT virtual ~Airy();


			// Member Functions

				// Access

					//- Get the length
			scalar length() const
			{
				return length_;
			}

			//- Get the phase
			scalar phase() const
			{
				return phase_;
			}

			//- Get the depth
			scalar depth() const
			{
				return depth_;
			}

			//- Get the wave elevation at a given time and local coordinates. Local
			//  x is aligned with the direction of propagation.
			FoamWave_EXPORT virtual tmp<scalarField> elevation
			(
				const scalar t,
				const scalarField& x
			) const;

			//- Get the wave velocity at a given time and local coordinates. Local
			//  x is aligned with the direction of propagation, and z with negative
			//  gravity.
			FoamWave_EXPORT virtual tmp<vector2DField> velocity
			(
				const scalar t,
				const vector2DField& xz
			) const;

			//- Get the wave pressure at a given time and local coordinates. Local
			//  x is aligned with the direction of propagation, and z with negative
			//  gravity.
			FoamWave_EXPORT virtual tmp<scalarField> pressure
			(
				const scalar t,
				const vector2DField& xz
			) const;

			//- Write
			FoamWave_EXPORT virtual void write(Ostream& os) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace waveModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Airy_Header
