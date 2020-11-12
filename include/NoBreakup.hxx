#pragma once
#ifndef _NoBreakup_Header
#define _NoBreakup_Header

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
	tnbLib::NoBreakup

Description
	Dummy breakup model for 'none'

\*---------------------------------------------------------------------------*/

#include <BreakupModel.hxx>

#include <vector.hxx>  // added by amir

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamNoBreakup_EXPORT __declspec(dllexport)
#else
#ifdef FoamNoBreakup_EXPORT_DEFINE
#define FoamNoBreakup_EXPORT __declspec(dllexport)
#else
#define FoamNoBreakup_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						   Class NoBreakup Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class NoBreakup
		:
		public BreakupModel<CloudType>
	{
	public:

		//- Runtime type information
		//TypeName("none");
		static const char* typeName_() { return "none"; }
		static FoamNoBreakup_EXPORT const ::tnbLib::word typeName;
		static FoamNoBreakup_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		NoBreakup(const dictionary&, CloudType&);

		//- Construct copy
		NoBreakup(const NoBreakup<CloudType>& bum);

		//- Construct and return a clone
		virtual autoPtr<BreakupModel<CloudType>> clone() const
		{
			return autoPtr<BreakupModel<CloudType>>
				(
					new NoBreakup<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~NoBreakup();


		// Member Functions

			//- Flag to indicate whether model activates break-up model
		virtual bool active() const;

		//- Update the parcel properties
		virtual bool update
		(
			const scalar dt,
			const vector& g,
			scalar& d,
			scalar& tc,
			scalar& ms,
			scalar& nParticle,
			scalar& KHindex,
			scalar& y,
			scalar& yDot,
			const scalar d0,
			const scalar rho,
			const scalar mu,
			const scalar sigma,
			const vector& U,
			const scalar rhoc,
			const scalar muc,
			const vector& Urel,
			const scalar Urmag,
			const scalar tMom,
			scalar& dChild,
			scalar& massChild
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <NoBreakupI.hxx>

//#ifdef NoRepository
//#include <NoBreakup.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NoBreakup_Header
