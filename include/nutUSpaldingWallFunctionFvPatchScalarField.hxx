#pragma once
#ifndef _nutUSpaldingWallFunctionFvPatchScalarField_Header
#define _nutUSpaldingWallFunctionFvPatchScalarField_Header

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
	tnbLib::nutUSpaldingWallFunctionFvPatchScalarField

Description
	This boundary condition provides a turbulent kinematic viscosity condition
	when using wall functions for rough walls, based on velocity,  using
	Spalding's law to give a continuous nut profile to the wall (y+ = 0)

		\f[
			y^+ = u^+ + \frac{1}{E} \left[exp(\kappa u^+) - 1 - \kappa u^+\,
				- 0.5 (\kappa u^+)^2 - \frac{1}{6} (\kappa u^+)^3\right]
		\f]

	where
	\vartable
		y^+     | non-dimensional position
		u^+     | non-dimensional velocity
		\kappa  | Von Karman constant
	\endvartable


Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            nutUSpaldingWallFunction;
		value           uniform 0;
	}
	\endverbatim

See also
	tnbLib::nutWallFunctionFvPatchScalarField

SourceFiles
	nutUSpaldingWallFunctionFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <nutWallFunctionFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			  Class nutUSpaldingWallFunctionFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class nutUSpaldingWallFunctionFvPatchScalarField
		:
		public nutWallFunctionFvPatchScalarField
	{
	protected:

		// Protected Member Functions

			//- Calculate the turbulence viscosity
		FoamTurbulence_EXPORT virtual tmp<scalarField> nut() const;

		//- Calculate the friction velocity
		FoamTurbulence_EXPORT virtual tmp<scalarField> calcUTau(const scalarField& magGradU) const;


	public:

		//- Runtime type information
		//TypeName("nutUSpaldingWallFunction");
		static const char* typeName_() { return "nutUSpaldingWallFunction"; }
		static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
		static FoamTurbulence_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamTurbulence_EXPORT nutUSpaldingWallFunctionFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamTurbulence_EXPORT nutUSpaldingWallFunctionFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  nutUSpaldingWallFunctionFvPatchScalarField
		//  onto a new patch
		FoamTurbulence_EXPORT nutUSpaldingWallFunctionFvPatchScalarField
		(
			const nutUSpaldingWallFunctionFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamTurbulence_EXPORT nutUSpaldingWallFunctionFvPatchScalarField
		(
			const nutUSpaldingWallFunctionFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new nutUSpaldingWallFunctionFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamTurbulence_EXPORT nutUSpaldingWallFunctionFvPatchScalarField
		(
			const nutUSpaldingWallFunctionFvPatchScalarField&,
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
					new nutUSpaldingWallFunctionFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

			// Evaluation functions

				//- Calculate and return the yPlus at the boundary
		FoamTurbulence_EXPORT virtual tmp<scalarField> yPlus() const;


		// I-O

			//- Write
		FoamTurbulence_EXPORT virtual void write(Ostream& os) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_nutUSpaldingWallFunctionFvPatchScalarField_Header
