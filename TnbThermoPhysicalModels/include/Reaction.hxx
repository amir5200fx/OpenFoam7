#pragma once
#ifndef _Reaction_Header
#define _Reaction_Header

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
	tnbLib::Reaction

Description
	Simple extension of ReactionThermo to handle reaction kinetics in addition
	to the equilibrium thermodynamics already handled.

SourceFiles
	ReactionI.H
	Reaction.C

\*---------------------------------------------------------------------------*/

#include <speciesTable.hxx>
#include <specieCoeffs.hxx>
#include <HashPtrTable.hxx>
#include <scalarField.hxx>
#include <simpleMatrix.hxx>
#include <Tuple2.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	template<class ReactionThermo>
	class Reaction;

	template<class ReactionThermo>
	inline Ostream& operator<<(Ostream&, const Reaction<ReactionThermo>&);


	/*---------------------------------------------------------------------------*\
							   Class Reaction Declaration
	\*---------------------------------------------------------------------------*/

	template<class ReactionThermo>
	class Reaction
		:
		public ReactionThermo::thermoType
	{

	public:

		// Static data

			//- Number of un-named reactions
		static label nUnNamedReactions;

		//- Default temperature limits of applicability of reaction rates
		static scalar TlowDefault, ThighDefault;

	private:

		// Private Data

			//- Name of reaction
		const word name_;

		//- List of specie names present in reaction system
		const speciesTable& species_;

		//- Temperature limits of applicability of reaction rates
		scalar Tlow_, Thigh_;

		//- Specie info for the left-hand-side of the reaction
		List<specieCoeffs> lhs_;

		//- Specie info for the right-hand-side of the reaction
		List<specieCoeffs> rhs_;


		// Private Member Functions

			//- Construct reaction thermo
		void setThermo(const HashPtrTable<ReactionThermo>& thermoDatabase);

		//- Return new reaction ID for un-named reactions
		label getNewReactionID();


	public:

		//- Runtime type information
		TypeName("Reaction");


		// Declare run-time constructor selection tables

		declareRunTimeSelectionTable
		(
			autoPtr,
			Reaction,
			dictionary,
			(
				const speciesTable& species,
				const HashPtrTable<ReactionThermo>& thermoDatabase,
				const dictionary& dict
				),
				(species, thermoDatabase, dict)
		);


		// Constructors

			//- Construct from components
		Reaction
		(
			const speciesTable& species,
			const List<specieCoeffs>& lhs,
			const List<specieCoeffs>& rhs,
			const HashPtrTable<ReactionThermo>& thermoDatabase
		);

		//- Construct as copy given new speciesTable
		Reaction(const Reaction<ReactionThermo>&, const speciesTable& species);

		//- Construct from dictionary
		Reaction
		(
			const speciesTable& species,
			const HashPtrTable<ReactionThermo>& thermoDatabase,
			const dictionary& dict
		);

		//- Construct and return a clone
		virtual autoPtr<Reaction<ReactionThermo>> clone() const = 0;

		//- Construct and return a clone with new speciesTable
		virtual autoPtr<Reaction<ReactionThermo>> clone
		(
			const speciesTable& species
		) const = 0;


		// Selectors

			//- Return a pointer to new patchField created on freestore from dict
		static autoPtr<Reaction<ReactionThermo>> New
		(
			const speciesTable& species,
			const HashPtrTable<ReactionThermo>& thermoDatabase,
			const dictionary& dict
		);


		//- Destructor
		virtual ~Reaction()
		{}


		// Member Functions

			// Access

				//- Return the name of the reaction
		inline const word& name() const;

		//- Return the lower temperature limit for the reaction
		inline scalar Tlow() const;

		//- Return the upper temperature limit for the reaction
		inline scalar Thigh() const;

		//- Return the components of the left hand side
		inline const List<specieCoeffs>& lhs() const;

		//- Return the components of the right hand side
		inline const List<specieCoeffs>& rhs() const;

		//- Return the specie list
		const speciesTable& species() const;


		// Reaction rate coefficients

			//- Forward reaction rate
		void ddot
		(
			const scalar p,
			const scalar T,
			const scalarField& c,
			scalarField& d
		) const;

		//- Backward reaction rate
		void fdot
		(
			const scalar p,
			const scalar T,
			const scalarField& c,
			scalarField& f
		) const;

		//- Net reaction rate for individual species
		void omega
		(
			const scalar p,
			const scalar T,
			const scalarField& c,
			scalarField& dcdt
		) const;

		//- Net reaction rate
		scalar omega
		(
			const scalar p,
			const scalar T,
			const scalarField& c,
			scalar& pf,
			scalar& cf,
			label& lRef,
			scalar& pr,
			scalar& cr,
			label& rRef
		) const;

		// Reaction rate coefficients

			//- Forward rate constant
		virtual scalar kf
		(
			const scalar p,
			const scalar T,
			const scalarField& c
		) const = 0;

		//- Reverse rate constant from the given forward rate constant
		virtual scalar kr
		(
			const scalar kfwd,
			const scalar p,
			const scalar T,
			const scalarField& c
		) const = 0;

		//- Reverse rate constant
		virtual scalar kr
		(
			const scalar p,
			const scalar T,
			const scalarField& c
		) const = 0;


		// Jacobian coefficients

			//- Derivative of the net reaction rate for each species involved
			//  w.r.t. the species concentration
		void dwdc
		(
			const scalar p,
			const scalar T,
			const scalarField& c,
			scalarSquareMatrix& J,
			scalarField& dcdt,
			scalar& omegaI,
			scalar& kfwd,
			scalar& kbwd,
			const bool reduced,
			const List<label>& c2s
		) const;

		//- Derivative of the net reaction rate for each species involved
		//  w.r.t. the temperature
		void dwdT
		(
			const scalar p,
			const scalar T,
			const scalarField& c,
			const scalar omegaI,
			const scalar kfwd,
			const scalar kbwd,
			scalarSquareMatrix& J,
			const bool reduced,
			const List<label>& c2s,
			const label indexT
		) const;

		//- Temperature derivative of forward rate
		virtual scalar dkfdT
		(
			const scalar p,
			const scalar T,
			const scalarField& c
		) const = 0;

		//- Temperature derivative of reverse rate
		virtual scalar dkrdT
		(
			const scalar p,
			const scalar T,
			const scalarField& c,
			const scalar dkfdT,
			const scalar kr
		) const = 0;

		//- Third-body efficiencies (beta = 1-alpha)
		//  non-empty only for third-body reactions
		//  with enhanced molecularity (alpha != 1)
		virtual const List<Tuple2<label, scalar>>& beta() const = 0;

		//- Species concentration derivative of the pressure dependent term
		virtual void dcidc
		(
			const scalar p,
			const scalar T,
			const scalarField& c,
			scalarField& dcidc
		) const = 0;

		//- Temperature derivative of the pressure dependent term
		virtual scalar dcidT
		(
			const scalar p,
			const scalar T,
			const scalarField& c
		) const = 0;


		//- Write
		virtual void write(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const Reaction<ReactionThermo>&) = delete;


		// Ostream Operator

		friend Ostream& operator<< <ReactionThermo>
			(
				Ostream&,
				const Reaction<ReactionThermo>&
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <ReactionI.hxx>
#include <Reaction_Imp.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include <Reaction.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Reaction_Header
