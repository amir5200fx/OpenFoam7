#pragma once
#ifndef _coupledFvPatchField_Header
#define _coupledFvPatchField_Header

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
	tnbLib::coupledFvPatchField

Description
	Abstract base class for coupled patches.

SourceFiles
	coupledFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <LduInterfaceFieldTemplate.hxx>
#include <fvPatchField.hxx>
#include <coupledFvPatch.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamCoupledFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamCoupledFvPatchField_EXPORT_DEFINE
#define FoamCoupledFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamCoupledFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class coupledFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class coupledFvPatchField
		:
		public LduInterfaceField<Type>,
		public fvPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName(coupledFvPatch::typeName_());
		static const char* typeName_() { return coupledFvPatch::typeName_(); }
		static FoamCoupledFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamCoupledFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		coupledFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch and internal field and patch field
		coupledFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const Field<Type>&
		);

		//- Construct from patch, internal field and dictionary
		coupledFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&,
			const bool valueRequired = true
		);

		//- Construct by mapping the given coupledFvPatchField onto a new patch
		coupledFvPatchField
		(
			const coupledFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&,
			const bool mappingRequired = true
		);

		//- Copy constructor
		coupledFvPatchField
		(
			const coupledFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const = 0;

		//- Copy constructor setting internal field reference
		coupledFvPatchField
		(
			const coupledFvPatchField<Type>&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone
		(
			const DimensionedField<Type, volMesh>&
		) const = 0;


		// Member Functions

			// Access

				//- Return true if this patch field is derived from
				//  coupledFvPatchField<Type>.
		virtual bool coupled() const
		{
			return true;
		}

		//- Return neighbour field of internal field
		virtual tmp<Field<Type>> patchNeighbourField() const = 0;


		// Evaluation functions

			//- Return patch-normal gradient
		virtual tmp<Field<Type>> snGrad
		(
			const scalarField& deltaCoeffs
		) const;

		//- Return patch-normal gradient
		virtual tmp<Field<Type>> snGrad() const
		{
			NotImplemented;
			return *this;
		}

		//- Initialise the evaluation of the patch field
		virtual void initEvaluate
		(
			const Pstream::commsTypes commsType
		);

		//- Evaluate the patch field
		virtual void evaluate
		(
			const Pstream::commsTypes commsType
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
		virtual tmp<Field<Type>> gradientInternalCoeffs
		(
			const scalarField& deltaCoeffs
		) const;

		//- Return the matrix diagonal coefficients corresponding to the
		//  evaluation of the gradient of this patchField
		virtual tmp<Field<Type>> gradientInternalCoeffs() const;

		//- Return the matrix source coefficients corresponding to the
		//  evaluation of the gradient of this patchField
		virtual tmp<Field<Type>> gradientBoundaryCoeffs
		(
			const scalarField& deltaCoeffs
		) const;

		//- Return the matrix source coefficients corresponding to the
		//  evaluation of the gradient of this patchField
		virtual tmp<Field<Type>> gradientBoundaryCoeffs() const;


		// Coupled interface functionality

			//- Update result field based on interface functionality
		virtual void updateInterfaceMatrix
		(
			scalarField& result,
			const scalarField& psiInternal,
			const scalarField& coeffs,
			const direction,
			const Pstream::commsTypes commsType
		) const = 0;

		//- Update result field based on interface functionality
		virtual void updateInterfaceMatrix
		(
			Field<Type>&,
			const Field<Type>&,
			const scalarField&,
			const Pstream::commsTypes commsType
		) const = 0;


		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <coupledFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <coupledFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_coupledFvPatchField_Header
