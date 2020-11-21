#pragma once
#ifndef _epsilonWallFunctionFvPatchScalarField_Header
#define _epsilonWallFunctionFvPatchScalarField_Header

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
	tnbLib::epsilonWallFunctionFvPatchScalarField

Description
	This boundary condition provides a turbulence dissipation wall constraint
	for low- and high-Reynolds number turbulence models.

	The condition can be applied to wall boundaries for which it
	- calculates \c epsilon and \c G
	- specifies the near-wall epsilon value

	where

	\vartable
		epsilon | turblence dissipation field
		G       | turblence generation field
	\endvartable

	The model switches between laminar and turbulent functions based on the
	laminar-to-turbulent y+ value derived from the kappa and E specified in the
	corresponding nutWallFunction.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            epsilonWallFunction;
	}
	\endverbatim

See also
	tnbLib::fixedInternalValueFvPatchField
	tnbLib::omegaWallFunctionFvPatchScalarField

SourceFiles
	epsilonWallFunctionFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class turbulenceModel;

	/*---------------------------------------------------------------------------*\
			   Class epsilonWallFunctionFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class epsilonWallFunctionFvPatchScalarField
		:
		public fixedValueFvPatchField<scalar>
	{
	protected:

		// Protected data

			//- Tolerance used in weighted calculations
		static FoamTurbulence_EXPORT scalar tolerance_;

		//- Local copy of turbulence G field
		scalarField G_;

		//- Local copy of turbulence epsilon field
		scalarField epsilon_;

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

		//- Helper function to return non-const access to an epsilon patch
		FoamTurbulence_EXPORT virtual epsilonWallFunctionFvPatchScalarField& epsilonPatch
		(
			const label patchi
		);

		//- Main driver to calculate the turbulence fields
		FoamTurbulence_EXPORT virtual void calculateTurbulenceFields
		(
			const turbulenceModel& turbulence,
			scalarField& G0,
			scalarField& epsilon0
		);

		//- Calculate the epsilon and G
		FoamTurbulence_EXPORT virtual void calculate
		(
			const turbulenceModel& turbulence,
			const List<scalar>& cornerWeights,
			const fvPatch& patch,
			scalarField& G,
			scalarField& epsilon
		);

		//- Return non-const access to the master patch ID
		virtual label& master()
		{
			return master_;
		}


	public:

		//- Runtime type information
		//TypeName("epsilonWallFunction");
		static const char* typeName_() { return "epsilonWallFunction"; }
		static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
		static FoamTurbulence_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamTurbulence_EXPORT epsilonWallFunctionFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamTurbulence_EXPORT epsilonWallFunctionFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  epsilonWallFunctionFvPatchScalarField
		//  onto a new patch
		FoamTurbulence_EXPORT epsilonWallFunctionFvPatchScalarField
		(
			const epsilonWallFunctionFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamTurbulence_EXPORT epsilonWallFunctionFvPatchScalarField
		(
			const epsilonWallFunctionFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new epsilonWallFunctionFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamTurbulence_EXPORT epsilonWallFunctionFvPatchScalarField
		(
			const epsilonWallFunctionFvPatchScalarField&,
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
					new epsilonWallFunctionFvPatchScalarField(*this, iF)
					);
		}

		//- Destructor
		virtual ~epsilonWallFunctionFvPatchScalarField()
		{}


		// Member Functions

			// Access

				//- Return non-const access to the master's G field
		FoamTurbulence_EXPORT scalarField& G(bool init = false);

		//- Return non-const access to the master's epsilon field
		FoamTurbulence_EXPORT scalarField& epsilon(bool init = false);


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
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_epsilonWallFunctionFvPatchScalarField_Header
