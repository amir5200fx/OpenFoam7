#pragma once
#ifndef _nonuniformTransformCyclicFvsPatchField_Header
#define _nonuniformTransformCyclicFvsPatchField_Header

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
	tnbLib::nonuniformTransformCyclicFvsPatchField

Description
	tnbLib::nonuniformTransformCyclicFvsPatchField

SourceFiles
	nonuniformTransformCyclicFvsPatchField.C

\*---------------------------------------------------------------------------*/

#include <cyclicFvsPatchField.hxx>
#include <nonuniformTransformCyclicFvPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				 Class nonuniformTransformCyclicFvsPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class nonuniformTransformCyclicFvsPatchField
		:
		public cyclicFvsPatchField<Type>
	{

	public:

		//- Runtime type information
		TypeName(nonuniformTransformCyclicFvPatch::typeName_());


		// Constructors

			//- Construct from patch and internal field
		nonuniformTransformCyclicFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct from patch, internal field and dictionary
		nonuniformTransformCyclicFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  nonuniformTransformCyclicFvsPatchField onto a new patch
		nonuniformTransformCyclicFvsPatchField
		(
			const nonuniformTransformCyclicFvsPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		nonuniformTransformCyclicFvsPatchField
		(
			const nonuniformTransformCyclicFvsPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type>> clone() const
		{
			return tmp<fvsPatchField<Type>>
				(
					new nonuniformTransformCyclicFvsPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		nonuniformTransformCyclicFvsPatchField
		(
			const nonuniformTransformCyclicFvsPatchField<Type>&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvsPatchField<Type>> clone
		(
			const DimensionedField<Type, surfaceMesh>& iF
		) const
		{
			return tmp<fvsPatchField<Type>>
				(
					new nonuniformTransformCyclicFvsPatchField<Type>(*this, iF)
					);
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <nonuniformTransformCyclicFvsPatchFieldI.hxx>

//#ifdef NoRepository
//#include <nonuniformTransformCyclicFvsPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_nonuniformTransformCyclicFvsPatchField_Header
