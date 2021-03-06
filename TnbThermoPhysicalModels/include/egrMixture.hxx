#pragma once
#ifndef _egrMixture_Header
#define _egrMixture_Header

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
	tnbLib::egrMixture

Description
	tnbLib::egrMixture

SourceFiles
	egrMixture.C

\*---------------------------------------------------------------------------*/

#include <basicCombustionMixture.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class egrMixture Declaration
	\*---------------------------------------------------------------------------*/

	template<class ThermoType>
	class egrMixture
		:
		public basicCombustionMixture
	{
		// Private Data

		static const int nSpecies_ = 3;
		static const char* specieNames_[3];

		dimensionedScalar stoicRatio_;

		ThermoType fuel_;
		ThermoType oxidant_;
		ThermoType products_;

		mutable ThermoType mixture_;

		//- Mixture fraction
		volScalarField& ft_;

		//- Regress variable
		volScalarField& b_;

		//- Residual gases
		volScalarField& egr_;

		//- Construct as copy (not implemented)
		egrMixture(const egrMixture<ThermoType>&);


	public:

		//- The type of thermodynamics this mixture is instantiated for
		typedef ThermoType thermoType;


		// Constructors

			//- Construct from dictionary, mesh and phaseName
		egrMixture(const dictionary&, const fvMesh&, const word&);


		//- Destructor
		virtual ~egrMixture()
		{}


		// Member Functions

			//- Return the instantiated type name
		static word typeName()
		{
			return "egrMixture<" + ThermoType::typeName() + '>';
		}

		const dimensionedScalar& stoicRatio() const
		{
			return stoicRatio_;
		}

		const ThermoType& mixture
		(
			const scalar,
			const scalar,
			const scalar
		) const;

		const ThermoType& cellMixture(const label celli) const
		{
			return mixture(ft_[celli], b_[celli], egr_[celli]);
		}

		const ThermoType& patchFaceMixture
		(
			const label patchi,
			const label facei
		) const
		{
			return mixture
			(
				ft_.boundaryField()[patchi][facei],
				b_.boundaryField()[patchi][facei],
				egr_.boundaryField()[patchi][facei]
			);
		}

		const ThermoType& cellReactants(const label celli) const
		{
			return mixture(ft_[celli], 1, egr_[celli]);
		}

		const ThermoType& patchFaceReactants
		(
			const label patchi,
			const label facei
		) const
		{
			return mixture
			(
				ft_.boundaryField()[patchi][facei],
				1,
				egr_.boundaryField()[patchi][facei]
			);
		}

		const ThermoType& cellProducts(const label celli) const
		{
			return mixture(ft_[celli], 0, 0);
		}

		const ThermoType& patchFaceProducts
		(
			const label patchi,
			const label facei
		) const
		{
			return mixture
			(
				ft_.boundaryField()[patchi][facei],
				0,
				0
			);
		}

		//- Read dictionary
		void read(const dictionary&);

		//- Return thermo based on index
		const ThermoType& getLocalThermo(const label speciei) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#include <egrMixtureI.hxx>

//#ifdef NoRepository
//#include <egrMixture.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_egrMixture_Header
