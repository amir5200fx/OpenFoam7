#pragma once
#ifndef _LocalInteraction_Header
#define _LocalInteraction_Header

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
	tnbLib::LocalInteraction

Description
	Patch interaction specified on a patch-by-patch basis

\*---------------------------------------------------------------------------*/

#include <PatchInteractionModel.hxx>
#include <patchInteractionDataList.hxx>
#include <Switch.hxx>

#include <volFieldsFwd.hxx>  // added by amir

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamLocalInteraction_EXPORT __declspec(dllexport)
#else
#ifdef FoamLocalInteraction_EXPORT_DEFINE
#define FoamLocalInteraction_EXPORT __declspec(dllexport)
#else
#define FoamLocalInteraction_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						  Class LocalInteraction Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class LocalInteraction
		:
		public PatchInteractionModel<CloudType>
	{
		// Private Data

			//- List of participating patches
		const patchInteractionDataList patchData_;


		// Counters for particle fates

			//- Number of parcels escaped
		List<label> nEscape_;

		//- Mass of parcels escaped
		List<scalar> massEscape_;

		//- Number of parcels stuck to patches
		List<label> nStick_;

		//- Mass of parcels stuck to patches
		List<scalar> massStick_;


		//- Flag to output data as fields
		Switch writeFields_;

		//- Mass escape field
		autoPtr<volScalarField> massEscapePtr_;

		//- Mass stick field
		autoPtr<volScalarField> massStickPtr_;


	public:

		//- Runtime type information
		//TypeName("localInteraction");
		static const char* typeName_() { return "localInteraction"; }
		static FoamLocalInteraction_EXPORT const ::tnbLib::word typeName;
		static FoamLocalInteraction_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		LocalInteraction(const dictionary& dict, CloudType& owner);

		//- Construct copy from owner cloud and patch interaction model
		LocalInteraction(const LocalInteraction<CloudType>& pim);

		//- Construct and return a clone using supplied owner cloud
		virtual autoPtr<PatchInteractionModel<CloudType>> clone() const
		{
			return autoPtr<PatchInteractionModel<CloudType>>
				(
					new LocalInteraction<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~LocalInteraction();


		// Member Functions

			//- Return access to the massEscape field
		volScalarField& massEscape();

		//- Return access to the massStick field
		volScalarField& massStick();

		//- Apply velocity correction
		//  Returns true if particle remains in same cell
		virtual bool correct
		(
			typename CloudType::parcelType& p,
			const polyPatch& pp,
			bool& keepParticle
		);


		// I-O

			//- Write patch interaction info to stream
		virtual void info(Ostream& os);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <LocalInteractionI.hxx>

//#ifdef NoRepository
//#include <LocalInteraction.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_LocalInteraction_Header
