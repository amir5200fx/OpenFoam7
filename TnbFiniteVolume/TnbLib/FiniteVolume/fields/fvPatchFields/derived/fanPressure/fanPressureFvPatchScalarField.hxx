#pragma once
#ifndef _fanPressureFvPatchScalarField_Header
#define _fanPressureFvPatchScalarField_Header

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
	tnbLib::fanPressureFvPatchScalarField

Description
	This boundary condition can be applied to assign either a pressure inlet
	or outlet total pressure condition for a fan.

Usage
	\table
		Property     | Description             | Required    | Default value
		file         | fan curve file name     | yes         |
		outOfBounds  | out of bounds handling  | yes         |
		direction    | direction of flow through fan [in/out] | yes |
		p0           | environmental total pressure | yes    |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	inlet
	{
		type            fanPressure;
		file            "fanCurve";
		outOfBounds     clamp;
		direction       in;
		p0              uniform 0;
		value           uniform 0;
	}

	outlet
	{
		type            fanPressure;
		file            "fanCurve";
		outOfBounds     clamp;
		direction       out;
		p0              uniform 0;
		value           uniform 0;
	}
	\endverbatim

See also
	tnbLib::fanFvPatchField
	tnbLib::totalPressureFvPatchScalarField
	tnbLib::interpolationTable

SourceFiles
   fanPressureFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <totalPressureFvPatchScalarField.hxx>
#include <interpolationTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				  Class fanPressureFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class fanPressureFvPatchScalarField
		:
		public totalPressureFvPatchScalarField
	{

	public:

		//- Fan flow direction
		enum fanFlowDirection
		{
			ffdIn,
			ffdOut
		};

		//- Fan flow directions names
		static const NamedEnum<fanFlowDirection, 2> fanFlowDirectionNames_;


	private:

		// Private Data

			//- Tabulated fan curve
		interpolationTable<scalar> fanCurve_;

		//- Direction of flow through the fan relative to patch
		fanFlowDirection direction_;


	public:

		//- Runtime type information
		TypeName("fanPressure");


		// Constructors

			//- Construct from patch and internal field
		fanPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		fanPressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  fanPressureFvPatchScalarField
		//  onto a new patch
		fanPressureFvPatchScalarField
		(
			const fanPressureFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		fanPressureFvPatchScalarField
		(
			const fanPressureFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new fanPressureFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		fanPressureFvPatchScalarField
		(
			const fanPressureFvPatchScalarField&,
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
					new fanPressureFvPatchScalarField
					(
						*this,
						iF
					)
					);
		}


		// Member Functions

			//- Update the coefficients associated with the patch field
		virtual void updateCoeffs();

		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fanPressureFvPatchScalarField_Header
