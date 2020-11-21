#pragma once
#ifndef _StochasticDispersionRAS_Header
#define _StochasticDispersionRAS_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::StochasticDispersionRAS

Description
	The velocity is perturbed in random direction, with a
	Gaussian random number distribution with variance sigma.
	where sigma is defined below

\*---------------------------------------------------------------------------*/

#include <DispersionRASModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamStochasticDispersionRAS_EXPORT __declspec(dllexport)
#else
#ifdef FoamStochasticDispersionRAS_EXPORT_DEFINE
#define FoamStochasticDispersionRAS_EXPORT __declspec(dllexport)
#else
#define FoamStochasticDispersionRAS_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class StochasticDispersionRAS Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class StochasticDispersionRAS
		:
		public DispersionRASModel<CloudType>
	{
	public:

		//- Runtime type information
		//TypeName("stochasticDispersionRAS");
		static const char* typeName_() { return "stochasticDispersionRAS"; }
		static FoamStochasticDispersionRAS_EXPORT const ::tnbLib::word typeName;
		static FoamStochasticDispersionRAS_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		StochasticDispersionRAS(const dictionary& dict, CloudType& owner);

		//- Construct copy
		StochasticDispersionRAS(const StochasticDispersionRAS<CloudType>& dm);

		//- Construct and return a clone
		virtual autoPtr<DispersionModel<CloudType>> clone() const
		{
			return autoPtr<DispersionModel<CloudType>>
				(
					new StochasticDispersionRAS<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~StochasticDispersionRAS();


		// Member Functions

			//- Update (disperse particles)
		virtual vector update
		(
			const scalar dt,
			const label celli,
			const vector& U,
			const vector& Uc,
			vector& UTurb,
			scalar& tTurb
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <StochasticDispersionRASI.hxx>

//#ifdef NoRepository
//#include <StochasticDispersionRAS.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_StochasticDispersionRAS_Header
