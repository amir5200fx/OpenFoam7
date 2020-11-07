#pragma once
#ifndef _prghTotalHydrostaticPressureFvPatchScalarField_Header
#define _prghTotalHydrostaticPressureFvPatchScalarField_Header

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
	tnbLib::prghTotalHydrostaticPressureFvPatchScalarField

Description
	This boundary condition provides static pressure condition for p_rgh,
	calculated as:

		\f[
			p_rgh = ph_rgh - 0.5 \rho |U|^2
		\f]

	where
	\vartable
		p_rgh   | Pressure - \rho g.(h - hRef) [Pa]
		ph_rgh  | Hydrostatic pressure - \rho g.(h - hRef) [Pa]
		h       | Height in the opposite direction to gravity
		hRef    | Reference height in the opposite direction to gravity
		\rho    | Density
		g       | Acceleration due to gravity [m/s^2]
	\endtable

Usage
	\table
		Property     | Description             | Required    | Default value
		U            | Velocity field name     | no          | U
		phi          | Flux field name         | no          | phi
		rho          | Density field name      | no          | rho
		ph_rgh       | ph_rgh field name       | no          | ph_rgh
		value        | Patch face values       | yes         |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            prghTotalHydrostaticPressure;
		value           uniform 0;
	}
	\endverbatim

See also
	tnbLib::fixedValueFvPatchScalarField
	tnbLib::prghTotalPressureFvPatchScalarField

SourceFiles
	prghTotalHydrostaticPressureFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			 Class prghTotalHydrostaticPressureFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class prghTotalHydrostaticPressureFvPatchScalarField
		:
		public fixedValueFvPatchScalarField
	{

	protected:

		// Protected data

			//- Name of the velocity field
		word UName_;

		//- Name of the flux transporting the field
		word phiName_;

		//- Name of density field
		word rhoName_;

		//- Name of hydrostatic pressure field
		word ph_rghName_;


	public:

		//- Runtime type information
		/*TypeName("prghTotalHydrostaticPressure");*/
		static const char* typeName_() { return "prghTotalHydrostaticPressure"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

		//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT prghTotalHydrostaticPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT prghTotalHydrostaticPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  prghTotalHydrostaticPressureFvPatchScalarField onto a new patch
		FoamFiniteVolume_EXPORT prghTotalHydrostaticPressureFvPatchScalarField
		(
			const prghTotalHydrostaticPressureFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT prghTotalHydrostaticPressureFvPatchScalarField
		(
			const prghTotalHydrostaticPressureFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField >
				(
					new prghTotalHydrostaticPressureFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT prghTotalHydrostaticPressureFvPatchScalarField
		(
			const prghTotalHydrostaticPressureFvPatchScalarField&,
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
					new prghTotalHydrostaticPressureFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

		// Evaluation functions

		//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();


		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_prghTotalHydrostaticPressureFvPatchScalarField_Header
