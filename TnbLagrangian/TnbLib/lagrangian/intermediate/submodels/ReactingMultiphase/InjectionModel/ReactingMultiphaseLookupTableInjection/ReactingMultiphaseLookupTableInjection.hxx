#pragma once
#ifndef _ReactingMultiphaseLookupTableInjection_Header
#define _ReactingMultiphaseLookupTableInjection_Header

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
	tnbLib::ReactingMultiphaseLookupTableInjection

Description
	Particle injection sources read from look-up table. Each row corresponds to
	an injection site.

	(
	   (x y z) (u v w) d rho mDot T cp (Y0..Y2) (Yg0..YgN) (Yl0..YlN) (Ys0..YsN)
	   (x y z) (u v w) d rho mDot T cp (Y0..Y2) (Yg0..YgN) (Yl0..YlN) (Ys0..YsN)
	   ...
	   (x y z) (u v w) d rho mDot T cp (Y0..Y2) (Yg0..YgN) (Yl0..YlN) (Ys0..YsN)
	);

	where:
		x, y, z  = global cartesian co-ordinates [m]
		u, v, w  = global cartesian velocity components [m/s]
		d        = diameter [m]
		rho      = density [kg/m^3]
		mDot     = mass flow rate [kg/s]
		T        = temperature [K]
		cp       = specific heat capacity [J/kg/K]
		Y(3)     = total mass fraction of gas (Y0), liquid (Y1), solid (Y3)
		Yg(Ngas) = mass fractions of gaseous components
		Yl(Nliq) = mass fractions of liquid components
		Ys(Nsld) = mass fractions of solid components

SourceFiles
	ReactingMultiphaseLookupTableInjection.C

\*---------------------------------------------------------------------------*/

#include <InjectionModelTemplate.hxx>
#include <reactingMultiphaseParcelInjectionDataIOList.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamReactingMultiphaseLookupTableInjection_EXPORT __declspec(dllexport)
#else
#ifdef FoamReactingMultiphaseLookupTableInjection_EXPORT_DEFINE
#define FoamReactingMultiphaseLookupTableInjection_EXPORT __declspec(dllexport)
#else
#define FoamReactingMultiphaseLookupTableInjection_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			   Class ReactingMultiphaseLookupTableInjection Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class ReactingMultiphaseLookupTableInjection
		:
		public InjectionModel<CloudType>
	{
		// Private Data

			//- Name of file containing injector/parcel data
		const word inputFileName_;

		//- Injection duration - common to all injection sources
		scalar duration_;

		//- Number of parcels per injector - common to all injection sources
		const scalar parcelsPerSecond_;

		//- Flag to indicate to randomise injection positions
		bool randomise_;

		//- List of injectors
		reactingMultiphaseParcelInjectionDataIOList injectors_;

		//- List of cell labels corresoponding to injector positions
		labelList injectorCells_;

		//- List of tetFace labels corresoponding to injector positions
		labelList injectorTetFaces_;

		//- List of tetPt labels corresoponding to injector positions
		labelList injectorTetPts_;


	public:

		//- Runtime type information
		//TypeName("reactingMultiphaseLookupTableInjection");
		static const char* typeName_() { return "reactingMultiphaseLookupTableInjection"; }
		static FoamReactingMultiphaseLookupTableInjection_EXPORT const ::tnbLib::word typeName;
		static FoamReactingMultiphaseLookupTableInjection_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		ReactingMultiphaseLookupTableInjection
		(
			const dictionary& dict,
			CloudType& owner,
			const word& modelName
		);

		//- Construct copy
		ReactingMultiphaseLookupTableInjection
		(
			const ReactingMultiphaseLookupTableInjection<CloudType>& im
		);

		//- Construct and return a clone
		virtual autoPtr<InjectionModel<CloudType>> clone() const
		{
			return autoPtr<InjectionModel<CloudType>>
				(
					new ReactingMultiphaseLookupTableInjection<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~ReactingMultiphaseLookupTableInjection();


		// Member Functions

			//- Set injector locations when mesh is updated
		virtual void updateMesh();

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

		//- Set the parcel properties
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

#include <ReactingMultiphaseLookupTableInjectionI.hxx>

//#ifdef NoRepository
//#include <ReactingMultiphaseLookupTableInjection.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ReactingMultiphaseLookupTableInjection_Header
