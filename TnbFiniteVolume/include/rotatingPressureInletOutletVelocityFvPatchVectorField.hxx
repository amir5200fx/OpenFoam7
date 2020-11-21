#pragma once
#ifndef _rotatingPressureInletOutletVelocityFvPatchVectorField_Header
#define _rotatingPressureInletOutletVelocityFvPatchVectorField_Header

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
	tnbLib::rotatingPressureInletOutletVelocityFvPatchVectorField

Description
	This velocity inlet/outlet boundary condition is applied to patches in a
	rotating frame where the pressure is specified.  A zero-gradient is applied
	for outflow (as defined by the flux); for inflow, the velocity is obtained
	from the flux with a direction normal to the patch faces.

Usage
	\table
		Property     | Description             | Required    | Default value
		phi          | flux field name         | no          | phi
		tangentialVelocity | tangential velocity field | no  |
		omega        | angular velocty of the frame [rad/s] | yes    |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            rotatingPressureInletOutletVelocity;
		phi             phi;
		tangentialVelocity uniform (0 0 0);
		omega           100;
	}
	\endverbatim

	The \c omega entry is a Function1 type, able to describe time varying
	functions.

Note
	Sign conventions:
	- positive flux (out of domain): apply zero-gradient condition
	- negative flux (into of domain): derive from the flux in the patch-normal
	  direction

See also
	tnbLib::pressureInletOutletVelocityFvPatchVectorField
	tnbLib::Function1Types

SourceFiles
	rotatingPressureInletOutletVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchFields.hxx>
#include <pressureInletOutletVelocityFvPatchVectorField.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
	   Class rotatingPressureInletOutletVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class rotatingPressureInletOutletVelocityFvPatchVectorField
		:
		public pressureInletOutletVelocityFvPatchVectorField
	{
		// Private Data

			//- Angular velocity of the frame
		autoPtr<Function1<vector>> omega_;


		// Private Member Functions

			//- Calculate the tangentialVelocity from omega
		FoamFiniteVolume_EXPORT void calcTangentialVelocity();


	public:

		//- Runtime type information
		/*TypeName("rotatingPressureInletOutletVelocity");*/
		static const char* typeName_() { return "rotatingPressureInletOutletVelocity"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT rotatingPressureInletOutletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT rotatingPressureInletOutletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  rotatingPressureInletOutletVelocityFvPatchVectorField
		//  onto a new patch
		FoamFiniteVolume_EXPORT rotatingPressureInletOutletVelocityFvPatchVectorField
		(
			const rotatingPressureInletOutletVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT rotatingPressureInletOutletVelocityFvPatchVectorField
		(
			const rotatingPressureInletOutletVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new rotatingPressureInletOutletVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT rotatingPressureInletOutletVelocityFvPatchVectorField
		(
			const rotatingPressureInletOutletVelocityFvPatchVectorField&,
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
					new rotatingPressureInletOutletVelocityFvPatchVectorField
					(
						*this,
						iF
					)
					);
		}


		// Member Functions

			//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_rotatingPressureInletOutletVelocityFvPatchVectorField_Header
