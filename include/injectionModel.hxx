#pragma once
#ifndef _injectionModel_Header
#define _injectionModel_Header

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
	tnbLib::regionModels::surfaceFilmModels::injectionModel

Description
	Base class for film injection models, handling mass transfer from the
	film.

SourceFiles
	injectionModel.C
	injectionModelNew.C

\*---------------------------------------------------------------------------*/

#include <filmSubModelBase.hxx>
#include <runTimeSelectionTables.hxx>
#include <scalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
								  Class injectionModel Declaration
			\*---------------------------------------------------------------------------*/

			class injectionModel
				:
				public filmSubModelBase
			{
				// Private Data

					//- Injected mass
				scalar injectedMass_;


			protected:

				// Protected Member Functions

					//- Add to injected mass
				FoamLagrangian_EXPORT void addToInjectedMass(const scalar dMass);

				//- Correct
				FoamLagrangian_EXPORT void correct();


			public:

				//- Runtime type information
				//TypeName("injectionModel");
				static const char* typeName_() { return "injectionModel"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Declare runtime constructor selection table

				/*declareRunTimeSelectionTable
				(
					autoPtr,
					injectionModel,
					dictionary,
					(
						surfaceFilmRegionModel& film,
						const dictionary& dict
						),
						(film, dict)
				);*/

				typedef autoPtr<injectionModel> (*dictionaryConstructorPtr)(
					surfaceFilmRegionModel& film, const dictionary& dict);
				typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
				static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
				static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
				static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

				template <class injectionModelType>
				class adddictionaryConstructorToTable
				{
				public:
					static autoPtr<injectionModel> New(surfaceFilmRegionModel& film, const dictionary& dict)
					{
						return autoPtr<injectionModel>(new injectionModelType(film, dict));
					}

					adddictionaryConstructorToTable(const word& lookup = injectionModelType::typeName)
					{
						constructdictionaryConstructorTables();
						if (!dictionaryConstructorTablePtr_->insert(lookup, New))
						{
							std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
								"injectionModel" << std::endl;
							error::safePrintStack(std::cerr);
						}
					}

					~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
				};

				template <class injectionModelType>
				class addRemovabledictionaryConstructorToTable
				{
					const word& lookup_;
				public:
					static autoPtr<injectionModel> New(surfaceFilmRegionModel& film, const dictionary& dict)
					{
						return autoPtr<injectionModel>(new injectionModelType(film, dict));
					}

					addRemovabledictionaryConstructorToTable(
						const word& lookup = injectionModelType::typeName) : lookup_(lookup)
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
				FoamLagrangian_EXPORT injectionModel(surfaceFilmRegionModel& film);

				//- Construct from type name, dictionary and surface film model
				FoamLagrangian_EXPORT injectionModel
				(
					const word& modelType,
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT injectionModel(const injectionModel&) = delete;


				// Selectors

					//- Return a reference to the selected injection model
				static FoamLagrangian_EXPORT autoPtr<injectionModel> New
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict,
					const word& mdoelType
				);


				//- Destructor
				FoamLagrangian_EXPORT virtual ~injectionModel();


				// Member Functions

					//- Correct
				FoamLagrangian_EXPORT virtual void correct
				(
					scalarField& availableMass,
					scalarField& massToInject,
					scalarField& diameterToInject
				) = 0;

				//- Return the total mass injected
				FoamLagrangian_EXPORT virtual scalar injectedMassTotal() const;

				//- Accumulate the total mass injected for the patches into the
				//  scalarField provided
				virtual void patchInjectedMassTotals(scalarField& patchMasses) const
				{}


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const injectionModel&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_injectionModel_Header
