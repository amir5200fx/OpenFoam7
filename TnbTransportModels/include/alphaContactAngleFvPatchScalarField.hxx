#pragma once
#ifndef _alphaContactAngleFvPatchScalarField_Header
#define _alphaContactAngleFvPatchScalarField_Header

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
	tnbLib::alphaContactAngleFvPatchScalarField

Description
	Abstract base class for alphaContactAngle boundary conditions.

	Derived classes must implement the theta() function which returns the
	wall contact angle field.

	The essential entry "limit" controls the gradient of alpha1 on the wall:
	  - none - Calculate the gradient from the contact-angle without limiter
	  - gradient - Limit the wall-gradient such that alpha1 remains bounded
		on the wall
	  - alpha - Bound the calculated alpha1 on the wall
	  - zeroGradient - Set the gradient of alpha1 to 0 on the wall, i.e.
		reproduce previous behaviour, the pressure BCs can be left as before.

	Note that if any of the first three options are used the boundary condition
	on \c p_rgh must set to guarantee that the flux is corrected to be zero at
	the wall e.g.:

	\verbatim
	<patchName>
	{
		type            alphaContactAngle;
		limit           none;
	}
	\endverbatim

SourceFiles
	alphaContactAngleFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <fixedGradientFvPatchFields.hxx>
#include <fvsPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				 Class alphaContactAngleFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class alphaContactAngleFvPatchScalarField
		:
		public fixedGradientFvPatchScalarField
	{

	public:

		//- Runtime type information
		//TypeName("alphaContactAngle");
		static const char* typeName_() { return "alphaContactAngle"; }
		static FoamTransportModels_EXPORT const ::tnbLib::word typeName;
		static FoamTransportModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Alpha limit options
		enum limitControls
		{
			lcNone,
			lcGradient,
			lcZeroGradient,
			lcAlpha
		};

		static FoamTransportModels_EXPORT const NamedEnum<limitControls, 4> limitControlNames_;
		limitControls limit_;

		// Constructors

			//- Construct from patch and internal field
		FoamTransportModels_EXPORT alphaContactAngleFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamTransportModels_EXPORT alphaContactAngleFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given alphaContactAngleFvPatchScalarField
		//  onto a new patch
		FoamTransportModels_EXPORT alphaContactAngleFvPatchScalarField
		(
			const alphaContactAngleFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamTransportModels_EXPORT alphaContactAngleFvPatchScalarField
		(
			const alphaContactAngleFvPatchScalarField&
		);

		//- Copy constructor setting internal field reference
		FoamTransportModels_EXPORT alphaContactAngleFvPatchScalarField
		(
			const alphaContactAngleFvPatchScalarField&,
			const DimensionedField<scalar, volMesh>&
		);


		// Member Functions

			//- Return the contact angle
		FoamTransportModels_EXPORT virtual tmp<scalarField> theta
		(
			const fvPatchVectorField& Up,
			const fvsPatchVectorField& nHat
		) const = 0;

		//- Evaluate the patch field
		FoamTransportModels_EXPORT virtual void evaluate
		(
			const Pstream::commsTypes commsType = Pstream::commsTypes::blocking
		);

		//- Write
		FoamTransportModels_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_alphaContactAngleFvPatchScalarField_Header
