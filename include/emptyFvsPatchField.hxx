#pragma once
#ifndef _emptyFvsPatchField_Header
#define _emptyFvsPatchField_Header

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
	tnbLib::emptyFvsPatchField

Description
	tnbLib::emptyFvsPatchField

SourceFiles
	emptyFvsPatchField.C

\*---------------------------------------------------------------------------*/

#include <fvsPatchField.hxx>
#include <emptyFvPatch.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamEmptyFvsPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamEmptyFvsPatchField_EXPORT_DEFINE
#define FoamEmptyFvsPatchField_EXPORT __declspec(dllexport)
#else
#define FoamEmptyFvsPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class emptyFvsPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class emptyFvsPatchField
		:
		public fvsPatchField<Type>
	{

	public:

		//- Runtime type information
		/*TypeName(emptyFvPatch::typeName_());*/
		static const char* typeName_() { return emptyFvPatch::typeName_(); }
		static FoamEmptyFvsPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamEmptyFvsPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		emptyFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct from patch, internal field and dictionary
		emptyFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const dictionary&
		);

		//- Construct by mapping given emptyFvsPatchField onto a new patch
		emptyFvsPatchField
		(
			const emptyFvsPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		emptyFvsPatchField
		(
			const emptyFvsPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type>> clone() const
		{
			return tmp<fvsPatchField<Type>>
				(
					new emptyFvsPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		emptyFvsPatchField
		(
			const emptyFvsPatchField<Type>&,
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
					new emptyFvsPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Mapping functions

				//- Map (and resize as needed) from self given a mapping object
				//  Used to update fields following mesh topology change
		virtual void autoMap(const fvPatchFieldMapper&)
		{}

		//- Reverse map the given fvsPatchField onto this fvsPatchField
		//  Used to reconstruct fields
		virtual void rmap(const fvsPatchField<Type>&, const labelList&)
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <emptyFvsPatchFieldI.hxx>

//#ifdef NoRepository
//#include <emptyFvsPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_emptyFvsPatchField_Header
