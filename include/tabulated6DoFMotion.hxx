#pragma once
#ifndef _tabulated6DoFMotion_Header
#define _tabulated6DoFMotion_Header

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
	tnbLib::solidBodyMotionFunctions::tabulated6DoFMotion

Description
	Tabulated 6DoF motion function.

	Obtained by interpolating tabulated data for surge (x-translation),
	sway (y-translation), heave (z-translation), roll (rotation about x),
	pitch (rotation about y) and yaw (rotation about z).

SourceFiles
	tabulated6DoFMotion.C

\*---------------------------------------------------------------------------*/

#include <solidBodyMotionFunction.hxx>
#include <primitiveFields.hxx>
#include <Vector2DTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace solidBodyMotionFunctions
	{

		/*---------------------------------------------------------------------------*\
								  Class tabulated6DoFMotion Declaration
		\*---------------------------------------------------------------------------*/

		class tabulated6DoFMotion
			:
			public solidBodyMotionFunction
		{
			// Private Data

				//- Time data file name read from dictionary
			fileName timeDataFileName_;

			//- Center of gravity read from dictionary
			vector CofG_;

			//- Type used to read in the translation and rotation "vectors"
			typedef Vector2D<vector> translationRotationVectors;

			//- Field of times
			scalarField times_;

			//- Field of translation and rotation "vectors"
			Field<translationRotationVectors> values_;


		public:

			//- Runtime type information
			//TypeName("tabulated6DoFMotion");
			static const char* typeName_() { return "tabulated6DoFMotion"; }
			static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
			static FoamDynamicMesh_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamDynamicMesh_EXPORT tabulated6DoFMotion
			(
				const dictionary& SBMFCoeffs,
				const Time& runTime
			);

			//- Disallow default bitwise copy construction
			FoamDynamicMesh_EXPORT tabulated6DoFMotion(const tabulated6DoFMotion&);


			//- Construct and return a clone
			virtual autoPtr<solidBodyMotionFunction> clone() const
			{
				return autoPtr<solidBodyMotionFunction>
					(
						new tabulated6DoFMotion
						(
							SBMFCoeffs_,
							time_
						)
						);
			}


			//- Destructor
			FoamDynamicMesh_EXPORT virtual ~tabulated6DoFMotion();


			// Member Functions

				//- Return the solid-body motion transformation septernion
			FoamDynamicMesh_EXPORT virtual septernion transformation() const;

			//- Update properties from given dictionary
			FoamDynamicMesh_EXPORT virtual bool read(const dictionary& SBMFCoeffs);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const tabulated6DoFMotion&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace solidBodyMotionFunctions
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_tabulated6DoFMotion_Header
