#pragma once
#ifndef _swirlFlowRateInletVelocityFvPatchVectorField_Header
#define _swirlFlowRateInletVelocityFvPatchVectorField_Header

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
	tnbLib::swirlFlowRateInletVelocityFvPatchVectorField

Description
	This boundary condition provides a volumetric- OR mass-flow normal vector
	boundary condition by its magnitude as an integral over its area with a
	swirl component determined by the angular speed, given in revolutions per
	minute (RPM)

	The basis of the patch (volumetric or mass) is determined by the
	dimensions of the flux, phi. The current density is used to correct the
	velocity when applying the mass basis.

Usage
	\table
		Property     | Description             | Required    | Default value
		phi          | flux field name         | no          | phi
		rho          | density field name      | no          | rho
		origin       | origin of rotation      | no          | patch centre
		axis         | axis of rotation        | no          | -patch normal
		flowRate     | flow rate profile       | yes         |
		rpm          | rotational speed profile | yes        |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            swirlFlowRateInletVelocity;
		flowRate        constant 0.2;
		rpm             constant 100;
	}
	\endverbatim

Note
	- the \c flowRate and \c rpm entries are Function1 types, able to describe
	  time varying functions.  The example above gives the usage for supplying
	  constant values.
	- the value is positive into the domain

See also
	tnbLib::fixedValueFvPatchField
	tnbLib::Function1Types

SourceFiles
	swirlFlowRateInletVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	/*---------------------------------------------------------------------------*\
			Class swirlFlowRateInletVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class swirlFlowRateInletVelocityFvPatchVectorField
		:
		public fixedValueFvPatchVectorField
	{
		// Private Data

			//- Name of the flux transporting the field
		const word phiName_;

		//- Name of the density field used to normalize the mass flux
		const word rhoName_;

		//- Origin of the rotation
		const vector origin_;

		//- Axis of the rotation
		const vector axis_;

		//- Inlet integral flow rate
		autoPtr<Function1<scalar>> flowRate_;

		//- Angular speed in revolutions per minute (RPM)
		autoPtr<Function1<scalar>> rpm_;


	public:

		//- Runtime type information
		/*TypeName("swirlFlowRateInletVelocity");*/
		static const char* typeName_() { return "swirlFlowRateInletVelocity"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			 //- Construct from patch and internal field
		FoamFiniteVolume_EXPORT swirlFlowRateInletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT swirlFlowRateInletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  flowRateInletVelocityFvPatchVectorField
		//  onto a new patch
		FoamFiniteVolume_EXPORT swirlFlowRateInletVelocityFvPatchVectorField
		(
			const swirlFlowRateInletVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT swirlFlowRateInletVelocityFvPatchVectorField
		(
			const swirlFlowRateInletVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new swirlFlowRateInletVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT swirlFlowRateInletVelocityFvPatchVectorField
		(
			const swirlFlowRateInletVelocityFvPatchVectorField&,
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
					new swirlFlowRateInletVelocityFvPatchVectorField(*this, iF)
					);
		}


		// Member Functions

		// Access

		//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();

		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_swirlFlowRateInletVelocityFvPatchVectorField_Header
