#pragma once
#ifndef _VoidFraction_Header
#define _VoidFraction_Header

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
	tnbLib::VoidFraction

Description
	Creates particle void fraction field on carrier phase

SourceFiles
	VoidFraction.C

\*---------------------------------------------------------------------------*/

#include <CloudFunctionObject.hxx>
#include <volFields.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamVoidFraction_EXPORT __declspec(dllexport)
#else
#ifdef FoamVoidFraction_EXPORT_DEFINE
#define FoamVoidFraction_EXPORT __declspec(dllexport)
#else
#define FoamVoidFraction_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class VoidFraction Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class VoidFraction
		:
		public CloudFunctionObject<CloudType>
	{
		// Private Data

			// Typedefs

				//- Convenience typedef for parcel type
		typedef typename CloudType::parcelType parcelType;


		//- Void fraction field
		autoPtr<volScalarField> thetaPtr_;


	protected:

		// Protected Member Functions

			//- Write post-processing info
		virtual void write();


	public:

		//- Runtime type information
		//TypeName("voidFraction");
		static const char* typeName_() { return "voidFraction"; }
		static FoamVoidFraction_EXPORT const ::tnbLib::word typeName;
		static FoamVoidFraction_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		VoidFraction
		(
			const dictionary& dict,
			CloudType& owner,
			const word& modelName
		);

		//- Construct copy
		VoidFraction(const VoidFraction<CloudType>& vf);

		//- Construct and return a clone
		virtual autoPtr<CloudFunctionObject<CloudType>> clone() const
		{
			return autoPtr<CloudFunctionObject<CloudType>>
				(
					new VoidFraction<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~VoidFraction();


		// Member Functions

			// Evaluation

				//- Pre-evolve hook
		virtual void preEvolve();

		//- Post-evolve hook
		virtual void postEvolve();

		//- Post-move hook
		virtual void postMove
		(
			parcelType& p,
			const scalar dt,
			const point& position0,
			bool& keepParticle
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <VoidFractionI.hxx>

//#ifdef NoRepository
//#include <VoidFraction.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_VoidFraction_Header
