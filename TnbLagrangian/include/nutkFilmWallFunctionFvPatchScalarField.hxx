#pragma once
#ifndef _nutkFilmWallFunctionFvPatchScalarField_Header
#define _nutkFilmWallFunctionFvPatchScalarField_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2020 OpenFOAM Foundation
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
	tnbLib::compressible::RASModels::nutkFilmWallFunctionFvPatchScalarField

Description
	This boundary condition provides a turbulent viscosity condition when
	using wall functions, based on turbulence kinetic energy, for use with
	surface film models.

Usage
	Example of the boundary condition specification:
	\verbatim
	<patchName>
	{
		type            nutkFilmWallFunction;
		value           uniform 0;
	}
	\endverbatim

See also
	tnbLib::nutkWallFunctionFvPatchScalarField

SourceFiles
	nutkFilmWallFunctionFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <nutkWallFunctionFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressible
	{
		namespace RASModels
		{

			/*---------------------------------------------------------------------------*\
					 Class nutkFilmWallFunctionFvPatchScalarField Declaration
			\*---------------------------------------------------------------------------*/

			class nutkFilmWallFunctionFvPatchScalarField
				:
				public nutkWallFunctionFvPatchScalarField
			{
			protected:

				// Protected data

					//- B Coefficient (default = 5.5)
				scalar B_;

				//- y+ value for laminar -> turbulent transition (default = 11.05)
				scalar yPlusCrit_;


				// Protected member functions

					//- Calculate the turbulence viscosity
				FoamLagrangian_EXPORT virtual tmp<scalarField> nut() const;

				//- Calculate the friction velocity
				FoamLagrangian_EXPORT virtual tmp<scalarField> calcUTau(const scalarField& magGradU) const;


			public:

				//- Runtime type information
				//TypeName("nutkFilmWallFunction");
				static const char* typeName_() { return "nutkFilmWallFunction"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from patch and internal field
				FoamLagrangian_EXPORT nutkFilmWallFunctionFvPatchScalarField
				(
					const fvPatch&,
					const DimensionedField<scalar, volMesh>&
				);

				//- Construct from patch, internal field and dictionary
				FoamLagrangian_EXPORT nutkFilmWallFunctionFvPatchScalarField
				(
					const fvPatch&,
					const DimensionedField<scalar, volMesh>&,
					const dictionary&
				);

				//- Construct by mapping given
				//  nutkFilmWallFunctionFvPatchScalarField
				//  onto a new patch
				FoamLagrangian_EXPORT nutkFilmWallFunctionFvPatchScalarField
				(
					const nutkFilmWallFunctionFvPatchScalarField&,
					const fvPatch&,
					const DimensionedField<scalar, volMesh>&,
					const fvPatchFieldMapper&
				);

				//- Copy constructor
				FoamLagrangian_EXPORT nutkFilmWallFunctionFvPatchScalarField
				(
					const nutkFilmWallFunctionFvPatchScalarField&
				);

				//- Construct and return a clone
				virtual tmp<fvPatchScalarField> clone() const
				{
					return tmp<fvPatchScalarField>
						(
							new nutkFilmWallFunctionFvPatchScalarField(*this)
							);
				}

				//- Copy constructor setting internal field reference
				FoamLagrangian_EXPORT nutkFilmWallFunctionFvPatchScalarField
				(
					const nutkFilmWallFunctionFvPatchScalarField&,
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
							new nutkFilmWallFunctionFvPatchScalarField(*this, iF)
							);
				}


				// Member Functions

					// Evaluation functions

						//- Calculate and return the yPlus at the boundary
				FoamLagrangian_EXPORT virtual tmp<scalarField> yPlus() const;


				// I-O

					//- Write
				FoamLagrangian_EXPORT virtual void write(Ostream& os) const;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace RASModels
	} // End namespace compressible
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_nutkFilmWallFunctionFvPatchScalarField_Header
