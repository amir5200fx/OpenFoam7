#pragma once
#ifndef _dimensionSet_Header
#define _dimensionSet_Header

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
	tnbLib::dimensionSet

Description
	Dimension set for the base types.

	This type may be used to implement rigorous dimension checking
	for algebraic manipulation.

SourceFiles
	dimensionSet.C
	dimensionSetIO.C
	dimensionSets.C

\*---------------------------------------------------------------------------*/

#include <bool.hxx>
#include <dimensionedScalarFwd.hxx>
#include <className.hxx>
#include <scalarField.hxx>
#include <PtrList.hxx>
#include <HashTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class dimensionSet;
	class dimensionSets;

	// Friend Functions

	FoamBase_EXPORT dimensionSet max(const dimensionSet&, const dimensionSet&);
	FoamBase_EXPORT dimensionSet min(const dimensionSet&, const dimensionSet&);
	FoamBase_EXPORT dimensionSet cmptMultiply(const dimensionSet&, const dimensionSet&);
	FoamBase_EXPORT dimensionSet cmptDivide(const dimensionSet&, const dimensionSet&);

	FoamBase_EXPORT dimensionSet pow(const dimensionSet&, const scalar);
	FoamBase_EXPORT dimensionSet pow(const dimensionSet&, const dimensionedScalar&);
	FoamBase_EXPORT dimensionSet pow(const dimensionedScalar&, const dimensionSet&);

	FoamBase_EXPORT dimensionSet sqr(const dimensionSet&);
	FoamBase_EXPORT dimensionSet pow3(const dimensionSet&);
	FoamBase_EXPORT dimensionSet pow4(const dimensionSet&);
	FoamBase_EXPORT dimensionSet pow5(const dimensionSet&);
	FoamBase_EXPORT dimensionSet pow6(const dimensionSet&);
	FoamBase_EXPORT dimensionSet pow025(const dimensionSet&);

	FoamBase_EXPORT dimensionSet sqrt(const dimensionSet&);
	FoamBase_EXPORT dimensionSet cbrt(const dimensionSet&);
	FoamBase_EXPORT dimensionSet magSqr(const dimensionSet&);
	FoamBase_EXPORT dimensionSet mag(const dimensionSet&);
	FoamBase_EXPORT dimensionSet sign(const dimensionSet&);
	FoamBase_EXPORT dimensionSet pos(const dimensionSet&);
	FoamBase_EXPORT dimensionSet pos0(const dimensionSet&);
	FoamBase_EXPORT dimensionSet neg(const dimensionSet&);
	FoamBase_EXPORT dimensionSet neg0(const dimensionSet&);
	FoamBase_EXPORT dimensionSet posPart(const dimensionSet&);
	FoamBase_EXPORT dimensionSet negPart(const dimensionSet&);
	FoamBase_EXPORT dimensionSet inv(const dimensionSet&);

	// Function to check the argument is dimensionless
	//  for transcendental functions
	FoamBase_EXPORT dimensionSet trans(const dimensionSet&);

	FoamBase_EXPORT dimensionSet atan2(const dimensionSet&, const dimensionSet&);

	// Return the argument; transformations do not change the dimensions
	FoamBase_EXPORT dimensionSet transform(const dimensionSet&);

	// Friend operators

	FoamBase_EXPORT dimensionSet operator-(const dimensionSet&);
	FoamBase_EXPORT dimensionSet operator+(const dimensionSet&, const dimensionSet&);
	FoamBase_EXPORT dimensionSet operator-(const dimensionSet&, const dimensionSet&);
	FoamBase_EXPORT dimensionSet operator*(const dimensionSet&, const dimensionSet&);
	FoamBase_EXPORT dimensionSet operator/(const dimensionSet&, const dimensionSet&);
	FoamBase_EXPORT dimensionSet operator&(const dimensionSet&, const dimensionSet&);
	FoamBase_EXPORT dimensionSet operator^(const dimensionSet&, const dimensionSet&);
	FoamBase_EXPORT dimensionSet operator&&(const dimensionSet&, const dimensionSet&);

	// IOstream Operators

	FoamBase_EXPORT Istream& operator>>(Istream&, dimensionSet&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const dimensionSet&);


	/*---------------------------------------------------------------------------*\
							Class dimensionSet Declaration
	\*---------------------------------------------------------------------------*/

	class dimensionSet
	{

	public:

		// Member constants

		enum
		{
			nDimensions = 7    // Number of dimensions in SI is 7
		};

		//- Define an enumeration for the names of the dimension exponents
		enum dimensionType
		{
			MASS,               // kilogram   kg
			LENGTH,             // metre      m
			TIME,               // second     s
			TEMPERATURE,        // Kelvin     K
			MOLES,              // mole       mol
			CURRENT,            // Ampere     A
			LUMINOUS_INTENSITY  // Candela    Cd
		};


		// Static Data Members

		static FoamBase_EXPORT const scalar smallExponent;


	private:

		// Private classes

		class tokeniser
		{
			// Private Data

			Istream& is_;

			List<token> tokens_;

			label start_;

			label size_;


			// Private Member Functions

			FoamBase_EXPORT void push(const token&);

			FoamBase_EXPORT token pop();

			FoamBase_EXPORT void unpop(const token&);

		public:

			// Constructors

			FoamBase_EXPORT tokeniser(Istream&);


			// Member Functions

			Istream& stream()
			{
				return is_;
			}

			FoamBase_EXPORT bool hasToken() const;

			FoamBase_EXPORT token nextToken();

			FoamBase_EXPORT void putBack(const token&);

			FoamBase_EXPORT void splitWord(const word&);

			static FoamBase_EXPORT bool valid(char c);

			static FoamBase_EXPORT label priority(const token& t);
		};


		//- Reset exponents to nearest integer if close to it. Used to
		//  handle reading with insufficient precision.
		FoamBase_EXPORT void round(const scalar tol);

		FoamBase_EXPORT dimensionedScalar parse
		(
			const label lastPrior,
			tokeniser& tis,
			const HashTable<dimensionedScalar>&
		) const;


		// private data

			// dimensionSet stored as an array of dimension exponents
		scalar exponents_[nDimensions];


	public:

		// Declare name of the class and its debug switch
		//ClassName("dimensionSet");
		static const char* typeName_() { return "dimensionSet"; } 
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;


		// Constructors

			//- Construct given individual dimension exponents for all
			//  seven dimensions
		FoamBase_EXPORT dimensionSet
		(
			const scalar mass,
			const scalar length,
			const scalar time,
			const scalar temperature,
			const scalar moles,
			const scalar current,
			const scalar luminousIntensity
		);

		//- Construct given individual dimension exponents for first
		//  five dimensions
		FoamBase_EXPORT dimensionSet
		(
			const scalar mass,
			const scalar length,
			const scalar time,
			const scalar temperature,
			const scalar moles
		);

		//- Copy constructor
		FoamBase_EXPORT dimensionSet(const dimensionSet& ds);

		//- Construct and return a clone
		autoPtr<dimensionSet> clone() const
		{
			return autoPtr<dimensionSet>(new dimensionSet(*this));
		}

		//- Construct from Istream
		FoamBase_EXPORT dimensionSet(Istream&);


		// Member Functions

			//- Return true if it is dimensionless
		FoamBase_EXPORT bool dimensionless() const;

		FoamBase_EXPORT void reset(const dimensionSet&);


		// I/O

			//- Read using provided units. Used only in initial parsing
		FoamBase_EXPORT Istream& read
		(
			Istream& is,
			scalar& multiplier,
			const dictionary&
		);

		//- Read using provided units
		FoamBase_EXPORT Istream& read
		(
			Istream& is,
			scalar& multiplier,
			const HashTable<dimensionedScalar>&
		);

		//- Read using system units
		FoamBase_EXPORT Istream& read
		(
			Istream& is,
			scalar& multiplier
		);

		//- Write using provided units
		FoamBase_EXPORT Ostream& write
		(
			Ostream& os,
			scalar& multiplier,
			const dimensionSets&
		) const;

		//- Write using system units
		FoamBase_EXPORT Ostream& write
		(
			Ostream& os,
			scalar& multiplier
		) const;


		// Member Operators

		FoamBase_EXPORT scalar operator[](const dimensionType) const;
		FoamBase_EXPORT scalar& operator[](const dimensionType);

		FoamBase_EXPORT scalar operator[](const label) const;
		FoamBase_EXPORT scalar& operator[](const label);

		FoamBase_EXPORT bool operator==(const dimensionSet&) const;
		FoamBase_EXPORT bool operator!=(const dimensionSet&) const;

		FoamBase_EXPORT bool operator=(const dimensionSet&) const;

		FoamBase_EXPORT bool operator+=(const dimensionSet&) const;
		FoamBase_EXPORT bool operator-=(const dimensionSet&) const;
		FoamBase_EXPORT bool operator*=(const dimensionSet&);
		FoamBase_EXPORT bool operator/=(const dimensionSet&);


		// Friend Functions

		friend FoamBase_EXPORT dimensionSet max(const dimensionSet&, const dimensionSet&);
		friend FoamBase_EXPORT dimensionSet min(const dimensionSet&, const dimensionSet&);
		friend FoamBase_EXPORT dimensionSet cmptMultiply
		(
			const dimensionSet&,
			const dimensionSet&
		);
		friend FoamBase_EXPORT dimensionSet cmptDivide
		(
			const dimensionSet&,
			const dimensionSet&
		);

		friend FoamBase_EXPORT dimensionSet pow(const dimensionSet&, const scalar);
		friend FoamBase_EXPORT dimensionSet pow(const dimensionSet&, const dimensionedScalar&);
		friend FoamBase_EXPORT dimensionSet pow(const dimensionedScalar&, const dimensionSet&);

		friend FoamBase_EXPORT dimensionSet sqr(const dimensionSet&);
		friend FoamBase_EXPORT dimensionSet pow3(const dimensionSet&);
		friend FoamBase_EXPORT dimensionSet pow4(const dimensionSet&);
		friend FoamBase_EXPORT dimensionSet pow5(const dimensionSet&);
		friend FoamBase_EXPORT dimensionSet pow6(const dimensionSet&);
		friend FoamBase_EXPORT dimensionSet pow025(const dimensionSet&);

		friend FoamBase_EXPORT dimensionSet sqrt(const dimensionSet&);
		friend FoamBase_EXPORT dimensionSet magSqr(const dimensionSet&);
		friend FoamBase_EXPORT dimensionSet mag(const dimensionSet&);
		friend FoamBase_EXPORT dimensionSet sign(const dimensionSet&);
		friend FoamBase_EXPORT dimensionSet pos0(const dimensionSet&);
		friend FoamBase_EXPORT dimensionSet neg(const dimensionSet&);
		friend FoamBase_EXPORT dimensionSet inv(const dimensionSet&);

		//- Function to check the argument is dimensionless
		//  for transcendental functions
		friend FoamBase_EXPORT dimensionSet trans(const dimensionSet&);

		friend FoamBase_EXPORT dimensionSet atan2(const dimensionSet&, const dimensionSet&);

		//- Return the argument; transformations do not change the dimensions
		friend FoamBase_EXPORT dimensionSet transform(const dimensionSet&);


		// Friend operators

		friend FoamBase_EXPORT dimensionSet operator-(const dimensionSet&);

		friend FoamBase_EXPORT dimensionSet operator+
			(
				const dimensionSet&,
				const dimensionSet&
				);

		friend FoamBase_EXPORT dimensionSet operator-
			(
				const dimensionSet&,
				const dimensionSet&
				);

		friend FoamBase_EXPORT dimensionSet operator*
			(
				const dimensionSet&,
				const dimensionSet&
				);

		friend FoamBase_EXPORT dimensionSet operator/
			(
				const dimensionSet&,
				const dimensionSet&
				);

		friend FoamBase_EXPORT dimensionSet operator&
			(
				const dimensionSet&,
				const dimensionSet&
				);

		friend FoamBase_EXPORT dimensionSet operator^
			(
				const dimensionSet&,
				const dimensionSet&
				);

		friend FoamBase_EXPORT dimensionSet operator&&
			(
				const dimensionSet&,
				const dimensionSet&
				);


		// IOstream Operators

		friend FoamBase_EXPORT Istream& operator>>(Istream&, dimensionSet&);
		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const dimensionSet&);
	};


	FoamBase_EXPORT void writeEntry(Ostream& os, const dimensionSet& value);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <dimensionSets.hxx>

#endif // !_dimensionSet_Header
