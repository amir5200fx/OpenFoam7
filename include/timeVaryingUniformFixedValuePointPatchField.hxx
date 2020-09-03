#pragma once
#ifndef _timeVaryingUniformFixedValuePointPatchField_Header
#define _timeVaryingUniformFixedValuePointPatchField_Header

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
	tnbLib::timeVaryingUniformFixedValuePointPatchField

Description
	A time-varying form of a uniform fixed value boundary condition.

See also
	tnbLib::timeVaryingUniformFixedValueFvField

SourceFiles
	timeVaryingUniformFixedValuePointPatchField.C

\*---------------------------------------------------------------------------*/

#include <fixedValuePointPatchField.hxx>
#include <interpolationTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			Class timeVaryingUniformFixedValuePointPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class timeVaryingUniformFixedValuePointPatchField
		:
		public fixedValuePointPatchField<Type>
	{
		// Private Data

			//- The time series being used, including the bounding treatment
		interpolationTable<Type> timeSeries_;


	public:

		//- Runtime type information
		TypeName("timeVaryingUniformFixedValue");


		// Constructors

			//- Construct from patch and internal field
		timeVaryingUniformFixedValuePointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&
		);

		//- Construct from patch, internal field and dictionary
		timeVaryingUniformFixedValuePointPatchField
		(
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const dictionary&
		);

		//- Construct by mapping given patch field onto a new patch
		timeVaryingUniformFixedValuePointPatchField
		(
			const timeVaryingUniformFixedValuePointPatchField<Type>&,
			const pointPatch&,
			const DimensionedField<Type, pointMesh>&,
			const pointPatchFieldMapper&
		);

		//- Copy constructor
		timeVaryingUniformFixedValuePointPatchField
		(
			const timeVaryingUniformFixedValuePointPatchField<Type>&
		);

		//- Construct and return a clone
		virtual autoPtr<pointPatchField<Type>> clone() const
		{
			return autoPtr<pointPatchField<Type>>
				(
					new timeVaryingUniformFixedValuePointPatchField<Type>(*this)
					);
		}

		//- Copy constructor setting internal field reference
		timeVaryingUniformFixedValuePointPatchField
		(
			const timeVaryingUniformFixedValuePointPatchField<Type>&,
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
					new timeVaryingUniformFixedValuePointPatchField<Type>(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Return the time series used
		const interpolationTable<Type>& timeSeries() const
		{
			return timeSeries_;
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

#include <timeVaryingUniformFixedValuePointPatchFieldI.hxx>

//#ifdef NoRepository
//#include <timeVaryingUniformFixedValuePointPatchField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_timeVaryingUniformFixedValuePointPatchField_Header
