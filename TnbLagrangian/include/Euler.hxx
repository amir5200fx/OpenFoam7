#pragma once
#ifndef _Euler_Header
#define _Euler_Header

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
	tnbLib::integrationSchemes::Euler

Description
	Euler-implicit integration scheme.

	\f[
		\Delta \phi = (A - B \phi^n) \frac{\Delta t}{1 + B \Delta t}
	\f]

\*---------------------------------------------------------------------------*/

#include <integrationScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace integrationSchemes
	{

		/*---------------------------------------------------------------------------*\
								   Class Euler Declaration
		\*---------------------------------------------------------------------------*/

		class Euler
			:
			public integrationScheme
		{
		public:

			//- Runtime type information
			//TypeName("Euler");
			static const char* typeName_() { return "Euler"; }
			static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
			static FoamLagrangian_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct
			FoamLagrangian_EXPORT Euler();

			//- Construct and return clone
			virtual autoPtr<integrationScheme> clone() const
			{
				return autoPtr<integrationScheme>(new Euler(*this));
			}


			//- Destructor
			FoamLagrangian_EXPORT virtual ~Euler();


			// Member Functions

				//- Return the integration effective time step
			FoamLagrangian_EXPORT virtual scalar dtEff(const scalar dt, const scalar Beta) const;

			//- Return the integral of the effective time step (using an Euler
			//  integration method)
			FoamLagrangian_EXPORT virtual scalar sumDtEff(const scalar dt, const scalar Beta) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace integrationSchemes
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Euler_Header
