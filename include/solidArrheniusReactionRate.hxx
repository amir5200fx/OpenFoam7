#pragma once
#ifndef _solidArrheniusReactionRate_Header
#define _solidArrheniusReactionRate_Header

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
	tnbLib::solidArrheniusReactionRate

Description
	Arrhenius reaction rate for solids

SourceFiles
	solidArrheniusReactionRateI.H

\*---------------------------------------------------------------------------*/

#include <scalarField.hxx>
#include <typeInfo.hxx>
#include <speciesTable.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class solidArrheniusReactionRate;

	Ostream& operator<<(Ostream&, const solidArrheniusReactionRate&);


	/*---------------------------------------------------------------------------*\
						   Class solidArrheniusReactionRate Declaration
	\*---------------------------------------------------------------------------*/

	class solidArrheniusReactionRate
	{
		// Private Data

		scalar A_;
		scalar Ta_;
		scalar Tcrit_;


	public:

		// Constructors

			//- Construct from components
		inline solidArrheniusReactionRate
		(
			const scalar A,
			const scalar Ta,
			const scalar Tcrit
		);


		//- Construct from dictionary
		inline solidArrheniusReactionRate
		(
			const speciesTable& species,
			const dictionary& dict
		);


		//- Destructor
		virtual ~solidArrheniusReactionRate()
		{}


		// Member Functions

			//- Return the type name
		static word type()
		{
			return "Arrhenius";
		}

		inline scalar operator()
			(
				const scalar p,
				const scalar T,
				const scalarField& c
				) const;

		inline scalar ddT
		(
			const scalar p,
			const scalar T,
			const scalarField& c
		) const;

		//- Third-body efficiencies (beta = 1-alpha)
		//  non-empty only for third-body reactions
		//  with enhanced molecularity (alpha != 1)
		inline const List<Tuple2<label, scalar>>& beta() const;

		//- Species concentration derivative of the pressure dependent term
		//  By default this value is 1 as it multiplies the third-body term
		inline void dcidc
		(
			const scalar p,
			const scalar T,
			const scalarField& c,
			scalarField& dcidc
		) const;

		//- Temperature derivative of the pressure dependent term
		//  By default this value is 0 since ddT of molecularity is approx.0
		inline scalar dcidT
		(
			const scalar p,
			const scalar T,
			const scalarField& c
		) const;


		//- Write to stream
		inline void write(Ostream& os) const;


		// Ostream Operator

		inline friend Ostream& operator<<
			(
				Ostream&,
				const solidArrheniusReactionRate&
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <solidArrheniusReactionRateI.hxx>

#endif // !_solidArrheniusReactionRate_Header
