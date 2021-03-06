#pragma once
#ifndef _basicSymmetryFvPatchField_Header
#define _basicSymmetryFvPatchField_Header

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
	tnbLib::basicSymmetryFvPatchField

Description
	A symmetry patch

SourceFiles
	basicSymmetryFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <transformFvPatchField.hxx>
#include <symmetryFvPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class basicSymmetryFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class basicSymmetryFvPatchField
		:
		public transformFvPatchField<Type>
	{

	public:

		// Constructors

			//- Construct from patch and internal field
		basicSymmetryFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		basicSymmetryFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given basicSymmetryFvPatchField onto a new
		//  patch
		basicSymmetryFvPatchField
		(
			const basicSymmetryFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		basicSymmetryFvPatchField
		(
			const basicSymmetryFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new basicSymmetryFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		basicSymmetryFvPatchField
		(
			const basicSymmetryFvPatchField<Type>&,
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
					new basicSymmetryFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			//- Return gradient at boundary
		virtual tmp<Field<Type>> snGrad() const;

		//- Evaluate the patch field
		virtual void evaluate
		(
			const Pstream::commsTypes commsType = Pstream::commsTypes::blocking
		);

		//- Return face-gradient transform diagonal
		virtual tmp<Field<Type>> snGradTransformDiag() const;
	};


	// * * * * * * * * * * * Template Specialisations  * * * * * * * * * * * * * //

	template<>
	FoamFiniteVolume_EXPORT tmp<scalarField > basicSymmetryFvPatchField<scalar>::snGrad() const;

	template<>
	FoamFiniteVolume_EXPORT void basicSymmetryFvPatchField<scalar>::evaluate
	(
		const Pstream::commsTypes commsType
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <basicSymmetryFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <basicSymmetryFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_basicSymmetryFvPatchField_Header
