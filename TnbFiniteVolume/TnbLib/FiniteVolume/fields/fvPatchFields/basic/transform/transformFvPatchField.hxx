#pragma once
#ifndef _transformFvPatchField_Header
#define _transformFvPatchField_Header

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
	tnbLib::transformFvPatchField

Description
	tnbLib::transformFvPatchField

SourceFiles
	transformFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchField.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamTransformFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamTransformFvPatchField_EXPORT_DEFINE
#define FoamTransformFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamTransformFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class transformFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class transformFvPatchField
		:
		public fvPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName("transform");
		static const char* typeName_() { return "transform"; }
		static FoamTransformFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamTransformFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		transformFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		transformFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping the given transformFvPatchField<Type>
		//  onto a new patch
		transformFvPatchField
		(
			const transformFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		transformFvPatchField
		(
			const transformFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const = 0;

		//- Copy constructor setting internal field reference
		transformFvPatchField
		(
			const transformFvPatchField<Type>&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvPatchField<Type>> clone
		(
			const DimensionedField<Type, volMesh>&
		) const = 0;


		// Member Functions

			// Attributes

				//- Return true if the value of the patch field
				//  is altered by assignment
		virtual bool assignable() const
		{
			return true;
		}


		// Evaluation functions

			//- Return gradient at boundary
		virtual tmp<Field<Type>> snGrad() const = 0;

		//- Return face-gradient transform diagonal
		virtual tmp<Field<Type>> snGradTransformDiag() const = 0;

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


		// Member Operators

		virtual void operator=(const fvPatchField<Type>&);
	};


	// * * * * * * * * * * * Template Specialisations  * * * * * * * * * * * * * //

	template<>
	FoamFiniteVolume_EXPORT tmp<scalarField> transformFvPatchField<scalar>::valueInternalCoeffs
	(
		const tmp<scalarField>&
	) const;

	template<>
	FoamFiniteVolume_EXPORT tmp<scalarField> transformFvPatchField<scalar>::gradientInternalCoeffs() const;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <transformFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <transformFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_transformFvPatchField_Header
