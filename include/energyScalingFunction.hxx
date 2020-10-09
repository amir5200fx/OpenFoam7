#pragma once
#ifndef _energyScalingFunction_Header
#define _energyScalingFunction_Header

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
	tnbLib::energyScalingFunction

Description

SourceFiles
	energyScalingFunction.C
	energyScalingFunctionNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>
#include <autoPtr.hxx>
#include <pairPotential.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class energyScalingFunction Declaration
	\*---------------------------------------------------------------------------*/

	class energyScalingFunction
	{

	protected:

		// Protected data

		word name_;

		dictionary energyScalingFunctionProperties_;

		const pairPotential& pairPot_;


	public:

		//- Runtime type information
		TypeName("energyScalingFunction");


		// Declare run-time constructor selection table

		declareRunTimeSelectionTable
		(
			autoPtr,
			energyScalingFunction,
			dictionary,
			(
				const word& name,
				const dictionary& energyScalingFunctionProperties,
				const pairPotential& pairPot
				),
				(name, energyScalingFunctionProperties, pairPot)
		);


		// Selectors

			//- Return a reference to the selected viscosity model
		static autoPtr<energyScalingFunction> New
		(
			const word& name,
			const dictionary& energyScalingFunctionProperties,
			const pairPotential& pairPot
		);


		// Constructors

			//- Construct from components
		energyScalingFunction
		(
			const word& name,
			const dictionary& energyScalingFunctionProperties,
			const pairPotential& pairPot
		);

		//- Disallow default bitwise copy construction
		energyScalingFunction(const energyScalingFunction&);


		//- Destructor
		virtual ~energyScalingFunction()
		{}


		// Member Functions

		virtual void scaleEnergy(scalar& e, const scalar r) const = 0;

		const dictionary& energyScalingFunctionProperties() const
		{
			return energyScalingFunctionProperties_;
		}

		//- Read energyScalingFunction dictionary
		virtual bool read
		(
			const dictionary& energyScalingFunctionProperties
		) = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const energyScalingFunction&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_energyScalingFunction_Header