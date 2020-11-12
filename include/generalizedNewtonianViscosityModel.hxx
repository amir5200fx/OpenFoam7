#pragma once
#ifndef _generalizedNewtonianViscosityModel_Header
#define _generalizedNewtonianViscosityModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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

Namespace
	tnbLib::laminarModels::generalizedNewtonianViscosityModels

Description
	A namespace for various generalized Newtonian viscosity model
	implementations.

Class
	tnbLib::laminarModels::generalizedNewtonianViscosityModel

Description
	An abstract base class for generalized Newtonian viscosity models.

SourceFiles
	generalizedNewtonianViscosityModel.C
	generalizedNewtonianViscosityModelNew.C

\*---------------------------------------------------------------------------*/

#include <tmp.hxx>  // added by amir
#include <dictionary.hxx>
#include <volFieldsFwd.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{

		/*---------------------------------------------------------------------------*\
						Class generalizedNewtonianViscosityModel Declaration
		\*---------------------------------------------------------------------------*/

		class generalizedNewtonianViscosityModel
		{
		protected:

			// Protected data

			dictionary viscosityProperties_;


		public:

			//- Runtime type information
			//TypeName("generalizedNewtonianViscosityModel");
			static const char* typeName_() { return "generalizedNewtonianViscosityModel"; }
			static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
			static FoamTurbulence_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Declare run-time constructor selection table

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				generalizedNewtonianViscosityModel,
				dictionary,
				(
					const dictionary& viscosityProperties
					),
					(viscosityProperties)
			);*/

			typedef autoPtr<generalizedNewtonianViscosityModel> (*dictionaryConstructorPtr)(
				const dictionary& viscosityProperties);
			typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
			static FoamTurbulence_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
			static FoamTurbulence_EXPORT void constructdictionaryConstructorTables();
			static FoamTurbulence_EXPORT void destroydictionaryConstructorTables();

			template <class generalizedNewtonianViscosityModelType>
			class adddictionaryConstructorToTable
			{
			public:
				static autoPtr<generalizedNewtonianViscosityModel> New(const dictionary& viscosityProperties)
				{
					return autoPtr<generalizedNewtonianViscosityModel>(
						new generalizedNewtonianViscosityModelType(viscosityProperties));
				}

				adddictionaryConstructorToTable(const word& lookup = generalizedNewtonianViscosityModelType::typeName)
				{
					constructdictionaryConstructorTables();
					if (!dictionaryConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
							"generalizedNewtonianViscosityModel" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
			};

			template <class generalizedNewtonianViscosityModelType>
			class addRemovabledictionaryConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<generalizedNewtonianViscosityModel> New(const dictionary& viscosityProperties)
				{
					return autoPtr<generalizedNewtonianViscosityModel>(
						new generalizedNewtonianViscosityModelType(viscosityProperties));
				}

				addRemovabledictionaryConstructorToTable(
					const word& lookup = generalizedNewtonianViscosityModelType::typeName) : lookup_(lookup)
				{
					constructdictionaryConstructorTables();
					dictionaryConstructorTablePtr_->set(lookup, New);
				}

				~addRemovabledictionaryConstructorToTable()
				{
					if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
				}
			};;


			// Selectors

				//- Return a reference to the selected viscosity model
			static FoamTurbulence_EXPORT autoPtr<generalizedNewtonianViscosityModel> New
			(
				const dictionary& viscosityProperties
			);


			// Constructors

				//- Construct from components
			FoamTurbulence_EXPORT generalizedNewtonianViscosityModel
			(
				const dictionary& viscosityProperties
			);

			//- Disallow default bitwise copy construction
			FoamTurbulence_EXPORT generalizedNewtonianViscosityModel
			(
				const generalizedNewtonianViscosityModel&
			);


			//- Destructor
			virtual ~generalizedNewtonianViscosityModel()
			{}


			// Member Functions

				//- Return the phase transport properties dictionary
			const dictionary& viscosityProperties() const
			{
				return viscosityProperties_;
			}

			//- Return the laminar viscosity
			FoamTurbulence_EXPORT virtual tmp<volScalarField> nu
			(
				const volScalarField& nu0,
				const volScalarField& strainRate
			) const = 0;

			//- Read transportProperties dictionary
			FoamTurbulence_EXPORT virtual bool read(const dictionary& viscosityProperties) = 0;


			// Member Operators

				//- Disallow default bitwise assignment
			FoamTurbulence_EXPORT void operator=(const generalizedNewtonianViscosityModel&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace laminarModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_generalizedNewtonianViscosityModel_Header
