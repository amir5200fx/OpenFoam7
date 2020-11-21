#pragma once
#ifndef _oscillatingDisplacementPointPatchVectorField_Header
#define _oscillatingDisplacementPointPatchVectorField_Header

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
	tnbLib::oscillatingDisplacementPointPatchVectorField

Description
	tnbLib::oscillatingDisplacementPointPatchVectorField

SourceFiles
	oscillatingDisplacementPointPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fixedValuePointPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			Class oscillatingDisplacementPointPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class oscillatingDisplacementPointPatchVectorField
		:
		public fixedValuePointPatchField<vector>
	{
		// Private Data

		vector amplitude_;
		scalar omega_;


	public:

		//- Runtime type information
		//TypeName("oscillatingDisplacement");
		static const char* typeName_() { return "oscillatingDisplacement"; }
		static FoamFvMotionSolver_EXPORT const ::tnbLib::word typeName;
		static FoamFvMotionSolver_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFvMotionSolver_EXPORT oscillatingDisplacementPointPatchVectorField
		(
			const pointPatch&,
			const DimensionedField<vector, pointMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFvMotionSolver_EXPORT oscillatingDisplacementPointPatchVectorField
		(
			const pointPatch&,
			const DimensionedField<vector, pointMesh>&,
			const dictionary&
		);

		//- Construct by mapping given patchField<vector> onto a new patch
		FoamFvMotionSolver_EXPORT oscillatingDisplacementPointPatchVectorField
		(
			const oscillatingDisplacementPointPatchVectorField&,
			const pointPatch&,
			const DimensionedField<vector, pointMesh>&,
			const pointPatchFieldMapper&
		);

		//- Construct and return a clone
		virtual autoPtr<pointPatchField<vector>> clone() const
		{
			return autoPtr<pointPatchField<vector>>
				(
					new oscillatingDisplacementPointPatchVectorField
					(
						*this
					)
					);
		}

		//- Construct as copy setting internal field reference
		FoamFvMotionSolver_EXPORT oscillatingDisplacementPointPatchVectorField
		(
			const oscillatingDisplacementPointPatchVectorField&,
			const DimensionedField<vector, pointMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual autoPtr<pointPatchField<vector>> clone
		(
			const DimensionedField<vector, pointMesh>& iF
		) const
		{
			return autoPtr<pointPatchField<vector>>
				(
					new oscillatingDisplacementPointPatchVectorField
					(
						*this,
						iF
					)
					);
		}


		// Member Functions

			// Evaluation functions

				//- Update the coefficients associated with the patch field
		FoamFvMotionSolver_EXPORT virtual void updateCoeffs();


		//- Write
		FoamFvMotionSolver_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_oscillatingDisplacementPointPatchVectorField_Header
