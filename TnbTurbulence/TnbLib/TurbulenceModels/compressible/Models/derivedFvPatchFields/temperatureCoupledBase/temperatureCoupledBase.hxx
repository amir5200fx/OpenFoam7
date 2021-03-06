#pragma once
#ifndef _temperatureCoupledBase_Header
#define _temperatureCoupledBase_Header

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
	tnbLib::temperatureCoupledBase

Description
	Common functions used in temperature coupled boundaries.

	The thermal conductivity \c kappa may be obtained by the following methods:
	  - 'lookup' : lookup volScalarField (or volSymmTensorField) with name
		defined by 'kappa'
	  - 'fluidThermo' : use fluidThermo and default
		compressible::turbulenceModel to calculate kappa
	  - 'solidThermo' : use solidThermo kappa()
	  - 'directionalSolidThermo': uses look up for volSymmTensorField for
		transformed kappa vector. Field name definable in 'alphaAni',
		named 'Anialpha' in solid solver by default

	\par Keywords provided by this class:
	  \table
		Property     | Description                | Required    | Default value
		kappaMethod  | Thermal conductivity method        | yes |
		kappa        | Name of thermal conductivity field | no  | none
		alphaAni     | Name of the non-isotropic alpha    | no  | Anialpha
	  \endtable

Usage
	\verbatim
	nonIsotropicWall
	{
		...
		kappaMethod     directionalSolidThermo;
		kappa           none;
		alphaAni        Anialpha;
		...
	}
	\endverbatim

SourceFiles
	temperatureCoupledBase.C

\*---------------------------------------------------------------------------*/

#include <scalarField.hxx>
#include <NamedEnum.hxx>
#include <fvPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class temperatureCoupledBase Declaration
	\*---------------------------------------------------------------------------*/

	class temperatureCoupledBase
	{
	public:

		// Public enumerations

			//- Type of supplied Kappa
		enum KMethodType
		{
			mtFluidThermo,
			mtSolidThermo,
			mtDirectionalSolidThermo,
			mtLookup
		};


	protected:

		// Protected data

		static FoamTurbulence_EXPORT const NamedEnum<KMethodType, 4> KMethodTypeNames_;

		//- Underlying patch
		const fvPatch& patch_;

		//- How to get K
		const KMethodType method_;

		//- Name of thermal conductivity field (if looked up from database)
		const word kappaName_;

		//- Name of the non-Isotropic alpha (default: Anialpha)
		const word alphaAniName_;


	public:

		// Constructors

			//- Construct from patch and K name
		FoamTurbulence_EXPORT temperatureCoupledBase
		(
			const fvPatch& patch,
			const word& calculationMethod,
			const word& kappaName,
			const word& alphaAniName
		);

		//- Construct from patch and dictionary
		FoamTurbulence_EXPORT temperatureCoupledBase
		(
			const fvPatch& patch,
			const dictionary& dict
		);

		//- Construct from patch and temperatureCoupledBase
		FoamTurbulence_EXPORT temperatureCoupledBase
		(
			const fvPatch& patch,
			const temperatureCoupledBase& base
		);


		// Member Functions

			//- Method to obtain K
		word KMethod() const
		{
			return KMethodTypeNames_[method_];
		}

		//- Name of thermal conductivity field
		const word& kappaName() const
		{
			return kappaName_;
		}

		//- Given patch temperature calculate corresponding K field
		FoamTurbulence_EXPORT tmp<scalarField> kappa(const scalarField& Tp) const;

		//- Write
		FoamTurbulence_EXPORT void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_temperatureCoupledBase_Header
