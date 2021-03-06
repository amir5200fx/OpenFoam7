#pragma once
#ifndef _uniformDensityHydrostaticPressureFvPatchScalarField_Header
#define _uniformDensityHydrostaticPressureFvPatchScalarField_Header

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
	tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField

Description
	This boundary condition provides a hydrostatic pressure condition,
	calculated as:

		\f[
			p_{hyd} = p_{ref} + \rho_{ref} g (x - x_{ref})
		\f]

	where
	\vartable
		p_{hyd}    | Hydrostatic pressure [Pa]
		p_{ref}    | Reference pressure [Pa]
		x_{ref}    | Reference point in Cartesian co-ordinates
		\rho_{ref} | Density (assumed uniform)
		g          | Acceleration due to gravity [m/s^2]
	\endtable

Usage
	\table
		Property     | Description             | Required    | Default value
		rhoRef       | Uniform density [kg/m^3] | yes         |
		pRef         | Reference pressure [Pa] | yes         |
		pRefPoint    | Reference pressure location | no      | hRef
		value        | Initial value           | no          | pRef
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            uniformDensityHydrostaticPressure;
		rhoRef          1000;
		pRef            1e5;
		pRefPoint       (0 0 0);
	}
	\endverbatim

SourceFiles
	uniformDensityHydrostaticPressureFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
		 Class uniformDensityHydrostaticPressureFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class uniformDensityHydrostaticPressureFvPatchScalarField
		:
		public fixedValueFvPatchScalarField
	{
		// Private Data

			//- Constant density in the far-field
		scalar rho_;

		//- Reference pressure
		scalar pRef_;

		//- True if the reference pressure location is specified
		bool pRefPointSpecified_;

		//- Optional reference pressure location
		vector pRefPoint_;


	public:

		//- Runtime type information
		/*TypeName("uniformDensityHydrostaticPressure");*/
		static const char* typeName_() { return "uniformDensityHydrostaticPressure"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT uniformDensityHydrostaticPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT uniformDensityHydrostaticPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  uniformDensityHydrostaticPressureFvPatchScalarField onto a new patch
		FoamFiniteVolume_EXPORT uniformDensityHydrostaticPressureFvPatchScalarField
		(
			const uniformDensityHydrostaticPressureFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT uniformDensityHydrostaticPressureFvPatchScalarField
		(
			const uniformDensityHydrostaticPressureFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new uniformDensityHydrostaticPressureFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT uniformDensityHydrostaticPressureFvPatchScalarField
		(
			const uniformDensityHydrostaticPressureFvPatchScalarField&,
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
					new uniformDensityHydrostaticPressureFvPatchScalarField
					(
						*this,
						iF
					)
					);
		}


		// Member Functions

		// Access

		//- Return the constant density in the far-field
		scalar rho() const
		{
			return rho_;
		}

		//- Return reference to the constant density in the far-field
		//  to allow adjustment
		scalar& rho()
		{
			return rho_;
		}

		//- Return the reference pressure
		scalar pRef() const
		{
			return pRef_;
		}

		//- Return reference to the reference pressure to allow adjustment
		scalar& pRef()
		{
			return pRef_;
		}

		//- Return the pressure reference location
		const vector& pRefPoint() const
		{
			return pRefPoint_;
		}

		//- Return reference to the pressure reference location
		//  to allow adjustment
		vector& pRefPoint()
		{
			return pRefPoint_;
		}


		// Evaluation functions

		//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();


		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_uniformDensityHydrostaticPressureFvPatchScalarField_Header
