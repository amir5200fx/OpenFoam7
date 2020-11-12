#pragma once
#ifndef _cellMotionFvPatchField_Header
#define _cellMotionFvPatchField_Header

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
	tnbLib::cellMotionFvPatchField

Description
	tnbLib::cellMotionFvPatchField

SourceFiles
	cellMotionFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <Random.hxx>
#include <fixedValueFvPatchFields.hxx>

#ifdef FoamFvMotionSolver_EXPORT_DEFINE
#define FoamcellMotionFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamcellMotionFvPatchField_EXPORT_DEFINE
#define FoamcellMotionFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamcellMotionFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class cellMotionFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class cellMotionFvPatchField
		:
		public fixedValueFvPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName("cellMotion");
		static const char* typeName_() { return "cellMotion"; }
		static FoamcellMotionFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamcellMotionFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		cellMotionFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		cellMotionFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given cellMotionFvPatchField
		//  onto a new patch
		cellMotionFvPatchField
		(
			const cellMotionFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		cellMotionFvPatchField
		(
			const cellMotionFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new cellMotionFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		cellMotionFvPatchField
		(
			const cellMotionFvPatchField<Type>&,
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
					new cellMotionFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			//- Update the coefficients associated with the patch field
		virtual void updateCoeffs();

		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <cellMotionFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <cellMotionFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellMotionFvPatchField_Header
