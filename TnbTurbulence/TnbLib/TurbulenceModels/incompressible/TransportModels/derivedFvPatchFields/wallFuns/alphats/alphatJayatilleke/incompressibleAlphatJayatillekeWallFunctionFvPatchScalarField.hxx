#pragma once
#ifndef _incompressibleAlphatJayatillekeWallFunctionFvPatchScalarField_Header
#define _incompressibleAlphatJayatillekeWallFunctionFvPatchScalarField_Header

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
	tnbLib::incompressible::alphatJayatillekeWallFunctionFvPatchScalarField

Description
	This boundary condition provides a kinematic turbulent thermal conductivity
	for using wall functions, using the Jayatilleke 'P' function.

Usage
	\table
		Property     | Description             | Required    | Default value
		Prt          | turbulent Prandtl number | no         | 0.85
		Cmu          | model coefficient       | no          | 0.09
		kappa        | Von Karman constant     | no          | 0.41
		E            | model coefficient       | no          | 9.8
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            alphatJayatillekeWallFunction;
	}
	\endverbatim

Note
	The units of kinematic turbulent thermal conductivity are [m2/s]

See also
	tnbLib::fixedValueFvPatchField

SourceFiles
	alphatJayatillekeWallFunctionFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>
#include <nutWallFunctionFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace incompressible
	{

		/*---------------------------------------------------------------------------*\
			   Class alphatJayatillekeWallFunctionFvPatchScalarField Declaration
		\*---------------------------------------------------------------------------*/

		class alphatJayatillekeWallFunctionFvPatchScalarField
			:
			public fixedValueFvPatchScalarField
		{
		protected:

			// Protected data

				//- Turbulent Prandtl number
			scalar Prt_;

			//- Cmu coefficient
			scalar Cmu_;

			//- Von Karman constant
			scalar kappa_;

			//- E coefficient
			scalar E_;


			// Solution parameters

			static FoamTurbulence_EXPORT scalar tolerance_;
			static FoamTurbulence_EXPORT label maxIters_;


			// Protected member functions

				//- `P' function
			FoamTurbulence_EXPORT scalar Psmooth(const scalar Prat) const;

			//- Calculate y+ at the edge of the thermal laminar sublayer
			FoamTurbulence_EXPORT scalar yPlusTherm
			(
				const nutWallFunctionFvPatchScalarField& nutw,
				const scalar P,
				const scalar Prat
			) const;


		public:

			//- Runtime type information
			//TypeName("alphatJayatillekeWallFunction");
			static const char* typeName_() { return "alphatJayatillekeWallFunction"; }
			static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
			static FoamTurbulence_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from patch and internal field
			FoamTurbulence_EXPORT alphatJayatillekeWallFunctionFvPatchScalarField
			(
				const fvPatch&,
				const DimensionedField<scalar, volMesh>&
			);

			//- Construct from patch, internal field and dictionary
			FoamTurbulence_EXPORT alphatJayatillekeWallFunctionFvPatchScalarField
			(
				const fvPatch&,
				const DimensionedField<scalar, volMesh>&,
				const dictionary&
			);

			//- Construct by mapping given
			//  alphatJayatillekeWallFunctionFvPatchScalarField
			//  onto a new patch
			FoamTurbulence_EXPORT alphatJayatillekeWallFunctionFvPatchScalarField
			(
				const alphatJayatillekeWallFunctionFvPatchScalarField&,
				const fvPatch&,
				const DimensionedField<scalar, volMesh>&,
				const fvPatchFieldMapper&
			);

			//- Copy constructor
			FoamTurbulence_EXPORT alphatJayatillekeWallFunctionFvPatchScalarField
			(
				const alphatJayatillekeWallFunctionFvPatchScalarField&
			);

			//- Construct and return a clone
			virtual tmp<fvPatchScalarField> clone() const
			{
				return tmp<fvPatchScalarField>
					(
						new alphatJayatillekeWallFunctionFvPatchScalarField(*this)
						);
			}

			//- Copy constructor setting internal field reference
			FoamTurbulence_EXPORT alphatJayatillekeWallFunctionFvPatchScalarField
			(
				const alphatJayatillekeWallFunctionFvPatchScalarField&,
				const DimensionedField<scalar, volMesh>&
			);

			//- Construct and return a clone setting internal field reference
			virtual tmp<fvPatchScalarField> clone
			(
				const DimensionedField<scalar, volMesh>& iF
			) const
			{
				return tmp<fvPatchScalarField>
					(
						new alphatJayatillekeWallFunctionFvPatchScalarField(*this, iF)
						);
			}


			// Member Functions

				// Evaluation functions

					//- Update the coefficients associated with the patch field
			FoamTurbulence_EXPORT virtual void updateCoeffs();


			// I-O

				//- Write
			FoamTurbulence_EXPORT virtual void write(Ostream&) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace incompressible
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_incompressibleAlphatJayatillekeWallFunctionFvPatchScalarField_Header
