#pragma once
#ifndef _fixedGradientFvPatchField_Header
#define _fixedGradientFvPatchField_Header

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
	tnbLib::fixedGradientFvPatchField

Description
	This boundary condition supplies a fixed gradient condition, such that
	the patch values are calculated using:

		\f[
			x_p = x_c + \frac{\nabla(x)}{\Delta}
		\f]

	where
	\vartable
		x_p      | patch values
		x_c      | internal field values
		\nabla(x)| gradient (user-specified)
		\Delta   | inverse distance from patch face centre to cell centre
	\endvartable

Usage
	\table
		Property     | Description             | Required    | Default value
		gradient     | gradient                | yes         |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            fixedGradient;
		gradient        uniform 0;
	}
	\endverbatim

SourceFiles
	fixedGradientFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchField.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamFixedGradientFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamFixedGradientFvPatchField_EXPORT_DEFINE
#define FoamFixedGradientFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamFixedGradientFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class fixedGradientFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class fixedGradientFvPatchField
		:
		public fvPatchField<Type>
	{
		// Private Data

		Field<Type> gradient_;


	public:

		//- Runtime type information
		//TypeName("fixedGradient");
		static const char* typeName_() { return "fixedGradient"; }
		static FoamFixedGradientFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamFixedGradientFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		fixedGradientFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		fixedGradientFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping the given fixedGradientFvPatchField
		//  onto a new patch
		fixedGradientFvPatchField
		(
			const fixedGradientFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		fixedGradientFvPatchField
		(
			const fixedGradientFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new fixedGradientFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		fixedGradientFvPatchField
		(
			const fixedGradientFvPatchField<Type>&,
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
					new fixedGradientFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Return defining fields

				//- Return gradient at boundary
		virtual Field<Type>& gradient()
		{
			return gradient_;
		}

		virtual const Field<Type>& gradient() const
		{
			return gradient_;
		}


		// Mapping functions

			//- Map (and resize as needed) from self given a mapping object
			//  Used to update fields following mesh topology change
		virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		virtual void rmap(const fvPatchField<Type>&, const labelList&);


		// Evaluation functions

			//- Return gradient at boundary
		virtual tmp<Field<Type>> snGrad() const
		{
			return gradient_;
		}

		//- Evaluate the patch field
		virtual void evaluate
		(
			const Pstream::commsTypes commsType =
			Pstream::commsTypes::blocking
		);

		//- Return the matrix diagonal coefficients corresponding to the
		//  evaluation of the value of this patchField with given weights
		virtual tmp<Field<Type>> valueInternalCoeffs
		(
			const tmp<scalarField>&
		) const;

		//- Return the matrix source coefficients corresponding to the
		//  evaluation of the value of this patchField with given weights
		virtual tmp<Field<Type>> valueBoundaryCoeffs
		(
			const tmp<scalarField>&
		) const;

		//- Return the matrix diagonal coefficients corresponding to the
		//  evaluation of the gradient of this patchField
		virtual tmp<Field<Type>> gradientInternalCoeffs() const;

		//- Return the matrix source coefficients corresponding to the
		//  evaluation of the gradient of this patchField
		virtual tmp<Field<Type>> gradientBoundaryCoeffs() const;


		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fixedGradientFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <fixedGradientFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedGradientFvPatchField_Header
