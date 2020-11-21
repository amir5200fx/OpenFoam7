#pragma once
#ifndef _nutWallFunctionFvPatchScalarField_Header
#define _nutWallFunctionFvPatchScalarField_Header

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
	tnbLib::nutWallFunctionFvPatchScalarField

Description
	This boundary condition provides a turbulent kinematic viscosity condition
	when using wall functions, based on turbulence kinetic energy.
	- replicates OpenFOAM v1.5 (and earlier) behaviour

Usage
	\table
		Property  | Description         | Required   | Default value
		Cmu       | Cmu coefficient     | no         | 0.09
		kappa     | Von Karman constant | no         | 0.41
		E         | E coefficient       | no         | 9.8
	\endtable

	Examples of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            nutWallFunction;
		value           uniform 0;
	}
	\endverbatim

	Reference for the default model coefficients:
	\verbatim
		H. Versteeg, W. Malalasekera
		An Introduction to Computational Fluid Dynamics: The Finite Volume
		Method, subsection "3.5.2 k-epsilon model"
	\endverbatim

See also
	tnbLib::fixedValueFvPatchField

SourceFiles
	nutWallFunctionFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class turbulenceModel;

	/*---------------------------------------------------------------------------*\
				 Class nutWallFunctionFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class nutWallFunctionFvPatchScalarField
		:
		public fixedValueFvPatchScalarField
	{
	protected:

		// Protected data

			//- Cmu coefficient
		scalar Cmu_;

		//- Von Karman constant
		scalar kappa_;

		//- E coefficient
		scalar E_;

		//- Y+ at the edge of the laminar sublayer
		scalar yPlusLam_;


		// Protected Member Functions

			//- Check the type of the patch
		FoamTurbulence_EXPORT virtual void checkType();

		//- Calculate the turbulence viscosity
		FoamTurbulence_EXPORT virtual tmp<scalarField> nut() const = 0;

		//- Write local wall function variables
		FoamTurbulence_EXPORT virtual void writeLocalEntries(Ostream&) const;


	public:

		//- Runtime type information
		//TypeName("nutWallFunction");
		static const char* typeName_() { return "nutWallFunction"; }
		static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
		static FoamTurbulence_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamTurbulence_EXPORT nutWallFunctionFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamTurbulence_EXPORT nutWallFunctionFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  nutWallFunctionFvPatchScalarField
		//  onto a new patch
		FoamTurbulence_EXPORT nutWallFunctionFvPatchScalarField
		(
			const nutWallFunctionFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamTurbulence_EXPORT nutWallFunctionFvPatchScalarField
		(
			const nutWallFunctionFvPatchScalarField&
		);

		//- Copy constructor setting internal field reference
		FoamTurbulence_EXPORT nutWallFunctionFvPatchScalarField
		(
			const nutWallFunctionFvPatchScalarField&,
			const DimensionedField<scalar, volMesh>&
		);


		// Member Functions

			//- Return Cmu
		scalar Cmu() const
		{
			return Cmu_;
		}

		//- Return kappa
		scalar kappa() const
		{
			return kappa_;
		}

		//- Return E
		scalar E() const
		{
			return E_;
		}

		//- Return the nut patchField for the given wall patch
		static FoamTurbulence_EXPORT const nutWallFunctionFvPatchScalarField& nutw
		(
			const turbulenceModel& turbModel,
			const label patchi
		);

		//- Calculate the Y+ at the edge of the laminar sublayer
		static FoamTurbulence_EXPORT scalar yPlusLam(const scalar kappa, const scalar E);

		//- Return the Y+ at the edge of the laminar sublayer
		FoamTurbulence_EXPORT scalar yPlusLam() const;

		//- Calculate and return the yPlus at the boundary
		FoamTurbulence_EXPORT virtual tmp<scalarField> yPlus() const = 0;


		// Evaluation functions

			//- Update the coefficients associated with the patch field
		FoamTurbulence_EXPORT virtual void updateCoeffs();


		// I-O

			//- Write
		FoamTurbulence_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_nutWallFunctionFvPatchScalarField_Header
