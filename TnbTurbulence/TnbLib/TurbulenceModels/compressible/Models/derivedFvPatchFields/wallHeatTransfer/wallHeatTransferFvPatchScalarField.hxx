#pragma once
#ifndef _wallHeatTransferFvPatchScalarField_Header
#define _wallHeatTransferFvPatchScalarField_Header

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
	tnbLib::wallHeatTransferFvPatchScalarField

Description
	This boundary condition provides an enthalpy condition for wall heat
	transfer

Usage
	\table
		Property     | Description             | Required    | Default value
		Tinf         | wall temperature        | yes         |
		alphaWall    | thermal diffusivity     | yes         |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            wallHeatTransfer;
		Tinf            uniform 500;
		alphaWall       uniform 1;
	}
	\endverbatim

SourceFiles
	wallHeatTransferFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <mixedFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				Class wallHeatTransferFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class wallHeatTransferFvPatchScalarField
		:
		public mixedFvPatchScalarField
	{
		// Private Data

			//- Temperature at the wall
		scalarField Tinf_;

		//- Thermal diffusivity at the wall
		scalarField alphaWall_;


	public:

		//- Runtime type information
		//TypeName("wallHeatTransfer");
		static const char* typeName_() { return "wallHeatTransfer"; }
		static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
		static FoamTurbulence_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamTurbulence_EXPORT wallHeatTransferFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamTurbulence_EXPORT wallHeatTransferFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given wallHeatTransferFvPatchScalarField
		// onto a new patch
		FoamTurbulence_EXPORT wallHeatTransferFvPatchScalarField
		(
			const wallHeatTransferFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamTurbulence_EXPORT wallHeatTransferFvPatchScalarField
		(
			const wallHeatTransferFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new wallHeatTransferFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamTurbulence_EXPORT wallHeatTransferFvPatchScalarField
		(
			const wallHeatTransferFvPatchScalarField&,
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
					new wallHeatTransferFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Return Tinf
		const scalarField& Tinf() const
		{
			return Tinf_;
		}

		//- Return reference to Tinf to allow adjustment
		scalarField& Tinf()
		{
			return Tinf_;
		}

		//- Return alphaWall
		const scalarField& alphaWall() const
		{
			return alphaWall_;
		}

		//- Return reference to alphaWall to allow adjustment
		scalarField& alphaWall()
		{
			return alphaWall_;
		}


		// Mapping functions

			//- Map (and resize as needed) from self given a mapping object
			//  Used to update fields following mesh topology change
		FoamTurbulence_EXPORT virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		FoamTurbulence_EXPORT virtual void rmap(const fvPatchScalarField&, const labelList&);


		// Evaluation functions

			//- Update the coefficients associated with the patch field
		FoamTurbulence_EXPORT virtual void updateCoeffs();


		//- Write
		FoamTurbulence_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wallHeatTransferFvPatchScalarField_Header
