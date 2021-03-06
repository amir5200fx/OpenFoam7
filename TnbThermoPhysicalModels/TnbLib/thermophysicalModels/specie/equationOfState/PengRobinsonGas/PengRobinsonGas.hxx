#pragma once
#ifndef _PengRobinsonGas_Header
#define _PengRobinsonGas_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2014-2019 OpenFOAM Foundation
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
	tnbLib::PengRobinsonGas

Description
	PengRobinsonGas gas equation of state.

SourceFiles
	PengRobinsonGasI.H
	PengRobinsonGas.C

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

	template<class Specie> class PengRobinsonGas;

	template<class Specie>
	inline PengRobinsonGas<Specie> operator+
		(
			const PengRobinsonGas<Specie>&,
			const PengRobinsonGas<Specie>&
			);

	template<class Specie>
	inline PengRobinsonGas<Specie> operator*
		(
			const scalar,
			const PengRobinsonGas<Specie>&
			);

	template<class Specie>
	inline PengRobinsonGas<Specie> operator==
		(
			const PengRobinsonGas<Specie>&,
			const PengRobinsonGas<Specie>&
			);

	template<class Specie>
	Ostream& operator<<
		(
			Ostream&,
			const PengRobinsonGas<Specie>&
			);



	/*---------------------------------------------------------------------------*\
							   Class PengRobinsonGas Declaration
	\*---------------------------------------------------------------------------*/

	template<class Specie>
	class PengRobinsonGas
		:
		public Specie
	{
		// Private Data

			//- Critical Temperature [K]
		scalar Tc_;

		//- Critical volume [m^3/kmol]
		scalar Vc_;

		//- Critical compression factor [-]
		scalar Zc_;

		//- Critical Pressure [Pa]
		scalar Pc_;

		//- Acentric factor [-]
		scalar omega_;


	public:

		// Constructors

			//- Construct from components
		inline PengRobinsonGas
		(
			const Specie& sp,
			const scalar& Tc,
			const scalar& Vc,
			const scalar& Zc,
			const scalar& Pc,
			const scalar& omega
		);

		//- Construct from dictionary
		PengRobinsonGas(const dictionary& dict);

		//- Construct as named copy
		inline PengRobinsonGas(const word& name, const PengRobinsonGas&);

		//- Construct and return a clone
		inline autoPtr<PengRobinsonGas> clone() const;

		// Selector from dictionary
		inline static autoPtr<PengRobinsonGas> New
		(
			const dictionary& dict
		);


		// Member Functions

			//- Return the instantiated type name
		static word typeName()
		{
			return "PengRobinsonGas<" + word(Specie::typeName_()) + '>';
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

		inline void operator+=(const PengRobinsonGas&);
		inline void operator*=(const scalar);


		// Friend operators

		friend PengRobinsonGas operator+ <Specie>
			(
				const PengRobinsonGas&,
				const PengRobinsonGas&
				);

		friend PengRobinsonGas operator* <Specie>
			(
				const scalar s,
				const PengRobinsonGas&
				);

		friend PengRobinsonGas operator== <Specie>
			(
				const PengRobinsonGas&,
				const PengRobinsonGas&
				);


		// Ostream Operator

		friend Ostream& operator<< <Specie>
			(
				Ostream&,
				const PengRobinsonGas&
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <PengRobinsonGasI.hxx>

#endif // !_PengRobinsonGas_Header
