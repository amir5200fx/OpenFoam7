#pragma once
#ifndef _filmViscosityModel_Header
#define _filmViscosityModel_Header

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
	tnbLib::regionModels::surfaceFilmModels::filmViscosityModel

Description
	Base class for surface film viscosity models

SourceFiles
	filmViscosityModel.C
	filmViscosityModelNew.C

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
								 Class filmViscosityModel Declaration
			\*---------------------------------------------------------------------------*/

			class filmViscosityModel
				:
				public filmSubModelBase
			{
			protected:

				// Protected Member Data

					//- Reference to the viscosity field
				volScalarField& mu_;


			public:

				//- Runtime type information
				//TypeName("filmViscosityModel");
				static const char* typeName_() { return "filmViscosityModel"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Declare runtime constructor selection table

				/*declareRunTimeSelectionTable
				(
					autoPtr,
					filmViscosityModel,
					dictionary,
					(
						surfaceFilmRegionModel& film,
						const dictionary& dict,
						volScalarField& mu
						),
						(film, dict, mu)
				);*/

				typedef autoPtr<filmViscosityModel> (*dictionaryConstructorPtr)(
					surfaceFilmRegionModel& film, const dictionary& dict, volScalarField& mu);
				typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
				static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
				static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
				static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

				template <class filmViscosityModelType>
				class adddictionaryConstructorToTable
				{
				public:
					static autoPtr<filmViscosityModel> New(surfaceFilmRegionModel& film, const dictionary& dict,
					                                       volScalarField& mu)
					{
						return autoPtr<filmViscosityModel>(new filmViscosityModelType(film, dict, mu));
					}

					adddictionaryConstructorToTable(const word& lookup = filmViscosityModelType::typeName)
					{
						constructdictionaryConstructorTables();
						if (!dictionaryConstructorTablePtr_->insert(lookup, New))
						{
							std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
								"filmViscosityModel" << std::endl;
							error::safePrintStack(std::cerr);
						}
					}

					~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
				};

				template <class filmViscosityModelType>
				class addRemovabledictionaryConstructorToTable
				{
					const word& lookup_;
				public:
					static autoPtr<filmViscosityModel> New(surfaceFilmRegionModel& film, const dictionary& dict,
					                                       volScalarField& mu)
					{
						return autoPtr<filmViscosityModel>(new filmViscosityModelType(film, dict, mu));
					}

					addRemovabledictionaryConstructorToTable(
						const word& lookup = filmViscosityModelType::typeName) : lookup_(lookup)
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

					//- Construct from type name, dictionary and surface film model
				FoamLagrangian_EXPORT filmViscosityModel
				(
					const word& modelType,
					surfaceFilmRegionModel& film,
					const dictionary& dict,
					volScalarField& mu
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT filmViscosityModel(const filmViscosityModel&) = delete;


				// Selectors

					//- Return a reference to the selected phase change model
				static FoamLagrangian_EXPORT autoPtr<filmViscosityModel> New
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict,
					volScalarField& mu
				);


				//- Destructor
				FoamLagrangian_EXPORT virtual ~filmViscosityModel();


				// Member Functions

					// Evolution

						//- Correct
				FoamLagrangian_EXPORT virtual void correct
				(
					const volScalarField& p,
					const volScalarField& T
				) = 0;


				// I-O

					//- Provide some feedback
				FoamLagrangian_EXPORT virtual void info(Ostream& os) const;


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const filmViscosityModel&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_filmViscosityModel_Header
