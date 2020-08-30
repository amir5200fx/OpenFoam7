#pragma once
#ifndef _partialSlipFvPatchField_Header
#define _partialSlipFvPatchField_Header

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
	tnbLib::partialSlipFvPatchField

Description
	This boundary condition provides a partial slip condition.  The amount of
	slip is controlled by a user-supplied field.

Usage
	\table
		Property      | Description             | Required    | Default value
		valueFraction | fraction of value used for boundary [0-1] | yes |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            partialSlip;
		valueFraction   uniform 0.1;
		value           uniform 0;
	}
	\endverbatim

See also
	tnbLib::transformFvPatchField

SourceFiles
	partialSlipFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <transformFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class partialSlipFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class partialSlipFvPatchField
		:
		public transformFvPatchField<Type>
	{
		// Private Data

			//- Fraction (0-1) of value used for boundary condition
		scalarField valueFraction_;


	public:

		//- Runtime type information
		TypeName("partialSlip");


		// Constructors

			//- Construct from patch and internal field
		partialSlipFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		partialSlipFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given partialSlipFvPatchField onto a new patch
		partialSlipFvPatchField
		(
			const partialSlipFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		partialSlipFvPatchField
		(
			const partialSlipFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new partialSlipFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		partialSlipFvPatchField
		(
			const partialSlipFvPatchField<Type>&,
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
					new partialSlipFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Attributes

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

		virtual scalarField& valueFraction()
		{
			return valueFraction_;
		}

		virtual const scalarField& valueFraction() const
		{
			return valueFraction_;
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

#ifdef NoRepository
#include <partialSlipFvPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_partialSlipFvPatchField_Header