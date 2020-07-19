#pragma once
#ifndef _wedgeFvPatchField_Header
#define _wedgeFvPatchField_Header

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
	tnbLib::wedgeFvPatchField

Description
	This boundary condition is similar to the cyclic condition, except that
	it is applied to 2-D geometries.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            wedge;
	}
	\endverbatim

See also
	tnbLib::cyclicFvPatchField

SourceFiles
	wedgeFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <transformFvPatchField.hxx>
#include <wedgeFvPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class wedgeFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class wedgeFvPatchField
		:
		public transformFvPatchField<Type>
	{

	public:

		//- Runtime type information
		TypeName(wedgeFvPatch::typeName_());


		// Constructors

			//- Construct from patch and internal field
		wedgeFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		wedgeFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given wedgeFvPatchField onto a new patch
		wedgeFvPatchField
		(
			const wedgeFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		wedgeFvPatchField
		(
			const wedgeFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new wedgeFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		wedgeFvPatchField
		(
			const wedgeFvPatchField<Type>&,
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
					new wedgeFvPatchField<Type>(*this, iF)
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
	tmp<scalarField > wedgeFvPatchField<scalar>::snGrad() const;

	template<>
	void wedgeFvPatchField<scalar>::evaluate
	(
		const Pstream::commsTypes commsType
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <wedgeFvPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wedgeFvPatchField_Header
