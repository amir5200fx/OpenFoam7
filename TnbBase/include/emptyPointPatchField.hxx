#pragma once
#ifndef _emptyPointPatchField_Header
#define _emptyPointPatchField_Header

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
	tnbLib::emptyPointPatchField

Description
	An empty boundary condition for pointField

SourceFiles
	emptyPointPatchField.C

\*---------------------------------------------------------------------------*/

#include <pointPatchField.hxx>
#include <emptyPointPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class emptyPointPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class emptyPointPatchField
		:
		public pointPatchField<Type>
	{

	public:

		//- Runtime type information
		TypeName(emptyPointPatch::typeName_());


		// Constructors

			//- Construct from patch and internal field
		emptyPointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&
		);

		//- Construct from patch, internal field and dictionary
		emptyPointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const dictionary&
		);

		//- Construct by mapping given patchField<Type> onto a new patch
		emptyPointPatchField
		(
			const emptyPointPatchField<Type>&,
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const pointPatchFieldMapper&
		);

		//- Construct and return a clone
		virtual autoPtr<pointPatchField<Type>> clone() const
		{
			return autoPtr<pointPatchField<Type>>
				(
					new emptyPointPatchField<Type>
					(
						*this
						)
					);
		}

		//- Construct as copy setting internal field reference
		emptyPointPatchField
		(
			const emptyPointPatchField<Type>&,
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
					new emptyPointPatchField<Type>
					(
						*this,
						iF
						)
					);
		}

		// Member Functions

			//- Constraint handling

				//- Return the constraint type this pointPatchField implements
		virtual const word& constraintType() const
		{
			return type();
		}

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <emptyPointPatchFieldI.hxx>

//#ifdef NoRepository
//#include <emptyPointPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_emptyPointPatchField_Header
