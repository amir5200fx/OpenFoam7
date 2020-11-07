#pragma once
#ifndef _symmetryFvPatchField_Header
#define _symmetryFvPatchField_Header

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
	tnbLib::symmetryFvPatchField

Description
	This boundary condition enforces a symmetry constraint

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            symmetry;
	}
	\endverbatim

SourceFiles
	symmetryFvPatchField.C
	symmetryFvPatchFields.C
	symmetryFvPatchFields.H
	symmetryFvPatchFieldsFwd.H

\*---------------------------------------------------------------------------*/

#include <basicSymmetryFvPatchField.hxx>
#include <symmetryFvPatch.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamSymmetryFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamSymmetryFvPatchField_EXPORT_DEFINE
#define FoamSymmetryFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamSymmetryFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class symmetryFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class symmetryFvPatchField
		:
		public basicSymmetryFvPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName(symmetryFvPatch::typeName_());
		static const char* typeName_() { return symmetryFvPatch::typeName_(); }
		static FoamSymmetryFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamSymmetryFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		symmetryFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		symmetryFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given symmetryFvPatchField onto a new patch
		symmetryFvPatchField
		(
			const symmetryFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		symmetryFvPatchField
		(
			const symmetryFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new symmetryFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		symmetryFvPatchField
		(
			const symmetryFvPatchField<Type>&,
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
					new symmetryFvPatchField<Type>(*this, iF)
					);
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <symmetryFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <symmetryFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_symmetryFvPatchField_Header
