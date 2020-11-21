#pragma once
#ifndef _calculatedFvPatchField_Header
#define _calculatedFvPatchField_Header

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
	tnbLib::calculatedFvPatchField

Description
	This boundary condition is not designed to be evaluated; it is assmued
	that the value is assigned via field assignment, and not via a call to
	e.g. \c updateCoeffs or \c evaluate.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            calculated;
		value           uniform (0 0 0);    // Required value entry
	}
	\endverbatim

SourceFiles
	calculatedFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchField.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamCalculatedFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamCalculatedFvPatchField_EXPORT_DEFINE
#define FoamCalculatedFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamCalculatedFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class calculatedFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class calculatedFvPatchField
		:
		public fvPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName("calculated");
		static const char* typeName_() { return "calculated"; }
		static FoamCalculatedFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamCalculatedFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		calculatedFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		calculatedFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&,
			const bool valueRequired = true
		);

		//- Construct by mapping given patchField<Type> onto a new patch
		calculatedFvPatchField
		(
			const calculatedFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&,
			const bool mappingRequired = true
		);

		//- Copy constructor
		calculatedFvPatchField
		(
			const calculatedFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new calculatedFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		calculatedFvPatchField
		(
			const calculatedFvPatchField<Type>&,
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
					new calculatedFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Attributes

				//- Return true if this patch field fixes a value.
				//  Needed to check if a level has to be specified while solving
				//  Poissons equations.
		virtual bool fixesValue() const
		{
			return true;
		}


		// Evaluation functions

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
		tmp<Field<Type>> gradientInternalCoeffs() const;

		//- Return the matrix source coefficients corresponding to the
		//  evaluation of the gradient of this patchField
		tmp<Field<Type>> gradientBoundaryCoeffs() const;


		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <calculatedFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <calculatedFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_calculatedFvPatchField_Header
