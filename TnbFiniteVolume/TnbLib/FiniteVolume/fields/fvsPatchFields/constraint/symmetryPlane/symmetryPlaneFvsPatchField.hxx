#pragma once
#ifndef _symmetryPlaneFvsPatchField_Header
#define _symmetryPlaneFvsPatchField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::symmetryPlaneFvsPatchField

Description
	tnbLib::symmetryPlaneFvsPatchField

SourceFiles
	symmetryPlaneFvsPatchField.C

\*---------------------------------------------------------------------------*/

#include <fvsPatchField.hxx>
#include <symmetryPlaneFvPatch.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamSymmetryPlaneFvsPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamSymmetryPlaneFvsPatchField_EXPORT_DEFINE
#define FoamSymmetryPlaneFvsPatchField_EXPORT __declspec(dllexport)
#else
#define FoamSymmetryPlaneFvsPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class symmetryPlaneFvsPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class symmetryPlaneFvsPatchField
		:
		public fvsPatchField<Type>
	{

	public:

		//- Runtime type information
		/*TypeName(symmetryPlaneFvPatch::typeName_());*/
		static const char* typeName_() { return symmetryPlaneFvPatch::typeName_(); }
		static FoamSymmetryPlaneFvsPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamSymmetryPlaneFvsPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from patch and internal field
		symmetryPlaneFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct from patch, internal field and dictionary
		symmetryPlaneFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const dictionary&
		);

		//- Construct by mapping given symmetryPlaneFvsPatchField
		//  onto a new patch
		symmetryPlaneFvsPatchField
		(
			const symmetryPlaneFvsPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		symmetryPlaneFvsPatchField
		(
			const symmetryPlaneFvsPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type>> clone() const
		{
			return tmp<fvsPatchField<Type>>
				(
					new symmetryPlaneFvsPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		symmetryPlaneFvsPatchField
		(
			const symmetryPlaneFvsPatchField<Type>&,
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
					new symmetryPlaneFvsPatchField<Type>(*this, iF)
					);
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <symmetryPlaneFvsPatchFieldI.hxx>

//#ifdef NoRepository
//#include <symmetryPlaneFvsPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_symmetryPlaneFvsPatchField_Header
