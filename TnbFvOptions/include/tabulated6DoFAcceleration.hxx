#pragma once
#ifndef _tabulated6DoFAcceleration_Header
#define _tabulated6DoFAcceleration_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
	tnbLib::tabulated6DoFAcceleration

Description
	Tabulated 6DoF acceleration.

	Obtained by interpolating tabulated data for linear acceleration,
	angular velocity and angular acceleration.

SourceFiles
	tabulated6DoFAcceleration.C

\*---------------------------------------------------------------------------*/

#include <FvOptions_Module.hxx>
#include <primitiveFields.hxx>
#include <Vector2DTemplate.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class tabulated6DoFAcceleration Declaration
	\*---------------------------------------------------------------------------*/

	class tabulated6DoFAcceleration
	{
		// Private Data

		const Time& time_;

		dictionary accelerationCoeffs_;

		//- Time data file name read from dictionary
		fileName timeDataFileName_;

		//- Type used to read in the acceleration "vectors"
		typedef Vector<vector> accelerationVectors;

		//- Field of times
		scalarField times_;

		//- Field of acceleration "vectors"
		Field<accelerationVectors> values_;


	public:

		//- Runtime type information
		//TypeName("tabulated6DoFAcceleration");
		static const char* typeName_() { return "tabulated6DoFAcceleration"; }
		static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
		static FoamFvOptions_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamFvOptions_EXPORT tabulated6DoFAcceleration
		(
			const dictionary& accelerationCoeffs,
			const Time& runTime
		);

		//- Disallow default bitwise copy construction
		FoamFvOptions_EXPORT tabulated6DoFAcceleration(const tabulated6DoFAcceleration&);


		//- Destructor
		FoamFvOptions_EXPORT virtual ~tabulated6DoFAcceleration();


		// Member Functions

			//- Return the solid-body accelerations
		FoamFvOptions_EXPORT virtual Vector<vector> acceleration() const;

		//- Update properties from given dictionary
		FoamFvOptions_EXPORT virtual bool read(const dictionary& accelerationCoeffs);


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const tabulated6DoFAcceleration&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_tabulated6DoFAcceleration_Header
