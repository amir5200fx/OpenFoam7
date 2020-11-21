#pragma once
#ifndef _coupledPointPatchField_Header
#define _coupledPointPatchField_Header

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
	tnbLib::coupledPointPatchField

Description
	A Coupled boundary condition for pointField

SourceFiles
	coupledPointPatchField.C

\*---------------------------------------------------------------------------*/

#include <pointPatchField.hxx>
#include <coupledPointPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class coupledPointPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class coupledPointPatchField
		:
		public pointPatchField<Type>
	{

	public:

		//- Runtime type information
		//TypeName(coupledPointPatch::typeName_());
		static const char* typeName_() { return coupledPointPatch::typeName_(); }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		coupledPointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&
		);

		//- Construct from patch, internal field and dictionary
		coupledPointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const dictionary& dict
		);

		//- Construct by mapping given patchField<Type> onto a new patch
		coupledPointPatchField
		(
			const coupledPointPatchField<Type>&,
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const pointPatchFieldMapper&
		);

		//- Construct and return a clone
		virtual autoPtr<pointPatchField<Type>> clone() const = 0;

		//- Construct as copy setting internal field reference
		coupledPointPatchField
		(
			const coupledPointPatchField<Type>&,
			const DimensionedField<Type, pointMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual autoPtr<pointPatchField<Type>> clone
		(
			const DimensionedField<Type, pointMesh>& iF
		) const = 0;


		// Member Functions

			// Access

				//- Return true if this patch field is derived from
				//  coupledFvPatchField<Type>.
		virtual bool coupled() const
		{
			return true;
		}

		//- Evaluate the patch field
		virtual void evaluate
		(
			const Pstream::commsTypes commsType =
			Pstream::commsTypes::blocking
		) = 0;

		//- Initialise swap of patch point values
		virtual void initSwapAddSeparated
		(
			const Pstream::commsTypes,
			Field<Type>&
		) const
		{}

		//- Complete swap of patch point values and add to local values
		virtual void swapAddSeparated
		(
			const Pstream::commsTypes,
			Field<Type>&
		) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <coupledPointPatchFieldI.hxx>

//#ifdef NoRepository
//#include <coupledPointPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_coupledPointPatchField_Header
