#pragma once
#ifndef _perfectGas_Header
#define _perfectGas_Header

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
	tnbLib::perfectGas

Description
	Perfect gas equation of state.

SourceFiles
	perfectGasI.H
	perfectGas.C

\*---------------------------------------------------------------------------*/

#include <autoPtr.hxx>
#include <scalar.hxx>  // added by amir
#include <Ostream.hxx>  // added by amir
#include <word.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators
	class dictionary;  // added by amir

	template<class Specie> class perfectGas;

	template<class Specie>
	inline perfectGas<Specie> operator+
		(
			const perfectGas<Specie>&,
			const perfectGas<Specie>&
			);

	template<class Specie>
	inline perfectGas<Specie> operator*
		(
			const scalar,
			const perfectGas<Specie>&
			);

	template<class Specie>
	inline perfectGas<Specie> operator==
		(
			const perfectGas<Specie>&,
			const perfectGas<Specie>&
			);

	template<class Specie>
	Ostream& operator<<
		(
			Ostream&,
			const perfectGas<Specie>&
			);


	/*---------------------------------------------------------------------------*\
							   Class perfectGas Declaration
	\*---------------------------------------------------------------------------*/

	template<class Specie>
	class perfectGas
		:
		public Specie
	{

	public:

		// Constructors

			//- Construct from components
		inline perfectGas(const Specie& sp);

		//- Construct from dictionary
		perfectGas(const dictionary& dict);

		//- Construct as named copy
		inline perfectGas(const word& name, const perfectGas&);

		//- Construct and return a clone
		inline autoPtr<perfectGas> clone() const;

		// Selector from dictionary
		inline static autoPtr<perfectGas> New(const dictionary& dict);


		// Member Functions

			//- Return the instantiated type name
		static word typeName()
		{
			return "perfectGas<" + word(Specie::typeName_()) + '>';
		}


		// Fundamental properties

			//- Is the equation of state is incompressible i.e. rho != f(p)
		static const bool incompressible = false;

		//- Is the equation of state is isochoric i.e. rho = const
		static const bool isochoric = false;

		//- Return density [kg/m^3]
		inline scalar rho(scalar p, scalar T) const;

		//- Return enthalpy departure [J/kg]
		inline scalar H(const scalar p, const scalar T) const;

		//- Return Cp departure [J/(kg K]
		inline scalar Cp(scalar p, scalar T) const;

		//- Return internal energy departure [J/kg]
		inline scalar E(const scalar p, const scalar T) const;

		//- Return Cv departure [J/(kg K]
		inline scalar Cv(scalar p, scalar T) const;

		//- Return entropy [J/kg/K]
		inline scalar S(const scalar p, const scalar T) const;

		//- Return compressibility rho/p [s^2/m^2]
		inline scalar psi(scalar p, scalar T) const;

		//- Return compression factor []
		inline scalar Z(scalar p, scalar T) const;

		//- Return (Cp - Cv) [J/(kg K]
		inline scalar CpMCv(scalar p, scalar T) const;


		// IO

			//- Write to Ostream
		void write(Ostream& os) const;


		// Member Operators

		inline void operator+=(const perfectGas&);
		inline void operator*=(const scalar);


		// Friend operators

		friend perfectGas operator+ <Specie>
			(
				const perfectGas&,
				const perfectGas&
				);

		friend perfectGas operator* <Specie>
			(
				const scalar s,
				const perfectGas&
				);

		friend perfectGas operator== <Specie>
			(
				const perfectGas&,
				const perfectGas&
				);


		// Ostream Operator

		friend Ostream& operator<< <Specie>
			(
				Ostream&,
				const perfectGas&
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <perfectGasI.hxx>

#endif // !_perfectGas_Header