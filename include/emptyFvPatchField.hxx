#pragma once
#ifndef _emptyFvPatchField_Header
#define _emptyFvPatchField_Header

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
	tnbLib::emptyFvPatchField

Description
	This boundary condition provides an 'empty' condition for reduced
	dimensions cases, i.e. 1- and 2-D geometries.  Apply this condition to
	patches whose normal is aligned to geometric directions that do not
	constitue solution directions.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            empty;
	}
	\endverbatim

SourceFiles
	emptyFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchField.hxx>
#include <emptyFvPatch.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamEmptyFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamEmptyFvPatchField_EXPORT_DEFINE
#define FoamEmptyFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamEmptyFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class emptyFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class emptyFvPatchField
		:
		public fvPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName(emptyFvPatch::typeName_());
		static const char* typeName_() { return emptyFvPatch::typeName_(); }
		static FoamEmptyFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamEmptyFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		emptyFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		emptyFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given emptyFvPatchField onto a new patch
		emptyFvPatchField
		(
			const emptyFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		emptyFvPatchField
		(
			const emptyFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new emptyFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		emptyFvPatchField
		(
			const emptyFvPatchField<Type>&,
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
					new emptyFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Mapping functions

				//- Map (and resize as needed) from self given a mapping object
				//  Used to update fields following mesh topology change
		virtual void autoMap(const fvPatchFieldMapper&)
		{}

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		virtual void rmap(const fvPatchField<Type>&, const labelList&)
		{}


		// Evaluation functions

			//- Update the coefficients associated with the patch field
			//  This only checks to see the case is actually 1D or 2D
			//  for which this boundary condition is valid
		void updateCoeffs();


		//- Return the matrix diagonal coefficients corresponding to the
		//  evaluation of the value of this patchField with given weights
		virtual tmp<Field<Type>> valueInternalCoeffs
		(
			const tmp<scalarField>&
		) const
		{
			return tmp<Field<Type>>(new Field<Type>(0));
		}

		//- Return the matrix source coefficients corresponding to the
		//  evaluation of the value of this patchField with given weights
		virtual tmp<Field<Type>> valueBoundaryCoeffs
		(
			const tmp<scalarField>&
		) const
		{
			return tmp<Field<Type>>(new Field<Type>(0));
		}

		//- Return the matrix diagonal coefficients corresponding to the
		//  evaluation of the gradient of this patchField
		tmp<Field<Type>> gradientInternalCoeffs() const
		{
			return tmp<Field<Type>>(new Field<Type>(0));
		}

		//- Return the matrix source coefficients corresponding to the
		//  evaluation of the gradient of this patchField
		tmp<Field<Type>> gradientBoundaryCoeffs() const
		{
			return tmp<Field<Type>>(new Field<Type>(0));
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <emptyFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <emptyFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_emptyFvPatchField_Header
