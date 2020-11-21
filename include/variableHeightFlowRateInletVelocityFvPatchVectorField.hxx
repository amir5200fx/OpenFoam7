#pragma once
#ifndef _variableHeightFlowRateInletVelocityFvPatchVectorField_Header
#define _variableHeightFlowRateInletVelocityFvPatchVectorField_Header

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
	tnbLib::variableHeightFlowRateInletVelocityFvPatchVectorField

Description
	This boundary condition provides a velocity boundary condition for
	multphase flow based on a user-specified volumetric flow rate.

	The flow rate is made proportional to the phase fraction alpha at each
	face of the patch and alpha is ensured to be bound between 0 and 1.

Usage
	\table
		Property     | Description             | Required    | Default value
		flowRate     | volumetric flow rate [m3/s] | yes |
		alpha        | phase-fraction field    | yes |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            variableHeightFlowRateInletVelocity;
		flowRate        0.2;
		alpha           alpha.water;
		value           uniform (0 0 0); // placeholder
	}
	\endverbatim

	The \c flowRate entry is a \c Function1 of time, see tnbLib::Function1Types.

Note
	- the value is positive into the domain
	- may not work correctly for transonic inlets
	- strange behaviour with potentialFoam since the momentum equation is
	  not solved

See also
	tnbLib::fixedValueFvPatchField
	tnbLib::Function1Types

SourceFiles
	variableHeightFlowRateInletVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
		Class variableHeightFlowRateInletVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class variableHeightFlowRateInletVelocityFvPatchVectorField
		:
		public fixedValueFvPatchVectorField
	{
		// Private Data

			//- Inlet integral flow rate
		autoPtr<Function1<scalar>> flowRate_;

		//- Name of the phase-fraction field
		word alphaName_;


	public:

		//- Runtime type information
		/*TypeName("variableHeightFlowRateInletVelocity");*/
		static const char* typeName_() { return "variableHeightFlowRateInletVelocity"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			 //- Construct from patch and internal field
		FoamFiniteVolume_EXPORT variableHeightFlowRateInletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT variableHeightFlowRateInletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  variableHeightFlowRateInletVelocityFvPatchVectorField
		//  onto a new patch
		FoamFiniteVolume_EXPORT variableHeightFlowRateInletVelocityFvPatchVectorField
		(
			const variableHeightFlowRateInletVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT variableHeightFlowRateInletVelocityFvPatchVectorField
		(
			const variableHeightFlowRateInletVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new variableHeightFlowRateInletVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT variableHeightFlowRateInletVelocityFvPatchVectorField
		(
			const variableHeightFlowRateInletVelocityFvPatchVectorField&,
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
					new variableHeightFlowRateInletVelocityFvPatchVectorField
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

#endif // !_variableHeightFlowRateInletVelocityFvPatchVectorField_Header
