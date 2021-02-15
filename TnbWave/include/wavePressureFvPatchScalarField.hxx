#pragma once
#ifndef _wavePressureFvPatchScalarField_Header
#define _wavePressureFvPatchScalarField_Header

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
	tnbLib::wavePressureFvPatchScalarField

Description
	This boundary condition provides a wavePressure condition. This sets the
	pressure to a value specified by a superposition of wave models. All the
	wave modelling parameters are obtained from a centrally registered
	waveSuperposition class.

	This functions like an outletInlet condition. Faces on which the flow is
	leaving the domain have a value set by the wave model. Faces on which the
	flow is entering the domain have the gradient set. This gradient is
	calculated numerically by evaluating the wave model on both the patch face
	and the adjacent cell.

	Use of this boundary condition triggers a consistent behaviour in the
	corresponding velocity and phase-fraction conditions.

Usage
	\table
		Property  | Description                | Req'd? | Default
		U         | name of the velocity field | no     | U
		rho       | name of the density field  | no     | rho
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type        wavePressure;
		U           U;
		rho         rho;
	}
	\endverbatim

See also
	tnbLib::waveSuperposition

SourceFiles
	wavePressureFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <Wave_Module.hxx>
#include <mixedFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					Class wavePressureFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class wavePressureFvPatchScalarField
		:
		public mixedFvPatchScalarField
	{
		// Private Data

			//- Name of the velocity field
		const word UName_;

		//- Name of the density field
		const word rhoName_;


	public:
		
		//- Runtime type information
		//TypeName("wavePressure");
		static const char* typeName_() { return "wavePressure"; }

		static FoamWave_EXPORT const ::tnbLib::word typeName;
		static FoamWave_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamWave_EXPORT wavePressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamWave_EXPORT wavePressureFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given mixedTypeFvPatchField
		//  onto a new patch
		FoamWave_EXPORT wavePressureFvPatchScalarField
		(
			const wavePressureFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamWave_EXPORT wavePressureFvPatchScalarField
		(
			const wavePressureFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new wavePressureFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamWave_EXPORT wavePressureFvPatchScalarField
		(
			const wavePressureFvPatchScalarField&,
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
					new wavePressureFvPatchScalarField
					(
						*this,
						iF
					)
					);
		}


		// Member Functions

			// Evaluation functions

				//- Return the current modelled pressure field on the patch faces
		FoamWave_EXPORT tmp<scalarField> p() const;

		//- Return the current modelled pressure field in the neighbour cell
		FoamWave_EXPORT tmp<scalarField> pn() const;

		//- Update the coefficients associated with the patch field
		FoamWave_EXPORT virtual void updateCoeffs();


		//- Write
		FoamWave_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wavePressureFvPatchScalarField_Header
