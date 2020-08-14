#pragma once
#ifndef _chemistrySolver_Header
#define _chemistrySolver_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::chemistrySolver

Description
	An abstract base class for solving chemistry

SourceFiles
	chemistrySolver.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <scalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class chemistrySolver Declaration
	\*---------------------------------------------------------------------------*/

	template<class ChemistryModel>
	class chemistrySolver
		:
		public ChemistryModel
	{

	public:

		// Constructors

			//- Construct from thermo
		chemistrySolver(typename ChemistryModel::reactionThermo& thermo);


		//- Destructor
		virtual ~chemistrySolver();


		// Member Functions

			//- Update the concentrations and return the chemical time
		virtual void solve
		(
			scalarField &c,
			scalar& T,
			scalar& p,
			scalar& deltaT,
			scalar& subDeltaT
		) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <chemistrySolver.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_chemistrySolver_Header
