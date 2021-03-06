#pragma once
#ifndef _NoSurfaceReaction_Header
#define _NoSurfaceReaction_Header

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
	tnbLib::NoSurfaceReaction

Description
	Dummy surface reaction model for 'none'

\*---------------------------------------------------------------------------*/

#include <SurfaceReactionModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamNoSurfaceReaction_EXPORT __declspec(dllexport)
#else
#ifdef FoamNoSurfaceReaction_EXPORT_DEFINE
#define FoamNoSurfaceReaction_EXPORT __declspec(dllexport)
#else
#define FoamNoSurfaceReaction_EXPORT __declspec(dllimport)
#endif
#endif


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
						 Class NoSurfaceReaction Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class NoSurfaceReaction
		:
		public SurfaceReactionModel<CloudType>
	{
	public:

		//- Runtime type information
		//TypeName("none");
		static const char* typeName_() { return "none"; }
		static FoamNoSurfaceReaction_EXPORT const ::tnbLib::word typeName;
		static FoamNoSurfaceReaction_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		NoSurfaceReaction(const dictionary& dict, CloudType& owner);

		//- Construct copy
		NoSurfaceReaction(const NoSurfaceReaction<CloudType>& srm);

		//- Construct and return a clone
		virtual autoPtr<SurfaceReactionModel<CloudType>> clone() const
		{
			return autoPtr<SurfaceReactionModel<CloudType>>
				(
					new NoSurfaceReaction<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~NoSurfaceReaction();


		// Member Functions

			//- Flag to indicate whether model activates devolatisation model
		virtual bool active() const;

		//- Update surface reactions
		virtual scalar calculate
		(
			const scalar dt,
			const label celli,
			const scalar d,
			const scalar T,
			const scalar Tc,
			const scalar pc,
			const scalar rhoc,
			const scalar mass,
			const scalarField& YGas,
			const scalarField& YLiquid,
			const scalarField& YSolid,
			const scalarField& YMixture,
			const scalar N,
			scalarField& dMassGas,
			scalarField& dMassLiquid,
			scalarField& dMassSolid,
			scalarField& dMassSRCarrier
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <NoSurfaceReactionI.hxx>

//#ifdef NoRepository
//#include <NoSurfaceReaction.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NoSurfaceReaction_Header
