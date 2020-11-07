#pragma once
#ifndef _symmetryFvsPatchField_Header
#define _symmetryFvsPatchField_Header

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
	tnbLib::symmetryFvsPatchField

Description
	tnbLib::symmetryFvsPatchField

SourceFiles
	symmetryFvsPatchField.C

\*---------------------------------------------------------------------------*/

#include <fvsPatchField.hxx>
#include <symmetryFvPatch.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamSymmetryFvsPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamSymmetryFvsPatchField_EXPORT_DEFINE
#define FoamSymmetryFvsPatchField_EXPORT __declspec(dllexport)
#else
#define FoamSymmetryFvsPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class symmetryFvsPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class symmetryFvsPatchField
		:
		public fvsPatchField<Type>
	{

	public:

		//- Runtime type information
		/*TypeName(symmetryFvPatch::typeName_());*/
		static const char* typeName_() { return symmetryFvPatch::typeName_(); }
		static FoamSymmetryFvsPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamSymmetryFvsPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		symmetryFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct from patch, internal field and dictionary
		symmetryFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const dictionary&
		);

		//- Construct by mapping given symmetryFvsPatchField onto a new patch
		symmetryFvsPatchField
		(
			const symmetryFvsPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		symmetryFvsPatchField
		(
			const symmetryFvsPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type>> clone() const
		{
			return tmp<fvsPatchField<Type>>
				(
					new symmetryFvsPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		symmetryFvsPatchField
		(
			const symmetryFvsPatchField<Type>&,
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
					new symmetryFvsPatchField<Type>(*this, iF)
					);
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <symmetryFvsPatchFieldI.hxx>

//#ifdef NoRepository
//#include <symmetryFvsPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_symmetryFvsPatchField_Header
