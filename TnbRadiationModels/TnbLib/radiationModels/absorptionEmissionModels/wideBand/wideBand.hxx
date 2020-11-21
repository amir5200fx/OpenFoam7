#pragma once
#ifndef _wideBand_Header
#define _wideBand_Header

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
	tnbLib::radiationModels::absorptionEmission::wideBand

Description
	wideBand radiation absorption and emission coefficients for continuous
	phase.

	All the bands should have the same number of species and have to be entered
	in the same order.

	There is no check of continuity of the bands. They should not overlap or
	have gaps.

	The emission constant proportionality is specified per band (EhrrCoeff).

	The coefficients for the species have to be specified for use in
	moles x P [atm], i.e. (k[i] = species[i]*p*9.869231e-6).

	The lookup table file should be in the constant directory.

Example
	\verbatim
	absorptionEmissionModel wideBand;

	wideBandCoeffs
	{
		band0
		{
			bandLimits      (1e-6 2.63e-6);

			CH4
			{
				Tcommon         300;
				Tlow            300;
				Thigh           2500;
				invTemp         false;
				loTcoeffs       (0 0 0 0 0 0) ;
				hiTcoeffs       (0.1 0 0 0 0 0);
			}

			CO2
			{
				Tcommon         300;
				Tlow            300;
				Thigh           2500;
				invTemp         false;
				loTcoeffs       (0 0 0 0 0 0) ;
				hiTcoeffs       (0.1 0 0 0 0 0);
			}

			H2O
			{
				Tcommon         300;
				Tlow            300;
				Thigh           2500;
				invTemp         false;
				loTcoeffs       (0 0 0 0 0 0);
				hiTcoeffs       (0.1 0 0 0 0 0);
			}
			Ysoot
			{
				Tcommon         300;
				Tlow            300;
				Thigh           2500;
				invTemp         false;
				loTcoeffs       (0 0 0 0 0 0);
				hiTcoeffs       (0.1 0 0 0 0 0);
			}
		}
	}
	\endverbatim

SourceFiles
	wideBand.C

\*---------------------------------------------------------------------------*/

#include <interpolationLookUpTable.hxx>
#include <absorptionEmissionModel.hxx>
#include <HashTable.hxx>
#include <absorptionCoeffs.hxx>
#include <fluidThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace absorptionEmissionModels
		{

			/*---------------------------------------------------------------------------*\
										Class wideBand Declaration
			\*---------------------------------------------------------------------------*/

			class wideBand
				:
				public absorptionEmissionModel
			{
			public:

				// Public data

					//- Maximum number of species considered for absorptivity
				static const int nSpecies_ = 5;

				//- Maximum number of bands
				static const int maxBands_ = 10;

				//-  Absorption coefficients
				FixedList<FixedList<absorptionCoeffs, nSpecies_>, maxBands_> coeffs_;


			protected:

				// Protected data

					//- Absorption model dictionary
				dictionary coeffsDict_;

				//- Hash table with species names
				HashTable<label> speciesNames_;

				//- Indices of species in the look-up table
				FixedList<label, nSpecies_> specieIndex_;

				//- Bands
				FixedList<Vector2D<scalar>, maxBands_> iBands_;

				//- Look-up table of species related to ft
				mutable autoPtr<interpolationLookUpTable<scalar>> lookUpTablePtr_;

				//- Thermo package
				const fluidThermo& thermo_;

				//- Bands
				label nBands_;

				//- Pointer list of species being solved involved in the absorption
				UPtrList<volScalarField> Yj_;

				// Total wave length covered by the bands
				scalar totalWaveLength_;


			public:

				//- Runtime type information
			//	TypeName("wideBand");
				static const char* typeName_() { return "wideBand"; }
				static FoamRadiationModels_EXPORT const ::tnbLib::word typeName;
				static FoamRadiationModels_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from components
				FoamRadiationModels_EXPORT wideBand
				(
					const dictionary& dict,
					const fvMesh& mesh,
					const word& modelName = typeName
				);


				//- Destructor
				FoamRadiationModels_EXPORT virtual ~wideBand();


				// Member Functions

					//- Absorption coefficient for continuous phase
				FoamRadiationModels_EXPORT tmp<volScalarField> aCont(const label bandi = 0) const;

				//- Emission coefficient for continuous phase
				FoamRadiationModels_EXPORT tmp<volScalarField> eCont(const label bandi = 0) const;

				//- Emission contribution for continuous phase
				FoamRadiationModels_EXPORT tmp<volScalarField> ECont(const label bandi = 0) const;

				//-
				inline bool isGrey() const
				{
					return false;
				}

				//- Number of bands
				inline label nBands() const
				{
					return nBands_;
				}

				//- Lower and upper limit of band i
				inline const Vector2D<scalar>& bands(const label bandi) const
				{
					return iBands_[bandi];
				}

				//- Correct rays
				FoamRadiationModels_EXPORT void correct
				(
					volScalarField& a,
					PtrList<volScalarField>& aLambda
				) const;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace absorptionEmissionModels
	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wideBand_Header
