#pragma once
#ifndef _zeroFixedValuePointPatchField_Header
#define _zeroFixedValuePointPatchField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2014-2019 OpenFOAM Foundation
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
	tnbLib::zeroFixedValuePointPatchField

Description
	Enables the specification of a zero fixed value boundary condition.

	Example of the boundary condition specification:
	\verbatim
	inlet
	{
		type            zeroFixedValue;
	}
	\endverbatim

SourceFiles
	zeroFixedValuePointPatchField.C

\*---------------------------------------------------------------------------*/

#include <fixedValuePointPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			  Class zeroFixedValuePointPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class zeroFixedValuePointPatchField
		:
		public fixedValuePointPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName("zeroFixedValue");
		static const char* typeName_() { return "zeroFixedValue"; }
		static FoamSnappyHexMesh_EXPORT const ::tnbLib::word typeName;
		static FoamSnappyHexMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamSnappyHexMesh_EXPORT zeroFixedValuePointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamSnappyHexMesh_EXPORT zeroFixedValuePointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const dictionary&
		);

		//- Construct by mapping given patchField<Type> onto a new patch
		FoamSnappyHexMesh_EXPORT zeroFixedValuePointPatchField
		(
			const zeroFixedValuePointPatchField<Type>&,
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const pointPatchFieldMapper&
		);

		//- Copy constructor
		FoamSnappyHexMesh_EXPORT zeroFixedValuePointPatchField
		(
			const zeroFixedValuePointPatchField<Type>&
		);

		//- Construct and return a clone
		virtual autoPtr<pointPatchField<Type>> clone() const
		{
			return autoPtr<pointPatchField<Type>>
				(
					new zeroFixedValuePointPatchField<Type>
					(
						*this
						)
					);
		}

		//- Copy constructor setting internal field reference
		FoamSnappyHexMesh_EXPORT zeroFixedValuePointPatchField
		(
			const zeroFixedValuePointPatchField<Type>&,
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
					new zeroFixedValuePointPatchField<Type>
					(
						*this,
						iF
						)
					);
		}

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
//#include <zeroFixedValuePointPatchField.cxx>
#endif

#include <zeroFixedValuePointPatchFieldI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_zeroFixedValuePointPatchField_Header
