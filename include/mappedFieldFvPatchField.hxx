#pragma once
#ifndef _mappedFieldFvPatchField_Header
#define _mappedFieldFvPatchField_Header

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
	tnbLib::mappedFieldFvPatchField

Description
	This boundary condition provides a self-contained version of the \c mapped
	condition.  It does not use information on the patch; instead it holds
	thr data locally.

Usage
	\table
		Property     | Description             | Required    | Default value
		fieldName    | name of field to be mapped | no       | this field name
		setAverage   | flag to activate setting of average value | yes |
		average      | average value to apply if \c setAverage = yes | yes |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            mappedField;
		fieldName       T;              // optional field name
		setAverage      no;             // apply an average value
		average         0;              // average to apply if setAverage
		value           uniform 0;      // place holder
	}
	\endverbatim

Note
	Since this condition can be applied on a per-field and per-patch basis,
	it is possible to duplicate the mapping information.  If possible, employ
	the \c mapped condition in preference to avoid this situation, and only
	employ this condition if it is not possible to change the underlying
	geometric (poly) patch type to \c mapped.

See also
	tnbLib::mappedPatchBase
	tnbLib::mappedPolyPatch
	tnbLib::mappedFvPatch
	tnbLib::fixedValueFvPatchField

SourceFiles
	mappedFieldFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <mappedPatchBase.hxx>
#include <mappedPatchFieldBase.hxx>
#include <fixedValueFvPatchFields.hxx>
#include <interpolation.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamMappedFieldFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamMappedFieldFvPatchField_EXPORT_DEFINE
#define FoamMappedFieldFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamMappedFieldFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class mappedFieldFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class mappedFieldFvPatchField
		:
		public fixedValueFvPatchField<Type>,
		public mappedPatchBase,
		public mappedPatchFieldBase<Type>
	{

	public:

		//- Runtime type information
		//TypeName("mappedField");
		static const char* typeName_() { return "mappedField"; }
		static FoamMappedFieldFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamMappedFieldFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

		//- Construct from patch and internal field
		mappedFieldFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		mappedFieldFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct from patch, internal field and distance for normal type
		//  sampling
		mappedFieldFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,

			// mappedPatchBase
			const word& sampleRegion,
			const sampleMode sampleMode,
			const word& samplePatch,
			const scalar distance,

			// My settings
			const word& fieldName,
			const bool setAverage,
			const Type average,
			const word& interpolationScheme
		);

		//- Construct by mapping given
		//  mappedFieldFvPatchField
		//  onto a new patch
		mappedFieldFvPatchField
		(
			const mappedFieldFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		mappedFieldFvPatchField
		(
			const mappedFieldFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new mappedFieldFvPatchField<Type>
					(
						*this
						)
					);
		}

		//- Copy constructor setting internal field reference
		mappedFieldFvPatchField
		(
			const mappedFieldFvPatchField<Type>&,
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
					new mappedFieldFvPatchField<Type>
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
		virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		virtual void rmap(const fvPatchField<Type>&, const labelList&);


		// Evaluation functions

			//- Update the coefficients associated with the patch field
		virtual void updateCoeffs();


		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <mappedFieldFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <mappedFieldFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_mappedFieldFvPatchField_Header
