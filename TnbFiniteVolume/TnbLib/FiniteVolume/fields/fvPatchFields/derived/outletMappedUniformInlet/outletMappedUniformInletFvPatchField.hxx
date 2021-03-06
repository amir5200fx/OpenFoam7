#pragma once
#ifndef _outletMappedUniformInletFvPatchField_Header
#define _outletMappedUniformInletFvPatchField_Header

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
	tnbLib::outletMappedUniformInletFvPatchField

Description
	This boundary condition averages the field over the "outlet" patch specified
	by name "outletPatch" and applies this as the uniform value of the field
	over this patch.

Usage
	\table
		Property        | Description             | Required    | Default value
		outletPatch     | Name of outlet patch    | yes         |
		phi             | Flux field name         | no          | phi
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            outletMappedUniformInlet;
		outletPatchName aPatch;
		phi             phi;
		value           uniform 0;
	}
	\endverbatim

See also
	tnbLib::fixedValueFvPatchField

SourceFiles
	outletMappedUniformInletFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamOutletMappedUniformInletFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamOutletMappedUniformInletFvPatchField_EXPORT_DEFINE
#define FoamOutletMappedUniformInletFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamOutletMappedUniformInletFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				Class outletMappedUniformInletFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class outletMappedUniformInletFvPatchField
		:
		public fixedValueFvPatchField<Type>
	{
		// Private Data

			//- Name of the outlet patch to be mapped
		word outletPatchName_;

		//- Name of the flux transporting the field
		word phiName_;


	public:

		//- Runtime type information
		/*TypeName("outletMappedUniformInlet");*/
		static const char* typeName_() { return "outletMappedUniformInlet"; }
		static FoamOutletMappedUniformInletFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamOutletMappedUniformInletFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		outletMappedUniformInletFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		outletMappedUniformInletFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given outletMappedUniformInletFvPatchField
		//  onto a new patch
		outletMappedUniformInletFvPatchField
		(
			const outletMappedUniformInletFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		outletMappedUniformInletFvPatchField
		(
			const outletMappedUniformInletFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new outletMappedUniformInletFvPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		outletMappedUniformInletFvPatchField
		(
			const outletMappedUniformInletFvPatchField<Type>&,
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
					new outletMappedUniformInletFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Name of the outlet patch to be mapped
		const word& outletPatchName() const
		{
			return outletPatchName_;
		}


		// Evaluation functions

			//- Update the coefficients associated with the patch field
		virtual void updateCoeffs();


		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <outletMappedUniformInletFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <outletMappedUniformInletFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_outletMappedUniformInletFvPatchField_Header
