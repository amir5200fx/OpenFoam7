#pragma once
#ifndef _filmTurbulenceModel_Header
#define _filmTurbulenceModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::regionModels::surfaceFilmModels::filmTurbulenceModel

Description
	Base class for film turbulence models

SourceFiles
	filmTurbulenceModel.C
	filmTurbulenceModelNew.C

\*---------------------------------------------------------------------------*/

#include <filmSubModelBase.hxx>
#include <runTimeSelectionTables.hxx>
#include <fvMatricesFwd.hxx>
#include <volFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
								   Class filmTurbulenceModel Declaration
			\*---------------------------------------------------------------------------*/

			class filmTurbulenceModel
				:
				public filmSubModelBase
			{
			public:

				//- Runtime type information
				//TypeName("filmTurbulenceModel");
				static const char* typeName_() { return "filmTurbulenceModel"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Declare runtime constructor selection table

				/*declareRunTimeSelectionTable
				(
					autoPtr,
					filmTurbulenceModel,
					dictionary,
					(
						surfaceFilmRegionModel& film,
						const dictionary& dict
						),
						(film, dict)
				);*/

				typedef autoPtr<filmTurbulenceModel> (*dictionaryConstructorPtr)(
					surfaceFilmRegionModel& film, const dictionary& dict);
				typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
				static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
				static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
				static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

				template <class filmTurbulenceModelType>
				class adddictionaryConstructorToTable
				{
				public:
					static autoPtr<filmTurbulenceModel> New(surfaceFilmRegionModel& film, const dictionary& dict)
					{
						return autoPtr<filmTurbulenceModel>(new filmTurbulenceModelType(film, dict));
					}

					adddictionaryConstructorToTable(const word& lookup = filmTurbulenceModelType::typeName)
					{
						constructdictionaryConstructorTables();
						if (!dictionaryConstructorTablePtr_->insert(lookup, New))
						{
							std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
								"filmTurbulenceModel" << std::endl;
							error::safePrintStack(std::cerr);
						}
					}

					~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
				};

				template <class filmTurbulenceModelType>
				class addRemovabledictionaryConstructorToTable
				{
					const word& lookup_;
				public:
					static autoPtr<filmTurbulenceModel> New(surfaceFilmRegionModel& film, const dictionary& dict)
					{
						return autoPtr<filmTurbulenceModel>(new filmTurbulenceModelType(film, dict));
					}

					addRemovabledictionaryConstructorToTable(
						const word& lookup = filmTurbulenceModelType::typeName) : lookup_(lookup)
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

					//- Construct null
				FoamLagrangian_EXPORT filmTurbulenceModel(surfaceFilmRegionModel& film);

				//- Construct from type name, dictionary and surface film model
				FoamLagrangian_EXPORT filmTurbulenceModel
				(
					const word& modelType,
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT filmTurbulenceModel(const filmTurbulenceModel&) = delete;


				// Selectors

					//- Return a reference to the selected injection model
				static FoamLagrangian_EXPORT autoPtr<filmTurbulenceModel> New
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);


				//- Destructor
				FoamLagrangian_EXPORT virtual ~filmTurbulenceModel();


				// Member Functions

					// Evolution

						//- Return the film surface velocity
				FoamLagrangian_EXPORT virtual tmp<volVectorField> Us() const = 0;

				//- Return the film turbulence viscosity
				FoamLagrangian_EXPORT virtual tmp<volScalarField> mut() const = 0;

				//- Correct/update the model
				FoamLagrangian_EXPORT virtual void correct() = 0;

				//- Return the source for the film momentum equation
				FoamLagrangian_EXPORT virtual tmp<fvVectorMatrix> Su(volVectorField& U) const = 0;


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const filmTurbulenceModel&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_filmTurbulenceModel_Header
