#pragma once
#ifndef _inclinedFilmNusseltInletVelocityFvPatchVectorField_Header
#define _inclinedFilmNusseltInletVelocityFvPatchVectorField_Header

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
	tnbLib::inclinedFilmNusseltInletVelocityFvPatchVectorField

Description
	Film velocity boundary condition for inclined films that imposes a
	sinusoidal perturbation on top of a mean flow rate, where the velocity is
	calculated using the Nusselt solution.

SourceFiles
	inclinedFilmNusseltInletVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchFields.hxx>
#include <fixedValueFvPatchFields.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
		 Class inclinedFilmNusseltInletVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class inclinedFilmNusseltInletVelocityFvPatchVectorField
		:
		public fixedValueFvPatchVectorField
	{
		// Private Data

			//- Mean mass flow rate per unit length [kg/s/m]
		autoPtr<Function1<scalar>> GammaMean_;

		//- Perturbation amplitude [m]
		autoPtr<Function1<scalar>> a_;

		//- Perturbation frequency [rad/s/m]
		autoPtr<Function1<scalar>> omega_;


	public:

		//- Runtime type information
		//TypeName("inclinedFilmNusseltInletVelocity");
		static const char* typeName_() { return "inclinedFilmNusseltInletVelocity"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamLagrangian_EXPORT inclinedFilmNusseltInletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamLagrangian_EXPORT inclinedFilmNusseltInletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		// inclinedFilmNusseltInletVelocityFvPatchVectorField onto a new patch
		FoamLagrangian_EXPORT inclinedFilmNusseltInletVelocityFvPatchVectorField
		(
			const inclinedFilmNusseltInletVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamLagrangian_EXPORT inclinedFilmNusseltInletVelocityFvPatchVectorField
		(
			const inclinedFilmNusseltInletVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new inclinedFilmNusseltInletVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamLagrangian_EXPORT inclinedFilmNusseltInletVelocityFvPatchVectorField
		(
			const inclinedFilmNusseltInletVelocityFvPatchVectorField&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvPatchVectorField> clone
		(
			const DimensionedField<vector, volMesh>& iF
		) const
		{
			return tmp<fvPatchVectorField>
				(
					new inclinedFilmNusseltInletVelocityFvPatchVectorField
					(
						*this, iF
					)
					);
		}


		// Member Functions

			//- Update the coefficients associated with the patch field
		FoamLagrangian_EXPORT virtual void updateCoeffs();

		//- Write
		FoamLagrangian_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_inclinedFilmNusseltInletVelocityFvPatchVectorField_Header
