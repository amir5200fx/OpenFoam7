#pragma once
#ifndef _nutkWallFunctionFvPatchScalarField_Header
#define _nutkWallFunctionFvPatchScalarField_Header

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
	tnbLib::nutkWallFunctionFvPatchScalarField

Description
	Turbulent viscosity wall-function boundary condition
	for high Reynolds number flows based on near-wall turbulence kinetic energy.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            nutkWallFunction;
		value           uniform 0;
	}
	\endverbatim

See also
	tnbLib::nutWallFunctionFvPatchScalarField

SourceFiles
	nutkWallFunctionFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <nutWallFunctionFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				 Class nutkWallFunctionFvPatchScalarField Declaration
	\*---------------------------------------------------------------------------*/

	class nutkWallFunctionFvPatchScalarField
		:
		public nutWallFunctionFvPatchScalarField
	{
	protected:

		// Protected Member Functions

			//- Calculate the turbulence viscosity
		FoamTurbulence_EXPORT virtual tmp<scalarField> nut() const;


	public:

		//- Runtime type information
		//TypeName("nutkWallFunction");
		static const char* typeName_() { return "nutkWallFunction"; }
		static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
		static FoamTurbulence_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from patch and internal field
		FoamTurbulence_EXPORT nutkWallFunctionFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		FoamTurbulence_EXPORT nutkWallFunctionFvPatchScalarField
		(
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given
		//  nutkWallFunctionFvPatchScalarField
		//  onto a new patch
		FoamTurbulence_EXPORT nutkWallFunctionFvPatchScalarField
		(
			const nutkWallFunctionFvPatchScalarField&,
			const fvPatch&,
			const DimensionedField<scalar, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Copy constructor
		FoamTurbulence_EXPORT nutkWallFunctionFvPatchScalarField
		(
			const nutkWallFunctionFvPatchScalarField&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchScalarField> clone() const
		{
			return tmp<fvPatchScalarField>
				(
					new nutkWallFunctionFvPatchScalarField(*this)
					);
		}

		//- Copy constructor setting internal field reference
		FoamTurbulence_EXPORT nutkWallFunctionFvPatchScalarField
		(
			const nutkWallFunctionFvPatchScalarField&,
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
					new nutkWallFunctionFvPatchScalarField(*this, iF)
					);
		}


		// Member Functions

			//- Calculate and return the yPlus at the boundary
		FoamTurbulence_EXPORT virtual tmp<scalarField> yPlus() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_nutkWallFunctionFvPatchScalarField_Header
