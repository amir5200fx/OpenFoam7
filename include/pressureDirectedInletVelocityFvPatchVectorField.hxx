#pragma once
#ifndef _pressureDirectedInletVelocityFvPatchVectorField_Header
#define _pressureDirectedInletVelocityFvPatchVectorField_Header

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
	tnbLib::pressureDirectedInletVelocityFvPatchVectorField

Description
	This velocity inlet boundary condition is applied to patches where the
	pressure is specified.  The inflow velocity is obtained from the flux with
	the specified inlet direction" direction.

Usage
	\table
		Property     | Description             | Required    | Default value
		phi          | flux field name         | no          | phi
		rho          | density field name      | no          | rho
		inletDirection | inlet direction per patch face | yes |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            pressureDirectedInletVelocity;
		phi             phi;
		rho             rho;
		inletDirection  uniform (1 0 0);
		value           uniform 0;
	}
	\endverbatim

Note
	If reverse flow is possible or expected use the
	pressureDirectedInletOutletVelocityFvPatchVectorField condition instead.


See also
	tnbLib::fixedValueFvPatchField
	tnbLib::pressureDirectedInletOutletVelocityFvPatchVectorField

SourceFiles
	pressureDirectedInletVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchFields.hxx>
#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
		   Class pressureDirectedInletVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class pressureDirectedInletVelocityFvPatchVectorField
		:
		public fixedValueFvPatchVectorField
	{
		// Private Data

			//- Flux field name
		word phiName_;

		//- Density field name
		word rhoName_;

		//- Inlet direction
		vectorField inletDir_;


	public:

		//- Runtime type information
		/*TypeName("pressureDirectedInletVelocity");*/
		static const char* typeName_() { return "pressureDirectedInletVelocity"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

		//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT pressureDirectedInletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT pressureDirectedInletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  pressureDirectedInletVelocityFvPatchVectorField
		//  onto a new patch
		FoamFiniteVolume_EXPORT pressureDirectedInletVelocityFvPatchVectorField
		(
			const pressureDirectedInletVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT pressureDirectedInletVelocityFvPatchVectorField
		(
			const pressureDirectedInletVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new pressureDirectedInletVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT pressureDirectedInletVelocityFvPatchVectorField
		(
			const pressureDirectedInletVelocityFvPatchVectorField&,
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
					new pressureDirectedInletVelocityFvPatchVectorField
					(
						*this,
						iF
					)
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

		//- Return the name of rho
		const word& rhoName() const
		{
			return rhoName_;
		}

		//- Return reference to the name of rho to allow adjustment
		word& rhoName()
		{
			return rhoName_;
		}

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

#endif // !_pressureDirectedInletVelocityFvPatchVectorField_Header
