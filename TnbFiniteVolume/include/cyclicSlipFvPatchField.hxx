#pragma once
#ifndef _cyclicSlipFvPatchField_Header
#define _cyclicSlipFvPatchField_Header

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
	tnbLib::cyclicSlipFvPatchField

Description
	This boundary condition is a light wrapper around the cyclicFvPatchField
	condition, providing no new functionality.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            cyclicSlip;
	}
	\endverbatim

See also
	tnbLib::cyclicFvPatchField

SourceFiles
	cyclicSlipFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <cyclicFvPatchField.hxx>
#include <cyclicSlipFvPatch.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamCyclicSlipFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamCyclicSlipFvPatchField_EXPORT_DEFINE
#define FoamCyclicSlipFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamCyclicSlipFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class cyclicSlipFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class cyclicSlipFvPatchField
		:
		public cyclicFvPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName(cyclicSlipFvPatch::typeName_());
		static const char* typeName_() { return cyclicSlipFvPatch::typeName_(); }
		static FoamCyclicSlipFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamCyclicSlipFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		cyclicSlipFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		cyclicSlipFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given cyclicSlipFvPatchField onto a new patch
		cyclicSlipFvPatchField
		(
			const cyclicSlipFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		cyclicSlipFvPatchField
		(
			const cyclicSlipFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new cyclicSlipFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		cyclicSlipFvPatchField
		(
			const cyclicSlipFvPatchField<Type>&,
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
					new cyclicSlipFvPatchField<Type>(*this, iF)
					);
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <cyclicSlipFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <cyclicSlipFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicSlipFvPatchField_Header
