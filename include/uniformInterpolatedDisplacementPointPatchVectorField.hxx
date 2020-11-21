#pragma once
#ifndef _uniformInterpolatedDisplacementPointPatchVectorField_Header
#define _uniformInterpolatedDisplacementPointPatchVectorField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::uniformInterpolatedDisplacementPointPatchVectorField

Description
	Interpolates pre-specified motion.

	Motion specified as pointVectorFields.

Usage
	Example:
	\verbatim
	walls
	{
		type                uniformInterpolatedDisplacement;
		value               uniform (0 0 0);
		field               wantedDisplacement;
		interpolationScheme linear;
	}
	\endverbatim

	This will scan the case for \a wantedDisplacement pointVectorFields
	and interpolate those in time (using \c linear interpolation) to
	obtain the current displacement.
	The advantage of specifying displacement in this way is that it
	automatically works through decomposePar.

SourceFiles
	uniformInterpolatedDisplacementPointPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fixedValuePointPatchField.hxx>
#include <dynamicMeshPointInterpolator.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
		Class uniformInterpolatedDisplacementPointPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class uniformInterpolatedDisplacementPointPatchVectorField
		:
		public fixedValuePointPatchField<vector>
	{
		// Private Data

		autoPtr<dynamicMeshPointInterpolator> pointInterpolator_;


	public:

		//- Runtime type information
		//TypeName("uniformInterpolatedDisplacement");
		static const char* typeName_() { return "uniformInterpolatedDisplacement"; }
		static FoamFvMotionSolver_EXPORT const ::tnbLib::word typeName;
		static FoamFvMotionSolver_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFvMotionSolver_EXPORT uniformInterpolatedDisplacementPointPatchVectorField
		(
			const pointPatch&,
			const DimensionedField<vector, pointMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFvMotionSolver_EXPORT uniformInterpolatedDisplacementPointPatchVectorField
		(
			const pointPatch&,
			const DimensionedField<vector, pointMesh>&,
			const dictionary&
		);

		//- Construct by mapping given patchField<vector> onto a new patch
		FoamFvMotionSolver_EXPORT uniformInterpolatedDisplacementPointPatchVectorField
		(
			const uniformInterpolatedDisplacementPointPatchVectorField&,
			const pointPatch&,
			const DimensionedField<vector, pointMesh>&,
			const pointPatchFieldMapper&
		);

		//- Construct and return a clone
		virtual autoPtr<pointPatchField<vector>> clone() const
		{
			return autoPtr<pointPatchField<vector>>
				(
					new uniformInterpolatedDisplacementPointPatchVectorField
					(
						*this
					)
					);
		}

		//- Construct as copy setting internal field reference
		FoamFvMotionSolver_EXPORT uniformInterpolatedDisplacementPointPatchVectorField
		(
			const uniformInterpolatedDisplacementPointPatchVectorField&,
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
					new uniformInterpolatedDisplacementPointPatchVectorField
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

#endif // !_uniformInterpolatedDisplacementPointPatchVectorField_Header
