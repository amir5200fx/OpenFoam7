#pragma once
#ifndef _pressureInletVelocityFvPatchVectorField_Header
#define _pressureInletVelocityFvPatchVectorField_Header

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
	tnbLib::pressureInletVelocityFvPatchVectorField

Description
	This velocity inlet boundary condition is applied to patches where the
	pressure is specified.  The inflow velocity is obtained from the flux with
	a direction normal to the patch faces.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            pressureInletVelocity;
		phi             phi;
		rho             rho;
		value           uniform 0;
	}
	\endverbatim

Note
	If reverse flow is possible or expected use
	the pressureInletOutletVelocityFvPatchVectorField condition instead.

See also
	tnbLib::fixedValueFvPatchField
	tnbLib::pressureInletOutletVelocityFvPatchVectorField

SourceFiles
	pressureInletVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchFields.hxx>
#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			   Class pressureInletVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class pressureInletVelocityFvPatchVectorField
		:
		public fixedValueFvPatchVectorField
	{
		// Private Data

			//- Flux field name
		word phiName_;

		//- Density field name
		word rhoName_;


	public:

		//- Runtime type information
		//TypeName("pressureInletVelocity");
		static const char* typeName_() { return "pressureInletVelocity"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT pressureInletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT pressureInletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given pressureInletVelocityFvPatchVectorField
		//  onto a new patch
		FoamFiniteVolume_EXPORT pressureInletVelocityFvPatchVectorField
		(
			const pressureInletVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT pressureInletVelocityFvPatchVectorField
		(
			const pressureInletVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new pressureInletVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT pressureInletVelocityFvPatchVectorField
		(
			const pressureInletVelocityFvPatchVectorField&,
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
					new pressureInletVelocityFvPatchVectorField(*this, iF)
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

#endif // !_pressureInletVelocityFvPatchVectorField_Header
