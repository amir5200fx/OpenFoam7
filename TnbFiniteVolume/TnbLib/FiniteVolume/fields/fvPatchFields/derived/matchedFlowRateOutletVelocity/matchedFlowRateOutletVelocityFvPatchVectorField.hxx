#pragma once
#ifndef _matchedFlowRateOutletVelocityFvPatchVectorField_Header
#define _matchedFlowRateOutletVelocityFvPatchVectorField_Header

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
	tnbLib::matchedFlowRateOutletVelocityFvPatchVectorField

Description
	Velocity outlet boundary condition which corrects the extrapolated velocity
	to match the flow rate of the specified corresponding inlet patch.

Usage
	\table
		Property     | Description             | Required    | Default value
		inletPatch   | Corresponding inlet patch name | yes  |
		volumetric   | Set volumetric or mass flow-rate | no | false
		rho          | density field name      | no          | rho
	\endtable

	Example of the boundary condition specification for a volumetric flow rate:
	\verbatim
	<patchName>
	{
		type                matchedFlowRateOutletVelocity;
		inletPatch          inlet;
		value               uniform (0 0 0);
	}
	\endverbatim

See also
	tnbLib::fixedValueFvPatchField

SourceFiles
	matchedFlowRateOutletVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			   Class matchedFlowRateOutletVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class matchedFlowRateOutletVelocityFvPatchVectorField
		:
		public fixedValueFvPatchVectorField
	{
		// Private Data

			//- Inlet patch name from which the corresponding flow rate is obtained
		word inletPatchName_;

		//- Is volumetric?
		bool volumetric_;

		//- Name of the density field used to normalize the mass flux
		word rhoName_;


		// Private Member Functions

			//- Update the patch values given the appropriate density type and value
		template<class RhoType>
		void updateValues
		(
			const label inletPatchID,
			const RhoType& rhoOutlet,
			const RhoType& rhoInlet
		);


	public:

		//- Runtime type information
		/*TypeName("matchedFlowRateOutletVelocity");*/
		static const char* typeName_() { return "matchedFlowRateOutletVelocity"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			 //- Construct from patch and internal field
		FoamFiniteVolume_EXPORT matchedFlowRateOutletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT matchedFlowRateOutletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  matchedFlowRateOutletVelocityFvPatchVectorField
		//  onto a new patch
		FoamFiniteVolume_EXPORT matchedFlowRateOutletVelocityFvPatchVectorField
		(
			const matchedFlowRateOutletVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT matchedFlowRateOutletVelocityFvPatchVectorField
		(
			const matchedFlowRateOutletVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new matchedFlowRateOutletVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT matchedFlowRateOutletVelocityFvPatchVectorField
		(
			const matchedFlowRateOutletVelocityFvPatchVectorField&,
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
					new matchedFlowRateOutletVelocityFvPatchVectorField(*this, iF)
					);
		}


		// Member Functions

			//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();

		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_matchedFlowRateOutletVelocityFvPatchVectorField_Header
