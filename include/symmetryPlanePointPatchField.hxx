#pragma once
#ifndef _symmetryPlanePointPatchField_Header
#define _symmetryPlanePointPatchField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::symmetryPlanePointPatchField

Description
	A symmetry-plane boundary condition for pointField

SourceFiles
	symmetryPlanePointPatchField.C

\*---------------------------------------------------------------------------*/

#include <basicSymmetryPointPatchField.hxx>
#include <symmetryPlanePointPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class symmetryPlanePointPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class symmetryPlanePointPatchField
		:
		public basicSymmetryPointPatchField<Type>
	{
		// Private Data

			//- Local reference cast into the symmetryPlane patch
		const symmetryPlanePointPatch& symmetryPlanePatch_;


	public:

		//- Runtime type information
		//TypeName(symmetryPlanePointPatch::typeName_());
		static const char* typeName_() { return symmetryPlanePointPatch::typeName_(); }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		symmetryPlanePointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&
		);

		//- Construct from patch, internal field and dictionary
		symmetryPlanePointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const dictionary&
		);

		//- Construct by mapping given patchField<Type> onto a new patch
		symmetryPlanePointPatchField
		(
			const symmetryPlanePointPatchField<Type>&,
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const pointPatchFieldMapper&
		);

		//- Construct and return a clone
		virtual autoPtr<pointPatchField<Type>> clone() const
		{
			return autoPtr<pointPatchField<Type>>
				(
					new symmetryPlanePointPatchField<Type>
					(
						*this
						)
					);
		}

		//- Construct as copy setting internal field reference
		symmetryPlanePointPatchField
		(
			const symmetryPlanePointPatchField<Type>&,
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
					new symmetryPlanePointPatchField<Type>
					(
						*this,
						iF
						)
					);
		}


		// Member Functions

			//- Return the constraint type this pointPatchField implements
		virtual const word& constraintType() const
		{
			return symmetryPlanePointPatch::typeName;
		}

		//- Update the patch field
		virtual void evaluate
		(
			const Pstream::commsTypes commsType = Pstream::commsTypes::blocking
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <symmetryPlanePointPatchFieldI.hxx>

//#ifdef NoRepository
//#include <symmetryPlanePointPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_symmetryPlanePointPatchField_Header
