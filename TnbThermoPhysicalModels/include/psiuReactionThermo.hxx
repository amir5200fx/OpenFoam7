#pragma once
#ifndef _psiuReactionThermo_Header
#define _psiuReactionThermo_Header

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
	tnbLib::psiuReactionThermo

Description
	tnbLib::psiuReactionThermo

SourceFiles
	psiuReactionThermo.C
	psiuReactionThermoNew.C

\*---------------------------------------------------------------------------*/

#include <psiReactionThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class psiuReactionThermo Declaration
	\*---------------------------------------------------------------------------*/

	class psiuReactionThermo
		:
		public psiReactionThermo
	{

	protected:

		// Protected Member Functions

		wordList heuBoundaryTypes();
		void heuBoundaryCorrection(volScalarField& heu);


	public:

		//- Runtime type information
		//TypeName("psiuReactionThermo");
		static const char* typeName_() { return "psiuReactionThermo"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			psiuReactionThermo,
			fvMesh,
			(const fvMesh& mesh, const word& phaseName),
			(mesh, phaseName)
		);*/

		typedef autoPtr<psiuReactionThermo> (*fvMeshConstructorPtr)(const fvMesh& mesh, const word& phaseName);
		typedef HashTable<fvMeshConstructorPtr, word, string::hash> fvMeshConstructorTable;
		static FoamThermophysicalModels_EXPORT fvMeshConstructorTable* fvMeshConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructfvMeshConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroyfvMeshConstructorTables();

		template <class psiuReactionThermoType>
		class addfvMeshConstructorToTable
		{
		public:
			static autoPtr<psiuReactionThermo> New(const fvMesh& mesh, const word& phaseName)
			{
				return autoPtr<psiuReactionThermo>(new psiuReactionThermoType(mesh, phaseName));
			}

			addfvMeshConstructorToTable(const word& lookup = psiuReactionThermoType::typeName)
			{
				constructfvMeshConstructorTables();
				if (!fvMeshConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "psiuReactionThermo"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addfvMeshConstructorToTable() { destroyfvMeshConstructorTables(); }
		};

		template <class psiuReactionThermoType>
		class addRemovablefvMeshConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<psiuReactionThermo> New(const fvMesh& mesh, const word& phaseName)
			{
				return autoPtr<psiuReactionThermo>(new psiuReactionThermoType(mesh, phaseName));
			}

			addRemovablefvMeshConstructorToTable(const word& lookup = psiuReactionThermoType::typeName) : lookup_(
				lookup)
			{
				constructfvMeshConstructorTables();
				fvMeshConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablefvMeshConstructorToTable()
			{
				if (fvMeshConstructorTablePtr_) { fvMeshConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct from mesh and phase name
		FoamThermophysicalModels_EXPORT psiuReactionThermo
		(
			const fvMesh&,
			const word& phaseName
		);


		// Selectors

		static FoamThermophysicalModels_EXPORT autoPtr<psiuReactionThermo> New
		(
			const fvMesh&,
			const word& phaseName = word::null
		);


		//- Destructor
		FoamThermophysicalModels_EXPORT virtual ~psiuReactionThermo();


		// Member Functions

			//- Update properties
		FoamThermophysicalModels_EXPORT virtual void correct() = 0;


		// Access to thermodynamic state variables.

			//- Unburnt gas enthalpy [J/kg]
			//  Non-const access allowed for transport equations
		FoamThermophysicalModels_EXPORT virtual volScalarField& heu() = 0;

		//- Unburnt gas enthalpy [J/kg]
		FoamThermophysicalModels_EXPORT virtual const volScalarField& heu() const = 0;


		// Fields derived from thermodynamic state variables

			//- Unburnt gas enthalpy for cell-set [J/kg]
		FoamThermophysicalModels_EXPORT virtual tmp<scalarField> heu
		(
			const scalarField& p,
			const scalarField& T,
			const labelList& cells
		) const = 0;

		//- Unburnt gas enthalpy for patch [J/kg]
		FoamThermophysicalModels_EXPORT virtual tmp<scalarField> heu
		(
			const scalarField& p,
			const scalarField& T,
			const label patchi
		) const = 0;

		//- Unburnt gas temperature [K]
		FoamThermophysicalModels_EXPORT virtual const volScalarField& Tu() const = 0;

		//- Burnt gas temperature [K]
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField> Tb() const = 0;

		//- Unburnt gas density [kg/m^3]
		virtual tmp<volScalarField> rhou() const
		{
			return p_ * psiu();
		}

		//- Burnt gas density [kg/m^3]
		virtual tmp<volScalarField> rhob() const
		{
			return p_ * psib();
		}

		//- Unburnt gas compressibility [s^2/m^2]
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField> psiu() const = 0;

		//- Burnt gas compressibility [s^2/m^2]
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField> psib() const = 0;

		//- Dynamic viscosity of unburnt gas [kg/m/s]
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField> muu() const = 0;

		//- Dynamic viscosity of burnt gas [kg/m/s]
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField> mub() const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_psiuReactionThermo_Header
