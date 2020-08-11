#pragma once
#ifndef _constAnIsoSolidTransport_Header
#define _constAnIsoSolidTransport_Header

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
	tnbLib::constAnIsoSolidTransport

Description
	Constant properties Transport package.
	Templated into a given Thermodynamics package (needed for thermal
	conductivity).

SourceFiles
	constAnIsoSolidTransportI.H
	constAnIsoSolidTransport.C

\*---------------------------------------------------------------------------*/

#include <vector.hxx>
#include <Ostream.hxx>  // added by amir
#include <autoPtr.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<class Thermo> class constAnIsoSolidTransport;

	template<class Thermo>
	inline constAnIsoSolidTransport<Thermo> operator*
		(
			const scalar,
			const constAnIsoSolidTransport<Thermo>&
			);

	template<class Thermo>
	Ostream& operator<<
		(
			Ostream&,
			const constAnIsoSolidTransport<Thermo>&
			);


	/*---------------------------------------------------------------------------*\
					   Class constAnIsoSolidTransport Declaration
	\*---------------------------------------------------------------------------*/

	template<class Thermo>
	class constAnIsoSolidTransport
		:
		public Thermo
	{
		// Private Data

			//- Constant anisotropic thermal conductivity.
		vector kappa_;


		// Private Member Functions

			//- Construct from components
		inline constAnIsoSolidTransport(const Thermo& t, const vector kappa);


	public:

		// Constructors

			//- Construct as named copy
		inline constAnIsoSolidTransport
		(
			const word&,
			const constAnIsoSolidTransport&
		);

		//- Construct from dictionary
		constAnIsoSolidTransport(const dictionary&);

		// Selector from dictionary
		inline static autoPtr<constAnIsoSolidTransport> New
		(
			const dictionary& dict
		);


		// Member Functions

			//- Return the instantiated type name
		static word typeName()
		{
			return "constAnIso<" + Thermo::typeName() + '>';
		}

		//- Is the thermal conductivity isotropic
		static const bool isotropic = false;

		//- Isotropic thermal conductivity [W/m/K]
		inline scalar kappa(const scalar p, const scalar T) const;

		//- Un-isotropic thermal conductivity [W/m/K]
		inline vector Kappa(const scalar p, const scalar T) const;

		//- Dynamic viscosity [kg/m/s]
		inline scalar mu(const scalar p, const scalar T) const;

		//- Thermal diffusivity of enthalpy [kg/m/s]
		inline vector alphah(const scalar p, const scalar T) const;


		//- Write to Ostream
		void write(Ostream& os) const;


		// Member Operators

		inline void operator+=(const constAnIsoSolidTransport&);


		// Friend operators

		friend constAnIsoSolidTransport operator* <Thermo>
			(
				const scalar,
				const constAnIsoSolidTransport&
				);


		// Ostream Operator

		friend Ostream& operator<< <Thermo>
			(
				Ostream&,
				const constAnIsoSolidTransport&
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <constAnIsoSolidTransportI.hxx>

#ifdef NoRepository
#include <constAnIsoSolidTransport.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_constAnIsoSolidTransport_Header
