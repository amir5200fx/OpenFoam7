#pragma once
#ifndef _thermophysicalFunction_Header
#define _thermophysicalFunction_Header

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
	tnbLib::thermophysicalFunction

Description
	Abstract base class for thermo-physical functions

\*---------------------------------------------------------------------------*/

#include <scalar.hxx>
#include <IOstreams.hxx>
#include <typeInfo.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class thermophysicalFunction Declaration
	\*---------------------------------------------------------------------------*/

	class thermophysicalFunction
	{

	public:

		//- Runtime type information
		TypeName("thermophysicalFunction");


		// Declare run-time constructor selection tables

		declareRunTimeSelectionTable
		(
			autoPtr,
			thermophysicalFunction,
			dictionary,
			(const dictionary& dict),
			(dict)
		);


		// Constructors

			//- Construct null
		thermophysicalFunction()
		{}

		//- Return pointer to new thermophysicalFunction created from dict
		static autoPtr<thermophysicalFunction> New(const dictionary& dict);


		//- Destructor
		virtual ~thermophysicalFunction()
		{}


		// Member Functions

			//- Evaluate the function and return the result
		virtual scalar f(scalar p, scalar T) const = 0;

		//- Write the function coefficients
		virtual void writeData(Ostream& os) const = 0;


		// Ostream Operator

		friend Ostream& operator<<(Ostream& os, const thermophysicalFunction& f)
		{
			f.writeData(os);
			return os;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_thermophysicalFunction_Header
