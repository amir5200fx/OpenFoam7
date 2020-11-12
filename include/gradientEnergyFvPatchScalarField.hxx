#pragma once
#ifndef _gradientEnergyFvPatchScalarField_Header
#define _gradientEnergyFvPatchScalarField_Header

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
	tnbLib::gradientEnergyFvPatchScalarField

Description
	This boundary condition provides a gradient condition for internal energy,
	where the gradient is calculated using:

		\f[
			\nabla(e_p) = \nabla_\perp C_p(p, T) + \frac{e_p - e_c}{\Delta}
		\f]

	where
	\vartable
		e_p     | energy at patch faces [J]
		e_c     | energy at patch internal cells [J]
		p       | pressure [bar]
		T       | temperature [K]
		C_p     | specific heat [J/kg/K]
		\Delta  | distance between patch face and internal cell centres [m]
	\endvartable

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            gradientEnergy;
		gradient        uniform 10;
	}
	\endverbatim

See also
	tnbLib::fixedGradientFvPatchField

SourceFiles
	gradientEnergyFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <fixedGradientFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				 Class gradientEnergyFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class gradientEnergyFvPatchScalarField
		:
		public fixedGradientFvPatchScalarField
	{

	public:

		//- Runtime type information
		//TypeName("gradientEnergy");
		static const char* typeName_() { return "gradientEnergy"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamThermophysicalModels_EXPORT gradientEnergyFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamThermophysicalModels_EXPORT gradientEnergyFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given gradientEnergyFvPatchScalarField
		// onto a new patch
		FoamThermophysicalModels_EXPORT gradientEnergyFvPatchScalarField
		(
			const gradientEnergyFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamThermophysicalModels_EXPORT gradientEnergyFvPatchScalarField
		(
			const gradientEnergyFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new gradientEnergyFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamThermophysicalModels_EXPORT gradientEnergyFvPatchScalarField
		(
			const gradientEnergyFvPatchScalarField&,
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
					new gradientEnergyFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

			// Evaluation functions

				//- Update the coefficients associated with the patch field
		FoamThermophysicalModels_EXPORT virtual void updateCoeffs();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_gradientEnergyFvPatchScalarField_Header
