#pragma once
#ifndef _linearMotion_Header
#define _linearMotion_Header

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
	tnbLib::solidBodyMotionFunctions::linearMotion

Description
	SolidBodyMotionFvMesh 6DoF motion function. Constant velocity displacement.

SourceFiles
	linearMotion.C

\*---------------------------------------------------------------------------*/

#include <solidBodyMotionFunction.hxx>
#include <primitiveFields.hxx>
#include <point.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace solidBodyMotionFunctions
	{

		/*---------------------------------------------------------------------------*\
								  Class linearMotion Declaration
		\*---------------------------------------------------------------------------*/

		class linearMotion
			:
			public solidBodyMotionFunction
		{
			// Private Data

				//- Linear velocity
			vector velocity_;


		public:

			//- Runtime type information
			//TypeName("linearMotion");
			static const char* typeName_() { return "linearMotion"; }
			static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
			static FoamDynamicMesh_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamDynamicMesh_EXPORT linearMotion
			(
				const dictionary& SBMFCoeffs,
				const Time& runTime
			);

			//- Disallow default bitwise copy construction
			FoamDynamicMesh_EXPORT linearMotion(const linearMotion&);


			//- Construct and return a clone
			virtual autoPtr<solidBodyMotionFunction> clone() const
			{
				return autoPtr<solidBodyMotionFunction>
					(
						new linearMotion
						(
							SBMFCoeffs_,
							time_
						)
						);
			}


			//- Destructor
			FoamDynamicMesh_EXPORT virtual ~linearMotion();


			// Member Functions

				//- Return the solid-body motion transformation septernion
			FoamDynamicMesh_EXPORT virtual septernion transformation() const;

			//- Update properties from given dictionary
			FoamDynamicMesh_EXPORT virtual bool read(const dictionary& SBMFCoeffs);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const linearMotion&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace solidBodyMotionFunctions
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_linearMotion_Header
