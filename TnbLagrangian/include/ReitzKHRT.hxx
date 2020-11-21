#pragma once
#ifndef _ReitzKHRT_Header
#define _ReitzKHRT_Header

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
	tnbLib::ReitzKHRT

Description
   secondary breakup model which uses the Kelvin-Helmholtz
	instability theory to predict the 'stripped' droplets... and
	the Raleigh-Taylor instability as well.

\*---------------------------------------------------------------------------*/

#include <BreakupModel.hxx>

#include <vector.hxx> // added by amir

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamReitzKHRT_EXPORT __declspec(dllexport)
#else
#ifdef FoamReitzKHRT_EXPORT_DEFINE
#define FoamReitzKHRT_EXPORT __declspec(dllexport)
#else
#define FoamReitzKHRT_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
							 Class ReitzKHRT Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class ReitzKHRT
		:
		public BreakupModel<CloudType>
	{
		// Private Data

			// model constants
		scalar b0_;
		scalar b1_;
		scalar cTau_;
		scalar cRT_;
		scalar msLimit_;
		scalar weberLimit_;


	public:

		//- Runtime type information
		//TypeName("ReitzKHRT");
		static const char* typeName_() { return "ReitzKHRT"; }
		static FoamReitzKHRT_EXPORT const ::tnbLib::word typeName;
		static FoamReitzKHRT_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		ReitzKHRT(const dictionary&, CloudType&);

		//- Construct copy
		ReitzKHRT(const ReitzKHRT<CloudType>& bum);

		//- Construct and return a clone
		virtual autoPtr<BreakupModel<CloudType>> clone() const
		{
			return autoPtr<BreakupModel<CloudType>>
				(
					new ReitzKHRT<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~ReitzKHRT();


		// Member Functions

			//- Update the parcel diameter
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

#include <ReitzKHRTI.hxx>

//#ifdef NoRepository
//#include <ReitzKHRT.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ReitzKHRT_Header
