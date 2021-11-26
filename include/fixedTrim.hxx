#pragma once
#ifndef _fixedTrim_Header
#define _fixedTrim_Header

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
	tnbLib::fixedTrim

Description
	Fixed trim coefficients

SourceFiles
	fixedTrim.C

\*---------------------------------------------------------------------------*/

#include <trimModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class fixedTrim Declaration
	\*---------------------------------------------------------------------------*/

	class fixedTrim
		:
		public trimModel
	{

	protected:

		// Protected data

			//- Geometric angle of attack [rad]
		scalarField thetag_;


	public:

		//- Run-time type information
		//TypeName("fixedTrim");
		static const char* typeName_() { return "fixedTrim"; }
		static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
		static FoamFvOptions_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Constructor
		FoamFvOptions_EXPORT fixedTrim(const fv::rotorDiskSource& rotor, const dictionary& dict);

		//- Destructor
		FoamFvOptions_EXPORT virtual ~fixedTrim();


		// Member Functions

			//- Read
		FoamFvOptions_EXPORT void read(const dictionary& dict);

		//- Return the geometric angle of attack [rad]
		FoamFvOptions_EXPORT virtual tmp<scalarField> thetag() const;

		//- Correct the model
		FoamFvOptions_EXPORT virtual void correct
		(
			const vectorField& U,
			vectorField& force
		);

		//- Correct the model for compressible flow
		FoamFvOptions_EXPORT virtual void correct
		(
			const volScalarField rho,
			const vectorField& U,
			vectorField& force
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedTrim_Header
