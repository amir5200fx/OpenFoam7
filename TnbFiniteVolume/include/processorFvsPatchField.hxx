#pragma once
#ifndef _processorFvsPatchField_Header
#define _processorFvsPatchField_Header

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
	tnbLib::processorFvsPatchField

Description
	tnbLib::processorFvsPatchField

SourceFiles
	processorFvsPatchField.C

\*---------------------------------------------------------------------------*/

#include <coupledFvsPatchField.hxx>
#include <processorFvPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class processorFvsPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class processorFvsPatchField
		:
		public coupledFvsPatchField<Type>
	{
		// Private Data

			//- Local reference cast into the processor patch
		const processorFvPatch& procPatch_;


	public:

		//- Runtime type information
		TypeName(processorFvPatch::typeName_());


		// Constructors

			//- Construct from patch and internal field
		processorFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct from patch and internal field and patch field
		processorFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const Field<Type>&
		);

		//- Construct from patch, internal field and dictionary
		processorFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const dictionary&
		);

		//- Construct by mapping given processorFvsPatchField onto a new patch
		processorFvsPatchField
		(
			const processorFvsPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		processorFvsPatchField(const processorFvsPatchField<Type>&);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type>> clone() const
		{
			return tmp<fvsPatchField<Type>>
				(
					new processorFvsPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		processorFvsPatchField
		(
			const processorFvsPatchField<Type>&,
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
					new processorFvsPatchField<Type>(*this, iF)
					);
		}


		//- Destructor
		virtual ~processorFvsPatchField();


		// Member Functions

			// Access

				//- Return true if running parallel
		virtual bool coupled() const
		{
			if (Pstream::parRun())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <processorFvsPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_processorFvsPatchField_Header
