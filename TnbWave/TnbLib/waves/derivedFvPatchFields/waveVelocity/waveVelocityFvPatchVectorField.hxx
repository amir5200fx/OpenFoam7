#pragma once
#ifndef _waveVelocityFvPatchVectorField_Header
#define _waveVelocityFvPatchVectorField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::waveVelocityFvPatchVectorField

Description
	This boundary condition provides a waveVelocity condition. This sets the
	velocity to that specified by a superposition of wave models. All the
	wave modelling parameters are obtained from a centrally registered
	waveSuperposition class.

	Flow reversal will occur in the event that the amplitude of the velocity
	oscillation is greater than the mean flow. This triggers special handling,
	the form of which depends on the inletOutlet flag and whether a wave
	pressure condition is being used.

	If a wave pressure condition is not being used, and inletOutlet is false,
	then this is a standard fixed value condition, with the value supplied by
	the wave model. If flow reversal occurs this state may be unstable. The
	corresponding pressure condition should be fixedFluxPressure.

	If a wave pressure condition is not being used, and inletOutlet is true or
	not specified then the proportion of the patch over which the flow is
	reversed functions in a manner similar to the flowRateOutletVelocity
	condition; i.e., the velocity is extrapolated and then scaled to match the
	required outlet flow rate. Numerically, this is still a fixedValue
	constraint on the normal velocity, just one which tends to avoid
	instability. Again, the corresponding pressure condition should be
	fixedFluxPressure.

	If a wave pressure condition is being used, then the normal velocity
	condition becomes fixedGradient on outlet faces. This gradient is
	calculated numerically by evaluating the wave model on both the patch face
	and the adjacent cell. The pressure boundary in this case should be a
	wavePressure condition. This will do the opposite; it will fix the pressure
	value on outlet faces, and the gradient otherwise.

Usage
	\table
		Property    | Description                            | Req'd? | Default
		phi         | Name of the flux field                 | no     | phi
		p           | Name of the pressure field             | no     | p
		inletOutlet | does the condition behave like inletOutlet | no | true
		ramp        | ramping function for the mean flow speed | no   | None
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type        waveVelocity;
		phi         phi;
		p           p;
		inletOutlet yes;
		ramp        constant 1;
	}
	\endverbatim

See also
	tnbLib::waveSuperposition

SourceFiles
	waveVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <Wave_Module.hxx>
#include <directionMixedFvPatchFields.hxx>
#include <waveSuperposition.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMeshSubset;

	/*---------------------------------------------------------------------------*\
					Class waveVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class waveVelocityFvPatchVectorField
		:
		public directionMixedFvPatchVectorField
	{
		// Private Data

			//- Name of the flux field
		const word phiName_;

		//- Name of the pressure field
		const word pName_;

		//- Act as an inlet/outlet patch?
		const Switch inletOutlet_;

		//- Mesh subset corresponding to the patch adjacent cells
		mutable autoPtr<fvMeshSubset> faceCellSubset_;

		//- Time index for keeping the subset up to date
		mutable label faceCellSubsetTimeIndex_;


	public:
		
		//- Runtime type information
		//TypeName("waveVelocity");
		static const char* typeName_() { return "waveVelocity"; }

		static FoamWave_EXPORT const ::tnbLib::word typeName;
		static FoamWave_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamWave_EXPORT waveVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamWave_EXPORT waveVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given mixedTypeFvPatchField onto a new patch
		FoamWave_EXPORT waveVelocityFvPatchVectorField
		(
			const waveVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamWave_EXPORT waveVelocityFvPatchVectorField
		(
			const waveVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new waveVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamWave_EXPORT waveVelocityFvPatchVectorField
		(
			const waveVelocityFvPatchVectorField&,
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
					new waveVelocityFvPatchVectorField(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Access the name of the pressure field
		const word& pName() const
		{
			return pName_;
		}

		//- Access the face-cell subset
		FoamWave_EXPORT const fvMeshSubset& faceCellSubset() const;


		// Evaluation functions

			//- Return the current modelled velocity field on the patch faces
		FoamWave_EXPORT tmp<vectorField> U() const;

		//- Return the current modelled velocity field in the neighbour cell
		FoamWave_EXPORT tmp<vectorField> Un() const;

		//- Update the coefficients associated with the patch field
		FoamWave_EXPORT virtual void updateCoeffs();


		//- Write
		FoamWave_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_waveVelocityFvPatchVectorField_Header
