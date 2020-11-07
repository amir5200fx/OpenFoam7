#pragma once
#ifndef _inletOutletTotalTemperatureFvPatchScalarField_Header
#define _inletOutletTotalTemperatureFvPatchScalarField_Header

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
	tnbLib::inletOutletTotalTemperatureFvPatchScalarField

Description
	This boundary condition provides an outflow condition for total
	temperature for use with supersonic cases, where a user-specified
	value is applied in the case of reverse flow.

Usage
	\table
		Property     | Description             | Required    | Default value
		U            | velocity field name     | no          | U
		phi          | flux field name         | no          | phi
		psi          | compressibility field name |  no      | thermo:psi
		gamma        | heat capacity ration (Cp/Cv) | yes    |
		inletValue   | reverse flow (inlet) value | yes      |
		T0           | static temperature [K]  | yes         |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            inletOutletTotalTemperature;
		U               U;
		phi             phi;
		psi             psi;
		gamma           gamma;
		inletValue      uniform 0;
		T0              uniform 0;
		value           uniform 0;
	}
	\endverbatim

See also
	tnbLib::inletOutletFvPatchField

SourceFiles
	inletOutletTotalTemperatureFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <inletOutletFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
		   Class inletOutletTotalTemperatureFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class inletOutletTotalTemperatureFvPatchScalarField
		:
		public inletOutletFvPatchScalarField
	{
		// Private Data

			//- Name of the velocity field
		word UName_;

		//- Name of the compressibility field used to calculate the wave speed
		word psiName_;

		//- Heat capacity ratio
		scalar gamma_;

		//- Total pressure
		scalarField T0_;


	public:

		//- Runtime type information
		//TypeName("inletOutletTotalTemperature");
		static const char* typeName_() { return "inletOutletTotalTemperature"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT inletOutletTotalTemperatureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT inletOutletTotalTemperatureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  inletOutletTotalTemperatureFvPatchScalarField onto a new patch
		FoamFiniteVolume_EXPORT inletOutletTotalTemperatureFvPatchScalarField
		(
			const inletOutletTotalTemperatureFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT inletOutletTotalTemperatureFvPatchScalarField
		(
			const inletOutletTotalTemperatureFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new inletOutletTotalTemperatureFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT inletOutletTotalTemperatureFvPatchScalarField
		(
			const inletOutletTotalTemperatureFvPatchScalarField&,
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
					new inletOutletTotalTemperatureFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Return the total pressure
		const scalarField& T0() const
		{
			return T0_;
		}

		//- Return reference to the total pressure to allow adjustment
		scalarField& T0()
		{
			return T0_;
		}


		// Mapping functions

			//- Map (and resize as needed) from self given a mapping object
			//  Used to update fields following mesh topology change
		FoamFiniteVolume_EXPORT virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		FoamFiniteVolume_EXPORT virtual void rmap(const fvPatchScalarField&, const labelList&);


		// Evaluation functions

			//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();


		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_inletOutletTotalTemperatureFvPatchScalarField_Header
