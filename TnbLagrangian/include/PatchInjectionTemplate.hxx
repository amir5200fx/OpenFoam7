#pragma once
#ifndef _PatchInjectionTemplate_Header
#define _PatchInjectionTemplate_Header

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
	tnbLib::PatchInjection

Description
	Patch injection.

	User specifies:
	  - Total mass to inject
	  - Name of patch
	  - Injection duration
	  - Initial parcel velocity
	  - Injection volume flow rate

	Properties:
	  - Parcel diameters obtained by distribution model
	  - Parcels injected randomly across the patch

SourceFiles
	PatchInjection.C

\*---------------------------------------------------------------------------*/

#include <InjectionModelTemplate.hxx>
#include <patchInjectionBase.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamPatchInjection_EXPORT __declspec(dllexport)
#else
#ifdef FoamPatchInjection_EXPORT_DEFINE
#define FoamPatchInjection_EXPORT __declspec(dllexport)
#else
#define FoamPatchInjection_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<class Type>
	class TimeFunction1;

	class distributionModel;

	/*---------------------------------------------------------------------------*\
						   Class PatchInjection Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class PatchInjection
		:
		public InjectionModel<CloudType>,
		public patchInjectionBase
	{
		// Private Data

			//- Injection duration [s]
		scalar duration_;

		//- Number of parcels to introduce per second []
		const label parcelsPerSecond_;

		//- Initial parcel velocity [m/s]
		const vector U0_;

		//- Flow rate profile relative to SOI []
		const TimeFunction1<scalar> flowRateProfile_;

		//- Parcel size distribution model
		const autoPtr<distributionModel> sizeDistribution_;


	public:

		//- Runtime type information
		//TypeName("patchInjection");
		static const char* typeName_() { return "patchInjection"; }
		static FoamPatchInjection_EXPORT const ::tnbLib::word typeName;
		static FoamPatchInjection_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		PatchInjection
		(
			const dictionary& dict,
			CloudType& owner,
			const word& modelName
		);

		//- Construct copy
		PatchInjection(const PatchInjection<CloudType>& im);

		//- Construct and return a clone
		virtual autoPtr<InjectionModel<CloudType>> clone() const
		{
			return autoPtr<InjectionModel<CloudType>>
				(
					new PatchInjection<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~PatchInjection();


		// Member Functions

			//- Inherit updateMesh from patchInjectionBase
		using patchInjectionBase::updateMesh;

		//- Set injector locations when mesh is updated
		virtual void updateMesh();

		//- Return the end-of-injection time
		virtual scalar timeEnd() const;

		//- Number of parcels to introduce relative to SOI
		virtual label parcelsToInject(const scalar time0, const scalar time1);

		//- Volume of parcels to introduce relative to SOI
		virtual scalar volumeToInject(const scalar time0, const scalar time1);


		// Injection geometry

			//- Inherit setPositionAndCell from patchInjectionBase
		using patchInjectionBase::setPositionAndCell;

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

#include <PatchInjectionTemplateI.hxx>

//#ifdef NoRepository
//#include <PatchInjectionTemplate.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_PatchInjectionTemplate_Header
