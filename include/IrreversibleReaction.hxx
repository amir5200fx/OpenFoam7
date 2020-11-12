#pragma once
#ifndef _IrreversibleReaction_Header
#define _IrreversibleReaction_Header

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
	tnbLib::IrreversibleReaction

Description
	Simple extension of Reaction to handle irreversible reactions

SourceFiles
	IrreversibleReaction.C

\*---------------------------------------------------------------------------*/

#include <Reaction.hxx>

#ifdef FoamThermophysicalModels_EXPORT_DEFINE
#define FoamIrreversibleReaction_EXPORT __declspec(dllexport)
#else
#ifdef FoamIrreversibleReaction_EXPORT_DEFINE
#define FoamIrreversibleReaction_EXPORT __declspec(dllexport)
#else
#define FoamIrreversibleReaction_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class IrreversibleReaction Declaration
	\*---------------------------------------------------------------------------*/

	template
		<
		template<class> class ReactionType,
		class ReactionThermo,
		class ReactionRate
		>
		class IrreversibleReaction
		:
		public ReactionType<ReactionThermo>
	{
		// Private Data

		ReactionRate k_;


	public:

		//- Runtime type information
		//TypeName("irreversible");
		static const char* typeName_() { return "irreversible"; }
		static FoamIrreversibleReaction_EXPORT const ::tnbLib::word typeName;
		static FoamIrreversibleReaction_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		IrreversibleReaction
		(
			const ReactionType<ReactionThermo>& reaction,
			const ReactionRate& reactionRate
		);

		//- Construct as copy given new speciesTable
		IrreversibleReaction
		(
			const IrreversibleReaction
			<
			ReactionType,
			ReactionThermo,
			ReactionRate
			>&,
			const speciesTable& species
		);

		//- Construct from dictionary
		IrreversibleReaction
		(
			const speciesTable& species,
			const HashPtrTable<ReactionThermo>& thermoDatabase,
			const dictionary& dict
		);

		//- Construct and return a clone
		virtual autoPtr<Reaction<ReactionThermo>> clone() const
		{
			return autoPtr<Reaction<ReactionThermo>>
				(
					new IrreversibleReaction
					<
					ReactionType,
					ReactionThermo,
					ReactionRate
					>(*this)
					);
		}

		//- Construct and return a clone with new speciesTable
		virtual autoPtr<Reaction<ReactionThermo>> clone
		(
			const speciesTable& species
		) const
		{
			return autoPtr<Reaction<ReactionThermo>>
				(
					new IrreversibleReaction
					<
					ReactionType,
					ReactionThermo,
					ReactionRate
					>
					(
						*this,
						species
						)
					);
		}


		//- Destructor
		virtual ~IrreversibleReaction()
		{}


		// Member Functions

			// IrreversibleReaction rate coefficients

				//- Forward rate constant
		virtual scalar kf
		(
			const scalar p,
			const scalar T,
			const scalarField& c
		) const;

		//- Reverse rate constant from the given forward rate constant
		//  Returns 0
		virtual scalar kr
		(
			const scalar kfwd,
			const scalar p,
			const scalar T,
			const scalarField& c
		) const;

		//- Reverse rate constant
		//  Returns 0
		virtual scalar kr
		(
			const scalar p,
			const scalar T,
			const scalarField& c
		) const;


		// IrreversibleReaction Jacobian functions

			//- Temperature derivative of forward rate
		virtual scalar dkfdT
		(
			const scalar p,
			const scalar T,
			const scalarField& c
		) const;

		//- Temperature derivative of reverse rate
		//  Returns 0
		virtual scalar dkrdT
		(
			const scalar p,
			const scalar T,
			const scalarField& c,
			const scalar dkfdT,
			const scalar kr
		) const;

		//- Third-body efficiencies (beta = 1-alpha)
		//  non-empty only for third-body reactions
		//  with enhanced molecularity (alpha != 1)
		virtual const List<Tuple2<label, scalar>>& beta() const;

		//- Species concentration derivative of the pressure dependent term
		//  By default this value is 1 as it multiplies the third-body term
		virtual void dcidc
		(
			const scalar p,
			const scalar T,
			const scalarField& c,
			scalarField& dcidc
		) const;

		//- Temperature derivative of the pressure dependent term
		//  By default this value is 0 since ddT of molecularity is approx.0
		virtual scalar dcidT
		(
			const scalar p,
			const scalar T,
			const scalarField& c
		) const;


		//- Write
		virtual void write(Ostream&) const;    // Private Member Functions


	// Member Operators

		//- Disallow default bitwise assignment
		void operator=
			(
				const IrreversibleReaction
				<
				ReactionType,
				ReactionThermo,
				ReactionRate
				>&
				) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <IrreversibleReactionI.hxx>

//#ifdef NoRepository
//#include <IrreversibleReaction.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_IrreversibleReaction_Header
