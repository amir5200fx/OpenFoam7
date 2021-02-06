#pragma once
#ifndef _reactionRateFlameArea_Header
#define _reactionRateFlameArea_Header

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
	tnbLib::reactionRateFlameArea

Description
	Abstract class for reaction rate per flame area unit

SourceFiles
	reactionRateFlameArea.C
	reactionRateFlameAreaNew.C

\*---------------------------------------------------------------------------*/

#include <CombustionModels_Module.hxx>
#include <runTimeSelectionTables.hxx>
#include <dictionary.hxx>
#include <autoPtr.hxx>
#include <volFields.hxx>
#include <combustionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	class fvMesh;

	/*---------------------------------------------------------------------------*\
							   Class reactionRateFlameArea Declaration
	\*---------------------------------------------------------------------------*/

	class reactionRateFlameArea
	{

	protected:

		// Protected data

			//- Dictionary
		dictionary coeffDict_;

		//- Mesh reference
		const fvMesh& mesh_;

		//- Combstion model owner
		const combustionModel& combModel_;

		//- Fuel name
		word fuel_;

		//- Fuel consumption rate per unit of flame area
		volScalarField omega_;


	public:

		//- Runtime type information
		//TypeName("reactionRateFlameArea");
		static const char* typeName_() { return "reactionRateFlameArea"; }
		static FoamCombustionModels_EXPORT const ::tnbLib::word typeName;
		static FoamCombustionModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			reactionRateFlameArea,
			dictionary,
			(
				const word modelType,
				const dictionary& dict,
				const fvMesh& mesh,
				const combustionModel& combModel
				),
				(modelType, dict, mesh, combModel)
		);*/


		typedef autoPtr<reactionRateFlameArea> (*dictionaryConstructorPtr)(const word modelType, const dictionary& dict,
		                                                                   const fvMesh& mesh,
		                                                                   const combustionModel& combModel);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamCombustionModels_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamCombustionModels_EXPORT void constructdictionaryConstructorTables();
		static FoamCombustionModels_EXPORT void destroydictionaryConstructorTables();

		template <class reactionRateFlameAreaType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<reactionRateFlameArea> New(const word modelType, const dictionary& dict, const fvMesh& mesh,
			                                          const combustionModel& combModel)
			{
				return autoPtr<reactionRateFlameArea>(new reactionRateFlameAreaType(modelType, dict, mesh, combModel));
			}

			adddictionaryConstructorToTable(const word& lookup = reactionRateFlameAreaType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "reactionRateFlameArea" << std::
						endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class reactionRateFlameAreaType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<reactionRateFlameArea> New(const word modelType, const dictionary& dict, const fvMesh& mesh,
			                                          const combustionModel& combModel)
			{
				return autoPtr<reactionRateFlameArea>(new reactionRateFlameAreaType(modelType, dict, mesh, combModel));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = reactionRateFlameAreaType::typeName) : lookup_(lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct from components
		FoamCombustionModels_EXPORT reactionRateFlameArea
		(
			const word& modelType,
			const dictionary& dict,
			const fvMesh& mesh,
			const combustionModel& combModel
		);

		//- Disallow default bitwise copy construction
		reactionRateFlameArea(const reactionRateFlameArea&);


		// Selector

		static FoamCombustionModels_EXPORT autoPtr<reactionRateFlameArea> New
		(
			const dictionary& dict,
			const fvMesh& mesh,
			const combustionModel& combModel
		);


		// Destructor

		FoamCombustionModels_EXPORT virtual ~reactionRateFlameArea();


		// Member Functions

			//- Access functions

				//- Return omega
		const volScalarField& omega() const
		{
			return omega_;
		}


		//- Correct omega
		virtual void correct(const volScalarField& sigma) = 0;

		//- Update from dictionary
		FoamCombustionModels_EXPORT virtual bool read(const dictionary& dictProperties);


		// Member Operators

			 //- Disallow default bitwise assignment
		void operator=(const reactionRateFlameArea&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_reactionRateFlameArea_Header
