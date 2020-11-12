#pragma once
#ifndef _surfaceFilmModel_Header
#define _surfaceFilmModel_Header

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
	tnbLib::regionModels::surfaceFilmModel

Description
	Base class for surface film models

SourceFiles
	surfaceFilmModelI.H
	surfaceFilmModel.C
	surfaceFilmModelNew.C

\*---------------------------------------------------------------------------*/

#include <runTimeSelectionTables.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{

		/*---------------------------------------------------------------------------*\
							  Class surfaceFilmModel Declaration
		\*---------------------------------------------------------------------------*/

		class surfaceFilmModel
		{
		public:

			//- Runtime type information
			//TypeName("surfaceFilmModel");
			static const char* typeName_() { return "surfaceFilmModel"; }
			static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
			static FoamLagrangian_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			//- Reference temperature for enthalpy
			static FoamLagrangian_EXPORT const dimensionedScalar Tref;


			// Declare runtime constructor selection table

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				surfaceFilmModel,
				mesh,
				(
					const word& modelType,
					const fvMesh& mesh,
					const dimensionedVector& g,
					const word& regionType
					),
					(modelType, mesh, g, regionType)
			);*/

			typedef autoPtr<surfaceFilmModel> (*meshConstructorPtr)(const word& modelType, const fvMesh& mesh,
			                                                        const dimensionedVector& g, const word& regionType);
			typedef HashTable<meshConstructorPtr, word, string::hash> meshConstructorTable;
			static FoamLagrangian_EXPORT meshConstructorTable* meshConstructorTablePtr_;
			static FoamLagrangian_EXPORT void constructmeshConstructorTables();
			static FoamLagrangian_EXPORT void destroymeshConstructorTables();

			template <class surfaceFilmModelType>
			class addmeshConstructorToTable
			{
			public:
				static autoPtr<surfaceFilmModel> New(const word& modelType, const fvMesh& mesh,
				                                     const dimensionedVector& g, const word& regionType)
				{
					return autoPtr<surfaceFilmModel>(new surfaceFilmModelType(modelType, mesh, g, regionType));
				}

				addmeshConstructorToTable(const word& lookup = surfaceFilmModelType::typeName)
				{
					constructmeshConstructorTables();
					if (!meshConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
							"surfaceFilmModel" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addmeshConstructorToTable() { destroymeshConstructorTables(); }
			};

			template <class surfaceFilmModelType>
			class addRemovablemeshConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<surfaceFilmModel> New(const word& modelType, const fvMesh& mesh,
				                                     const dimensionedVector& g, const word& regionType)
				{
					return autoPtr<surfaceFilmModel>(new surfaceFilmModelType(modelType, mesh, g, regionType));
				}

				addRemovablemeshConstructorToTable(const word& lookup = surfaceFilmModelType::typeName) : lookup_(
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


			// Constructors

			FoamLagrangian_EXPORT surfaceFilmModel();

			//- Disallow default bitwise copy construction
			FoamLagrangian_EXPORT surfaceFilmModel(const surfaceFilmModel&) = delete;


			// Selectors

				//- Return a reference to the selected surface film model
			static FoamLagrangian_EXPORT autoPtr<surfaceFilmModel> New
			(
				const fvMesh& mesh,
				const dimensionedVector& g,
				const word& regionType = "surfaceFilm"
			);


			//- Destructor
			FoamLagrangian_EXPORT virtual ~surfaceFilmModel();


			// Member Functions

				// Solution parameters

					//- Courant number evaluation
			FoamLagrangian_EXPORT virtual scalar CourantNumber() const = 0;


			// Primary region source fields

				//- Return total mass source - Eulerian phase only
			FoamLagrangian_EXPORT virtual tmp<volScalarField::Internal> Srho() const = 0;

			//- Return mass source for specie i - Eulerian phase only
			virtual tmp<volScalarField::Internal> Srho
			(
				const label i
			) const = 0;

			//- Return enthalpy source - Eulerian phase only
			FoamLagrangian_EXPORT virtual tmp<volScalarField::Internal> Sh() const = 0;


			// Evolution

				//- Main driver routing to evolve the region - calls other evolves
			FoamLagrangian_EXPORT virtual void evolve() = 0;


			// Member Operators

				//- Disallow default bitwise assignment
			FoamLagrangian_EXPORT void operator=(const surfaceFilmModel&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace regionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceFilmModel_Header
