#pragma once
#ifndef _IDEA_Header
#define _IDEA_Header

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
	tnbLib::IDEA

Description
	The IDEA fuel is constructed by adding 30% alphaMethylNaphthalene
	with 70% n-decane.

	The new properties have been calculated by adding the values in these
	proportions and making a least square fit, using the same NSRDS-eq.
	so that Y = 0.3*Y_naphthalene + 0.7*Y_decane

	The valid Temperature range for n-decane is normally 243.51 - 617.70 K
	and for the naphthalene it is 242.67 - 772.04 K
	The least square fit was done in the interval 244 - 617 K

	The critical temperature was taken to be 618.074 K, since this
	is the 'c'-value in the rho-equation, which corresponds to Tcrit,
	This value was then used in the fit for the NSRDS6-eq, which uses Tcrit.
	(important for the latent heat and surface tension)

	The molecular weights are 142.20 and 142.285 and for the IDEA fuel
	it is thus 142.26 ( approximately 0.3*142.2 + 0.7*142.285 )

	Critical pressure was set to the lowest one (n-Decane)

	Critical volume... also the lowest one (naphthalene) 0.523 m^3/kmol

	Second Virial Coefficient is n-Decane

SourceFiles
	IDEA.C

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
							   Class IDEA Declaration
	\*---------------------------------------------------------------------------*/

	class IDEA
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
		//TypeName("IDEA");
		static const char* typeName_() { return "IDEA"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct null
		FoamThermophysicalModels_EXPORT IDEA();

		// Construct from components
		FoamThermophysicalModels_EXPORT IDEA
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
		FoamThermophysicalModels_EXPORT IDEA(const dictionary& dict);

		//- Construct and return clone
		virtual autoPtr<liquidProperties> clone() const
		{
			return autoPtr<liquidProperties>(new IDEA(*this));
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
		FoamThermophysicalModels_EXPORT void writeData(Ostream& os) const;

		//- Ostream Operator
		friend FoamThermophysicalModels_EXPORT Ostream& operator<<(Ostream& os, const IDEA& l);
	};


	FoamThermophysicalModels_EXPORT Ostream& operator<<(Ostream& os, const IDEA& l);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <IDEAI.hxx>

#endif // !_IDEA_Header
