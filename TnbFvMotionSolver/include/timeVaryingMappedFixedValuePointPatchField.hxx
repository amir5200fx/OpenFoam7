#pragma once
#ifndef _timeVaryingMappedFixedValuePointPatchField_Header
#define _timeVaryingMappedFixedValuePointPatchField_Header

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
	tnbLib::timeVaryingMappedFixedValuePointPatchField

Description
	A time-varying form of a mapped fixed value boundary condition.

See also
	tnbLib::timeVaryingMappedFixedValueFvPatchField

SourceFiles
	timeVaryingMappedFixedValuePointPatchField.C

\*---------------------------------------------------------------------------*/

#include <fixedValuePointPatchField.hxx>
#include <instantList.hxx>
#include <pointToPointPlanarInterpolation.hxx>
#include <Function1.hxx>

#include <Switch.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			Class timeVaryingMappedFixedValuePointPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class timeVaryingMappedFixedValuePointPatchField
		:
		public fixedValuePointPatchField<Type>
	{
		// Private Data

			//- Name of the field data table, defaults to the name of the field
		word fieldTableName_;

		//- If true adjust the mapped field to maintain average value
		Switch setAverage_;

		//- Fraction of perturbation (fraction of bounding box) to add
		scalar perturb_;

		//- Interpolation scheme to use
		word mapMethod_;

		//- 2D interpolation (for 'planarInterpolation' mapMethod)
		autoPtr<pointToPointPlanarInterpolation> mapperPtr_;

		//- List of boundaryData time directories
		instantList sampleTimes_;

		//- Current starting index in sampleTimes
		label startSampleTime_;

		//- Interpolated values from startSampleTime
		Field<Type> startSampledValues_;

		//- If setAverage: starting average value
		Type startAverage_;

		//- Current end index in sampleTimes
		label endSampleTime_;

		//- Interpolated values from endSampleTime
		Field<Type> endSampledValues_;

		//- If setAverage: end average value
		Type endAverage_;

		//- Time varying offset values to interpolated data
		autoPtr<Function1<Type>> offset_;


	public:

		//- Runtime type information
		//TypeName("timeVaryingMappedFixedValue");
		static const char* typeName_() { return "timeVaryingMappedFixedValue"; }
		static FoamFvMotionSolver_EXPORT const ::tnbLib::word typeName;
		static FoamFvMotionSolver_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFvMotionSolver_EXPORT timeVaryingMappedFixedValuePointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFvMotionSolver_EXPORT timeVaryingMappedFixedValuePointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const dictionary&
		);

		//- Construct by mapping given patch field onto a new patch
		FoamFvMotionSolver_EXPORT timeVaryingMappedFixedValuePointPatchField
		(
			const timeVaryingMappedFixedValuePointPatchField<Type>&,
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const pointPatchFieldMapper&
		);

		//- Copy constructor
		FoamFvMotionSolver_EXPORT timeVaryingMappedFixedValuePointPatchField
		(
			const timeVaryingMappedFixedValuePointPatchField<Type>&
		);

		//- Construct and return a clone
		virtual autoPtr<pointPatchField<Type>> clone() const
		{
			return autoPtr<pointPatchField<Type>>
				(
					new timeVaryingMappedFixedValuePointPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFvMotionSolver_EXPORT timeVaryingMappedFixedValuePointPatchField
		(
			const timeVaryingMappedFixedValuePointPatchField<Type>&,
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
					new timeVaryingMappedFixedValuePointPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Utility functions

				//- Find boundary data in between current time and interpolate
		FoamFvMotionSolver_EXPORT void checkTable();


		// Mapping functions

			//- Map (and resize as needed) from self given a mapping object
			//  Used to update fields following mesh topology change
		FoamFvMotionSolver_EXPORT virtual void autoMap(const pointPatchFieldMapper&);

		//- Reverse map the given pointPatchField onto this pointPatchField
		//  Used to reconstruct fields
		FoamFvMotionSolver_EXPORT virtual void rmap(const pointPatchField<Type>&, const labelList&);


		// Evaluation functions

			//- Update the coefficients associated with the patch field
		FoamFvMotionSolver_EXPORT virtual void updateCoeffs();


		//- Write
		FoamFvMotionSolver_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <timeVaryingMappedFixedValuePointPatchFieldI.hxx>

//#ifdef NoRepository
//#include <timeVaryingMappedFixedValuePointPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_timeVaryingMappedFixedValuePointPatchField_Header
