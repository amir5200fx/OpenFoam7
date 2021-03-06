#pragma once
#ifndef _kqRWallFunctionFvPatchField_Header
#define _kqRWallFunctionFvPatchField_Header

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
	tnbLib::kqRWallFunctionFvPatchField

Description
	This boundary condition provides a suitable condition for turbulence
	\c k, \c q, and \c R fields for the case of high Reynolds number flow using
	wall functions.

	It is a simple wrapper around the zero-gradient condition.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            kqRWallFunction;
	}
	\endverbatim

See also
	tnbLib::zeroGradientFvPatchField

SourceFiles
	kqRWallFunctionFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <zeroGradientFvPatchField.hxx>

#ifdef FoamTurbulence_EXPORT_DEFINE
#define FoamkqRWallFunctionFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamkqRWallFunctionFvPatchField_EXPORT_DEFINE
#define FoamkqRWallFunctionFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamkqRWallFunctionFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					Class kqRWallFunctionFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class kqRWallFunctionFvPatchField
		:
		public zeroGradientFvPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName("kqRWallFunction");
		static const char* typeName_() { return "kqRWallFunction"; }
		static FoamkqRWallFunctionFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamkqRWallFunctionFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		kqRWallFunctionFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		kqRWallFunctionFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		// kqRWallFunctionFvPatchField
		//  onto a new patch
		kqRWallFunctionFvPatchField
		(
			const kqRWallFunctionFvPatchField&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		kqRWallFunctionFvPatchField
		(
			const kqRWallFunctionFvPatchField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new kqRWallFunctionFvPatchField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		kqRWallFunctionFvPatchField
		(
			const kqRWallFunctionFvPatchField&,
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
					new kqRWallFunctionFvPatchField(*this, iF)
					);
		}


		// Member Functions

			//- Evaluate the patchField
		virtual void evaluate
		(
			const Pstream::commsTypes commsType = Pstream::commsTypes::blocking
		);

		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <kqRWallFunctionFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <kqRWallFunctionFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_kqRWallFunctionFvPatchField_Header
