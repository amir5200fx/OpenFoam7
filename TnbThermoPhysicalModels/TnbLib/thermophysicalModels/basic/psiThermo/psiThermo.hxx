#pragma once
#ifndef _psiThermo_Header
#define _psiThermo_Header

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
	tnbLib::psiThermo

Description
	Basic thermodynamic properties based on compressibility

SourceFiles
	psiThermo.C

\*---------------------------------------------------------------------------*/

#include <fluidThermo.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class psiThermo Declaration
	\*---------------------------------------------------------------------------*/

	class psiThermo
		:
		public fluidThermo
	{

	protected:

		// Protected data

			//- Compressibility [s^2/m^2]
		volScalarField psi_;

		//- Dynamic viscosity [kg/m/s]
		volScalarField mu_;


		// Protected Member Functions

		//- Construct as copy (not implemented)
		FoamThermophysicalModels_EXPORT psiThermo(const psiThermo&);


	public:

		//- Runtime type information
		//TypeName("psiThermo");
		static const char* typeName_() { return "psiThermo"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		//- Declare run-time constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			psiThermo,
			fvMesh,
			(const fvMesh& mesh, const word& phaseName),
			(mesh, phaseName)
		);*/
		
		typedef autoPtr<psiThermo> (*fvMeshConstructorPtr)(const fvMesh& mesh, const word& phaseName);
		typedef HashTable<fvMeshConstructorPtr, word, string::hash> fvMeshConstructorTable;
		static FoamThermophysicalModels_EXPORT fvMeshConstructorTable* fvMeshConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructfvMeshConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroyfvMeshConstructorTables();

		template <class psiThermoType>
		class addfvMeshConstructorToTable
		{
		public:
			static autoPtr<psiThermo> New(const fvMesh& mesh, const word& phaseName)
			{
				return autoPtr<psiThermo>(new psiThermoType(mesh, phaseName));
			}

			addfvMeshConstructorToTable(const word& lookup = psiThermoType::typeName)
			{
				constructfvMeshConstructorTables();
				if (!fvMeshConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "psiThermo" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addfvMeshConstructorToTable() { destroyfvMeshConstructorTables(); }
		};

		template <class psiThermoType>
		class addRemovablefvMeshConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<psiThermo> New(const fvMesh& mesh, const word& phaseName)
			{
				return autoPtr<psiThermo>(new psiThermoType(mesh, phaseName));
			}

			addRemovablefvMeshConstructorToTable(const word& lookup = psiThermoType::typeName) : lookup_(lookup)
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
		FoamThermophysicalModels_EXPORT psiThermo
		(
			const fvMesh&,
			const word& phaseName
		);


		//- Selector
		static FoamThermophysicalModels_EXPORT autoPtr<psiThermo> New
		(
			const fvMesh& mesh,
			const word& phaseName = word::null
		);


		//- Destructor
		FoamThermophysicalModels_EXPORT virtual ~psiThermo();


		// Member Functions

			// Fields derived from thermodynamic state variables

				//- Add the given density correction to the density field.
				//  Used to update the density field following pressure solution.
				//  For psiThermo does nothing.
		FoamThermophysicalModels_EXPORT virtual void correctRho(const volScalarField& deltaRho);

		//- Density [kg/m^3] - uses current value of pressure
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField> rho() const;

		//- Density for patch [kg/m^3]
		FoamThermophysicalModels_EXPORT virtual tmp<scalarField> rho(const label patchi) const;

		//- Compressibility [s^2/m^2]
		FoamThermophysicalModels_EXPORT virtual const volScalarField& psi() const;


		// Access to transport state variables

			//- Dynamic viscosity of mixture [kg/m/s]
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField> mu() const;

		//- Dynamic viscosity of mixture for patch [kg/m/s]
		FoamThermophysicalModels_EXPORT virtual tmp<scalarField> mu(const label patchi) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_psiThermo_Header
