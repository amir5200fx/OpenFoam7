#pragma once
#ifndef _limitVelocity_Header
#define _limitVelocity_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::fv::limitVelocity

Description
	Limits the maximum velocity magnitude to the specified \c max value.

Usage
	Example usage:
	\verbatim
	limitU
	{
		type            limitVelocity;
		active          yes;

		selectionMode   all;
		max             100;
	}
	\endverbatim

SourceFiles
	limitVelocity.C

\*---------------------------------------------------------------------------*/

#include <cellSetOption.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
						 Class limitVelocity Declaration
		\*---------------------------------------------------------------------------*/

		class limitVelocity
			:
			public cellSetOption
		{
		protected:

			// Protected data

				//- Velocity field name, default = U
			word UName_;

			//- Maximum velocity magnitude
			scalar max_;


		public:

			//- Runtime type information
			//TypeName("limitVelocity");
			static const char* typeName_() { return "limitVelocity"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvOptions_EXPORT limitVelocity
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);

			//- Disallow default bitwise copy construction
			FoamFvOptions_EXPORT limitVelocity(const limitVelocity&) = delete;


			//- Destructor
			virtual ~limitVelocity()
			{}


			// Member Functions

				//- Read dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);

			//- Correct the energy field
			FoamFvOptions_EXPORT virtual void correct(volVectorField& U);


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFvOptions_EXPORT void operator=(const limitVelocity&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_limitVelocity_Header
