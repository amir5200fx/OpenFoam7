#pragma once
#ifndef _mixedEnergyFvPatchScalarField_Header
#define _mixedEnergyFvPatchScalarField_Header

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
	tnbLib::mixedEnergyFvPatchScalarField

Description
	This boundary condition provides a mixed condition for internal energy

See also
	tnbLib::mixedFvPatchField

SourceFiles
	mixedEnergyFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <mixedFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				   Class mixedEnergyFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class mixedEnergyFvPatchScalarField
		:
		public mixedFvPatchScalarField
	{

	public:

		//- Runtime type information
		//TypeName("mixedEnergy");
		static const char* typeName_() { return "mixedEnergy"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamThermophysicalModels_EXPORT mixedEnergyFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamThermophysicalModels_EXPORT mixedEnergyFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given mixedEnergyFvPatchScalarField
		// onto a new patch
		FoamThermophysicalModels_EXPORT mixedEnergyFvPatchScalarField
		(
			const mixedEnergyFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamThermophysicalModels_EXPORT mixedEnergyFvPatchScalarField
		(
			const mixedEnergyFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new mixedEnergyFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamThermophysicalModels_EXPORT mixedEnergyFvPatchScalarField
		(
			const mixedEnergyFvPatchScalarField&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvPatchScalarField> clone
		(
			const DimensionedField<scalar, volMesh>& iF
		) const
		{
			return tmp<fvPatchScalarField>
				(
					new mixedEnergyFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Allow manipulation of the boundary values
		virtual bool fixesValue() const
		{
			return false;
		}


		// Evaluation functions

			//- Update the coefficients associated with the patch field
		FoamThermophysicalModels_EXPORT virtual void updateCoeffs();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_mixedEnergyFvPatchScalarField_Header
