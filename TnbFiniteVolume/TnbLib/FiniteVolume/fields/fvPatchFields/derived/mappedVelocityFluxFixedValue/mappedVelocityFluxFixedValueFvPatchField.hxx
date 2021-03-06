#pragma once
#ifndef _mappedVelocityFluxFixedValueFvPatchField_Header
#define _mappedVelocityFluxFixedValueFvPatchField_Header

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
	tnbLib::mappedVelocityFluxFixedValueFvPatchField

Description
	This boundary condition maps the velocity and flux from a neighbour patch
	to this patch

Usage
	\table
		Property     | Description             | Required    | Default value
		phi          | flux field name         | no          | phi
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            mappedVelocityFlux;
		phi             phi;
		value           uniform 0;  // place holder
	}
	\endverbatim

	The underlying sample mode should be set to \c nearestPatchFace or
	\c nearestFace

Note
	This boundary condition can only be applied to patches that are of
	the \c mappedPolyPatch type.

See also
	tnbLib::mappedPatchBase
	tnbLib::mappedPolyPatch
	tnbLib::mappedFvPatch
	tnbLib::fixedValueFvPatchVectorField

SourceFiles
	mappedVelocityFluxFixedValueFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>
#include <mappedFvPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			   Class mappedVelocityFluxFixedValueFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class mappedVelocityFluxFixedValueFvPatchField
		:
		public fixedValueFvPatchVectorField
	{
		// Private Data

			//- Name of flux field
		word phiName_;

	public:

		//- Runtime type information
		/*TypeName("mappedVelocityFlux");*/
		static const char* typeName_() { return "mappedVelocityFlux"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT mappedVelocityFluxFixedValueFvPatchField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT mappedVelocityFluxFixedValueFvPatchField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  mappedVelocityFluxFixedValueFvPatchField
		//  onto a new patch
		FoamFiniteVolume_EXPORT mappedVelocityFluxFixedValueFvPatchField
		(
			const mappedVelocityFluxFixedValueFvPatchField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT mappedVelocityFluxFixedValueFvPatchField
		(
			const mappedVelocityFluxFixedValueFvPatchField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new mappedVelocityFluxFixedValueFvPatchField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT mappedVelocityFluxFixedValueFvPatchField
		(
			const mappedVelocityFluxFixedValueFvPatchField&,
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
					new mappedVelocityFluxFixedValueFvPatchField(*this, iF)
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

#endif // !_mappedVelocityFluxFixedValueFvPatchField_Header
