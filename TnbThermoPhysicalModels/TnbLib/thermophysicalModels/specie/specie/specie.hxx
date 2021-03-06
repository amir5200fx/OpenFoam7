#pragma once
#ifndef _specie_Header
#define _specie_Header

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
	tnbLib::specie

Description
	Base class of the thermophysical property types.

SourceFiles
	specieI.H
	specie.C

\*---------------------------------------------------------------------------*/

#include <word.hxx>
#include <scalar.hxx>
#include <dictionary.hxx>

#include <thermodynamicConstants.hxx>
using namespace tnbLib::constant::thermodynamic;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class specie;

	inline specie operator+(const specie&, const specie&);
	inline specie operator*(const scalar, const specie&);
	inline specie operator==(const specie&, const specie&);

	FoamThermophysicalModels_EXPORT Ostream& operator<<(Ostream&, const specie&);


	/*---------------------------------------------------------------------------*\
							   Class specie Declaration
	\*---------------------------------------------------------------------------*/

	class specie
	{
		// Private Data

			//- Name of specie
		word name_;

		//- Number of moles of this component in the mixture
		scalar Y_;

		//- Molecular weight of specie [kg/kmol]
		scalar molWeight_;


	public:

		//- Runtime type information
		//ClassName("specie");
		static const char* typeName_() { return "specie"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;


		// Constructors

			//- Construct from components without name
		inline specie(const scalar Y, const scalar molWeight);

		//- Construct from components with name
		inline specie
		(
			const word& name,
			const scalar Y,
			const scalar molWeight
		);

		//- Construct as named copy
		inline specie(const word& name, const specie&);

		//- Construct from dictionary
		FoamThermophysicalModels_EXPORT specie(const dictionary& dict);

		//- Copy constructor
		FoamThermophysicalModels_EXPORT specie(const specie&) = default;


		// Member Functions

			// Access

				//- Name
		inline const word& name() const;

		//- Molecular weight [kg/kmol]
		inline scalar W() const;

		//- No of moles of this species in mixture
		inline scalar Y() const;

		//- Gas constant [J/kg/K]
		inline scalar R() const;


		// I-O

			//- Write to Ostream
		FoamThermophysicalModels_EXPORT void write(Ostream& os) const;


		// Member Operators

		inline void operator=(const specie&);
		inline void operator+=(const specie&);
		inline void operator*=(const scalar);


		// Friend operators

		inline friend specie operator+(const specie&, const specie&);
		inline friend specie operator*(const scalar, const specie&);
		inline friend specie operator==(const specie&, const specie&);


		// Ostream Operator

		friend FoamThermophysicalModels_EXPORT Ostream& operator<<(Ostream&, const specie&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <specieI.hxx>

#endif // !_specie_Header
