#pragma once
#ifndef _immiscibleIncompressibleTwoPhaseMixture_Header
#define _immiscibleIncompressibleTwoPhaseMixture_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2014-2018 OpenFOAM Foundation
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
	tnbLib::immiscibleIncompressibleTwoPhaseMixture

Description
	An immiscible incompressible two-phase mixture transport model

SourceFiles
	immiscibleIncompressibleTwoPhaseMixture.C

\*---------------------------------------------------------------------------*/

#include <incompressibleTwoPhaseMixture.hxx>
#include <interfaceProperties.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			   Class immiscibleIncompressibleTwoPhaseMixture Declaration
	\*---------------------------------------------------------------------------*/

	class immiscibleIncompressibleTwoPhaseMixture
		:
		public incompressibleTwoPhaseMixture,
		public interfaceProperties
	{

	public:

		// Constructors

			//- Construct from components
		FoamTransportModels_EXPORT immiscibleIncompressibleTwoPhaseMixture
		(
			const volVectorField& U,
			const surfaceScalarField& phi
		);


		//- Destructor
		virtual ~immiscibleIncompressibleTwoPhaseMixture()
		{}


		// Member Functions

			//- Correct the transport and interface properties
		virtual void correct()
		{
			incompressibleTwoPhaseMixture::correct();
			interfaceProperties::correct();
		}

		//- Read base transportProperties dictionary
		FoamTransportModels_EXPORT virtual bool read();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_immiscibleIncompressibleTwoPhaseMixture_Header
