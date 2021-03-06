#pragma once
#ifndef _angularOscillatingDisplacementPointPatchVectorField_Header
#define _angularOscillatingDisplacementPointPatchVectorField_Header

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
	tnbLib::angularOscillatingDisplacementPointPatchVectorField

Description
	tnbLib::angularOscillatingDisplacementPointPatchVectorField

SourceFiles
	angularOscillatingDisplacementPointPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fixedValuePointPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			Class angularOscillatingDisplacementPointPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class angularOscillatingDisplacementPointPatchVectorField
		:
		public fixedValuePointPatchField<vector>
	{
		// Private Data

		vector axis_;
		vector origin_;
		scalar angle0_;
		scalar amplitude_;
		scalar omega_;

		pointField p0_;


	public:

		//- Runtime type information
		//TypeName("angularOscillatingDisplacement");
		static const char* typeName_() { return "angularOscillatingDisplacement"; }
		static FoamFvMotionSolver_EXPORT const ::tnbLib::word typeName;
		static FoamFvMotionSolver_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFvMotionSolver_EXPORT angularOscillatingDisplacementPointPatchVectorField
		(
			const pointPatch&,
			const DimensionedField<vector, pointMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFvMotionSolver_EXPORT angularOscillatingDisplacementPointPatchVectorField
		(
			const pointPatch&,
			const DimensionedField<vector, pointMesh>&,
			const dictionary&
		);

		//- Construct by mapping given patchField<vector> onto a new patch
		FoamFvMotionSolver_EXPORT angularOscillatingDisplacementPointPatchVectorField
		(
			const angularOscillatingDisplacementPointPatchVectorField&,
			const pointPatch&,
			const DimensionedField<vector, pointMesh>&,
			const pointPatchFieldMapper&
		);

		//- Construct and return a clone
		virtual autoPtr<pointPatchField<vector>> clone() const
		{
			return autoPtr<pointPatchField<vector>>
				(
					new angularOscillatingDisplacementPointPatchVectorField
					(
						*this
					)
					);
		}

		//- Construct as copy setting internal field reference
		FoamFvMotionSolver_EXPORT angularOscillatingDisplacementPointPatchVectorField
		(
			const angularOscillatingDisplacementPointPatchVectorField&,
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
					new angularOscillatingDisplacementPointPatchVectorField
					(
						*this,
						iF
					)
					);
		}


		// Member Functions

			// Mapping functions

				//- Map (and resize as needed) from self given a mapping object
				//  Used to update fields following mesh topology change
		FoamFvMotionSolver_EXPORT virtual void autoMap(const pointPatchFieldMapper&);

		//- Reverse map the given pointPatchField onto this pointPatchField
		//  Used to reconstruct fields
		FoamFvMotionSolver_EXPORT virtual void rmap(const pointPatchField<vector>&, const labelList&);


		// Evaluation functions

			//- Update the coefficients associated with the patch field
		FoamFvMotionSolver_EXPORT virtual void updateCoeffs();


		//- Write
		FoamFvMotionSolver_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_angularOscillatingDisplacementPointPatchVectorField_Header
