#pragma once
#ifndef _coupledFvsPatchField_Header
#define _coupledFvsPatchField_Header

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
	tnbLib::coupledFvsPatchField

Description
	tnbLib::coupledFvsPatchField

SourceFiles
	coupledFvsPatchField.C

\*---------------------------------------------------------------------------*/

#include <fvsPatchField.hxx>
#include <coupledFvPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class coupledFvsPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class coupledFvsPatchField
		:
		public fvsPatchField<Type>
	{

	public:

		//- Runtime type information
		TypeName(coupledFvPatch::typeName_());


		// Constructors

			//- Construct from patch and internal field
		coupledFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct from patch and internal field and patch field
		coupledFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const Field<Type>&
		);

		//- Construct from patch, internal field and dictionary
		coupledFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const dictionary&
		);

		//- Construct by mapping the given coupledFvsPatchField onto a new patch
		coupledFvsPatchField
		(
			const coupledFvsPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		coupledFvsPatchField
		(
			const coupledFvsPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type>> clone() const = 0;

		//- Copy constructor setting internal field reference
		coupledFvsPatchField
		(
			const coupledFvsPatchField<Type>&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type>> clone
		(
			const DimensionedField<Type, surfaceMesh>&
		) const = 0;


		// Member Functions

			// Access

				//- Return true if this patch field is derived from
				//  coupledFvsPatchField<Type>.
		virtual bool coupled() const
		{
			return true;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <coupledFvsPatchFieldI.hxx>

//#ifdef NoRepository
//#include <coupledFvsPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_coupledFvsPatchField_Header