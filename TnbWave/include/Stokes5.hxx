#pragma once
#ifndef _Stokes5_Header
#define _Stokes5_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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
	tnbLib::waveModels::Stokes5

Description
	Fifth-order wave model.

	Reference:
	\verbatim
		Fenton, J. D. (1985).
		A fifth-order Stokes theory for steady waves.
		Journal of waterway, port, coastal, and ocean engineering, 111(2),
		216-234.
	\endverbatim

SourceFiles
	Stokes5.C

\*---------------------------------------------------------------------------*/

#include <Stokes2.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace waveModels
	{

		/*---------------------------------------------------------------------------*\
								   Class Stokes5 Declaration
		\*---------------------------------------------------------------------------*/

		class Stokes5
			:
			public Stokes2
		{
		public:
			
			//- Runtime type information
			//TypeName("Stokes5");
			static const char* typeName_() { return "Stokes5"; }

			static FoamWave_EXPORT const ::tnbLib::word typeName;
			static FoamWave_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from a database and a dictionary
			FoamWave_EXPORT Stokes5(const objectRegistry& db, const dictionary& dict);

			//- Construct a clone
			virtual autoPtr<waveModel> clone() const
			{
				return autoPtr<waveModel>(new Stokes5(*this));
			}


			//- Destructor
			FoamWave_EXPORT virtual ~Stokes5();


			// Member Functions

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
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace tnbLib
} // End namespace waveModels

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Stokes5_Header
