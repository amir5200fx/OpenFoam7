#pragma once
#ifndef _NoInjection_Header
#define _NoInjection_Header

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
	tnbLib::NoInjection

Description
	Place holder for 'none' option

SourceFiles
	NoInjection.C

\*---------------------------------------------------------------------------*/

#include <InjectionModelTemplate.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamNoInjection_EXPORT __declspec(dllexport)
#else
#ifdef FoamNoInjection_EXPORT_DEFINE
#define FoamNoInjection_EXPORT __declspec(dllexport)
#else
#define FoamNoInjection_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class NoInjection Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class NoInjection
		:
		public InjectionModel<CloudType>
	{

	public:

		//- Runtime type information
		//TypeName("none");
		static const char* typeName_() { return "none"; }
		static FoamNoInjection_EXPORT const ::tnbLib::word typeName;
		static FoamNoInjection_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		NoInjection(const dictionary&, CloudType&, const word&);

		//- Construct copy
		NoInjection(const NoInjection<CloudType>& im);

		//- Construct and return a clone
		virtual autoPtr<InjectionModel<CloudType>> clone() const
		{
			return autoPtr<InjectionModel<CloudType>>
				(
					new NoInjection<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~NoInjection();


		// Member Functions

			//- Flag to indicate whether model activates injection model
		bool active() const;

		//- Return the end-of-injection time
		scalar timeEnd() const;

		//- Number of parcels to introduce relative to SOI
		virtual label parcelsToInject(const scalar time0, const scalar time1);

		//- Volume of parcels to introduce relative to SOI
		virtual scalar volumeToInject(const scalar time0, const scalar time1);


		// Injection geometry

			//- Set the injection position and owner cell, tetFace and tetPt
		virtual void setPositionAndCell
		(
			const label parcelI,
			const label nParcels,
			const scalar time,
			vector& position,
			label& cellOwner,
			label& tetFacei,
			label& tetPti
		);

		virtual void setProperties
		(
			const label parcelI,
			const label nParcels,
			const scalar time,
			typename CloudType::parcelType& parcel
		);

		//- Flag to identify whether model fully describes the parcel
		virtual bool fullyDescribed() const;

		//- Return flag to identify whether or not injection of parcelI is
		//  permitted
		virtual bool validInjection(const label parcelI);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <NoInjectionI.hxx>

//#ifdef NoRepository
//#include <NoInjection.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NoInjection_Header
