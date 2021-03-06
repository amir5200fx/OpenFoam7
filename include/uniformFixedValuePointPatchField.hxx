#pragma once
#ifndef _uniformFixedValuePointPatchField_Header
#define _uniformFixedValuePointPatchField_Header

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
	tnbLib::uniformFixedValuePointPatchField

Description
	Enables the specification of a uniform fixed value boundary condition.

	Example of the boundary condition specification:
	\verbatim
	inlet
	{
		type            uniformFixedValue;
		uniformValue    constant 0.2;
	}
	\endverbatim

	The uniformValue entry is a Function1 type, able to describe time
	varying functions.  The example above gives the usage for supplying a
	constant value.

SourceFiles
	uniformFixedValuePointPatchField.C

\*---------------------------------------------------------------------------*/

#include <fixedValuePointPatchField.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			  Class uniformFixedValuePointPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class uniformFixedValuePointPatchField
		:
		public fixedValuePointPatchField<Type>
	{
		// Private Data

		autoPtr<Function1<Type>> uniformValue_;


	public:

		//- Runtime type information
		//TypeName("uniformFixedValue");
		static const char* typeName_() { return "uniformFixedValue"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		uniformFixedValuePointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&
		);

		//- Construct from patch, internal field and dictionary
		uniformFixedValuePointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const dictionary&
		);

		//- Construct by mapping given patchField<Type> onto a new patch
		uniformFixedValuePointPatchField
		(
			const uniformFixedValuePointPatchField<Type>&,
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const pointPatchFieldMapper&
		);

		//- Copy constructor
		uniformFixedValuePointPatchField
		(
			const uniformFixedValuePointPatchField<Type>&
		);

		//- Construct and return a clone
		virtual autoPtr<pointPatchField<Type>> clone() const
		{
			return autoPtr<pointPatchField<Type>>
				(
					new uniformFixedValuePointPatchField<Type>
					(
						*this
						)
					);
		}

		//- Copy constructor setting internal field reference
		uniformFixedValuePointPatchField
		(
			const uniformFixedValuePointPatchField<Type>&,
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
					new uniformFixedValuePointPatchField<Type>
					(
						*this,
						iF
						)
					);
		}


		// Member Functions

			// Access

				//- Return the fluctuation scale
		const Function1<Type>& uniformValue() const
		{
			return uniformValue_;
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

#include <uniformFixedValuePointPatchFieldI.hxx>

//#ifdef NoRepository
//#include <uniformFixedValuePointPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_uniformFixedValuePointPatchField_Header
