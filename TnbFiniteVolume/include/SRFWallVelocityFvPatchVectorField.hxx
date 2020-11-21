#pragma once
#ifndef _SRFWallVelocityFvPatchVectorField_Header
#define _SRFWallVelocityFvPatchVectorField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::SRFWallVelocityFvPatchVectorField

Description
	Wall-velocity condition to be used in conjunction with the single rotating
	frame (SRF) model (see: FOAM::SRFModel)

	The condition applies the appropriate rotation transformation in time and
	space to determine the local SRF velocity of the wall.

		\f[
			U_p = - U_{p,srf}
		\f]

	where
	\vartable
		U_p     = patch velocity [m/s]
		U_{p,srf} = SRF velocity
	\endvartable

	The normal component of \f$ U_p \f$ is removed to ensure 0 wall-flux even
	if the wall patch faces are irregular.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            SRFWallVelocity;
		value           uniform (0 0 0);    // Initial value
	}
	\endverbatim

See also
	tnbLib::SRFModel
	tnbLib::SRFVelocityFvPatchVectorField
	tnbLib::fixedValueFvPatchField

SourceFiles
	SRFWallVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchFields.hxx>
#include <fixedValueFvPatchFields.hxx>
#include <Switch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				   Class SRFWallVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class SRFWallVelocityFvPatchVectorField
		:
		public fixedValueFvPatchVectorField
	{

	public:

		//- Runtime type information
		//TypeName("SRFWallVelocity");
		static const char* typeName_() { return "SRFWallVelocity"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

		//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT SRFWallVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT SRFWallVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given SRFWallVelocityFvPatchVectorField
		//  onto a new patch
		FoamFiniteVolume_EXPORT SRFWallVelocityFvPatchVectorField
		(
			const SRFWallVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT SRFWallVelocityFvPatchVectorField
		(
			const SRFWallVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new SRFWallVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT SRFWallVelocityFvPatchVectorField
		(
			const SRFWallVelocityFvPatchVectorField&,
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
					new SRFWallVelocityFvPatchVectorField(*this, iF)
					);
		}


		// Member Functions

		// Mapping functions

		//- Map (and resize as needed) from self given a mapping object
		//  Used to update fields following mesh topology change
		FoamFiniteVolume_EXPORT virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		FoamFiniteVolume_EXPORT virtual void rmap(const fvPatchVectorField&, const labelList&);


		// Evaluation functions

		//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();


		// I-O

		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SRFWallVelocityFvPatchVectorField_Header
