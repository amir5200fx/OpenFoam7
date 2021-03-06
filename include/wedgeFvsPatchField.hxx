#pragma once
#ifndef _wedgeFvsPatchField_Header
#define _wedgeFvsPatchField_Header

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
	tnbLib::wedgeFvsPatchField

Description
	tnbLib::wedgeFvsPatchField

SourceFiles
	wedgeFvsPatchField.C

\*---------------------------------------------------------------------------*/

#include <fvsPatchField.hxx>
#include <wedgeFvPatch.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamWedgeFvsPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamWedgeFvsPatchField_EXPORT_DEFINE
#define FoamWedgeFvsPatchField_EXPORT __declspec(dllexport)
#else
#define FoamWedgeFvsPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class wedgeFvsPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class wedgeFvsPatchField
		:
		public fvsPatchField<Type>
	{

	public:

		//- Runtime type information
		/*TypeName(wedgeFvPatch::typeName_());*/
		static const char* typeName_() { return wedgeFvPatch::typeName_(); }
		static FoamWedgeFvsPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamWedgeFvsPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		wedgeFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct from patch, internal field and dictionary
		wedgeFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const dictionary&
		);

		//- Construct by mapping given wedgeFvsPatchField onto a new patch
		wedgeFvsPatchField
		(
			const wedgeFvsPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		wedgeFvsPatchField
		(
			const wedgeFvsPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type>> clone() const
		{
			return tmp<fvsPatchField<Type>>
				(
					new wedgeFvsPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		wedgeFvsPatchField
		(
			const wedgeFvsPatchField<Type>&,
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
					new wedgeFvsPatchField<Type>(*this, iF)
					);
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <wedgeFvsPatchFieldI.hxx>

//#ifdef NoRepository
//#include <wedgeFvsPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wedgeFvsPatchField_Header
