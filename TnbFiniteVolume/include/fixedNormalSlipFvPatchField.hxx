#pragma once
#ifndef _fixedNormalSlipFvPatchField_Header
#define _fixedNormalSlipFvPatchField_Header

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
	tnbLib::fixedNormalSlipFvPatchField

Description
	This boundary condition sets the patch-normal component to a fixed value.

Usage
	\table
		Property     | Description             | Required    | Default value
		fixedValue   | fixed value             | yes         |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            fixedNormalSlip;
		fixedValue      uniform 0;     // example entry for a scalar field
	}
	\endverbatim

See also
	tnbLib::transformFvPatchField

SourceFiles
	fixedNormalSlipFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <transformFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class fixedNormalSlipFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class fixedNormalSlipFvPatchField
		:
		public transformFvPatchField<Type>
	{
		// Private Data

			//- Value the normal component of which the boundary is set to
		Field<Type> fixedValue_;


	public:

		//- Runtime type information
		TypeName("fixedNormalSlip");


		// Constructors

			//- Construct from patch and internal field
		fixedNormalSlipFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		fixedNormalSlipFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given fixedNormalSlipFvPatchField
		//  onto a new patch
		fixedNormalSlipFvPatchField
		(
			const fixedNormalSlipFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		fixedNormalSlipFvPatchField
		(
			const fixedNormalSlipFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new fixedNormalSlipFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		fixedNormalSlipFvPatchField
		(
			const fixedNormalSlipFvPatchField<Type>&,
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
					new fixedNormalSlipFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Return false: this patch field is not altered by assignment
		virtual bool assignable() const
		{
			return false;
		}


		// Mapping functions

			//- Map (and resize as needed) from self given a mapping object
			//  Used to update fields following mesh topology change
		virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		virtual void rmap(const fvPatchField<Type>&, const labelList&);


		// Return defining fields

		virtual Field<Type>& fixedValue()
		{
			return fixedValue_;
		}

		virtual const Field<Type>& fixedValue() const
		{
			return fixedValue_;
		}


		// Evaluation functions

			//- Return gradient at boundary
		virtual tmp<Field<Type>> snGrad() const;

		//- Evaluate the patch field
		virtual void evaluate
		(
			const Pstream::commsTypes commsType =
			Pstream::commsTypes::blocking
		);

		//- Return face-gradient transform diagonal
		virtual tmp<Field<Type>> snGradTransformDiag() const;


		//- Write
		virtual void write(Ostream&) const;


		// Member Operators

		virtual void operator=(const UList<Type>&) {}

		virtual void operator=(const fvPatchField<Type>&) {}
		virtual void operator+=(const fvPatchField<Type>&) {}
		virtual void operator-=(const fvPatchField<Type>&) {}
		virtual void operator*=(const fvPatchField<scalar>&) {}
		virtual void operator/=(const fvPatchField<scalar>&) {}

		virtual void operator+=(const Field<Type>&) {}
		virtual void operator-=(const Field<Type>&) {}

		virtual void operator*=(const Field<scalar>&) {}
		virtual void operator/=(const Field<scalar>&) {}

		virtual void operator=(const Type&) {}
		virtual void operator+=(const Type&) {}
		virtual void operator-=(const Type&) {}
		virtual void operator*=(const scalar) {}
		virtual void operator/=(const scalar) {}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fixedNormalSlipFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <fixedNormalSlipFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedNormalSlipFvPatchField_Header
