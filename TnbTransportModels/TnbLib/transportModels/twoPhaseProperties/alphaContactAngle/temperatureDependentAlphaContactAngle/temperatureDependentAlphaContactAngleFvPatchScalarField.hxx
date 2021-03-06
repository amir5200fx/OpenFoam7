#pragma once
#ifndef _temperatureDependentAlphaContactAngleFvPatchScalarField_Header
#define _temperatureDependentAlphaContactAngleFvPatchScalarField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
	tnbLib::temperatureDependentAlphaContactAngleFvPatchScalarField

Description
	Temperature-dependent alphaContactAngle scalar boundary condition.

	The contact angle is evaluated from the specified tnbLib::Function1 for the
	temperature field looked-up from the mesh database the name of which
	may optionally be provided.

Usage
	\table
		Property     | Description             | Required    | Default value
		T            | Temperature field name  | no          | T
		theta0       | Contact angle function  | yes         |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            temperatureDependentAlphaContactAngle;
		theta0          constant 60;
	}
	\endverbatim

See also
	tnbLib::alphaContactAngleFvPatchScalarField
	tnbLib::constantAlphaContactAngleFvPatchScalarField
	tnbLib::Function1

SourceFiles
	temperatureDependentAlphaContactAngleFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <alphaContactAngleFvPatchScalarField.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
		   Class temperatureDependentAlphaContactAngleFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class temperatureDependentAlphaContactAngleFvPatchScalarField
		:
		public alphaContactAngleFvPatchScalarField
	{
		// Private Data

			//- Name of temperature field, default = "T"
		word TName_;

		//- Equilibrium contact angle function
		autoPtr<Function1<scalar>> theta0_;


	public:

		//- Runtime type information
		//TypeName("temperatureDependentAlphaContactAngle");
		static const char* typeName_() { return "temperatureDependentAlphaContactAngle"; }
		static FoamTransportModels_EXPORT const ::tnbLib::word typeName;
		static FoamTransportModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamTransportModels_EXPORT temperatureDependentAlphaContactAngleFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamTransportModels_EXPORT temperatureDependentAlphaContactAngleFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  temperatureDependentAlphaContactAngleFvPatchScalarField
		//  onto a new patch
		FoamTransportModels_EXPORT temperatureDependentAlphaContactAngleFvPatchScalarField
		(
			const temperatureDependentAlphaContactAngleFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamTransportModels_EXPORT temperatureDependentAlphaContactAngleFvPatchScalarField
		(
			const temperatureDependentAlphaContactAngleFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new temperatureDependentAlphaContactAngleFvPatchScalarField
					(
						*this
					)
					);
		}

		//- Copy constructor setting internal field reference
		FoamTransportModels_EXPORT temperatureDependentAlphaContactAngleFvPatchScalarField
		(
			const temperatureDependentAlphaContactAngleFvPatchScalarField&,
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
					new temperatureDependentAlphaContactAngleFvPatchScalarField
					(
						*this,
						iF
					)
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

#endif // !_temperatureDependentAlphaContactAngleFvPatchScalarField_Header
