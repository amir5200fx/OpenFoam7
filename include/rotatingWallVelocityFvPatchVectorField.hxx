#pragma once
#ifndef _rotatingWallVelocityFvPatchVectorField_Header
#define _rotatingWallVelocityFvPatchVectorField_Header

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
	tnbLib::rotatingWallVelocityFvPatchVectorField

Description
	This boundary condition provides a rotational velocity condition.

Usage
	\table
		Property     | Description             | Required    | Default value
		origin       | origin of rotation in Cartesian co-ordinates | yes|
		axis         | axis of rotation        | yes         |
		omega        | angular velocty of the frame [rad/s] | yes    |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            rotatingWallVelocity;
		origin          (0 0 0);
		axis            (0 0 1);
		omega           100;
	}
	\endverbatim

	The \c omega entry is a Function1 of time, see tnbLib::Function1Types.

See also
	tnbLib::fixedValueFvPatchField
	tnbLib::Function1Types

SourceFiles
	rotatingWallVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			   Class rotatingWallVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class rotatingWallVelocityFvPatchVectorField
		:
		public fixedValueFvPatchVectorField
	{
		// Private Data

			//- Origin of the rotation
		vector origin_;

		//- Axis of the rotation
		vector axis_;

		//- Rotational speed
		autoPtr<Function1<scalar>> omega_;


	public:

		//- Runtime type information
		/*TypeName("rotatingWallVelocity");*/
		static const char* typeName_() { return "rotatingWallVelocity"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT rotatingWallVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT rotatingWallVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given rotatingWallVelocityFvPatchVectorField
		//  onto a new patch
		FoamFiniteVolume_EXPORT rotatingWallVelocityFvPatchVectorField
		(
			const rotatingWallVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT rotatingWallVelocityFvPatchVectorField
		(
			const rotatingWallVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new rotatingWallVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT rotatingWallVelocityFvPatchVectorField
		(
			const rotatingWallVelocityFvPatchVectorField&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvPatchVectorField> clone
		(
			const DimensionedField<vector, volMesh>& iF
		) const
		{
			return tmp<fvPatchVectorField>
				(
					new rotatingWallVelocityFvPatchVectorField(*this, iF)
					);
		}



		// Member Functions

			// Access functions

				//- Return the origin of the rotation
		const vector& origin() const
		{
			return origin_;
		}

		//- Return the axis of the rotation
		const vector& axis() const
		{
			return axis_;
		}

		//- Return non-const access to the origin of the rotation
		vector& origin()
		{
			return origin_;
		}

		//- Return non-const access to the axis of the rotation
		vector& axis()
		{
			return axis_;
		}


		//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();

		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_rotatingWallVelocityFvPatchVectorField_Header
