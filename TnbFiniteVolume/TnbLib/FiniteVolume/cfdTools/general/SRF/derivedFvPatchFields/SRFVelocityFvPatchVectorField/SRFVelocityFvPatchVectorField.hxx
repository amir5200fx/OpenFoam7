#pragma once
#ifndef _SRFVelocityFvPatchVectorField_Header
#define _SRFVelocityFvPatchVectorField_Header

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
	tnbLib::SRFVelocityFvPatchVectorField

Description
	Velocity condition to be used in conjunction with the single
	rotating frame (SRF) model (see: SRFModel class)

	Given the free stream velocity in the absolute frame, the condition
	applies the appropriate rotation transformation in time and space to
	determine the local velocity.

	The optional \c relative flag switches the behaviour of the patch
	such that:

		- relative = yes: inlet velocity applied 'as is':

		\f[
			U_p = U_{in}
		\f]

		- relative = no : SRF velocity is subtracted from the inlet velocity:

		\f[
			U_p = U_{in} - U_{p,srf}
		\f]

	where
	\vartable
		U_p     = patch velocity [m/s]
		U_{in}  = user-specified inlet velocity
		U_{p,srf} = SRF velocity
	\endvartable


Usage
	\table
		Property     | Description             | Required    | Default value
		inletValue   | inlet velocity          | yes         |
		relative     | inletValue relative motion to the SRF? | yes     |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            SRFVelocity;
		inletValue      uniform (0 0 0);
		relative        yes;
		value           uniform (0 0 0);    // initial value
	}
	\endverbatim

See also
	tnbLib::fixedValueFvPatchField

SourceFiles
	SRFVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchFields.hxx>
#include <fixedValueFvPatchFields.hxx>
#include <Switch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				   Class SRFVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class SRFVelocityFvPatchVectorField
		:
		public fixedValueFvPatchVectorField
	{
		// Private Data

		//- Is the supplied inlet value relative to the SRF
		Switch relative_;

		//- Inlet value [m/s]
		vectorField inletValue_;


	public:

		//- Runtime type information
		//TypeName("SRFVelocity");
		static const char* typeName_() { return "SRFVelocity"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

		//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT SRFVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT SRFVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given SRFVelocityFvPatchVectorField
		//  onto a new patch
		FoamFiniteVolume_EXPORT SRFVelocityFvPatchVectorField
		(
			const SRFVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT SRFVelocityFvPatchVectorField
		(
			const SRFVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new SRFVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT SRFVelocityFvPatchVectorField
		(
			const SRFVelocityFvPatchVectorField&,
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
					new SRFVelocityFvPatchVectorField(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Return const access to the relative flag
		const Switch& relative() const
		{
			return relative_;
		}


		// Mapping functions

			//- Map (and resize as needed) from self given a mapping object
			//  Used to update fields following mesh topology change
		FoamFiniteVolume_EXPORT virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		FoamFiniteVolume_EXPORT virtual void rmap(const fvPatchVectorField&, const labelList&);

		// Evaluation functions

		//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();


		// I-O

		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SRFVelocityFvPatchVectorField_Header
