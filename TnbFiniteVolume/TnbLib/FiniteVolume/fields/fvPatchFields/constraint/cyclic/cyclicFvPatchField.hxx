#pragma once
#ifndef _cyclicFvPatchField_Header
#define _cyclicFvPatchField_Header

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
	tnbLib::cyclicFvPatchField

Description
	This boundary condition enforces a cyclic condition between a pair of
	boundaries.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            cyclic;
	}
	\endverbatim

Note
	The patches must be topologically similar, i.e. if the owner patch is
	transformed to the neighbour patch, the patches should be identical (or
	very similar).

SourceFiles
	cyclicFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <coupledFvPatchField.hxx>
#include <cyclicLduInterfaceField.hxx>
#include <cyclicFvPatch.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamCyclicFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamCyclicFvPatchField_EXPORT_DEFINE
#define FoamCyclicFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamCyclicFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class cyclicFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class cyclicFvPatchField
		:
		public coupledFvPatchField<Type>,
		public cyclicLduInterfaceField
	{
		// Private Data

			//- Local reference cast into the cyclic patch
		const cyclicFvPatch& cyclicPatch_;


	public:

		//- Runtime type information
		//TypeName(cyclicFvPatch::typeName_());
		static const char* typeName_() { return cyclicFvPatch::typeName_(); }
		static FoamCyclicFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamCyclicFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		cyclicFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		cyclicFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given cyclicFvPatchField onto a new patch
		cyclicFvPatchField
		(
			const cyclicFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		cyclicFvPatchField
		(
			const cyclicFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new cyclicFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		cyclicFvPatchField
		(
			const cyclicFvPatchField<Type>&,
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
					new cyclicFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Return local reference cast into the cyclic patch
		const cyclicFvPatch& cyclicPatch() const
		{
			return cyclicPatch_;
		}


		// Evaluation functions

			//- Return neighbour coupled internal cell data
		tmp<Field<Type>> patchNeighbourField() const;

		//- Return reference to neighbour patchField
		const cyclicFvPatchField<Type>& neighbourPatchField() const;

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
			Field<Type>& result,
			const Field<Type>& psiInternal,
			const scalarField& coeffs,
			const Pstream::commsTypes commsType
		) const;


		// Cyclic coupled interface functions

			//- Does the patch field perform the transformation
		virtual bool doTransform() const
		{
			return !(cyclicPatch_.parallel() || pTraits<Type>::rank == 0);
		}

		//- Return face transformation tensor
		virtual const tensorField& forwardT() const
		{
			return cyclicPatch_.forwardT();
		}

		//- Return neighbour-cell transformation tensor
		virtual const tensorField& reverseT() const
		{
			return cyclicPatch_.reverseT();
		}

		//- Return rank of component for transform
		virtual int rank() const
		{
			return pTraits<Type>::rank;
		}


		// I-O

			//- Write
		virtual void write(Ostream& os) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <cyclicFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <cyclicFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicFvPatchField_Header
