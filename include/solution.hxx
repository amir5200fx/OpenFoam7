#pragma once
#ifndef _solution_Header
#define _solution_Header

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
	tnbLib::solution

Description
	Selector class for relaxation factors, solver type and solution.

SourceFiles
	solution.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							  Class solution Declaration
	\*---------------------------------------------------------------------------*/

	class solution
		:
		public IOdictionary
	{
		// Private Data

			//- Dictionary of temporary fields to cache
		dictionary cache_;

		//- Switch for the caching mechanism
		bool caching_;

		//- Dictionary of relaxation factors for all the fields
		dictionary fieldRelaxDict_;

		//- Dictionary of relaxation factors for all the equations
		dictionary eqnRelaxDict_;

		//- Optional default relaxation factor for all the fields
		scalar fieldRelaxDefault_;

		//- Optional default relaxation factor for all the equations
		scalar eqnRelaxDefault_;

		//- Dictionary of solver parameters for all the fields
		dictionary solvers_;


		// Private Member Functions

			//- Read settings from the dictionary
		FoamBase_EXPORT void read(const dictionary&);


	public:

		//- Update from older solver controls syntax
		//  Usually verbose, since we want to know about the changes
		//  Returns the number of settings changed
		static FoamBase_EXPORT label upgradeSolverDict(dictionary& dict, const bool verbose = true);

		//- Debug switch
		static FoamBase_EXPORT int debug;


		// Constructors

			//- Construct for given objectRegistry and dictionary
		FoamBase_EXPORT solution
		(
			const objectRegistry& obr,
			const fileName& dictName
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT solution(const solution&) = delete;


		// Member Functions

			// Access

				//- Return true if the given field should be cached
		FoamBase_EXPORT bool cache(const word& name) const;

		//- Helper for printing cache message
		template<class FieldType>
		static void cachePrintMessage
		(
			const char* message,
			const word& name,
			const FieldType& vf
		);

		//- Return true if the relaxation factor is given for the field
		FoamBase_EXPORT bool relaxField(const word& name) const;

		//- Return true if the relaxation factor is given for the equation
		FoamBase_EXPORT bool relaxEquation(const word& name) const;

		//- Return the relaxation factor for the given field
		FoamBase_EXPORT scalar fieldRelaxationFactor(const word& name) const;

		//- Return the relaxation factor for the given eqation
		FoamBase_EXPORT scalar equationRelaxationFactor(const word& name) const;

		//- Return the selected sub-dictionary of solvers if the "select"
		//  keyword is given, otherwise return the complete dictionary
		FoamBase_EXPORT const dictionary& solutionDict() const;

		//- Return the solver controls dictionary for the given field
		FoamBase_EXPORT const dictionary& solverDict(const word& name) const;


		// Read

			//- Read the solution dictionary
		FoamBase_EXPORT bool read();


		// Member Operators

		FoamBase_EXPORT void operator=(const solution&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <solutionTemplatesI.hxx>

//#ifdef NoRepository
//#include <solutionTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_solution_Header
