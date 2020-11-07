#pragma once
#ifndef _uniformFixedValueFvPatchField_Header
#define _uniformFixedValueFvPatchField_Header

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
	tnbLib::uniformFixedValueFvPatchField

Description
	This boundary condition provides a uniform fixed value condition.

Usage
	\table
		Property     | Description             | Required    | Default value
		uniformValue | uniform value           | yes         |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            uniformFixedValue;
		uniformValue    constant 0.2;
	}
	\endverbatim

Note
	The uniformValue entry is a Function1 type, able to describe time
	varying functions.  The example above gives the usage for supplying a
	constant value.

See also
	tnbLib::Function1Types
	tnbLib::fixedValueFvPatchField

SourceFiles
	uniformFixedValueFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchField.hxx>
#include <Function1.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamUniformFixedValueFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamUniformFixedValueFvPatchField_EXPORT_DEFINE
#define FoamUniformFixedValueFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamUniformFixedValueFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					Class uniformFixedValueFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class uniformFixedValueFvPatchField
		:
		public fixedValueFvPatchField<Type>
	{
		// Private Data

		autoPtr<Function1<Type>> uniformValue_;


	public:

		//- Runtime type information
		/*TypeName("uniformFixedValue");*/
		static const char* typeName_() { return "uniformFixedValue"; }
		static FoamUniformFixedValueFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamUniformFixedValueFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		uniformFixedValueFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch and internal field and patch field
		uniformFixedValueFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const Field<Type>& fld
		);

		//- Construct from patch, internal field and dictionary
		uniformFixedValueFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given uniformFixedValueFvPatchField
		//  onto a new patch
		uniformFixedValueFvPatchField
		(
			const uniformFixedValueFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		uniformFixedValueFvPatchField
		(
			const uniformFixedValueFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new uniformFixedValueFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		uniformFixedValueFvPatchField
		(
			const uniformFixedValueFvPatchField<Type>&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvPatchField<Type>> clone
		(
			const DimensionedField<Type, volMesh>& iF
		) const
		{
			return tmp<fvPatchField<Type>>
				(
					new uniformFixedValueFvPatchField<Type>(*this, iF)
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

#include <uniformFixedValueFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <uniformFixedValueFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_uniformFixedValueFvPatchField_Header
