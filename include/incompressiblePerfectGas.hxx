#pragma once
#ifndef _incompressiblePerfectGas_Header
#define _incompressiblePerfectGas_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::incompressiblePerfectGas

Description
	Incompressible gas equation of state using a constant reference pressure in
	the perfect gas equation of state rather than the local pressure so that the
	density only varies with temperature and composition.

SourceFiles
	incompressiblePerfectGasI.H
	incompressiblePerfectGas.C

\*---------------------------------------------------------------------------*/

#include <autoPtr.hxx>
#include <scalar.hxx>  // added by amir
#include <word.hxx>  // added by amir
#include <Ostream.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	template<class Specie> class incompressiblePerfectGas;

	template<class Specie>
	inline incompressiblePerfectGas<Specie> operator+
		(
			const incompressiblePerfectGas<Specie>&,
			const incompressiblePerfectGas<Specie>&
			);

	template<class Specie>
	inline incompressiblePerfectGas<Specie> operator*
		(
			const scalar,
			const incompressiblePerfectGas<Specie>&
			);

	template<class Specie>
	inline incompressiblePerfectGas<Specie> operator==
		(
			const incompressiblePerfectGas<Specie>&,
			const incompressiblePerfectGas<Specie>&
			);

	template<class Specie>
	Ostream& operator<<
		(
			Ostream&,
			const incompressiblePerfectGas<Specie>&
			);


	/*---------------------------------------------------------------------------*\
						Class incompressiblePerfectGas Declaration
	\*---------------------------------------------------------------------------*/

	template<class Specie>
	class incompressiblePerfectGas
		:
		public Specie
	{
		// Private Data

			//- Reference pressure
		scalar pRef_;


	public:

		// Constructors

			//- Construct from components
		inline incompressiblePerfectGas(const Specie& sp, const scalar pRef);

		//- Construct from dictionary
		incompressiblePerfectGas(const dictionary& dict);

		//- Construct as named copy
		inline incompressiblePerfectGas
		(
			const word& name,
			const incompressiblePerfectGas&
		);

		//- Construct and return a clone
		inline autoPtr<incompressiblePerfectGas> clone() const;

		// Selector from dictionary
		inline static autoPtr<incompressiblePerfectGas> New
		(
			const dictionary& dict
		);


		// Member Functions

			//- Return the instantiated type name
		static word typeName()
		{
			return
				"incompressiblePerfectGas<"
				+ word(Specie::typeName_()) + '>';
		}


		// Fundamental properties

			//- Is the equation of state is incompressible i.e. rho != f(p)
		static const bool incompressible = true;

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

		inline void operator+=(const incompressiblePerfectGas&);
		inline void operator*=(const scalar);


		// Friend operators

		friend incompressiblePerfectGas operator+ <Specie>
			(
				const incompressiblePerfectGas&,
				const incompressiblePerfectGas&
				);

		friend incompressiblePerfectGas operator* <Specie>
			(
				const scalar s,
				const incompressiblePerfectGas&
				);

		friend incompressiblePerfectGas operator== <Specie>
			(
				const incompressiblePerfectGas&,
				const incompressiblePerfectGas&
				);


		// Ostream Operator

		friend Ostream& operator<< <Specie>
			(
				Ostream&,
				const incompressiblePerfectGas&
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <incompressiblePerfectGasI.hxx>

#endif // !_incompressiblePerfectGas_Header
