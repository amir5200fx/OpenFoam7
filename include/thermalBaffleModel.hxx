#pragma once
#ifndef _thermalBaffleModel_Header
#define _thermalBaffleModel_Header

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
	tnbLib::regionModels::thermalBaffleModels::thermalBaffleModel

Description

SourceFiles
	thermalBaffleModel.C

\*---------------------------------------------------------------------------*/

#include <runTimeSelectionTables.hxx>
#include <scalarIOField.hxx>
#include <autoPtr.hxx>
#include <volFieldsFwd.hxx>
#include <solidThermo.hxx>
#include <regionModel1D.hxx>
#include <radiationModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace thermalBaffleModels
		{

			/*---------------------------------------------------------------------------*\
								  Class thermalBaffleModel Declaration
			\*---------------------------------------------------------------------------*/

			class thermalBaffleModel
				:
				public regionModel1D
			{
				// Private Member Functions

					//- Initialize thermal Baffle
				FoamLagrangian_EXPORT void init();


			protected:

				// Protected Data

					//- Baffle physical thickness
				scalarField thickness_;

				//- Baffle mesh thickness
				dimensionedScalar delta_;

				//- Is it one dimension
				bool oneD_;

				//- Is thickness constant
				bool constantThickness_;


				// Protected Member Functions

					//- Read control parameters from IO dictionary
				FoamLagrangian_EXPORT virtual bool read();

				//- Read control parameters from dictionary
				FoamLagrangian_EXPORT virtual bool read(const dictionary&);


			public:

				//- Runtime type information
				//TypeName("thermalBaffleModel");
				static const char* typeName_() { return "thermalBaffleModel"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Declare runtime constructor selection tables

				/*declareRunTimeSelectionTable
				(
					autoPtr,
					thermalBaffleModel,
					mesh,
					(
						const word& modelType,
						const fvMesh& mesh
						),
						(modelType, mesh)
				);*/

				typedef autoPtr<thermalBaffleModel> (*meshConstructorPtr)(const word& modelType, const fvMesh& mesh);
				typedef HashTable<meshConstructorPtr, word, string::hash> meshConstructorTable;
				static FoamLagrangian_EXPORT meshConstructorTable* meshConstructorTablePtr_;
				static FoamLagrangian_EXPORT void constructmeshConstructorTables();
				static FoamLagrangian_EXPORT void destroymeshConstructorTables();

				template <class thermalBaffleModelType>
				class addmeshConstructorToTable
				{
				public:
					static autoPtr<thermalBaffleModel> New(const word& modelType, const fvMesh& mesh)
					{
						return autoPtr<thermalBaffleModel>(new thermalBaffleModelType(modelType, mesh));
					}

					addmeshConstructorToTable(const word& lookup = thermalBaffleModelType::typeName)
					{
						constructmeshConstructorTables();
						if (!meshConstructorTablePtr_->insert(lookup, New))
						{
							std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
								"thermalBaffleModel" << std::endl;
							error::safePrintStack(std::cerr);
						}
					}

					~addmeshConstructorToTable() { destroymeshConstructorTables(); }
				};

				template <class thermalBaffleModelType>
				class addRemovablemeshConstructorToTable
				{
					const word& lookup_;
				public:
					static autoPtr<thermalBaffleModel> New(const word& modelType, const fvMesh& mesh)
					{
						return autoPtr<thermalBaffleModel>(new thermalBaffleModelType(modelType, mesh));
					}

					addRemovablemeshConstructorToTable(const word& lookup = thermalBaffleModelType::typeName) : lookup_(
						lookup)
					{
						constructmeshConstructorTables();
						meshConstructorTablePtr_->set(lookup, New);
					}

					~addRemovablemeshConstructorToTable()
					{
						if (meshConstructorTablePtr_) { meshConstructorTablePtr_->erase(lookup_); }
					}
				};

				/*declareRunTimeSelectionTable
				(
					autoPtr,
					thermalBaffleModel,
					dictionary,
					(
						const word& modelType,
						const fvMesh& mesh,
						const dictionary& dict
						),
						(modelType, mesh, dict)
				);*/

				typedef autoPtr<thermalBaffleModel> (*dictionaryConstructorPtr)(
					const word& modelType, const fvMesh& mesh, const dictionary& dict);
				typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
				static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
				static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
				static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

				template <class thermalBaffleModelType>
				class adddictionaryConstructorToTable
				{
				public:
					static autoPtr<thermalBaffleModel> New(const word& modelType, const fvMesh& mesh,
					                                       const dictionary& dict)
					{
						return autoPtr<thermalBaffleModel>(new thermalBaffleModelType(modelType, mesh, dict));
					}

					adddictionaryConstructorToTable(const word& lookup = thermalBaffleModelType::typeName)
					{
						constructdictionaryConstructorTables();
						if (!dictionaryConstructorTablePtr_->insert(lookup, New))
						{
							std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
								"thermalBaffleModel" << std::endl;
							error::safePrintStack(std::cerr);
						}
					}

					~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
				};

				template <class thermalBaffleModelType>
				class addRemovabledictionaryConstructorToTable
				{
					const word& lookup_;
				public:
					static autoPtr<thermalBaffleModel> New(const word& modelType, const fvMesh& mesh,
					                                       const dictionary& dict)
					{
						return autoPtr<thermalBaffleModel>(new thermalBaffleModelType(modelType, mesh, dict));
					}

					addRemovabledictionaryConstructorToTable(
						const word& lookup = thermalBaffleModelType::typeName) : lookup_(lookup)
					{
						constructdictionaryConstructorTables();
						dictionaryConstructorTablePtr_->set(lookup, New);
					}

					~addRemovabledictionaryConstructorToTable()
					{
						if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
					}
				};


				// Constructors

					//- Construct null from mesh
				FoamLagrangian_EXPORT thermalBaffleModel(const fvMesh& mesh);

				//- Construct from type name and mesh
				FoamLagrangian_EXPORT thermalBaffleModel(const word& modelType, const fvMesh& mesh);

				//- Construct from type name and mesh and dict
				FoamLagrangian_EXPORT thermalBaffleModel
				(
					const word& modelType,
					const fvMesh& mesh,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT thermalBaffleModel(const thermalBaffleModel&) = delete;


				// Selectors

					//- Return a reference to the selected model
				static FoamLagrangian_EXPORT autoPtr<thermalBaffleModel> New(const fvMesh& mesh);

				//- Return a reference to the selected model using dictionary
				static FoamLagrangian_EXPORT autoPtr<thermalBaffleModel> New
				(
					const fvMesh& mesh,
					const dictionary& dict
				);


				//- Destructor
				FoamLagrangian_EXPORT virtual ~thermalBaffleModel();


				// Member Functions

					// Access

						//- Return solid thermo
				FoamLagrangian_EXPORT virtual const solidThermo& thermo() const = 0;

				//- Return thickness
				const scalarField& thickness() const
				{
					return thickness_;
				}

				//- Return geometrical thickness
				const dimensionedScalar& delta() const
				{
					return delta_;
				}

				//- Return if region is one dimensional
				bool oneD() const
				{
					return oneD_;
				}

				//- Return if region has constant thickness
				bool constantThickness() const
				{
					return constantThickness_;
				}


				// Fields

					//- Return density [kg/m^3]
				FoamLagrangian_EXPORT virtual const volScalarField& rho() const = 0;

				//- Return const temperature [K]
				FoamLagrangian_EXPORT virtual const volScalarField& T() const = 0;

				//- Return specific heat capacity [J/kg/K]
				FoamLagrangian_EXPORT virtual const tmp<volScalarField> Cp() const = 0;

				//- Return the region absorptivity [1/m]
				FoamLagrangian_EXPORT virtual const volScalarField& kappaRad() const = 0;

				//- Return the region thermal conductivity [W/m/k]
				FoamLagrangian_EXPORT virtual const volScalarField& kappa() const = 0;


				// Evolution

					//- Pre-evolve region
				FoamLagrangian_EXPORT virtual void preEvolveRegion();


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const thermalBaffleModel&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace thermalBaffleModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_thermalBaffleModel_Header
