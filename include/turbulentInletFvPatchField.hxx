#pragma once
#ifndef _turbulentInletFvPatchField_Header
#define _turbulentInletFvPatchField_Header

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
	tnbLib::turbulentInletFvPatchField

Description
	This boundary condition generates a fluctuating inlet condition by adding
	a random component to a reference (mean) field.

	\f[
		x_p = (1 - \alpha) x_p^{n-1} + \alpha (x_{ref} + s C_{RMS} x_{ref})
	\f]

	where

	\vartable
		x_p     | patch values
		x_{ref} | reference patch values
		n       | time level
		\alpha  | fraction of new random component added to previous time value
		C_{RMS} | RMS coefficient
		s       | fluctuation scale
	\endvartable

Usage
	\table
		Property     | Description             | Required    | Default value
		fluctuationScale | RMS fluctuation scale (fraction of mean) | yes |
		referenceField | reference (mean) field | yes        |
		alpha | fraction of new random component added to previous| no| 0.1
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            turbulentInlet;
		fluctuationScale 0.1;
		referenceField  uniform 10;
		alpha           0.1;
	}
	\endverbatim

See also
	tnbLib::fixedValueFvPatchField

SourceFiles
	turbulentInletFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <Random.hxx>
#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class turbulentInletFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class turbulentInletFvPatchField
		:
		public fixedValueFvPatchField<Type>
	{
		// Private Data

			//- Random number generator
		Random ranGen_;

		//- Fluctuation scale
		Type fluctuationScale_;

		//- Reference field
		Field<Type> referenceField_;

		//- Fraction of RMS component to apply to last time step values
		scalar alpha_;

		//- Current time index (used for updating)
		label curTimeIndex_;


	public:

		//- Runtime type information
		TypeName("turbulentInlet");


		// Constructors

			//- Construct from patch and internal field
		turbulentInletFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		turbulentInletFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given turbulentInletFvPatchField
		//  onto a new patch
		turbulentInletFvPatchField
		(
			const turbulentInletFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		turbulentInletFvPatchField
		(
			const turbulentInletFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new turbulentInletFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		turbulentInletFvPatchField
		(
			const turbulentInletFvPatchField<Type>&,
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
					new turbulentInletFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Return the fluctuation scale
		const Type& fluctuationScale() const
		{
			return fluctuationScale_;
		}

		//- Return reference to the fluctuation scale to allow adjustment
		Type& fluctuationScale()
		{
			return fluctuationScale_;
		}

		//- Return the reference field
		const Field<Type>& referenceField() const
		{
			return referenceField_;
		}

		//- Return reference to the reference field to allow adjustment
		Field<Type>& referenceField()
		{
			return referenceField_;
		}


		// Mapping functions

			//- Map (and resize as needed) from self given a mapping object
			//  Used to update fields following mesh topology change
		virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		virtual void rmap(const fvPatchField<Type>&, const labelList&);


		// Evaluation functions

			//- Update the coefficients associated with the patch field
		virtual void updateCoeffs();


		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <turbulentInletFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <turbulentInletFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_turbulentInletFvPatchField_Header
