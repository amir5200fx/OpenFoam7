#pragma once
#ifndef _fluidThermo_Header
#define _fluidThermo_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::fluidThermo

Description
	Fundamental fluid thermodynamic properties

SourceFiles
	fluidThermo.C

\*---------------------------------------------------------------------------*/

#include <basicThermo.hxx>
#include <compressibleTransportModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class fluidThermo Declaration
	\*---------------------------------------------------------------------------*/

	class fluidThermo
		:
		public basicThermo,
		public compressibleTransportModel
	{

	public:

		//- Runtime type information
		//TypeName("fluidThermo");
		static const char* typeName_() { return "fluidThermo"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		//- Declare run-time constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			fluidThermo,
			fvMesh,
			(const fvMesh& mesh, const word& phaseName),
			(mesh, phaseName)
		);*/
		
		typedef autoPtr<fluidThermo> (*fvMeshConstructorPtr)(const fvMesh& mesh, const word& phaseName);
		typedef HashTable<fvMeshConstructorPtr, word, string::hash> fvMeshConstructorTable;
		static FoamThermophysicalModels_EXPORT fvMeshConstructorTable* fvMeshConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructfvMeshConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroyfvMeshConstructorTables();

		template <class fluidThermoType>
		class addfvMeshConstructorToTable
		{
		public:
			static autoPtr<fluidThermo> New(const fvMesh& mesh, const word& phaseName)
			{
				return autoPtr<fluidThermo>(new fluidThermoType(mesh, phaseName));
			}

			addfvMeshConstructorToTable(const word& lookup = fluidThermoType::typeName)
			{
				constructfvMeshConstructorTables();
				if (!fvMeshConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "fluidThermo" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addfvMeshConstructorToTable() { destroyfvMeshConstructorTables(); }
		};

		template <class fluidThermoType>
		class addRemovablefvMeshConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<fluidThermo> New(const fvMesh& mesh, const word& phaseName)
			{
				return autoPtr<fluidThermo>(new fluidThermoType(mesh, phaseName));
			}

			addRemovablefvMeshConstructorToTable(const word& lookup = fluidThermoType::typeName) : lookup_(lookup)
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
		FoamThermophysicalModels_EXPORT fluidThermo
		(
			const fvMesh&,
			const word& phaseName
		);

		//- Construct from mesh and phase name
		FoamThermophysicalModels_EXPORT fluidThermo
		(
			const fvMesh&,
			const dictionary&,
			const word& phaseName
		);


		//- Selector
		static FoamThermophysicalModels_EXPORT autoPtr<fluidThermo> New
		(
			const fvMesh&,
			const word& phaseName = word::null
		);


		//- Destructor
		FoamThermophysicalModels_EXPORT virtual ~fluidThermo();


		// Member Functions

			// Access to thermodynamic state variables

				//- Add the given density correction to the density field.
				//  Used to update the density field following pressure solution
		FoamThermophysicalModels_EXPORT virtual void correctRho(const volScalarField& deltaRho) = 0;

		//- Compressibility [s^2/m^2]
		FoamThermophysicalModels_EXPORT virtual const volScalarField& psi() const = 0;


		// Access to transport state variables

			//- Dynamic viscosity of mixture [kg/m/s]
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField> mu() const = 0;

		//- Dynamic viscosity of mixture for patch [kg/m/s]
		FoamThermophysicalModels_EXPORT virtual tmp<scalarField> mu(const label patchi) const = 0;

		//- Kinematic viscosity of mixture [m^2/s]
		FoamThermophysicalModels_EXPORT virtual tmp<volScalarField> nu() const;

		//- Kinematic viscosity of mixture for patch [m^2/s]
		FoamThermophysicalModels_EXPORT virtual tmp<scalarField> nu(const label patchi) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fluidThermo_Header
