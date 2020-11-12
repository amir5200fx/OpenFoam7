#pragma once
#ifndef _energyJumpAMIFvPatchScalarField_Header
#define _energyJumpAMIFvPatchScalarField_Header

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
	tnbLib::energyJumpAMIFvPatchScalarField

Description
	This boundary condition provides an energy jump condition across a pair
	of coupled patches with an arbitrary mesh interface (AMI).  It is not
	applied directly, but is employed on-the-fly when converting temperature
	boundary conditions into energy.

See also
	tnbLib::fixedJumpAMIFvPatchField

SourceFiles
	energyJumpAMIFvPatchScalarField.C

\*---------------------------------------------------------------------------*/


#include <fixedJumpAMIFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				  Class energyJumpAMIFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class energyJumpAMIFvPatchScalarField
		:
		public fixedJumpAMIFvPatchField<scalar>
	{

	public:

		//- Runtime type information
		//TypeName("energyJumpAMI");
		static const char* typeName_() { return "energyJumpAMI"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from patch and internal field
		FoamThermophysicalModels_EXPORT energyJumpAMIFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamThermophysicalModels_EXPORT energyJumpAMIFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given energyJumpAMIFvPatchScalarField onto a
		//  new patch
		FoamThermophysicalModels_EXPORT energyJumpAMIFvPatchScalarField
		(
			const energyJumpAMIFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamThermophysicalModels_EXPORT energyJumpAMIFvPatchScalarField
		(
			const energyJumpAMIFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<scalar>> clone() const
		{
			return tmp<fvPatchField<scalar>>
				(
					new energyJumpAMIFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamThermophysicalModels_EXPORT energyJumpAMIFvPatchScalarField
		(
			const energyJumpAMIFvPatchScalarField&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvPatchField<scalar>> clone
		(
			const DimensionedField<scalar, volMesh>& iF
		) const
		{
			return tmp<fvPatchField<scalar>>
				(
					new energyJumpAMIFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

			// Evaluation functions

				//- Update the coefficients
		FoamThermophysicalModels_EXPORT virtual void updateCoeffs();


		//- Write
		FoamThermophysicalModels_EXPORT virtual void write(Ostream&) const;
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_energyJumpAMIFvPatchScalarField_Header
