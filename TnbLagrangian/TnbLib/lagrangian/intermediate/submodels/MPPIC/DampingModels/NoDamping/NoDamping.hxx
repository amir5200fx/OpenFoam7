#pragma once
#ifndef _NoDamping_Header
#define _NoDamping_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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
	tnbLib::DampingModels::NoDamping

Description

SourceFiles
	NoDamping.C

\*---------------------------------------------------------------------------*/

#include <DampingModel.hxx>
#include <vector.hxx> // added by amir

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamNoDamping_EXPORT __declspec(dllexport)
#else
#ifdef FoamNoDamping_EXPORT_DEFINE
#define FoamNoDamping_EXPORT __declspec(dllexport)
#else
#define FoamNoDamping_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace DampingModels
	{

		/*---------------------------------------------------------------------------*\
								 Class NoDamping Declaration
		\*---------------------------------------------------------------------------*/

		template<class CloudType>
		class NoDamping
			:
			public DampingModel<CloudType>
		{
		public:

			//- Runtime type information
			//TypeName("none");
			static const char* typeName_() { return "none"; }
			static FoamNoDamping_EXPORT const ::tnbLib::word typeName;
			static FoamNoDamping_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			// Constructors

				//- Construct from components
			NoDamping(const dictionary& dict, CloudType& owner);

			//- Construct copy
			NoDamping(const NoDamping<CloudType>& cm);

			//- Construct and return a clone
			virtual autoPtr<DampingModel<CloudType>> clone() const
			{
				return autoPtr<DampingModel<CloudType>>
					(
						new NoDamping<CloudType>(*this)
						);
			}


			//- Destructor
			virtual ~NoDamping();


			//- Member Functions

				//- Calculate the velocity correction
			virtual vector velocityCorrection
			(
				typename CloudType::parcelType& p,
				const scalar deltaT
			) const;

			//- Return the model 'active' status
			virtual bool active() const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace DampingModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <NoDampingI.hxx>

//#ifdef NoRepository
//#include <NoDamping.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NoDamping_Header
