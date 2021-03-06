#pragma once
#ifndef _zeroGradientFvPatchField_Header
#define _zeroGradientFvPatchField_Header

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
	tnbLib::zeroGradientFvPatchField

Description
	This boundary condition applies a zero-gradient condition from the patch
	internal field onto the patch faces.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            zeroGradient;
	}
	\endverbatim

SourceFiles
	zeroGradientFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchField.hxx>

#include <Pstream.hxx>  // added by amir

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamZeroGradientFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamZeroGradientFvPatchField_EXPORT_DEFINE
#define FoamZeroGradientFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamZeroGradientFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class zeroGradientFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class zeroGradientFvPatchField
		:
		public fvPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName("zeroGradient");
		static const char* typeName_() { return "zeroGradient"; }
		static FoamZeroGradientFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamZeroGradientFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		zeroGradientFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		zeroGradientFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping the given zeroGradientFvPatchField<Type>
		//  onto a new patch
		zeroGradientFvPatchField
		(
			const zeroGradientFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		zeroGradientFvPatchField
		(
			const zeroGradientFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new zeroGradientFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		zeroGradientFvPatchField
		(
			const zeroGradientFvPatchField<Type>&,
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
					new zeroGradientFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Evaluation functions

				//- Return gradient at boundary
		virtual tmp<Field<Type>> snGrad() const
		{
			return tmp<Field<Type>>
				(
					new Field<Type>(this->size(), Zero)
					);
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
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <zeroGradientFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <zeroGradientFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_zeroGradientFvPatchField_Header
