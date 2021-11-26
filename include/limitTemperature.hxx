#pragma once
#ifndef _limitTemperature_Header
#define _limitTemperature_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::fv::limitTemperature

Description
	Correction for temperature to apply limits between minimum and maximum
	values.

Usage
	Example usage:
	\verbatim
	limitT
	{
		type            limitTemperature;
		active          yes;

		selectionMode   all;
		min             200;
		max             500;
		phase           gas; // optional
	}
	\endverbatim

SourceFiles
	limitTemperature.C

\*---------------------------------------------------------------------------*/

#include <cellSetOption.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
						 Class limitTemperature Declaration
		\*---------------------------------------------------------------------------*/

		class limitTemperature
			:
			public cellSetOption
		{
		protected:

			// Protected data

				//- Minimum temperature limit [K]
			scalar Tmin_;

			//- Maximum temperature limit [K]
			scalar Tmax_;

			//- Optional phase name [K]
			word phase_;


		public:

			//- Runtime type information
			//TypeName("limitTemperature");
			static const char* typeName_() { return "limitTemperature"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvOptions_EXPORT limitTemperature
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);

			//- Disallow default bitwise copy construction
			FoamFvOptions_EXPORT limitTemperature(const limitTemperature&) = delete;


			//- Destructor
			virtual ~limitTemperature()
			{}


			// Member Functions

				//- Read dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);

			//- Correct the energy field
			FoamFvOptions_EXPORT virtual void correct(volScalarField& he);


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFvOptions_EXPORT void operator=(const limitTemperature&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_limitTemperature_Header
