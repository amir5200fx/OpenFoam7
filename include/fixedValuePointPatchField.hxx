#pragma once
#ifndef _fixedValuePointPatchField_Header
#define _fixedValuePointPatchField_Header

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
	tnbLib::fixedValuePointPatchField

Description
	A FixedValue boundary condition for pointField.

SourceFiles
	fixedValuePointPatchField.C

\*---------------------------------------------------------------------------*/

#include <valuePointPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class fixedValuePointPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class fixedValuePointPatchField
		:
		public valuePointPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName("fixedValue");
		static const char* typeName_() { return "fixedValue"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		fixedValuePointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&
		);

		//- Construct from patch, internal field and dictionary
		fixedValuePointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const dictionary&,
			const bool valueRequired = true
		);

		//- Construct by mapping given patchField<Type> onto a new patch
		fixedValuePointPatchField
		(
			const fixedValuePointPatchField<Type>&,
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const pointPatchFieldMapper&
		);

		//- Construct and return a clone
		virtual autoPtr<pointPatchField<Type>> clone() const
		{
			return autoPtr<pointPatchField<Type>>
				(
					new fixedValuePointPatchField<Type>
					(
						*this
						)
					);
		}

		//- Construct as copy setting internal field reference
		fixedValuePointPatchField
		(
			const fixedValuePointPatchField<Type>&,
			const DimensionedField<Type, pointMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual autoPtr<pointPatchField<Type>> clone
		(
			const DimensionedField<Type, pointMesh>& iF
		) const
		{
			return autoPtr<pointPatchField<Type>>
				(
					new fixedValuePointPatchField<Type>
					(
						*this,
						iF
						)
					);
		}


		// Member Functions

			// Access

				//- Return true if this patch field fixes a value
		virtual bool fixesValue() const
		{
			return true;
		}


		// Member Operators

			// Disable assignment operators

		virtual void operator=(const Field<Type>&) {}
		virtual void operator=(const Type&) {}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fixedValuePointPatchFieldI.hxx>

//#ifdef NoRepository
//#include <fixedValuePointPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedValuePointPatchField_Header
