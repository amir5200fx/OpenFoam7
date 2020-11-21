#pragma once
#ifndef _dynamicAlphaContactAngleFvPatchScalarField_Header
#define _dynamicAlphaContactAngleFvPatchScalarField_Header

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
	tnbLib::dynamicAlphaContactAngleFvPatchScalarField

Description
	A dynamic alphaContactAngle scalar boundary condition

Usage
	Standard properties:
	\table
		Property | Description                      | Required | Default value
		theta0   | Equilibrium contact angle        | yes      |
		uTheta   | Velocity scale                   | yes      |
	\endtable

	The advancing and receding contact angles can be either specified with
	respect to the interface normal direction:
	\table
		Property | Description                      | Required | Default value
		thetaA   | Limiting advancing contact angle | yes      |
		thetaR   | Limiting receding contact angle  | yes      |
	\endtable

	or with respect to the phase outward direction:
	\table
		Property | Description                      | Required | Default value
		thetaAdv | Limiting advancing contact angle | yes      |
		thetaRec | Limiting receding  contact angle | yes      |
	\endtable

	Example of the boundary condition specification using the interface
	normal direction convention:
	\verbatim
	<patchName>
	{
		type           dynamicAlphaContactAngle;
		uTheta         1;
		theta0         90;
		thetaA         70;
		thetaR         110;
		limit          gradient;
		value          uniform 0;
	}
	\endverbatim

	Example of the boundary condition specification using the phase outward
	direction convention (opposite to the normal direction):
	\verbatim
	<patchName>
	{
		type           dynamicAlphaContactAngle;
		uTheta         1;
		theta0         90;
		thetaAdv       110;
		thetaRec       70;
		limit          gradient;
		value          uniform 0;
	}
	\endverbatim

See also
	tnbLib::alphaContactAngleFvPatchScalarField
	tnbLib::constantAlphaContactAngleFvPatchScalarField

SourceFiles
	dynamicAlphaContactAngleFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <alphaContactAngleFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class dynamicAlphaContactAngleFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class dynamicAlphaContactAngleFvPatchScalarField
		:
		public alphaContactAngleFvPatchScalarField
	{
		// Private Data

			//- Equilibrium contact angle
		scalar theta0_;

		//- Dynamic contact angle velocity scale
		scalar uTheta_;

		//- Limiting advancing contact angle
		scalar thetaA_;

		//- Limiting receding contact angle
		scalar thetaR_;


	public:

		//- Runtime type information
		//TypeName("dynamicAlphaContactAngle");
		static const char* typeName_() { return "dynamicAlphaContactAngle"; }
		static FoamTransportModels_EXPORT const ::tnbLib::word typeName;
		static FoamTransportModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamTransportModels_EXPORT dynamicAlphaContactAngleFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamTransportModels_EXPORT dynamicAlphaContactAngleFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  dynamicAlphaContactAngleFvPatchScalarField
		//  onto a new patch
		FoamTransportModels_EXPORT dynamicAlphaContactAngleFvPatchScalarField
		(
			const dynamicAlphaContactAngleFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamTransportModels_EXPORT dynamicAlphaContactAngleFvPatchScalarField
		(
			const dynamicAlphaContactAngleFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new dynamicAlphaContactAngleFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamTransportModels_EXPORT dynamicAlphaContactAngleFvPatchScalarField
		(
			const dynamicAlphaContactAngleFvPatchScalarField&,
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
					new dynamicAlphaContactAngleFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

			//- Evaluate and return dynamic contact-angle
		FoamTransportModels_EXPORT virtual tmp<scalarField> theta
		(
			const fvPatchVectorField& Up,
			const fvsPatchVectorField& nHat
		) const;

		//- Write
		FoamTransportModels_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dynamicAlphaContactAngleFvPatchScalarField_Header
