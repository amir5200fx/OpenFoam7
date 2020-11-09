#pragma once
#ifndef _constantAlphaContactAngleFvPatchScalarField_Header
#define _constantAlphaContactAngleFvPatchScalarField_Header

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
	tnbLib::constantAlphaContactAngleFvPatchScalarField

Description
	A constant alphaContactAngle scalar boundary condition.

See also
	tnbLib::alphaContactAngleFvPatchScalarField
	tnbLib::temperatureDependentAlphaContactAngleFvPatchScalarField

SourceFiles
	constantAlphaContactAngleFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <alphaContactAngleFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class constantAlphaContactAngleFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class constantAlphaContactAngleFvPatchScalarField
		:
		public alphaContactAngleFvPatchScalarField
	{
		// Private Data

			//- Equilibrium contact angle
		scalar theta0_;


	public:

		//- Runtime type information
		//TypeName("constantAlphaContactAngle");
		static const char* typeName_() { return "constantAlphaContactAngle"; }
		static FoamTransportModels_EXPORT const ::tnbLib::word typeName;
		static FoamTransportModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamTransportModels_EXPORT constantAlphaContactAngleFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamTransportModels_EXPORT constantAlphaContactAngleFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  constantAlphaContactAngleFvPatchScalarField
		//  onto a new patch
		FoamTransportModels_EXPORT constantAlphaContactAngleFvPatchScalarField
		(
			const constantAlphaContactAngleFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamTransportModels_EXPORT constantAlphaContactAngleFvPatchScalarField
		(
			const constantAlphaContactAngleFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new constantAlphaContactAngleFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamTransportModels_EXPORT constantAlphaContactAngleFvPatchScalarField
		(
			const constantAlphaContactAngleFvPatchScalarField&,
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
					new constantAlphaContactAngleFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

			//- Return the equilibrium contact-angle
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

#endif // !_constantAlphaContactAngleFvPatchScalarField_Header
