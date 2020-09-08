#pragma once
#ifndef _noChemistrySolver_Header
#define _noChemistrySolver_Header

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
	tnbLib::noChemistrySolver

Description
	Dummy chemistry solver for 'none' option

SourceFiles
	noChemistrySolver.H
	noChemistrySolver.C

\*---------------------------------------------------------------------------*/

#include <chemistrySolver.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class noChemistrySolver Declaration
	\*---------------------------------------------------------------------------*/

	template<class ChemistryModel>
	class noChemistrySolver
		:
		public chemistrySolver<ChemistryModel>
	{

	public:

		//- Runtime type information
		TypeName("none");


		// Constructors

			//- Construct from thermo
		noChemistrySolver(typename ChemistryModel::reactionThermo& thermo);


		//- Destructor
		virtual ~noChemistrySolver();


		// Member Functions

			//- Update the concentrations and return the chemical time
		virtual void solve
		(
			scalarField& c,
			scalar& T,
			scalar& p,
			scalar& deltaT,
			scalar& subDeltaT
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <noChemistrySolverI.hxx>

//#ifdef NoRepository
//#include <noChemistrySolver.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noChemistrySolver_Header
