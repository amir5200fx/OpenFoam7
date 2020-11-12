#pragma once
#ifndef _omegaWallFunctionFvPatchScalarField_Header
#define _omegaWallFunctionFvPatchScalarField_Header

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
	tnbLib::omegaWallFunctionFvPatchScalarField

Description
	This boundary condition provides a wall constraint on turbulnce specific
	dissipation, omega for both low and high Reynolds number turbulence models.

	The near-wall omega may be either blended between the viscous region and
	logarithmic region values using:

		\f[
			\omega = sqrt(\omega_{vis}^2 + \omega_{log}^2)
		\f]

	where

	\vartable
		\omega_{vis} | omega in viscous region
		\omega_{log} | omega in logarithmic region
	\endvartable

	see eq.(15) of:
	\verbatim
		Menter, F., Esch, T.
		"Elements of Industrial Heat Transfer Prediction"
		16th Brazilian Congress of Mechanical Engineering (COBEM),
		Nov. 2001
	\endverbatim

	or switched between these values based on the laminar-to-turbulent y+ value
	derived from kappa and E specified in the corresponding nutWallFunction.
	Recent tests have shown that the standard switching method provides more
	accurate results for 10 < y+ < 30 when used with high Reynolds number
	wall-functions and both methods provide accurate results when used with
	continuous wall-functions.  Based on this the standard switching method is
	used by default.

Usage
	\table
		Property     | Description             | Required    | Default value
		beta1        | Model coefficient       | no          | 0.075
		blended      | Blending switch         | no          | false
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            omegaWallFunction;
	}
	\endverbatim

See also
	tnbLib::fixedInternalValueFvPatchField
	tnbLib::epsilonWallFunctionFvPatchScalarField

SourceFiles
	omegaWallFunctionFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchField.hxx>
#include <Switch.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class turbulenceModel;

	/*---------------------------------------------------------------------------*\
				 Class omegaWallFunctionFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class omegaWallFunctionFvPatchScalarField
		:
		public fixedValueFvPatchField<scalar>
	{
	protected:

		// Protected data

			//- Tolerance used in weighted calculations
		static FoamTurbulence_EXPORT scalar tolerance_;

		//- beta1 coefficient
		scalar beta1_;

		//- Blending switch (defaults to false)
		Switch blended_;

		//- Local copy of turbulence G field
		scalarField G_;

		//- Local copy of turbulence omega field
		scalarField omega_;

		//- Initialised flag
		bool initialised_;

		//- Master patch ID
		label master_;

		//- List of averaging corner weights
		List<List<scalar>> cornerWeights_;


		// Protected Member Functions

			//- Set the master patch - master is responsible for updating all
			//  wall function patches
		FoamTurbulence_EXPORT virtual void setMaster();

		//- Create the averaging weights for cells which are bounded by
		//  multiple wall function faces
		FoamTurbulence_EXPORT virtual void createAveragingWeights();

		//- Helper function to return non-const access to an omega patch
		FoamTurbulence_EXPORT virtual omegaWallFunctionFvPatchScalarField& omegaPatch
		(
			const label patchi
		);

		//- Main driver to calculate the turbulence fields
		FoamTurbulence_EXPORT virtual void calculateTurbulenceFields
		(
			const turbulenceModel& turbulence,
			scalarField& G0,
			scalarField& omega0
		);

		//- Calculate the omega and G
		FoamTurbulence_EXPORT virtual void calculate
		(
			const turbulenceModel& turbulence,
			const List<scalar>& cornerWeights,
			const fvPatch& patch,
			scalarField& G,
			scalarField& omega
		);

		//- Return non-const access to the master patch ID
		virtual label& master()
		{
			return master_;
		}

		typedef DimensionedField<scalar, volMesh> FieldType;


	public:

		//- Runtime type information
		//TypeName("omegaWallFunction");
		static const char* typeName_() { return "omegaWallFunction"; }
		static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
		static FoamTurbulence_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamTurbulence_EXPORT omegaWallFunctionFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamTurbulence_EXPORT omegaWallFunctionFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		// omegaWallFunctionFvPatchScalarField
		//  onto a new patch
		FoamTurbulence_EXPORT omegaWallFunctionFvPatchScalarField
		(
			const omegaWallFunctionFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamTurbulence_EXPORT omegaWallFunctionFvPatchScalarField
		(
			const omegaWallFunctionFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new omegaWallFunctionFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamTurbulence_EXPORT omegaWallFunctionFvPatchScalarField
		(
			const omegaWallFunctionFvPatchScalarField&,
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
					new omegaWallFunctionFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Return non-const access to the master's G field
		FoamTurbulence_EXPORT scalarField& G(bool init = false);

		//- Return non-const access to the master's omega field
		FoamTurbulence_EXPORT scalarField& omega(bool init = false);


		// Evaluation functions

			//- Update the coefficients associated with the patch field
		FoamTurbulence_EXPORT virtual void updateCoeffs();

		//- Update the coefficients associated with the patch field
		FoamTurbulence_EXPORT virtual void updateWeightedCoeffs(const scalarField& weights);

		//- Manipulate matrix
		FoamTurbulence_EXPORT virtual void manipulateMatrix(fvMatrix<scalar>& matrix);

		//- Manipulate matrix with given weights
		FoamTurbulence_EXPORT virtual void manipulateMatrix
		(
			fvMatrix<scalar>& matrix,
			const scalarField& weights
		);


		// I-O

			//- Write
		FoamTurbulence_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_omegaWallFunctionFvPatchScalarField_Header
