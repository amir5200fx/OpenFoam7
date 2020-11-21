#pragma once
#ifndef _filmRadiationModel_Header
#define _filmRadiationModel_Header

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
	tnbLib::regionModels::surfaceFilmModels::filmRadiationModel

Description
	Base class for film radiation models

SourceFiles
	filmRadiationModel.C
	filmRadiationModelNew.C

\*---------------------------------------------------------------------------*/

#include <filmSubModelBase.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			/*---------------------------------------------------------------------------*\
								Class filmRadiationModel Declaration
			\*---------------------------------------------------------------------------*/

			class filmRadiationModel
				:
				public filmSubModelBase
			{
			public:

				//- Runtime type information
				//TypeName("radiationModel");
				static const char* typeName_() { return "radiationModel"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Declare runtime constructor selection table

				/*declareRunTimeSelectionTable
				(
					autoPtr,
					filmRadiationModel,
					dictionary,
					(
						surfaceFilmRegionModel& film,
						const dictionary& dict
						),
						(film, dict)
				);*/

				typedef autoPtr<filmRadiationModel> (*dictionaryConstructorPtr)(
					surfaceFilmRegionModel& film, const dictionary& dict);
				typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
				static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
				static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
				static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

				template <class filmRadiationModelType>
				class adddictionaryConstructorToTable
				{
				public:
					static autoPtr<filmRadiationModel> New(surfaceFilmRegionModel& film, const dictionary& dict)
					{
						return autoPtr<filmRadiationModel>(new filmRadiationModelType(film, dict));
					}

					adddictionaryConstructorToTable(const word& lookup = filmRadiationModelType::typeName)
					{
						constructdictionaryConstructorTables();
						if (!dictionaryConstructorTablePtr_->insert(lookup, New))
						{
							std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
								"filmRadiationModel" << std::endl;
							error::safePrintStack(std::cerr);
						}
					}

					~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
				};

				template <class filmRadiationModelType>
				class addRemovabledictionaryConstructorToTable
				{
					const word& lookup_;
				public:
					static autoPtr<filmRadiationModel> New(surfaceFilmRegionModel& film, const dictionary& dict)
					{
						return autoPtr<filmRadiationModel>(new filmRadiationModelType(film, dict));
					}

					addRemovabledictionaryConstructorToTable(
						const word& lookup = filmRadiationModelType::typeName) : lookup_(lookup)
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
				FoamLagrangian_EXPORT filmRadiationModel(surfaceFilmRegionModel& film);

				//- Construct from type name, dictionary and surface film model
				FoamLagrangian_EXPORT filmRadiationModel
				(
					const word& modelType,
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT filmRadiationModel(const filmRadiationModel&) = delete;


				// Selectors

					//- Return a reference to the selected phase change model
				static FoamLagrangian_EXPORT autoPtr<filmRadiationModel> New
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);


				//- Destructor
				FoamLagrangian_EXPORT virtual ~filmRadiationModel();


				// Member Functions

					// Evolution

						//- Correct
				FoamLagrangian_EXPORT virtual void correct() = 0;

				//- Return the radiation sensible enthalpy source
				FoamLagrangian_EXPORT virtual tmp<volScalarField> Shs() = 0;


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const filmRadiationModel&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_filmRadiationModel_Header
