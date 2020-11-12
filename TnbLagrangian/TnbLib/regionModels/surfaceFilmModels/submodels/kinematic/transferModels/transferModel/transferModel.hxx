#pragma once
#ifndef _transferModel_Header
#define _transferModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::regionModels::surfaceFilmModels::transferModel

Description
	Base class for film transfer models, handling mass transfer between the
	film and the continuous phase.

SourceFiles
	transferModel.C
	transferModelNew.C

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
								  Class transferModel Declaration
			\*---------------------------------------------------------------------------*/

			class transferModel
				:
				public filmSubModelBase
			{
				// Private Data

					//- Transferred mass
				scalar transferredMass_;


			protected:

				// Protected Member Functions

					//- Add to transferred mass
				FoamLagrangian_EXPORT void addToTransferredMass(const scalar dMass);

				//- Correct
				FoamLagrangian_EXPORT void correct();


			public:

				//- Runtime type information
				//TypeName("transferModel");
				static const char* typeName_() { return "transferModel"; }
				static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
				static FoamLagrangian_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Declare runtime constructor selection table

				/*declareRunTimeSelectionTable
				(
					autoPtr,
					transferModel,
					dictionary,
					(
						surfaceFilmRegionModel& film,
						const dictionary& dict
						),
						(film, dict)
				);*/

				typedef autoPtr<transferModel> (*dictionaryConstructorPtr)(
					surfaceFilmRegionModel& film, const dictionary& dict);
				typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
				static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
				static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
				static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

				template <class transferModelType>
				class adddictionaryConstructorToTable
				{
				public:
					static autoPtr<transferModel> New(surfaceFilmRegionModel& film, const dictionary& dict)
					{
						return autoPtr<transferModel>(new transferModelType(film, dict));
					}

					adddictionaryConstructorToTable(const word& lookup = transferModelType::typeName)
					{
						constructdictionaryConstructorTables();
						if (!dictionaryConstructorTablePtr_->insert(lookup, New))
						{
							std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
								"transferModel" << std::endl;
							error::safePrintStack(std::cerr);
						}
					}

					~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
				};

				template <class transferModelType>
				class addRemovabledictionaryConstructorToTable
				{
					const word& lookup_;
				public:
					static autoPtr<transferModel> New(surfaceFilmRegionModel& film, const dictionary& dict)
					{
						return autoPtr<transferModel>(new transferModelType(film, dict));
					}

					addRemovabledictionaryConstructorToTable(
						const word& lookup = transferModelType::typeName) : lookup_(lookup)
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

					//- Construct for film
				FoamLagrangian_EXPORT transferModel(surfaceFilmRegionModel& film);

				//- Construct from type name, dictionary and surface film model
				FoamLagrangian_EXPORT transferModel
				(
					const word& modelType,
					surfaceFilmRegionModel& film,
					const dictionary& dict
				);

				//- Disallow default bitwise copy construction
				FoamLagrangian_EXPORT transferModel(const transferModel&) = delete;


				// Selectors

					//- Return a reference to the selected injection model
				static FoamLagrangian_EXPORT autoPtr<transferModel> New
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict,
					const word& modelType
				);


				//- Destructor
				FoamLagrangian_EXPORT virtual ~transferModel();


				// Member Functions

					//- Correct kinematic transfers
				FoamLagrangian_EXPORT virtual void correct
				(
					scalarField& availableMass,
					scalarField& massToTransfer
				) = 0;

				//- Correct kinematic and thermodynamic transfers
				FoamLagrangian_EXPORT virtual void correct
				(
					scalarField& availableMass,
					scalarField& massToTransfer,
					scalarField& energyToTransfer
				);

				//- Return the total mass transferred
				FoamLagrangian_EXPORT virtual scalar transferredMassTotal() const;

				//- Accumulate the total mass transferred for the patches into the
				//  scalarField provided
				virtual void patchTransferredMassTotals(scalarField& patchMasses) const
				{}


				// Member Operators

					//- Disallow default bitwise assignment
				FoamLagrangian_EXPORT void operator=(const transferModel&) = delete;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_transferModel_Header
