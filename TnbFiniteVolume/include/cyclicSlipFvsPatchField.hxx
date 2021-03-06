#pragma once
#ifndef _cyclicSlipFvsPatchField_Header
#define _cyclicSlipFvsPatchField_Header

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
	tnbLib::cyclicSlipFvsPatchField

Description
	tnbLib::cyclicSlipFvsPatchField

SourceFiles
	cyclicSlipFvsPatchField.C

\*---------------------------------------------------------------------------*/

#include <cyclicFvsPatchField.hxx>
#include <cyclicSlipFvPatch.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamCyclicSlipFvsPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamCyclicSlipFvsPatchField_EXPORT_DEFINE
#define FoamCyclicSlipFvsPatchField_EXPORT __declspec(dllexport)
#else
#define FoamCyclicSlipFvsPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class cyclicSlipFvsPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class cyclicSlipFvsPatchField
		:
		public cyclicFvsPatchField<Type>
	{

	public:

		//- Runtime type information
		/*TypeName(cyclicSlipFvPatch::typeName_());*/
		static const char* typeName_() { return cyclicSlipFvPatch::typeName_(); }
		static FoamCyclicSlipFvsPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamCyclicSlipFvsPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		cyclicSlipFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct from patch, internal field and dictionary
		cyclicSlipFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const dictionary&
		);

		//- Construct by mapping given cyclicSlipFvsPatchField onto a new patch
		cyclicSlipFvsPatchField
		(
			const cyclicSlipFvsPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		cyclicSlipFvsPatchField
		(
			const cyclicSlipFvsPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type>> clone() const
		{
			return tmp<fvsPatchField<Type>>
				(
					new cyclicSlipFvsPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		cyclicSlipFvsPatchField
		(
			const cyclicSlipFvsPatchField<Type>&,
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
					new cyclicSlipFvsPatchField<Type>(*this, iF)
					);
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <cyclicSlipFvsPatchFieldI.hxx>

//#ifdef NoRepository
//#include <cyclicSlipFvsPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicSlipFvsPatchField_Header
