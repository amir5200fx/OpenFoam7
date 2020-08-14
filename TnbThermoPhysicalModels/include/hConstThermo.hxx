#pragma once
#ifndef _hConstThermo_Header
#define _hConstThermo_Header

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
	tnbLib::hConstThermo

Description
	Constant properties thermodynamics package
	templated into the EquationOfState.

SourceFiles
	hConstThermoI.H
	hConstThermo.C

\*---------------------------------------------------------------------------*/

#include <scalar.hxx>  // added by amir
#include <Ostream.hxx>  // added by amir
#include <autoPtr.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	template<class EquationOfState> class hConstThermo;

	template<class EquationOfState>
	inline hConstThermo<EquationOfState> operator+
		(
			const hConstThermo<EquationOfState>&,
			const hConstThermo<EquationOfState>&
			);

	template<class EquationOfState>
	inline hConstThermo<EquationOfState> operator*
		(
			const scalar,
			const hConstThermo<EquationOfState>&
			);

	template<class EquationOfState>
	inline hConstThermo<EquationOfState> operator==
		(
			const hConstThermo<EquationOfState>&,
			const hConstThermo<EquationOfState>&
			);

	template<class EquationOfState>
	Ostream& operator<<
		(
			Ostream&,
			const hConstThermo<EquationOfState>&
			);


	/*---------------------------------------------------------------------------*\
							   Class hConstThermo Declaration
	\*---------------------------------------------------------------------------*/

	template<class EquationOfState>
	class hConstThermo
		:
		public EquationOfState
	{
		// Private Data

		scalar Cp_;
		scalar Hf_;


		// Private Member Functions

			//- Construct from components
		inline hConstThermo
		(
			const EquationOfState& st,
			const scalar cp,
			const scalar hf
		);


	public:

		// Constructors

			//- Construct from dictionary
		hConstThermo(const dictionary& dict);

		//- Construct as named copy
		inline hConstThermo(const word&, const hConstThermo&);

		//- Construct and return a clone
		inline autoPtr<hConstThermo> clone() const;

		//- Selector from dictionary
		inline static autoPtr<hConstThermo> New(const dictionary& dict);


		// Member Functions

			//- Return the instantiated type name
		static word typeName()
		{
			return "hConst<" + EquationOfState::typeName() + '>';
		}

		//- Limit the temperature to be in the range Tlow_ to Thigh_
		inline scalar limit(const scalar T) const;


		// Fundamental properties

			//- Heat capacity at constant pressure [J/kg/K]
		inline scalar Cp(const scalar p, const scalar T) const;

		//- Absolute Enthalpy [J/kg]
		inline scalar Ha(const scalar p, const scalar T) const;

		//- Sensible enthalpy [J/kg]
		inline scalar Hs(const scalar p, const scalar T) const;

		//- Chemical enthalpy [J/kg]
		inline scalar Hc() const;

		//- Entropy [J/kg/K]
		inline scalar S(const scalar p, const scalar T) const;

		inline scalar Cv
		(
			const scalar p,
			const scalar T
		) const
		{
			return Cp(p, T) - EquationOfState::CpMCv(p, T);
		}

		inline scalar Es
		(
			const scalar p,
			const scalar T
		) const
		{
			return Hs(p, T) - p / EquationOfState::rho(p, T);
		}

		inline scalar Ea
		(
			const scalar p,
			const scalar T
		) const
		{
			return Ha(p, T) - p / EquationOfState::rho(p, T);
		}


		// Derivative term used for Jacobian

			//- Derivative of Gibbs free energy w.r.t. temperature
		inline scalar dGdT(const scalar p, const scalar T) const;

		//- Temperature derivative of heat capacity at constant pressure
		inline scalar dCpdT(const scalar p, const scalar T) const;


		// I-O

			//- Write to Ostream
		void write(Ostream& os) const;


		// Member Operators

		inline void operator+=(const hConstThermo&);


		// Friend operators

		friend hConstThermo operator+ <EquationOfState>
			(
				const hConstThermo&,
				const hConstThermo&
				);

		friend hConstThermo operator* <EquationOfState>
			(
				const scalar,
				const hConstThermo&
				);

		friend hConstThermo operator== <EquationOfState>
			(
				const hConstThermo&,
				const hConstThermo&
				);


		// IOstream Operators

		friend Ostream& operator<< <EquationOfState>
			(
				Ostream&,
				const hConstThermo&
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <hConstThermoI.hxx>

#ifdef NoRepository
#include <hConstThermo.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_hConstThermo_Header
