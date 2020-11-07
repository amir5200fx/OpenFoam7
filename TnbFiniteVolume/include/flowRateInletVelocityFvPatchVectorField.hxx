#pragma once
#ifndef _flowRateInletVelocityFvPatchVectorField_Header
#define _flowRateInletVelocityFvPatchVectorField_Header

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
	tnbLib::flowRateInletVelocityFvPatchVectorField

Description
	Velocity inlet boundary condition either correcting the extrapolated
	velocity or creating a uniform velocity field normal to the patch adjusted
	to match the specified flow rate

	For a mass-based flux:
	- the flow rate should be provided in kg/s
	- if \c rho is "none" the flow rate is in m3/s
	- otherwise \c rho should correspond to the name of the density field
	- if the density field cannot be found in the database, the user must
	  specify the inlet density using the \c rhoInlet entry

	For a volumetric-based flux:
	- the flow rate is in m3/s

Usage
	\table
		Property     | Description             | Required    | Default value
		massFlowRate | mass flow rate [kg/s]   | no          |
		volumetricFlowRate | volumetric flow rate [m3/s]| no |
		rho          | density field name      | no          | rho
		rhoInlet     | inlet density           | no          |
		extrapolateProfile | Extrapolate velocity profile | no | false
	\endtable

	Example of the boundary condition specification for a volumetric flow rate:
	\verbatim
	<patchName>
	{
		type                flowRateInletVelocity;
		volumetricFlowRate  0.2;
		extrapolateProfile  yes;
		value               uniform (0 0 0);
	}
	\endverbatim

	Example of the boundary condition specification for a mass flow rate:
	 \verbatim
	<patchName>
	{
		type                flowRateInletVelocity;
		massFlowRate        0.2;
		extrapolateProfile  yes;
		rho                 rho;
		rhoInlet            1.0;
		value               uniform (0 0 0);
	}
	\endverbatim

	The \c flowRate entry is a \c Function1 of time, see tnbLib::Function1Types.

Note
	- \c rhoInlet is required for the case of a mass flow rate, where the
	  density field is not available at start-up
	- The value is positive into the domain (as an inlet)
	- May not work correctly for transonic inlets
	- Strange behaviour with potentialFoam since the U equation is not solved

See also
	tnbLib::fixedValueFvPatchField
	tnbLib::Function1Types
	tnbLib::flowRateOutletVelocityFvPatchVectorField

SourceFiles
	flowRateInletVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fixedValueFvPatchFields.hxx>
#include <Function1.hxx>

#include <Switch.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			   Class flowRateInletVelocityFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class flowRateInletVelocityFvPatchVectorField
		:
		public fixedValueFvPatchVectorField
	{
		// Private Data

			//- Inlet integral flow rate
		autoPtr<Function1<scalar>> flowRate_;

		//- Is volumetric?
		bool volumetric_;

		//- Name of the density field used to normalize the mass flux
		word rhoName_;

		//- Rho initialisation value (for start; if value not supplied)
		scalar rhoInlet_;

		//- Set true to extrapolate the velocity profile from the interior
		Switch extrapolateProfile_;


		// Private Member Functions

			//- Update the patch values given the appropriate density type and value
		template<class RhoType>
		void updateValues(const RhoType& rho);


	public:

		//- Runtime type information
		//TypeName("flowRateInletVelocity");
		static const char* typeName_() { return "flowRateInletVelocity"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			 //- Construct from patch and internal field
		FoamFiniteVolume_EXPORT flowRateInletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT flowRateInletVelocityFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  flowRateInletVelocityFvPatchVectorField
		//  onto a new patch
		FoamFiniteVolume_EXPORT flowRateInletVelocityFvPatchVectorField
		(
			const flowRateInletVelocityFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT flowRateInletVelocityFvPatchVectorField
		(
			const flowRateInletVelocityFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new flowRateInletVelocityFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT flowRateInletVelocityFvPatchVectorField
		(
			const flowRateInletVelocityFvPatchVectorField&,
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
					new flowRateInletVelocityFvPatchVectorField(*this, iF)
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

#endif // !_flowRateInletVelocityFvPatchVectorField_Header
