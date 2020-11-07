#pragma once
#ifndef _cyclicAMIFvsPatchField_Header
#define _cyclicAMIFvsPatchField_Header

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
	tnbLib::cyclicAMIFvsPatchField

Description
	tnbLib::cyclicAMIFvsPatchField

SourceFiles
	cyclicAMIFvsPatchField.C

\*---------------------------------------------------------------------------*/

#include <coupledFvsPatchField.hxx>
#include <cyclicAMIFvPatch.hxx>

#ifdef FoamFiniteVolume_EXPORT_DEFINE
#define FoamCyclicAMIFvsPatchField_EXPORT __declspec(dllexport)
#else
#ifdef FoamCyclicAMIFvsPatchField_EXPORT_DEFINE
#define FoamCyclicAMIFvsPatchField_EXPORT __declspec(dllexport)
#else
#define FoamCyclicAMIFvsPatchField_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class cyclicAMIFvsPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class cyclicAMIFvsPatchField
		:
		public coupledFvsPatchField<Type>
	{
		// Private Data

			//- Local reference cast into the cyclic patch
		const cyclicAMIFvPatch& cyclicAMIPatch_;


	public:

		//- Runtime type information
		/*TypeName(cyclicAMIFvPatch::typeName_());*/
		static const char* typeName_() { return cyclicAMIFvPatch::typeName_(); }
		static FoamCyclicAMIFvsPatchField_EXPORT const ::tnbLib::word typeName;
		static FoamCyclicAMIFvsPatchField_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		cyclicAMIFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct from patch, internal field and dictionary
		cyclicAMIFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const dictionary&
		);

		//- Construct by mapping given cyclicAMIFvsPatchField onto a new patch
		cyclicAMIFvsPatchField
		(
			const cyclicAMIFvsPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		cyclicAMIFvsPatchField
		(
			const cyclicAMIFvsPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type>> clone() const
		{
			return tmp<fvsPatchField<Type>>
				(
					new cyclicAMIFvsPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		cyclicAMIFvsPatchField
		(
			const cyclicAMIFvsPatchField<Type>&,
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
					new cyclicAMIFvsPatchField<Type>(*this, iF)
					);
		}

		// Member Functions

			// Access

				//- Return true if running parallel
		virtual bool coupled() const;

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <cyclicAMIFvsPatchFieldI.hxx>

//#ifdef NoRepository
//#include <cyclicAMIFvsPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicAMIFvsPatchField_Header
