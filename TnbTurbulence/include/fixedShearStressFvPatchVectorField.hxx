#pragma once
#ifndef _fixedShearStressFvPatchVectorField_Header
#define _fixedShearStressFvPatchVectorField_Header

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
	tnbLib::fixedShearStressFvPatchVectorField

Description
	Set a constant shear stress as tau0 = -nuEff dU/dn.

SourceFiles
	fixedShearStressFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchFields.hxx>
#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				Class fixedShearStressFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class fixedShearStressFvPatchVectorField
		:
		public fixedValueFvPatchVectorField
	{
		// Private Data

			//- Constant shear stress
		const vector tau0_;


	public:

		//- Runtime type information
		//TypeName("fixedShearStress");
		static const char* typeName_() { return "fixedShearStress"; }
		static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
		static FoamTurbulence_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamTurbulence_EXPORT fixedShearStressFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamTurbulence_EXPORT fixedShearStressFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		FoamTurbulence_EXPORT fixedShearStressFvPatchVectorField
		(
			const fixedShearStressFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamTurbulence_EXPORT fixedShearStressFvPatchVectorField
		(
			const fixedShearStressFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new fixedShearStressFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamTurbulence_EXPORT fixedShearStressFvPatchVectorField
		(
			const fixedShearStressFvPatchVectorField&,
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
					new fixedShearStressFvPatchVectorField(*this, iF)
					);
		}


		// Member Functions

			//- Update the coefficients associated with the patch field
		FoamTurbulence_EXPORT virtual void updateCoeffs();

		//- Write
		FoamTurbulence_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedShearStressFvPatchVectorField_Header
