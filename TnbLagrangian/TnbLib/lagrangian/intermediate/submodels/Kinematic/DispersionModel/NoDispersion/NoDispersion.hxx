#pragma once
#ifndef _NoDispersion_Header
#define _NoDispersion_Header

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
	tnbLib::NoDispersion

Description
	Place holder for 'none' option

\*---------------------------------------------------------------------------*/

#include <DispersionModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamNoDispersion_EXPORT __declspec(dllexport)
#else
#ifdef FoamNoDispersion_EXPORT_DEFINE
#define FoamNoDispersion_EXPORT __declspec(dllexport)
#else
#define FoamNoDispersion_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class NoDispersion Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class NoDispersion
		:
		public DispersionModel<CloudType>
	{
	public:

		//- Runtime type information
		//TypeName("none");
		static const char* typeName_() { return "none"; }
		static FoamNoDispersion_EXPORT const ::tnbLib::word typeName;
		static FoamNoDispersion_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		NoDispersion(const dictionary& dict, CloudType& owner);

		//- Construct copy
		NoDispersion(const NoDispersion<CloudType>& dm);

		//- Construct and return a clone
		virtual autoPtr<DispersionModel<CloudType>> clone() const
		{
			return autoPtr<DispersionModel<CloudType>>
				(
					new NoDispersion<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~NoDispersion();


		// Member Functions

			//- Flag to indicate whether model activates injection model
		virtual bool active() const;

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

#include <NoDispersionI.hxx>

//#ifdef NoRepository
//#include <NoDispersion.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NoDispersion_Header
