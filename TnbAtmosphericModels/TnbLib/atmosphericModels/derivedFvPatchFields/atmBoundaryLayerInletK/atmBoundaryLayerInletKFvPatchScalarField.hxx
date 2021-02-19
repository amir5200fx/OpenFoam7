#pragma once
#ifndef _atmBoundaryLayerInletKFvPatchScalarField_Header
#define _atmBoundaryLayerInletKFvPatchScalarField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2014-2019 OpenFOAM Foundation
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
	tnbLib::atmBoundaryLayerInletKFvPatchScalarField

Description
	This boundary condition specifies an inlet value for the turbulence
	kinetic energy, \f$k\f$, appropriate for atmospheric boundary layers.

	See tnbLib::atmBoundaryLayer for details.

	Example of the boundary condition specification:
	\verbatim
	ground
	{
		type            atmBoundaryLayerInletK;
		z               (0 0 1);
		Uref            10.0;
		Zref            20.0;
		z0              uniform 0.1;
		zGround         uniform 0.0;
	}
	\endverbatim

See also
	tnbLib::atmBoundaryLayer,
	tnbLib::atmBoundaryLayerInletVelocityFvPatchVectorField,
	tnbLib::atmBoundaryLayerInletEpsilonFvPatchScalarField

SourceFiles
	atmBoundaryLayerInletKFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <atmBoundaryLayer.hxx>
#include <fvPatchFields.hxx>
#include <inletOutletFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			Class atmBoundaryLayerInletKFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class atmBoundaryLayerInletKFvPatchScalarField
		:
		public inletOutletFvPatchScalarField,
		public atmBoundaryLayer
	{

	public:

		//- Runtime type information
		//TypeName("atmBoundaryLayerInletK");
		static const char* typeName_() { return "atmBoundaryLayerInletK"; }
		static FoamAtmosphericModels_EXPORT const ::tnbLib::word typeName;
		static FoamAtmosphericModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

		//- Construct from patch and internal field
		FoamAtmosphericModels_EXPORT atmBoundaryLayerInletKFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamAtmosphericModels_EXPORT atmBoundaryLayerInletKFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  atmBoundaryLayerInletKFvPatchScalarField onto a new patch
		FoamAtmosphericModels_EXPORT atmBoundaryLayerInletKFvPatchScalarField
		(
			const atmBoundaryLayerInletKFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new atmBoundaryLayerInletKFvPatchScalarField(*this)
					);
		}

		//- Construct as copy setting internal field reference
		FoamAtmosphericModels_EXPORT atmBoundaryLayerInletKFvPatchScalarField
		(
			const atmBoundaryLayerInletKFvPatchScalarField&,
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
					new atmBoundaryLayerInletKFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

		// Mapping functions

		//- Map (and resize as needed) from self given a mapping object
		//  Used to update fields following mesh topology change
		FoamAtmosphericModels_EXPORT virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		FoamAtmosphericModels_EXPORT virtual void rmap(const fvPatchScalarField&, const labelList&);


		//- Write
		FoamAtmosphericModels_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_atmBoundaryLayerInletKFvPatchScalarField_Header
