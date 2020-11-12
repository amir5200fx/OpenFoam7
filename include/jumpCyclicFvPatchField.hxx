#pragma once
#ifndef _jumpCyclicFvPatchField_Header
#define _jumpCyclicFvPatchField_Header

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
	tnbLib::jumpCyclicFvPatchField

Description
	This boundary condition provides a base class for coupled-cyclic
	conditions with a specified 'jump' (or offset) between the values

See also
	tnbLib::cyclicFvPatchField

SourceFiles
	jumpCyclicFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <cyclicFvPatchField.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamJumpCyclicFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamJumpCyclicFvPatchField_EXPORT_DEFINE
#define FoamJumpCyclicFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamJumpCyclicFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class jumpCyclicFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class jumpCyclicFvPatchField
		:
		public cyclicFvPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName("jumpCyclic");
		static const char* typeName_() { return "jumpCyclic"; }
		static FoamJumpCyclicFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamJumpCyclicFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		jumpCyclicFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		jumpCyclicFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given jumpCyclicFvPatchField onto a new patch
		jumpCyclicFvPatchField
		(
			const jumpCyclicFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		jumpCyclicFvPatchField
		(
			const jumpCyclicFvPatchField<Type>&
		);

		//- Copy constructor setting internal field reference
		jumpCyclicFvPatchField
		(
			const jumpCyclicFvPatchField<Type>&,
			const DimensionedField<Type, volMesh>&
		);


		// Member Functions

			// Access

				//- Return the interface type
		virtual const word& interfaceFieldType() const
		{
			return cyclicFvPatchField<Type>::type();
		}

		//- Return the "jump" across the patch as a "half" field
		virtual tmp<Field<Type>> jump() const = 0;


		// Evaluation functions

			//- Return neighbour coupled given internal cell data
		tmp<Field<Type>> patchNeighbourField() const;

		//- Update result field based on interface functionality
		virtual void updateInterfaceMatrix
		(
			scalarField& result,
			const scalarField& psiInternal,
			const scalarField& coeffs,
			const direction cmpt,
			const Pstream::commsTypes commsType
		) const;

		//- Update result field based on interface functionality
		virtual void updateInterfaceMatrix
		(
			Field<Type>&,
			const Field<Type>&,
			const scalarField&,
			const Pstream::commsTypes commsType
		) const;
	};

	//- Update result field based on interface functionality
	template<>
	FoamFiniteVolume_EXPORT void jumpCyclicFvPatchField<scalar>::updateInterfaceMatrix
	(
		scalarField& result,
		const scalarField& psiInternal,
		const scalarField& coeffs,
		const direction cmpt,
		const Pstream::commsTypes commsType
	) const;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <jumpCyclicFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <jumpCyclicFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_jumpCyclicFvPatchField_Header
