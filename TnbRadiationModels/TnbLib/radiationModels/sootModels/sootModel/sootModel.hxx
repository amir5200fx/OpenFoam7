#pragma once
#ifndef _sootModel_Header
#define _sootModel_Header

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
	tnbLib::radiationModels::sootModel

Description
	Base class for soot models

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{

		/*---------------------------------------------------------------------------*\
									Class sootModel Declaration
		\*---------------------------------------------------------------------------*/

		class sootModel
		{
		protected:

			// Protected data

				//- Radiation model dictionary
			const dictionary dict_;

			//- Reference to the fvMesh
			const fvMesh& mesh_;


		public:

			//- Runtime type information
			//TypeName("sootModel");
			static const char* typeName_() { return "sootModel"; }
			static FoamRadiationModels_EXPORT const ::tnbLib::word typeName;
			static FoamRadiationModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			//- Declare runtime constructor selection table

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				sootModel,
				dictionary,
				(
					const dictionary& dict,
					const fvMesh& mesh,
					const word& modelType
					),
					(dict, mesh, modelType)
			);*/

			typedef autoPtr<sootModel> (*dictionaryConstructorPtr)(const dictionary& dict, const fvMesh& mesh,
			                                                       const word& modelType);
			typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
			static FoamRadiationModels_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
			static FoamRadiationModels_EXPORT void constructdictionaryConstructorTables();
			static FoamRadiationModels_EXPORT void destroydictionaryConstructorTables();

			template <class sootModelType>
			class adddictionaryConstructorToTable
			{
			public:
				static autoPtr<sootModel> New(const dictionary& dict, const fvMesh& mesh, const word& modelType)
				{
					return autoPtr<sootModel>(new sootModelType(dict, mesh, modelType));
				}

				adddictionaryConstructorToTable(const word& lookup = sootModelType::typeName)
				{
					constructdictionaryConstructorTables();
					if (!dictionaryConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "sootModel" <<
							std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
			};

			template <class sootModelType>
			class addRemovabledictionaryConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<sootModel> New(const dictionary& dict, const fvMesh& mesh, const word& modelType)
				{
					return autoPtr<sootModel>(new sootModelType(dict, mesh, modelType));
				}

				addRemovabledictionaryConstructorToTable(const word& lookup = sootModelType::typeName) : lookup_(lookup)
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

				//- Construct from components
			FoamRadiationModels_EXPORT sootModel
			(
				const dictionary& dict,
				const fvMesh& mesh,
				const word& modelType
			);


			//- Selector
			static FoamRadiationModels_EXPORT autoPtr<sootModel> New
			(
				const dictionary& dict,
				const fvMesh& mesh
			);


			//- Destructor
			FoamRadiationModels_EXPORT virtual ~sootModel();


			// Member Functions

				// Access

					//- Reference to the mesh
			inline const fvMesh& mesh() const
			{
				return mesh_;
			}

			//- Reference to the dictionary
			inline const dictionary& dict() const
			{
				return dict_;
			}


			// Edit

				//- Main update/correction routine
			FoamRadiationModels_EXPORT virtual void correct() = 0;


			// Access

				//- Return const reference to soot
			FoamRadiationModels_EXPORT virtual const volScalarField& soot() const = 0;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sootModel_Header
