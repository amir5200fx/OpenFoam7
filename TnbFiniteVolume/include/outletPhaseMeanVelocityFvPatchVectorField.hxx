#pragma once
#ifndef _outletPhaseMeanVelocityFvPatchVectorField_Header
#define _outletPhaseMeanVelocityFvPatchVectorField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::outletPhaseMeanVelocityFvPatchVectorField

Description
	This boundary condition adjusts the velocity for the given phase to achieve
	the specified mean thus causing the phase-fraction to adjust according to
	the mass flow rate.

	Typical usage is as the outlet condition for a towing-tank ship simulation
	to maintain the outlet water level at the level as the inlet.

Usage
	\table
		Property     | Description             | Required    | Default value
		UnMean       | mean velocity normal to the boundary [m/s] | yes |
		alpha        | phase-fraction field    | yes |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            outletPhaseMeanVelocity;
		UnMean          1.2;
		alpha           alpha.water;
		value           uniform (1.2 0 0);
	}
	\endverbatim

See also
	tnbLib::mixedFvPatchField
	tnbLib::variableHeightFlowRateInletVelocityFvPatchVectorField

SourceFiles
	outletPhaseMeanVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <mixedFvPatchFields.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
			 Class outletPhaseMeanVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class outletPhaseMeanVelocityFvPatchVectorField
		:
		public mixedFvPatchVectorField
	{
		// Private Data

			//- Mean velocity normal to the boundary
		autoPtr<Function1<scalar>> UnMean_;

		//- Name of the phase-fraction field
		word alphaName_;


	public:

		//- Runtime type information
		//TypeName("outletPhaseMeanVelocity");
		static const char* typeName_() { return "outletPhaseMeanVelocity"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

		//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT outletPhaseMeanVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT outletPhaseMeanVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  outletPhaseMeanVelocityFvPatchVectorField
		//  onto a new patch
		FoamFiniteVolume_EXPORT outletPhaseMeanVelocityFvPatchVectorField
		(
			const outletPhaseMeanVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT outletPhaseMeanVelocityFvPatchVectorField
		(
			const outletPhaseMeanVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new outletPhaseMeanVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT outletPhaseMeanVelocityFvPatchVectorField
		(
			const outletPhaseMeanVelocityFvPatchVectorField&,
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
					new outletPhaseMeanVelocityFvPatchVectorField
					(
						*this,
						iF
					)
					);
		}


		// Member Functions

			//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();

		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_outletPhaseMeanVelocityFvPatchVectorField_Header
