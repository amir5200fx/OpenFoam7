#pragma once
#ifndef _MarshakRadiationFixedTemperatureFvPatchScalarField_Header
#define _MarshakRadiationFixedTemperatureFvPatchScalarField_Header

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
	tnbLib::MarshakRadiationFixedTemperatureFvPatchScalarField

Description
	A 'mixed' boundary condition that implements a Marshak condition for the
	incident radiation field (usually written as G)

	The radiation temperature field across the patch is supplied by the user
	using the \c Trad entry.

Usage
	\table
		Property     | Description             | Required    | Default value
		T            | temperature field name  | no          | T
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            MarshakRadiationFixedTemperature;
		Trad            uniform 1000;       // radiation temperature field
		value           uniform 0;          // place holder
	}
	\endverbatim

See also
	tnbLib::radiationCoupledBase
	tnbLib::mixedFvPatchField

SourceFiles
	MarshakRadiationFixedTemperatureFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <mixedFvPatchFields.hxx>
#include <radiationCoupledBase.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
		 Class MarshakRadiationFixedTemperatureFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class MarshakRadiationFixedTemperatureFvPatchScalarField
		:
		public mixedFvPatchScalarField,
		public radiationCoupledBase
	{

		// Private Data

			//- Radiation temperature field
		scalarField Trad_;


	public:

		//- Runtime type information
		//TypeName("MarshakRadiationFixedTemperature");
		static const char* typeName_() { return "MarshakRadiationFixedTemperature"; }
		static FoamRadiationModels_EXPORT const ::tnbLib::word typeName;
		static FoamRadiationModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamRadiationModels_EXPORT MarshakRadiationFixedTemperatureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamRadiationModels_EXPORT MarshakRadiationFixedTemperatureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given MarshakRadiationFvPatchField onto a new
		//  patch
		FoamRadiationModels_EXPORT MarshakRadiationFixedTemperatureFvPatchScalarField
		(
			const MarshakRadiationFixedTemperatureFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamRadiationModels_EXPORT MarshakRadiationFixedTemperatureFvPatchScalarField
		(
			const MarshakRadiationFixedTemperatureFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new MarshakRadiationFixedTemperatureFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamRadiationModels_EXPORT MarshakRadiationFixedTemperatureFvPatchScalarField
		(
			const MarshakRadiationFixedTemperatureFvPatchScalarField&,
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
					new MarshakRadiationFixedTemperatureFvPatchScalarField
					(
						*this,
						iF
					)
					);
		}


		// Member Functions

			// Access

				//- Return the radiation temperature
		const scalarField& Trad() const
		{
			return Trad_;
		}

		//- Return reference to the radiation temperature to allow
		//  adjustment
		scalarField& Trad()
		{
			return Trad_;
		}


		// Mapping functions

			//- Map (and resize as needed) from self given a mapping object
			//  Used to update fields following mesh topology change
		FoamRadiationModels_EXPORT virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		FoamRadiationModels_EXPORT virtual void rmap(const fvPatchScalarField&, const labelList&);


		// Evaluation functions

			//- Update the coefficients associated with the patch field
		FoamRadiationModels_EXPORT virtual void updateCoeffs();


		// I-O

			//- Write
		FoamRadiationModels_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_MarshakRadiationFixedTemperatureFvPatchScalarField_Header
