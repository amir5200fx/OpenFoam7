#pragma once
#ifndef _surfaceNormalFixedValueFvPatchVectorField_Header
#define _surfaceNormalFixedValueFvPatchVectorField_Header

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
	tnbLib::surfaceNormalFixedValueFvPatchVectorField

Description
	Surface-normal fixed value vector boundary condition

	in which the vector field is obtained by scaling the patch normals
	by the scalar field provided.

Usage
	\table
		Property     | Description             | Required    | Default value
		refValue     | reference value         | yes         |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            surfaceNormalFixedValue;
		refValue        uniform -10;           // 10 INTO the domain
	}
	\endverbatim

Note
	Sign conventions:
	- the value is positive for outward-pointing vectors

See also
	tnbLib::fixedValueFvPatchField

SourceFiles
	surfaceNormalFixedValueFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchField.hxx>
#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			  Class surfaceNormalFixedValueFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class surfaceNormalFixedValueFvPatchVectorField
		:
		public fixedValueFvPatchVectorField
	{
		// Private Data

		scalarField refValue_;


	public:

		//- Runtime type information
		/*TypeName("surfaceNormalFixedValue");*/
		static const char* typeName_() { return "surfaceNormalFixedValue"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT surfaceNormalFixedValueFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT surfaceNormalFixedValueFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  surfaceNormalFixedValueFvPatchVectorField
		//  onto a new patch
		FoamFiniteVolume_EXPORT surfaceNormalFixedValueFvPatchVectorField
		(
			const surfaceNormalFixedValueFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT surfaceNormalFixedValueFvPatchVectorField
		(
			const surfaceNormalFixedValueFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new surfaceNormalFixedValueFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT surfaceNormalFixedValueFvPatchVectorField
		(
			const surfaceNormalFixedValueFvPatchVectorField&,
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
					new surfaceNormalFixedValueFvPatchVectorField
					(
						*this,
						iF
					)
					);
		}


		// Member Functions

		// Mapping functions

		//- Map (and resize as needed) from self given a mapping object
		//  Used to update fields following mesh topology change
		FoamFiniteVolume_EXPORT virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		FoamFiniteVolume_EXPORT virtual void rmap(const fvPatchVectorField&, const labelList&);


		// Evaluation functions

		//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();


		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_surfaceNormalFixedValueFvPatchVectorField_Header
