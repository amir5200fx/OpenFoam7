#pragma once
#ifndef _fixedMeanFvPatchField_Header
#define _fixedMeanFvPatchField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::fixedMeanFvPatchField

Description
	This boundary condition extrapolates field to the patch using the near-cell
	values and adjusts the distribution to match the specified, optionally
	time-varying, mean value.

Usage
	\table
		Property     | Description             | Required    | Default value
		meanValue    | mean value Function1    | yes         |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            fixedMean;
		meanValue       1.0;
	}
	\endverbatim

See also
	tnbLib::fixedValueFvPatchField
	tnbLib::Function1Types

SourceFiles
	fixedMeanFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>
#include <Function1.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamFixedMeanFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamFixedMeanFvPatchField_EXPORT_DEFINE
#define FoamFixedMeanFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamFixedMeanFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class fixedMeanFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class fixedMeanFvPatchField
		:
		public fixedValueFvPatchField<Type>
	{
		// Private Data

		//- MeanValue value the field is adjusted to maintain
		autoPtr<Function1<Type>> meanValue_;


	public:

		//- Runtime type information
		//TypeName("fixedMean");
		static const char* typeName_() { return "fixedMean"; }
		static FoamFixedMeanFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamFixedMeanFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		fixedMeanFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		fixedMeanFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given fixedMeanFvPatchField
		//  onto a new patch
		fixedMeanFvPatchField
		(
			const fixedMeanFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		fixedMeanFvPatchField
		(
			const fixedMeanFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new fixedMeanFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		fixedMeanFvPatchField
		(
			const fixedMeanFvPatchField<Type>&,
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
					new fixedMeanFvPatchField<Type>(*this, iF)
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

#include <fixedMeanFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <fixedMeanFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedMeanFvPatchField_Header
