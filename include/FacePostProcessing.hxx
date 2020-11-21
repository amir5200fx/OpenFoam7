#pragma once
#ifndef _FacePostProcessing_Header
#define _FacePostProcessing_Header

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
	tnbLib::FacePostProcessing

Description
	Records particle face quantities on used-specified face zone

	Currently supports:
		accummulated mass
		average mass flux

SourceFiles
	FacePostProcessing.C

\*---------------------------------------------------------------------------*/

#include <CloudFunctionObject.hxx>
#include <faceZone.hxx>

#include <PtrList.hxx>  // added by amir
#include <OFstream.hxx> // added by amir
#include <Switch.hxx>  // added by amir

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamFacePostProcessing_EXPORT __declspec(dllexport)
#else
#ifdef FoamFacePostProcessing_EXPORT_DEFINE
#define FoamFacePostProcessing_EXPORT __declspec(dllexport)
#else
#define FoamFacePostProcessing_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class FacePostProcessing Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class FacePostProcessing
		:
		public CloudFunctionObject<CloudType>
	{
		// Private Data

			// Typedefs

				//- Convenience typedef for parcel type
		typedef typename CloudType::parcelType parcelType;


		//- Face zone IDs
		labelList faceZoneIDs_;

		//- Surface output format
		const word surfaceFormat_;

		//- Flag to indicate whether data should be reset/cleared on writing
		Switch resetOnWrite_;

		//- Total time
		scalar totalTime_;

		//- Mass storage
		List<scalarField> mass_;

		//- Mass total storage
		List<scalarField> massTotal_;

		//- Mass flow rate storage
		List<scalarField> massFlowRate_;

		//- Flag to indicate whether data should be written to file
		Switch log_;

		//- Output file pointer per zone
		PtrList<OFstream> outputFilePtr_;

		//- Last calculation time
		scalar timeOld_;


		// Private Member Functions

			//- Helper function to create log files
		void makeLogFile
		(
			const word& zoneName,
			const label zoneI,
			const label nFaces,
			const scalar totArea
		);


	protected:

		// Protected Member Functions

			//- Write post-processing info
		void write();


	public:

		//- Runtime type information
		//TypeName("facePostProcessing");
		static const char* typeName_() { return "facePostProcessing"; }
		static FoamFacePostProcessing_EXPORT const ::tnbLib::word typeName;
		static FoamFacePostProcessing_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		FacePostProcessing
		(
			const dictionary& dict,
			CloudType& owner,
			const word& modelName
		);

		//- Construct copy
		FacePostProcessing(const FacePostProcessing<CloudType>& ppm);

		//- Construct and return a clone
		virtual autoPtr<CloudFunctionObject<CloudType>> clone() const
		{
			return autoPtr<CloudFunctionObject<CloudType>>
				(
					new FacePostProcessing<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~FacePostProcessing();


		// Member Functions

			// Access

				//- Return const access to the reset on write flag
		inline const Switch& resetOnWrite() const;


		// Evaluation

			//- Post-face hook
		virtual void postFace(const parcelType& p, bool& keepParticle);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <FacePostProcessingI.hxx>
#include <FacePostProcessing_Imp.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include <FacePostProcessing.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_FacePostProcessing_Header
