#pragma once
#ifndef _StandardChemistryModel_Header
#define _StandardChemistryModel_Header

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
	tnbLib::StandardChemistryModel

Description
	Extends base chemistry model by adding a thermo package, and ODE functions.
	Introduces chemistry equation system and evaluation of chemical source
	terms.

SourceFiles
	StandardChemistryModelI.H
	StandardChemistryModel.C

\*---------------------------------------------------------------------------*/

#include <BasicChemistryModelTemplate.hxx>
#include <Reaction.hxx>
#include <ODESystem.hxx>
#include <volFields.hxx>
#include <simpleMatrix.hxx>

#ifdef FoamThermophysicalModels_EXPORT_DEFINE
#define FoamStandardChemistryModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamStandardChemistryModel_EXPORT_DEFINE
#define FoamStandardChemistryModel_EXPORT __declspec(dllexport)
#else
#define FoamStandardChemistryModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class fvMesh;

	/*---------------------------------------------------------------------------*\
						  Class StandardChemistryModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class ReactionThermo, class ThermoType>
	class StandardChemistryModel
		:
		public BasicChemistryModel<ReactionThermo>,
		public ODESystem
	{
		// Private Member Functions

			//- Solve the reaction system for the given time step
			//  of given type and return the characteristic time
		template<class DeltaTType>
		scalar solve(const DeltaTType& deltaT);


	protected:

		typedef ThermoType thermoType;


		// Protected data

			//- Reference to the field of specie mass fractions
		PtrList<volScalarField>& Y_;

		//- Reactions
		const PtrList<Reaction<ThermoType>>& reactions_;

		//- Thermodynamic data of the species
		const PtrList<ThermoType>& specieThermo_;

		//- Number of species
		label nSpecie_;

		//- Number of reactions
		label nReaction_;

		//- Temperature below which the reaction rates are assumed 0
		scalar Treact_;

		//- List of reaction rate per specie [kg/m^3/s]
		PtrList<volScalarField::Internal> RR_;

		//- Temporary concentration field
		mutable scalarField c_;

		//- Temporary rate-of-change of concentration field
		mutable scalarField dcdt_;


		// Protected Member Functions

			//- Write access to chemical source terms
			//  (e.g. for multi-chemistry model)
		inline PtrList<volScalarField::Internal>& RR();


	public:

		//- Runtime type information
		//TypeName("standard");
		static const char* typeName_() { return "standard"; }
		static FoamStandardChemistryModel_EXPORT const ::tnbLib::word typeName;
		static FoamStandardChemistryModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from thermo
		StandardChemistryModel(ReactionThermo& thermo);

		//- Disallow default bitwise copy construction
		StandardChemistryModel(const StandardChemistryModel&);


		//- Destructor
		virtual ~StandardChemistryModel();


		// Member Functions

			//- The reactions
		inline const PtrList<Reaction<ThermoType>>& reactions() const;

		//- Thermodynamic data of the species
		inline const PtrList<ThermoType>& specieThermo() const;

		//- The number of species
		virtual inline label nSpecie() const;

		//- The number of reactions
		virtual inline label nReaction() const;

		//- Temperature below which the reaction rates are assumed 0
		inline scalar Treact() const;

		//- Temperature below which the reaction rates are assumed 0
		inline scalar& Treact();

		//- dc/dt = omega, rate of change in concentration, for each species
		virtual void omega
		(
			const scalarField& c,
			const scalar T,
			const scalar p,
			scalarField& dcdt
		) const;


		//- Return the reaction rate for iReaction and the reference
		//  species and charateristic times
		virtual scalar omegaI
		(
			label iReaction,
			const scalarField& c,
			const scalar T,
			const scalar p,
			scalar& pf,
			scalar& cf,
			label& lRef,
			scalar& pr,
			scalar& cr,
			label& rRef
		) const;

		//- Calculates the reaction rates
		virtual void calculate();


		// Chemistry model functions (overriding abstract functions in
		// basicChemistryModel.H)

			//- Return const access to the chemical source terms for specie, i
		inline const volScalarField::Internal& RR
		(
			const label i
		) const;

		//- Return non const access to chemical source terms [kg/m^3/s]
		virtual volScalarField::Internal& RR
		(
			const label i
		);

		//- Return reaction rate of the speciei in reactionI
		virtual tmp<volScalarField::Internal> calculateRR
		(
			const label reactionI,
			const label speciei
		) const;

		//- Solve the reaction system for the given time step
		//  and return the characteristic time
		virtual scalar solve(const scalar deltaT);

		//- Solve the reaction system for the given time step
		//  and return the characteristic time
		virtual scalar solve(const scalarField& deltaT);

		//- Return the chemical time scale
		virtual tmp<volScalarField> tc() const;

		//- Return the heat release rate [kg/m/s^3]
		virtual tmp<volScalarField> Qdot() const;


		// ODE functions (overriding abstract functions in ODE.H)

			//- Number of ODE's to solve
		inline virtual label nEqns() const;

		virtual void derivatives
		(
			const scalar t,
			const scalarField& c,
			scalarField& dcdt
		) const;

		virtual void jacobian
		(
			const scalar t,
			const scalarField& c,
			scalarField& dcdt,
			scalarSquareMatrix& J
		) const;

		virtual void solve
		(
			scalarField &c,
			scalar& T,
			scalar& p,
			scalar& deltaT,
			scalar& subDeltaT
		) const = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const StandardChemistryModel&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <StandardChemistryModelI.hxx>
#include <StandardChemistryModel_Imp.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include <StandardChemistryModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_StandardChemistryModel_Header
