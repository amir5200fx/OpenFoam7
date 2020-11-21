#pragma once
#ifndef _greyDiffusiveViewFactorFixedValueFvPatchScalarField_Header
#define _greyDiffusiveViewFactorFixedValueFvPatchScalarField_Header

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
	tnbLib::greyDiffusiveViewFactorFixedValueFvPatchScalarField

Description
	This boundary condition provides a grey-diffuse condition for radiative
	heat flux, \c qr, for use with the view factor model

Usage
	\table
		Property     | Description             | Required    | Default value
		qro          | external radiative heat flux | yes    |
		emissivityMode | emissivity mode: solidRadiation or lookup | yes |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            greyDiffusiveRadiationViewFactor;
		qro             uniform 0;
		emissivityMode  solidRadiation;
		value           uniform 0;
	}
	\endverbatim

See also
	tnbLib::radiationCoupledBase
	tnbLib::radiationModel
	tnbLib::radiationModels::viewFactor
	tnbLib::fixedValueFvPatchField

SourceFiles
	greyDiffusiveViewFactorFixedValueFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <radiationCoupledBase.hxx>
#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
		  Class greyDiffusiveViewFactorFixedValueFvPatchScalarField declaration
	\*---------------------------------------------------------------------------*/

	class greyDiffusiveViewFactorFixedValueFvPatchScalarField
		:
		public fixedValueFvPatchScalarField,
		public radiationCoupledBase
	{
		// Private Data

			//- External radiative heat flux
		scalarField qro_;


	public:

		//- Runtime type information
		//TypeName("greyDiffusiveRadiationViewFactor");
		static const char* typeName_() { return "greyDiffusiveRadiationViewFactor"; }
		static FoamRadiationModels_EXPORT const ::tnbLib::word typeName;
		static FoamRadiationModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamRadiationModels_EXPORT greyDiffusiveViewFactorFixedValueFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamRadiationModels_EXPORT greyDiffusiveViewFactorFixedValueFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given a
		// greyDiffusiveViewFactorFixedValueFvPatchScalarField onto a new patch
		FoamRadiationModels_EXPORT greyDiffusiveViewFactorFixedValueFvPatchScalarField
		(
			const greyDiffusiveViewFactorFixedValueFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamRadiationModels_EXPORT greyDiffusiveViewFactorFixedValueFvPatchScalarField
		(
			const greyDiffusiveViewFactorFixedValueFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new greyDiffusiveViewFactorFixedValueFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamRadiationModels_EXPORT greyDiffusiveViewFactorFixedValueFvPatchScalarField
		(
			const greyDiffusiveViewFactorFixedValueFvPatchScalarField&,
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
					new greyDiffusiveViewFactorFixedValueFvPatchScalarField
					(
						*this,
						iF
					)
					);
		}


		// Member Functions

			// Access

				//- Return external radiative heat flux
		const scalarList& qro()
		{
			return qro_;
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

#endif // !_greyDiffusiveViewFactorFixedValueFvPatchScalarField_Header
