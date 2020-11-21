#pragma once
#ifndef _solidThermo_Header
#define _solidThermo_Header

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
	tnbLib::solidThermo

Description
	Fundamental solid thermodynamic properties

SourceFiles
	solidThermo.C

\*---------------------------------------------------------------------------*/

#include <basicThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class solidThermo Declaration
	\*---------------------------------------------------------------------------*/

	class solidThermo
		:
		public basicThermo
	{

	protected:

		// Protected data

			//- Density field [kg/m^3]
			//  Named 'rhoThermo' to avoid (potential) conflict with solver density
		volScalarField rho_;


	public:

		//- Runtime type information
		//TypeName("solidThermo");
		static const char* typeName_() { return "solidThermo"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Declare run-time constructor selection tables
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			solidThermo,
			fvMesh,
			(const fvMesh& mesh, const word& phaseName),
			(mesh, phaseName)
		);*/
		
		typedef autoPtr<solidThermo> (*fvMeshConstructorPtr)(const fvMesh& mesh, const word& phaseName);
		typedef HashTable<fvMeshConstructorPtr, word, string::hash> fvMeshConstructorTable;
		static FoamThermophysicalModels_EXPORT fvMeshConstructorTable* fvMeshConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructfvMeshConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroyfvMeshConstructorTables();

		template <class solidThermoType>
		class addfvMeshConstructorToTable
		{
		public:
			static autoPtr<solidThermo> New(const fvMesh& mesh, const word& phaseName)
			{
				return autoPtr<solidThermo>(new solidThermoType(mesh, phaseName));
			}

			addfvMeshConstructorToTable(const word& lookup = solidThermoType::typeName)
			{
				constructfvMeshConstructorTables();
				if (!fvMeshConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "solidThermo" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addfvMeshConstructorToTable() { destroyfvMeshConstructorTables(); }
		};

		template <class solidThermoType>
		class addRemovablefvMeshConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<solidThermo> New(const fvMesh& mesh, const word& phaseName)
			{
				return autoPtr<solidThermo>(new solidThermoType(mesh, phaseName));
			}

			addRemovablefvMeshConstructorToTable(const word& lookup = solidThermoType::typeName) : lookup_(lookup)
			{
				constructfvMeshConstructorTables();
				fvMeshConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablefvMeshConstructorToTable()
			{
				if (fvMeshConstructorTablePtr_) { fvMeshConstructorTablePtr_->erase(lookup_); }
			}
		};;

		// Declare run-time constructor selection tables
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			solidThermo,
			dictionary,
			(const fvMesh& mesh, const dictionary& dict, const word& phaseName),
			(mesh, dict, phaseName)
		);*/

		typedef autoPtr<solidThermo> (*dictionaryConstructorPtr)(const fvMesh& mesh, const dictionary& dict,
		                                                         const word& phaseName);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamThermophysicalModels_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructdictionaryConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroydictionaryConstructorTables();

		template <class solidThermoType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<solidThermo> New(const fvMesh& mesh, const dictionary& dict, const word& phaseName)
			{
				return autoPtr<solidThermo>(new solidThermoType(mesh, dict, phaseName));
			}

			adddictionaryConstructorToTable(const word& lookup = solidThermoType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "solidThermo" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class solidThermoType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<solidThermo> New(const fvMesh& mesh, const dictionary& dict, const word& phaseName)
			{
				return autoPtr<solidThermo>(new solidThermoType(mesh, dict, phaseName));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = solidThermoType::typeName) : lookup_(lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct from mesh and phase name
		FoamThermophysicalModels_EXPORT solidThermo
		(
			const fvMesh&,
			const word& phaseName
		);

		//- Construct from mesh, dictionary and phase name
		FoamThermophysicalModels_EXPORT solidThermo
		(
			const fvMesh&,
			const dictionary& dict,
			const word& phaseName
		);

		//- Return a pointer to a new solidThermo created from
		//  the solidThermophysicalProperties dictionary
		static FoamThermophysicalModels_EXPORT autoPtr<solidThermo> New
		(
			const fvMesh&,
			const word& phaseName = word::null
		);

		//- Return a pointer to a new solidThermo created from
		//  local dictionary
		static FoamThermophysicalModels_EXPORT autoPtr<solidThermo> New
		(
			const fvMesh&,
			const dictionary&,
			const word& phaseName = word::null
		);


		//- Destructor
		FoamThermophysicalModels_EXPORT virtual ~solidThermo();


		// Member Functions

			// Fields derived from thermodynamic state variables

				//- Density [kg/m^3]
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField> rho() const;

		//- Density for patch [kg/m^3]
		FoamThermophysicalModels_EXPORT virtual tmp<scalarField> rho(const label patchi) const;

		//- Return non-const access to the local density field [kg/m^3]
		FoamThermophysicalModels_EXPORT virtual volScalarField& rho();

		//- Thermal conductivity [W/m/K]
		FoamThermophysicalModels_EXPORT virtual tmp<volVectorField> Kappa() const = 0;

		//- Return true if thermal conductivity is isotropic
		FoamThermophysicalModels_EXPORT virtual bool isotropic() const = 0;


		// Per patch calculation

			//- Anisotropic thermal conductivity [W/m/K]
		FoamThermophysicalModels_EXPORT virtual tmp<vectorField> Kappa
		(
			const label patchi
		) const = 0;


		// I-O

			//- Read thermophysicalProperties dictionary
		FoamThermophysicalModels_EXPORT virtual bool read();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_solidThermo_Header
