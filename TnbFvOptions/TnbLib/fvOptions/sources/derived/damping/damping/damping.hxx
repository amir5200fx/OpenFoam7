#pragma once
#ifndef _damping_Header
#define _damping_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::fv::damping

Description
	Base fvOption for damping functions.

See also
	tnbLib::fv::isotropicDamping
	tnbLib::fv::verticalDamping

SourceFiles
	damping.C

\*---------------------------------------------------------------------------*/

#include <cellSetOption.hxx>
#include <Function1.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
						   Class damping Declaration
		\*---------------------------------------------------------------------------*/

		class damping
			:
			public cellSetOption
		{
		protected:

			// Protected Data

				//- Damping coefficient [1/s]
			dimensionedScalar lambda_;

			//- The scaling function
			autoPtr<Function1<scalar>> scale_;

			//- Origins of the scaling coordinate
			vectorField origins_;

			//- Directions of increasing scaling coordinate
			vectorField directions_;


			// Protected Member Functions

			FoamFvOptions_EXPORT tmp<volScalarField::Internal> forceCoeff() const;


		public:

			//- Runtime type information
			//TypeName("damping");
			static const char* typeName_() { return "damping"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvOptions_EXPORT damping
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);


			//- Destructor
			virtual ~damping()
			{}


			// Member Functions

				// IO

					//- Read dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_damping_Header
