#pragma once
#ifndef _directionMixedFvPatchField_Header
#define _directionMixedFvPatchField_Header

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
	tnbLib::directionMixedFvPatchField

Description
	Base class for direction-mixed boundary conditions.

SourceFiles
	directionMixedFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <transformFvPatchField.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamDirectionMixedFvPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamDirectionMixedFvPatchField_EXPORT_DEFINE
#define FoamDirectionMixedFvPatchField_EXPORT __declspec(dllexport)
#else
#define FoamDirectionMixedFvPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class directionMixedFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class directionMixedFvPatchField
		:
		public transformFvPatchField<Type>
	{
		// Private Data

			//- Value field
		Field<Type> refValue_;

		//- Normal gradient field
		Field<Type> refGrad_;

		//- Fraction (0-1) of value used for boundary condition
		symmTensorField valueFraction_;


	public:

		//- Runtime type information
		//TypeName("directionMixed");
		static const char* typeName_() { return "directionMixed"; }
		static FoamDirectionMixedFvPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamDirectionMixedFvPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		directionMixedFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		directionMixedFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given directionMixedFvPatchField onto
		//  a new patch
		directionMixedFvPatchField
		(
			const directionMixedFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type>> clone() const
		{
			return tmp<fvPatchField<Type>>
				(
					new directionMixedFvPatchField<Type>(*this)
					);
		}

		//- Construct as copy setting internal field reference
		directionMixedFvPatchField
		(
			const directionMixedFvPatchField<Type>&,
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
					new directionMixedFvPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Attributes

				//- Return true: this patch field fixes a value.
				//  Needed to check if a level has to be specified while solving
				//  Poissons equations.
		virtual bool fixesValue() const
		{
			return true;
		}

		//- Return false: this patch field is not altered by assignment
		virtual bool assignable() const
		{
			return false;
		}


		// Mapping functions

			//- Map (and resize as needed) from self given a mapping object
			//  Used to update fields following mesh topology change
		virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		virtual void rmap(const fvPatchField<Type>&, const labelList&);


		// Return defining fields

		virtual Field<Type>& refValue()
		{
			return refValue_;
		}

		virtual const Field<Type>& refValue() const
		{
			return refValue_;
		}

		virtual Field<Type>& refGrad()
		{
			return refGrad_;
		}

		virtual const Field<Type>& refGrad() const
		{
			return refGrad_;
		}

		virtual symmTensorField& valueFraction()
		{
			return valueFraction_;
		}

		virtual const symmTensorField& valueFraction() const
		{
			return valueFraction_;
		}


		// Evaluation functions

			//- Return gradient at boundary
		virtual tmp<Field<Type>> snGrad() const;

		//- Evaluate the patch field
		virtual void evaluate
		(
			const Pstream::commsTypes commsType =
			Pstream::commsTypes::blocking
		);

		//- Return face-gradient transform diagonal
		virtual tmp<Field<Type>> snGradTransformDiag() const;


		//- Write
		virtual void write(Ostream&) const;


		// Member Operators

		virtual void operator=(const fvPatchField<Type>&) {}
		virtual void operator+=(const fvPatchField<Type>&) {}
		virtual void operator-=(const fvPatchField<Type>&) {}
		virtual void operator*=(const fvPatchField<Type>&) {}
		virtual void operator/=(const fvPatchField<Type>&) {}

		virtual void operator=(const Field<Type>&) {}
		virtual void operator+=(const Field<Type>&) {}
		virtual void operator-=(const Field<Type>&) {}
		virtual void operator*=(const Field<scalar>&) {}
		virtual void operator/=(const Field<scalar>&) {}

		virtual void operator=(const Type&) {}
		virtual void operator+=(const Type&) {}
		virtual void operator-=(const Type&) {}
		virtual void operator*=(const scalar) {}
		virtual void operator/=(const scalar) {}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <directionMixedFvPatchFieldI.hxx>

//#ifdef NoRepository
//#include <directionMixedFvPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_directionMixedFvPatchField_Header
