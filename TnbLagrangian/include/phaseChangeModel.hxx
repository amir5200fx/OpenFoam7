#pragma once
#ifndef _phaseChangeModel_Header
#define _phaseChangeModel_Header

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
	tnbLib::regionModels::surfaceFilmModels::phaseChangeModel

Description
	Base class for surface film phase change models

SourceFiles
	phaseChangeModel.C
	phaseChangeModelNew.C

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
								  Class phaseChangeModel Declaration
			\*---------------------------------------------------------------------------*/

			class phaseChangeModel
				:
				public filmSubModelBase
			{
			protected:

				// Protected Member Functions

					//- Latest mass transfer due to phase change
				scalar latestMassPC_;

				//- Total mass transfer due to phase change
				scalar totalMassPC_;


			public:

				//- Runtime type information
				//TypeName("phaseChangeModel");
				static const char* typeName_() { return "phaseChangeModel"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Declare runtime constructor selection table

				/*declareRunTimeSelectionTable
				(
					autoPtr,
					phaseChangeModel,
					dictionary,
					(
						surfaceFilmRegionModel& film,
						const dictionary& dict
						),
						(film, dict)
				);*/

				typedef autoPtr<phaseChangeModel> (*dictionaryConstructorPtr)(
					surfaceFilmRegionModel& film, const dictionary& dict);
				typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
				static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
				static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
				static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

				template <class phaseChangeModelType>
				class adddictionaryConstructorToTable
				{
				public:
					static autoPtr<phaseChangeModel> New(surfaceFilmRegionModel& film, const dictionary& dict)
					{
						return autoPtr<phaseChangeModel>(new phaseChangeModelType(film, dict));
					}

					adddictionaryConstructorToTable(const word& lookup = phaseChangeModelType::typeName)
					{
						constructdictionaryConstructorTables();
						if (!dictionaryConstructorTablePtr_->insert(lookup, New))
						{
							std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
								"phaseChangeModel" << std::endl;
							error::safePrintStack(std::cerr);
						}
					}

					~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
				};

				template <class phaseChangeModelType>
				class addRemovabledictionaryConstructorToTable
				{
					const word& lookup_;
				public:
					static autoPtr<phaseChangeModel> New(surfaceFilmRegionModel& film, const dictionary& dict)
					{
						return autoPtr<phaseChangeModel>(new phaseChangeModelType(film, dict));
					}

					addRemovabledictionaryConstructorToTable(
						const word& lookup = phaseChangeModelType::typeName) : lookup_(lookup)
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
				FoamLagrangian_EXPORT phaseChangeModel(surfaceFilmRegionModel& film);

				//- Construct from type name, dictionary and surface film model
				FoamLagrangian_EXPORT phaseChangeModel
				(
					const word& modelType,
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT phaseChangeModel(const phaseChangeModel&) = delete;


				// Selectors

					//- Return a reference to the selected phase change model
				static FoamLagrangian_EXPORT autoPtr<phaseChangeModel> New
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);


				//- Destructor
				FoamLagrangian_EXPORT virtual ~phaseChangeModel();


				// Member Functions

					// Evolution

						//- Correct
				FoamLagrangian_EXPORT virtual void correct
				(
					const scalar dt,
					scalarField& availableMass,
					volScalarField& dMass,
					volScalarField& dEnergy
				);

				//- Correct
				FoamLagrangian_EXPORT virtual void correctModel
				(
					const scalar dt,
					scalarField& availableMass,
					scalarField& dMass,
					scalarField& dEnergy
				) = 0;


				// I-O

					//- Provide some feedback
				FoamLagrangian_EXPORT virtual void info(Ostream& os) const;


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const phaseChangeModel&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_phaseChangeModel_Header
