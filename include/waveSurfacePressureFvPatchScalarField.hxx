#pragma once
#ifndef _waveSurfacePressureFvPatchScalarField_Header
#define _waveSurfacePressureFvPatchScalarField_Header

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
	tnbLib::waveSurfacePressureFvPatchScalarField

Description
	This is a pressure boundary condition, whose value is calculated as
	the hydrostatic pressure based on a given displacement:

		\f[
			p = -\rho*g*\zeta
		\f]

	\vartable
		\rho  | density [kg/m^3]
		g     | acceleration due to gravity [m/s^2]
		\zeta | wave amplitude [m]
	\endvartable

	The wave amplitude is updated as part of the calculation, derived from the
	local volumetric flux.

Usage
	\table
		Property     | Description             | Required    | Default value
		phi          | flux field name         | no          | phi
		rho          | density field name      | no          | rho
		zeta         | wave amplitude field name | no        | zeta
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            waveSurfacePressure;
		phi             phi;
		rho             rho;
		zeta            zeta;
		value           uniform 0;  // place holder
	}
	\endverbatim

	The density field is only required if the flux is mass-based as opposed to
	volumetric-based.

See also
	tnbLib::fixedValueFvPatchField

SourceFiles
	waveSurfacePressureFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>
#include <NamedEnum.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				Class waveSurfacePressureFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class waveSurfacePressureFvPatchScalarField
		:
		public fixedValueFvPatchScalarField
	{
	public:

		// Public data

			//- Enumeration defining the available ddt schemes
		enum ddtSchemeType
		{
			tsEuler,
			tsCrankNicolson,
			tsBackward
		};


	private:

		// Private Data

			//- Flux field name
		word phiName_;

		//- Wave height field name
		word zetaName_;

		//- Density field for mass-based flux evaluations
		word rhoName_;

		//- Time scheme type names
		static FoamFiniteVolume_EXPORT const NamedEnum<ddtSchemeType, 3> ddtSchemeTypeNames_;


	public:

		//- Runtime type information
		/*TypeName("waveSurfacePressure");*/
		static const char* typeName_() { return "waveSurfacePressure"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT waveSurfacePressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT waveSurfacePressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given waveSurfacePressureFvPatchScalarField
		//  onto a new patch
		FoamFiniteVolume_EXPORT waveSurfacePressureFvPatchScalarField
		(
			const waveSurfacePressureFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT waveSurfacePressureFvPatchScalarField
		(
			const waveSurfacePressureFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new waveSurfacePressureFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT waveSurfacePressureFvPatchScalarField
		(
			const waveSurfacePressureFvPatchScalarField&,
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
					new waveSurfacePressureFvPatchScalarField(*this, iF)
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

#endif // !_waveSurfacePressureFvPatchScalarField_Header
