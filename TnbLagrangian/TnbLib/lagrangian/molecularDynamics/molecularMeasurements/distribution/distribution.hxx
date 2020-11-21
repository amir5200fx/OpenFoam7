#pragma once
#ifndef _distribution_Header
#define _distribution_Header

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
	tnbLib::distribution

Description
	Accumulating histogram of values.  Specified bin resolution
	automatic generation of bins.

SourceFiles
	distributionI.H
	distribution.C

\*---------------------------------------------------------------------------*/

#include <Map.hxx>
#include <Pair.hxx>

#include <typeInfo.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class distribution;

	FoamLagrangian_EXPORT Ostream& operator<<(Ostream&, const distribution&);


	/*---------------------------------------------------------------------------*\
							Class distribution Declaration
	\*---------------------------------------------------------------------------*/

	class distribution
		:
		public Map<label>
	{
		// Private Data

		scalar binWidth_;


	public:

		//- Runtime type information

		//TypeName("distribution");
		static const char* typeName_() { return "distribution"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Static functions

			//- Write to file

		static FoamLagrangian_EXPORT void write
		(
			const fileName& file,
			const List<Pair<scalar>>& pairs
		);


		// Constructors

			//- Construct null
		FoamLagrangian_EXPORT distribution();

		//- Construct from binWidth
		FoamLagrangian_EXPORT distribution(const scalar binWidth);

		//- Copy constructor
		FoamLagrangian_EXPORT distribution(const distribution&);


		//- Destructor
		FoamLagrangian_EXPORT virtual ~distribution();


		// Member Functions

		FoamLagrangian_EXPORT label totalEntries() const;

		FoamLagrangian_EXPORT scalar approxTotalEntries() const;

		FoamLagrangian_EXPORT scalar mean() const;

		FoamLagrangian_EXPORT scalar median();

		//- Add a value to the appropriate bin of the distribution.
		FoamLagrangian_EXPORT void add(const scalar valueToAdd);

		FoamLagrangian_EXPORT void add(const label valueToAdd);

		FoamLagrangian_EXPORT void insertMissingKeys();

		FoamLagrangian_EXPORT List<Pair<scalar>> normalised();

		FoamLagrangian_EXPORT List<Pair<scalar>> normalisedMinusMean();

		FoamLagrangian_EXPORT List<Pair<scalar>> normalisedShifted(scalar shiftValue);

		FoamLagrangian_EXPORT List<Pair<scalar>> raw();


		// Access

		inline scalar binWidth() const;


		// Member Operators

		FoamLagrangian_EXPORT void operator=(const distribution&);


		// IOstream Operators

		friend FoamLagrangian_EXPORT Ostream& operator<<(Ostream&, const distribution&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <distributionI.hxx>

#endif // !_distribution_Header
