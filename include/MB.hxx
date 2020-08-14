#pragma once
#ifndef _MB_Header
#define _MB_Header

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
	tnbLib::MB

Description
	Liquid nC3H7COOCH3 or (MB) methyl butyrate (used for biodiesel surrogate)

SourceFiles
	MB.C

\*---------------------------------------------------------------------------*/

#include <liquidProperties.hxx>
#include <NSRDSfunc0.hxx>
#include <NSRDSfunc1.hxx>
#include <NSRDSfunc2.hxx>
#include <NSRDSfunc3.hxx>
#include <NSRDSfunc4.hxx>
#include <NSRDSfunc5.hxx>
#include <NSRDSfunc6.hxx>
#include <NSRDSfunc7.hxx>
#include <NSRDSfunc14.hxx>
#include <APIdiffCoefFunc.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class MB Declaration
	\*---------------------------------------------------------------------------*/

	class MB
		:
		public liquidProperties
	{
		// Private Data

		NSRDSfunc5 rho_;
		NSRDSfunc1 pv_;
		NSRDSfunc6 hl_;
		NSRDSfunc0 Cp_;
		NSRDSfunc0 h_;
		NSRDSfunc7 Cpg_;
		NSRDSfunc4 B_;
		NSRDSfunc1 mu_;
		NSRDSfunc2 mug_;
		NSRDSfunc0 kappa_;
		NSRDSfunc2 kappag_;
		NSRDSfunc6 sigma_;
		APIdiffCoefFunc D_;


	public:

		friend class liquidProperties;

		//- Runtime type information
		TypeName("MB");


		// Constructors

			//- Construct null
		MB();

		//- Construct from components
		MB
		(
			const liquidProperties& l,
			const NSRDSfunc5& density,
			const NSRDSfunc1& vapourPressure,
			const NSRDSfunc6& heatOfVapourisation,
			const NSRDSfunc0& heatCapacity,
			const NSRDSfunc0& enthalpy,
			const NSRDSfunc7& idealGasHeatCapacity,
			const NSRDSfunc4& secondVirialCoeff,
			const NSRDSfunc1& dynamicViscosity,
			const NSRDSfunc2& vapourDynamicViscosity,
			const NSRDSfunc0& thermalConductivity,
			const NSRDSfunc2& vapourThermalConductivity,
			const NSRDSfunc6& surfaceTension,
			const APIdiffCoefFunc& vapourDiffussivity
		);

		//- Construct from dictionary
		MB(const dictionary& dict);

		//- Construct and return clone
		virtual autoPtr<liquidProperties> clone() const
		{
			return autoPtr<liquidProperties>(new MB(*this));
		}


		// Member Functions

			//- Liquid density [kg/m^3]
		inline scalar rho(scalar p, scalar T) const;

		//- Vapour pressure [Pa]
		inline scalar pv(scalar p, scalar T) const;

		//- Heat of vapourisation [J/kg]
		inline scalar hl(scalar p, scalar T) const;

		//- Liquid heat capacity [J/kg/K]
		inline scalar Cp(scalar p, scalar T) const;

		//- Liquid Enthalpy [J/kg]
		inline scalar h(scalar p, scalar T) const;

		//- Ideal gas heat capacity [J/kg/K]
		inline scalar Cpg(scalar p, scalar T) const;

		//- Second Virial Coefficient [m^3/kg]
		inline scalar B(scalar p, scalar T) const;

		//- Liquid viscosity [Pa s]
		inline scalar mu(scalar p, scalar T) const;

		//- Vapour viscosity [Pa s]
		inline scalar mug(scalar p, scalar T) const;

		//- Liquid thermal conductivity  [W/m/K]
		inline scalar kappa(scalar p, scalar T) const;

		//- Vapour thermal conductivity  [W/m/K]
		inline scalar kappag(scalar p, scalar T) const;

		//- Surface tension [N/m]
		inline scalar sigma(scalar p, scalar T) const;

		//- Vapour diffussivity [m2/s]
		inline scalar D(scalar p, scalar T) const;

		//- Vapour diffussivity [m2/s] with specified binary pair
		inline scalar D(scalar p, scalar T, scalar Wb) const;


		// I-O

			//- Write the function coefficients
		void writeData(Ostream& os) const;

		//- Ostream Operator
		friend Ostream& operator<<(Ostream& os, const MB& l);
	};


	Ostream& operator<<(Ostream& os, const MB& l);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <MBI.hxx>

#endif // !_MB_Header
