#pragma once
#ifndef _fixedJumpAMIFvPatchField_Header
#define _fixedJumpAMIFvPatchField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::fixedJumpAMIFvPatchField

Description
	This boundary condition provides a jump condition, across non-conformal
	cyclic path-pairs, employing an arbitraryMeshInterface (AMI).

	The jump is specified as a fixed value field, applied as an offset to the
	'owner' patch.

Usage
	\table
		Property     | Description             | Required    | Default value
		patchType    | underlying patch type should be \c cyclic| yes |
		jump         | current jump value      | yes         |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            fixedJumpAMI;
		patchType       cyclic;
		jump            uniform 10;
	}
	\endverbatim

	The above example shows the use of a fixed jump of '10'.

Note
	 The underlying \c patchType should be set to \c cyclicAMI

See also
	tnbLib::jumpCyclicAMIFvPatchField

SourceFiles
	fixedJumpAMIFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <jumpCyclicAMIFvPatchField.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamFixedJumpAMIFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamFixedJumpAMIFvPatchField_EXPORT_DEFINE
#define FoamFixedJumpAMIFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamFixedJumpAMIFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class fixedJumpAMIFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class fixedJumpAMIFvPatchField
		:
		public jumpCyclicAMIFvPatchField<Type>
	{

	protected:

		// Protected data

		//- "jump" field
		Field<Type> jump_;


	public:

		//- Runtime type information
		//TypeName("fixedJumpAMI");
		static const char* typeName_() { return "fixedJumpAMI"; }
		static FoamFixedJumpAMIFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamFixedJumpAMIFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		fixedJumpAMIFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		fixedJumpAMIFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given fixedJumpAMIFvPatchField onto a
		//  new patch
		fixedJumpAMIFvPatchField
		(
			const fixedJumpAMIFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		fixedJumpAMIFvPatchField
		(
			const fixedJumpAMIFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new fixedJumpAMIFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		fixedJumpAMIFvPatchField
		(
			const fixedJumpAMIFvPatchField<Type>&,
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
					new fixedJumpAMIFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Return the "jump" across the patch
		virtual tmp<Field<Type>> jump() const;


		// Mapping functions

			//- Map (and resize as needed) from self given a mapping object
		virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		virtual void rmap(const fvPatchField<Type>&, const labelList&);


		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fixedJumpAMIFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <fixedJumpAMIFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedJumpAMIFvPatchField_Header
