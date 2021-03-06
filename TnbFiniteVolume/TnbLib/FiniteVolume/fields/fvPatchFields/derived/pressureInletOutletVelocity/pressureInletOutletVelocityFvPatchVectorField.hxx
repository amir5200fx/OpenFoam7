#pragma once
#ifndef _pressureInletOutletVelocityFvPatchVectorField_Header
#define _pressureInletOutletVelocityFvPatchVectorField_Header

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
	tnbLib::pressureInletOutletVelocityFvPatchVectorField

Description
	This velocity inlet/outlet boundary condition is applied to pressure
	boundaries where the pressure is specified.  A zero-gradient condition is
	applied for outflow (as defined by the flux); for inflow, the velocity is
	obtained from the patch-face normal component of the internal-cell value.

	The tangential patch velocity can be optionally specified.

Usage
	\table
		Property     | Description             | Required    | Default value
		phi          | flux field name         | no          | phi
		tangentialVelocity | tangential velocity field | no  |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            pressureInletOutletVelocity;
		phi             phi;
		tangentialVelocity uniform (0 0 0);
		value           uniform 0;
	}
	\endverbatim

Note
	Sign conventions:
	- positive flux (out of domain): apply zero-gradient condition
	- negative flux (into of domain): derive from the flux in the patch-normal
	  direction

SourceFiles
	pressureInletOutletVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchFields.hxx>
#include <directionMixedFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
		   Class pressureInletOutletVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class pressureInletOutletVelocityFvPatchVectorField
		:
		public directionMixedFvPatchVectorField
	{
		// Private Data

			//- Flux field name
		word phiName_;

		//- Optional tangential velocity component
		vectorField tangentialVelocity_;


	public:

		//- Runtime type information
		//TypeName("pressureInletOutletVelocity");
		static const char* typeName_() { return "pressureInletOutletVelocity"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT pressureInletOutletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT pressureInletOutletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  pressureInletOutletVelocityFvPatchVectorField onto a new patch
		FoamFiniteVolume_EXPORT pressureInletOutletVelocityFvPatchVectorField
		(
			const pressureInletOutletVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT pressureInletOutletVelocityFvPatchVectorField
		(
			const pressureInletOutletVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new pressureInletOutletVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT pressureInletOutletVelocityFvPatchVectorField
		(
			const pressureInletOutletVelocityFvPatchVectorField&,
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
					new pressureInletOutletVelocityFvPatchVectorField(*this, iF)
					);
		}


		// Member Functions

			// Attributes

				//- Return true: this patch field is altered by assignment
		virtual bool assignable() const
		{
			return true;
		}


		// Access

			//- Return the name of phi
		const word& phiName() const
		{
			return phiName_;
		}

		//- Return reference to the name of phi to allow adjustment
		word& phiName()
		{
			return phiName_;
		}

		//- Return the tangential velocity
		const vectorField& tangentialVelocity() const
		{
			return tangentialVelocity_;
		}

		//- Reset the tangential velocity
		FoamFiniteVolume_EXPORT void setTangentialVelocity(const vectorField& tangentialVelocity);


		// Mapping functions

			//- Map (and resize as needed) from self given a mapping object
			//  Used to update fields following mesh topology change
		FoamFiniteVolume_EXPORT virtual void autoMap(const fvPatchFieldMapper&);

		//- Reverse map the given fvPatchField onto this fvPatchField
		//  Used to reconstruct fields
		FoamFiniteVolume_EXPORT virtual void rmap(const fvPatchVectorField&, const labelList&);


		//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();

		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;


		// Member Operators

		FoamFiniteVolume_EXPORT virtual void operator=(const fvPatchField<vector>& pvf);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pressureInletOutletVelocityFvPatchVectorField_Header
