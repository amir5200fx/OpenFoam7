#pragma once
#ifndef _fixedInternalValueFvPatchField_Header
#define _fixedInternalValueFvPatchField_Header

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
	tnbLib::fixedInternalValueFvPatchField

Description
	This boundary condition provides a mechanism to set boundary (cell) values
	directly into a matrix, i.e. to set a constraint condition.  Default
	behaviour is to act as a zero gradient condition.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            fixedInternalValue;
		value           uniform 0;              // place holder
	}
	\endverbatim

Note
	This is used as a base for conditions such as the turbulence \c epsilon
	wall function, which applies a near-wall constraint for high Reynolds
	number flows.

See also
	tnbLib::epsilonWallFunctionFvPatchScalarField

SourceFiles
	fixedInternalValueFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <zeroGradientFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				  Class fixedInternalValueFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class fixedInternalValueFvPatchField
		:
		public zeroGradientFvPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName("fixedInternalValue");
		static const char* typeName_() { return "fixedInternalValue"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT fixedInternalValueFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT fixedInternalValueFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping the given fixedInternalValueFvPatchField<Type>
		//  onto a new patch
		FoamFiniteVolume_EXPORT fixedInternalValueFvPatchField
		(
			const fixedInternalValueFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT fixedInternalValueFvPatchField
		(
			const fixedInternalValueFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new fixedInternalValueFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT fixedInternalValueFvPatchField
		(
			const fixedInternalValueFvPatchField<Type>&,
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
					new fixedInternalValueFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Evaluation functions

				//-Manipulate a matrix
		FoamFiniteVolume_EXPORT virtual void manipulateMatrix(fvMatrix<Type>& matrix);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fixedInternalValueFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <fixedInternalValueFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedInternalValueFvPatchField_Header
