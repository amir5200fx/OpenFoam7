#pragma once
#ifndef _heheuPsiThermo_Header
#define _heheuPsiThermo_Header

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
	tnbLib::heheuReactionThermo

Description
	tnbLib::heheuReactionThermo

SourceFiles
	heheuReactionThermo.C

\*---------------------------------------------------------------------------*/

#include <heThermo.hxx>
#include <typeInfo.hxx>  // added by amir

#ifdef FoamThermophysicalModels_EXPORT_DEFINE
#define FoamheheuPsiThermo_EXPORT __declspec(dllexport)
#else
#ifdef FoamheheuPsiThermo_EXPORT_DEFINE
#define FoamheheuPsiThermo_EXPORT __declspec(dllexport)
#else
#define FoamheheuPsiThermo_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class heheuPsiThermo Declaration
	\*---------------------------------------------------------------------------*/

	template<class BasicPsiThermo, class MixtureType>
	class heheuPsiThermo
		:
		public heThermo<BasicPsiThermo, MixtureType>
	{
		// Private Member Functions

		volScalarField Tu_;
		volScalarField heu_;


		// Private Member Functions

		void calculate();

		//- Construct as copy (not implemented)
		heheuPsiThermo
		(
			const heheuPsiThermo<BasicPsiThermo, MixtureType>&
		);


	public:

		//- Runtime type information
		//TypeName("heheuPsiThermo");
		static const char* typeName_() { return "heheuPsiThermo"; }
		static FoamheheuPsiThermo_EXPORT const ::tnbLib::word typeName;
		static FoamheheuPsiThermo_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh and phase name
		heheuPsiThermo
		(
			const fvMesh&,
			const word& phaseName
		);


		//- Destructor
		virtual ~heheuPsiThermo();


		// Member Functions

			//- Update properties
		virtual void correct();

		// Access to thermodynamic state variables.

			//- Unburnt gas enthalpy [J/kg]
			//  Non-const access allowed for transport equations
		virtual volScalarField& heu()
		{
			return heu_;
		}

		//- Unburnt gas enthalpy [J/kg]
		virtual const volScalarField& heu() const
		{
			return heu_;
		}

		//- Unburnt gas temperature [K]
		virtual const volScalarField& Tu() const
		{
			return Tu_;
		}


		// Fields derived from thermodynamic state variables

			//- Unburnt gas enthalpy for cell-set [J/kg]
		virtual tmp<scalarField> heu
		(
			const scalarField& p,
			const scalarField& T,
			const labelList& cells
		) const;

		//- Unburnt gas enthalpy for patch [J/kg]
		virtual tmp<scalarField> heu
		(
			const scalarField& p,
			const scalarField& T,
			const label patchi
		) const;


		//- Burnt gas temperature [K]
		virtual tmp<volScalarField> Tb() const;

		//- Unburnt gas compressibility [s^2/m^2]
		virtual tmp<volScalarField> psiu() const;

		//- Burnt gas compressibility [s^2/m^2]
		virtual tmp<volScalarField> psib() const;


		// Access to transport variables

			//- Dynamic viscosity of unburnt gas [kg/m/s]
		virtual tmp<volScalarField> muu() const;

		//- Dynamic viscosity of burnt gas [kg/m/s]
		virtual tmp<volScalarField> mub() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#include <heheuPsiThermoI.hxx>

//#ifdef NoRepository
//#include <heheuPsiThermo.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_heheuPsiThermo_Header
