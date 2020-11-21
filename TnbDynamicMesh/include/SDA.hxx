#pragma once
#ifndef _SDA_Header
#define _SDA_Header

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
	tnbLib::solidBodyMotionFunctions::SDA

Description
	Ship design analysis (SDA) 3DoF motion function.

	Comprising sinusoidal roll (rotation about x), heave (z-translation)
	and sway (y-translation) motions with changing amplitude and phase.

See also
	tnbLib::solidBodyMotionFunctions::tabulated6DoFMotion

SourceFiles
	SDA.C

\*---------------------------------------------------------------------------*/

#include <solidBodyMotionFunction.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace solidBodyMotionFunctions
	{

		/*---------------------------------------------------------------------------*\
								  Class SDA Declaration
		\*---------------------------------------------------------------------------*/

		class SDA
			:
			public solidBodyMotionFunction
		{
			// Private Data

				//- Center of gravity
			vector CofG_;

			//- Model scale ratio
			scalar lamda_;

			//- Max roll amplitude [rad]
			scalar rollAmax_;

			//- Min roll amplitude [rad]
			scalar rollAmin_;

			//- Heave amplitude [m]
			scalar heaveA_;

			//- Sway amplitude [m]
			scalar swayA_;

			//- Damping Coefficient [-]
			scalar Q_;

			//- Time Period for liquid [sec]
			scalar Tp_;

			//- Natural Period of Ship [sec]
			scalar Tpn_;

			//- Reference time step [sec]
			scalar dTi_;

			//- Incr. in Tp/unit 'dTi'[-]
			scalar dTp_;


		public:

			//- Runtime type information
			//TypeName("SDA");
			static const char* typeName_() { return "SDA"; }
			static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
			static FoamDynamicMesh_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamDynamicMesh_EXPORT SDA
			(
				const dictionary& SBMFCoeffs,
				const Time& runTime
			);

			//- Disallow default bitwise copy construction
			FoamDynamicMesh_EXPORT SDA(const SDA&);


			//- Construct and return a clone
			virtual autoPtr<solidBodyMotionFunction> clone() const
			{
				return autoPtr<solidBodyMotionFunction>
					(
						new SDA
						(
							SBMFCoeffs_,
							time_
						)
						);
			}


			//- Destructor
			FoamDynamicMesh_EXPORT virtual ~SDA();


			// Member Functions

				//- Return the solid-body motion transformation septernion
			FoamDynamicMesh_EXPORT virtual septernion transformation() const;

			//- Update properties from given dictionary
			FoamDynamicMesh_EXPORT virtual bool read(const dictionary& SBMFCoeffs);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const SDA&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace solidBodyMotionFunctions
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SDA_Header
