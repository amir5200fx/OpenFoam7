#pragma once
#ifndef _pyrolysisModel_Header
#define _pyrolysisModel_Header

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
	tnbLib::regionModels::pyrolysisModels::pyrolysisModel

Description
	Base class for pyrolysis models

SourceFiles
	pyrolysisModelI.H
	pyrolysisModel.C

\*---------------------------------------------------------------------------*/

#include <runTimeSelectionTables.hxx>
#include <volFieldsFwd.hxx>
#include <regionModel1D.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class fvMesh;
	class Time;

	namespace regionModels
	{
		namespace pyrolysisModels
		{

			/*---------------------------------------------------------------------------*\
								  Class pyrolysisModel Declaration
			\*---------------------------------------------------------------------------*/

			class pyrolysisModel
				:
				public regionModel1D
			{
				// Private Member Functions

					//- Construct fields
				FoamLagrangian_EXPORT void constructMeshObjects();

				//- Read pyrolysis controls
				FoamLagrangian_EXPORT void readPyrolysisControls();


			protected:

				// Protected Member Functions

					//- Read control parameters
				FoamLagrangian_EXPORT virtual bool read();

				//- Read control parameters from dictionary
				FoamLagrangian_EXPORT virtual bool read(const dictionary& dict);


			public:

				//- Runtime type information
				//TypeName("pyrolysisModel");
				static const char* typeName_() { return "pyrolysisModel"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Declare runtime constructor selection table

				/*declareRunTimeSelectionTable
				(
					autoPtr,
					pyrolysisModel,
					mesh,
					(
						const word& modelType,
						const fvMesh& mesh,
						const word& regionType
						),
						(modelType, mesh, regionType)
				);*/

				typedef autoPtr<pyrolysisModel> (*meshConstructorPtr)(const word& modelType, const fvMesh& mesh,
				                                                      const word& regionType);
				typedef HashTable<meshConstructorPtr, word, string::hash> meshConstructorTable;
				static FoamLagrangian_EXPORT meshConstructorTable* meshConstructorTablePtr_;
				static FoamLagrangian_EXPORT void constructmeshConstructorTables();
				static FoamLagrangian_EXPORT void destroymeshConstructorTables();

				template <class pyrolysisModelType>
				class addmeshConstructorToTable
				{
				public:
					static autoPtr<pyrolysisModel> New(const word& modelType, const fvMesh& mesh,
					                                   const word& regionType)
					{
						return autoPtr<pyrolysisModel>(new pyrolysisModelType(modelType, mesh, regionType));
					}

					addmeshConstructorToTable(const word& lookup = pyrolysisModelType::typeName)
					{
						constructmeshConstructorTables();
						if (!meshConstructorTablePtr_->insert(lookup, New))
						{
							std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
								"pyrolysisModel" << std::endl;
							error::safePrintStack(std::cerr);
						}
					}

					~addmeshConstructorToTable() { destroymeshConstructorTables(); }
				};

				template <class pyrolysisModelType>
				class addRemovablemeshConstructorToTable
				{
					const word& lookup_;
				public:
					static autoPtr<pyrolysisModel> New(const word& modelType, const fvMesh& mesh,
					                                   const word& regionType)
					{
						return autoPtr<pyrolysisModel>(new pyrolysisModelType(modelType, mesh, regionType));
					}

					addRemovablemeshConstructorToTable(const word& lookup = pyrolysisModelType::typeName) : lookup_(
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
					pyrolysisModel,
					dictionary,
					(
						const word& modelType,
						const fvMesh& mesh,
						const dictionary& dict,
						const word& regionType
						),
						(modelType, mesh, dict, regionType)
				);*/

				typedef autoPtr<pyrolysisModel> (*dictionaryConstructorPtr)(
					const word& modelType, const fvMesh& mesh, const dictionary& dict, const word& regionType);
				typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
				static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
				static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
				static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

				template <class pyrolysisModelType>
				class adddictionaryConstructorToTable
				{
				public:
					static autoPtr<pyrolysisModel> New(const word& modelType, const fvMesh& mesh,
					                                   const dictionary& dict, const word& regionType)
					{
						return autoPtr<pyrolysisModel>(new pyrolysisModelType(modelType, mesh, dict, regionType));
					}

					adddictionaryConstructorToTable(const word& lookup = pyrolysisModelType::typeName)
					{
						constructdictionaryConstructorTables();
						if (!dictionaryConstructorTablePtr_->insert(lookup, New))
						{
							std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
								"pyrolysisModel" << std::endl;
							error::safePrintStack(std::cerr);
						}
					}

					~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
				};

				template <class pyrolysisModelType>
				class addRemovabledictionaryConstructorToTable
				{
					const word& lookup_;
				public:
					static autoPtr<pyrolysisModel> New(const word& modelType, const fvMesh& mesh,
					                                   const dictionary& dict, const word& regionType)
					{
						return autoPtr<pyrolysisModel>(new pyrolysisModelType(modelType, mesh, dict, regionType));
					}

					addRemovabledictionaryConstructorToTable(
						const word& lookup = pyrolysisModelType::typeName) : lookup_(lookup)
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
				FoamLagrangian_EXPORT pyrolysisModel
				(
					const fvMesh& mesh,
					const word& regionType
				);

				//- Construct from type name and mesh
				FoamLagrangian_EXPORT pyrolysisModel
				(
					const word& modelType,
					const fvMesh& mesh,
					const word& regionType
				);

				//- Construct from type name and mesh and dictionary
				FoamLagrangian_EXPORT pyrolysisModel
				(
					const word& modelType,
					const fvMesh& mesh,
					const dictionary& dict,
					const word& regionType
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT pyrolysisModel(const pyrolysisModel&) = delete;

				//- Return clone
				autoPtr<pyrolysisModel> clone() const
				{
					NotImplemented;
					return autoPtr<pyrolysisModel>(nullptr);
				}


				// Selectors

					//- Return a reference to the selected pyrolysis model
				static FoamLagrangian_EXPORT autoPtr<pyrolysisModel> New
				(
					const fvMesh& mesh,
					const word& regionType = "pyrolysis"
				);

				//- Return a reference to a named selected pyrolysis model
				static FoamLagrangian_EXPORT autoPtr<pyrolysisModel> New
				(
					const fvMesh& mesh,
					const dictionary& dict,
					const word& regionType = "pyrolysis"
				);


				//- Destructor
				FoamLagrangian_EXPORT virtual ~pyrolysisModel();


				// Member Functions

					// Access

						// Fields

							//- Return density [kg/m^3]
				FoamLagrangian_EXPORT virtual const volScalarField& rho() const = 0;

				//- Return const temperature [K]
				FoamLagrangian_EXPORT virtual const volScalarField& T() const = 0;

				//- Return specific heat capacity [J/kg/K]
				FoamLagrangian_EXPORT virtual const tmp<volScalarField> Cp() const = 0;

				//- Return the region absorptivity [1/m]
				FoamLagrangian_EXPORT virtual tmp<volScalarField> kappaRad() const = 0;

				//- Return the region thermal conductivity [W/m/k]
				FoamLagrangian_EXPORT virtual tmp<volScalarField> kappa() const = 0;

				//- Return the total gas mass flux to primary region [kg/m^2/s]
				FoamLagrangian_EXPORT virtual const surfaceScalarField& phiGas() const = 0;


				// Sources

					//- External hook to add mass to the primary region
				FoamLagrangian_EXPORT virtual scalar addMassSources
				(
					const label patchi,
					const label facei
				);


				// Helper function

					//- Mean diffusion number of the solid region
				FoamLagrangian_EXPORT virtual scalar solidRegionDiffNo() const;

				//- Return max diffusivity allowed in the solid
				FoamLagrangian_EXPORT virtual scalar maxDiff() const;


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const pyrolysisModel&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace pyrolysisModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <pyrolysisModelI.hxx>  // added by amir

#endif // !_pyrolysisModel_Header
