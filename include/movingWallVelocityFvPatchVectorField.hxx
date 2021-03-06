#pragma once
#ifndef _movingWallVelocityFvPatchVectorField_Header
#define _movingWallVelocityFvPatchVectorField_Header

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
	tnbLib::movingWallVelocityFvPatchVectorField

Description
	This boundary condition provides a velocity condition for cases with
	moving walls.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            movingWallVelocity;
		value           uniform (0 0 0);    // Initial value
	}
	\endverbatim

See also
	tnbLib::fixedValueFvPatchVectorField

SourceFiles
	movingWallVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				 Class movingWallVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class movingWallVelocityFvPatchVectorField
		:
		public fixedValueFvPatchVectorField
	{

	public:

		//- Runtime type information
		/*TypeName("movingWallVelocity");*/
		static const char* typeName_() { return "movingWallVelocity"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT movingWallVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT movingWallVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given movingWallVelocityFvPatchVectorField
		//  onto a new patch
		FoamFiniteVolume_EXPORT movingWallVelocityFvPatchVectorField
		(
			const movingWallVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT movingWallVelocityFvPatchVectorField
		(
			const movingWallVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new movingWallVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT movingWallVelocityFvPatchVectorField
		(
			const movingWallVelocityFvPatchVectorField&,
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
					new movingWallVelocityFvPatchVectorField(*this, iF)
					);
		}


		// Member Functions

		//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();

		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_movingWallVelocityFvPatchVectorField_Header
