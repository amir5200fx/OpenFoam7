#pragma once
#ifndef _cyclicAMIFvPatchField_Header
#define _cyclicAMIFvPatchField_Header

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
	tnbLib::cyclicAMIFvPatchField

Description
	This boundary condition enforces a cyclic condition between a pair of
	boundaries, whereby communication between the patches is performed using
	an arbitrary mesh interface (AMI) interpolation.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            cyclicAMI;
	}
	\endverbatim

Note
	The outer boundary of the patch pairs must be similar, i.e. if the owner
	patch is transformed to the neighbour patch, the outer perimiter of each
	patch should be identical (or very similar).

See also
	tnbLib::AMIInterpolation

SourceFiles
	cyclicAMIFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <coupledFvPatchField.hxx>
#include <cyclicAMILduInterfaceField.hxx>
#include <cyclicAMIFvPatch.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamCyclicAMIFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamCyclicAMIFvPatchField_EXPORT_DEFINE
#define FoamCyclicAMIFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamCyclicAMIFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class cyclicAMIFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class cyclicAMIFvPatchField
		:
		public coupledFvPatchField<Type>,
		public cyclicAMILduInterfaceField
	{
		// Private Data

			//- Local reference cast into the cyclic patch
		const cyclicAMIFvPatch& cyclicAMIPatch_;


	public:

		//- Runtime type information
		static const char* typeName_() { return cyclicAMIFvPatch::typeName_(); }
		static FoamCyclicAMIFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamCyclicAMIFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		cyclicAMIFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		cyclicAMIFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given cyclicAMIFvPatchField onto a new patch
		cyclicAMIFvPatchField
		(
			const cyclicAMIFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		cyclicAMIFvPatchField(const cyclicAMIFvPatchField<Type>&);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new cyclicAMIFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		cyclicAMIFvPatchField
		(
			const cyclicAMIFvPatchField<Type>&,
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
					new cyclicAMIFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Return local reference cast into the cyclic AMI patch
		const cyclicAMIFvPatch& cyclicAMIPatch() const
		{
			return cyclicAMIPatch_;
		}


		// Evaluation functions

			//- Return true if coupled. Note that the underlying patch
			//  is not coupled() - the points don't align.
		virtual bool coupled() const;

		//- Return neighbour coupled internal cell data
		virtual tmp<Field<Type>> patchNeighbourField() const;

		//- Return reference to neighbour patchField
		const cyclicAMIFvPatchField<Type>& neighbourPatchField() const;

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


		// Cyclic AMI coupled interface functions

			//- Does the patch field perform the transformation
		virtual bool doTransform() const
		{
			return
				!(cyclicAMIPatch_.parallel() || pTraits<Type>::rank == 0);
		}

		//- Return face transformation tensor
		virtual const tensorField& forwardT() const
		{
			return cyclicAMIPatch_.forwardT();
		}

		//- Return neighbour-cell transformation tensor
		virtual const tensorField& reverseT() const
		{
			return cyclicAMIPatch_.reverseT();
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

#include <cyclicAMIFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <cyclicAMIFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicAMIFvPatchField_Header
