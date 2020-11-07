#pragma once
#ifndef _supersonicFreestreamFvPatchVectorField_Header
#define _supersonicFreestreamFvPatchVectorField_Header

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
	tnbLib::supersonicFreestreamFvPatchVectorField

Description
	This boundary condition provides a supersonic free-stream condition.

	- supersonic outflow is vented according to ???
	- supersonic inflow is assumed to occur according to the Prandtl-Meyer
	  expansion process.
	- subsonic outflow is applied via a zero-gradient condition from inside
	  the domain.

Usage
	\table
		Property     | Description             | Required    | Default value
		T            | Temperature field name  | no          | T
		p            | Pressure field name     | no          | p
		psi          | Compressibility field name | no       | thermo:psi
		UInf         | free-stream velocity    | yes         |
		pInf         | free-stream pressure    | yes         |
		TInf         | free-stream temperature | yes         |
		gamma        | heat capacity ratio (cp/Cv) | yes     |
	\endtable

	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            supersonicFreestream;
		UInf            500;
		pInf            1e4;
		TInf            265;
		gamma           1.4;
	}
	\endverbatim

Note
	This boundary condition is ill-posed if the free-stream flow is normal
	to the boundary.

SourceFiles
	supersonicFreestreamFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <fvPatchFields.hxx>
#include <mixedFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
			   Class supersonicFreestreamFvPatchVectorField Declaration
	\*---------------------------------------------------------------------------*/

	class supersonicFreestreamFvPatchVectorField
		:
		public mixedFvPatchVectorField
	{
		// Private Data

			//- Name of temperature field, default = "T"
		word TName_;

		//- Name of pressure field, default = "p"
		word pName_;

		//- Name of compressibility field field, default = "thermo:psi"
		word psiName_;

		//- Velocity of the free stream
		vector UInf_;

		//- Pressure of the free stream
		scalar pInf_;

		//- Temperature of the free stream
		scalar TInf_;

		//- Heat capacity ratio
		scalar gamma_;


	public:

		//- Runtime type information
		/*TypeName("supersonicFreestream");*/
		static const char* typeName_() { return "supersonicFreestream"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamFiniteVolume_EXPORT supersonicFreestreamFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamFiniteVolume_EXPORT supersonicFreestreamFvPatchVectorField
		(
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given supersonicFreestreamFvPatchVectorField
		//  onto a new patch
		FoamFiniteVolume_EXPORT supersonicFreestreamFvPatchVectorField
		(
			const supersonicFreestreamFvPatchVectorField&,
			const fvPatch&,
			const DimensionedField<vector, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamFiniteVolume_EXPORT supersonicFreestreamFvPatchVectorField
		(
			const supersonicFreestreamFvPatchVectorField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchVectorField> clone() const
		{
			return tmp<fvPatchVectorField>
				(
					new supersonicFreestreamFvPatchVectorField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamFiniteVolume_EXPORT supersonicFreestreamFvPatchVectorField
		(
			const supersonicFreestreamFvPatchVectorField&,
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
					new supersonicFreestreamFvPatchVectorField(*this, iF)
					);
		}


		// Member Functions

			// Access

				//- Return the velocity at infinity
		const vector& UInf() const
		{
			return UInf_;
		}

		//- Return reference to the velocity at infinity to allow adjustment
		vector& UInf()
		{
			return UInf_;
		}

		//- Return the pressure at infinity
		scalar pInf() const
		{
			return pInf_;
		}

		//- Return reference to the pressure at infinity to allow adjustment
		scalar& pInf()
		{
			return pInf_;
		}

		//- Return the temperature at infinity
		scalar TInf() const
		{
			return TInf_;
		}

		//- Return reference to the temperature at infinity
		//  to allow adjustment
		scalar& TInf()
		{
			return TInf_;
		}


		// Evaluation functions

		//- Update the coefficients associated with the patch field
		FoamFiniteVolume_EXPORT virtual void updateCoeffs();


		//- Write
		FoamFiniteVolume_EXPORT virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_supersonicFreestreamFvPatchVectorField_Header
