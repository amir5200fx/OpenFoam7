#pragma once
#ifndef _viscosityModel_Header
#define _viscosityModel_Header

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

Namespace
	tnbLib::viscosityModels

Description
	A namespace for various incompressible viscosityModel implementations.

Class
	tnbLib::viscosityModel

Description
	An abstract base class for incompressible viscosityModels.

	The strain rate is defined by:

		mag(symm(grad(U)))


SourceFiles
	viscosityModel.C
	viscosityModelNew.C

\*---------------------------------------------------------------------------*/

#include <dictionary.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <dimensionedScalar.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					Class viscosityModel Declaration
	\*---------------------------------------------------------------------------*/

	class viscosityModel
	{

	protected:

		// Protected data

		word name_;
		dictionary viscosityProperties_;

		const volVectorField& U_;
		const surfaceScalarField& phi_;


	public:

		//- Runtime type information
		//TypeName("viscosityModel");
		static const char* typeName_() { return "viscosityModel"; }
		static FoamTransportModels_EXPORT const ::tnbLib::word typeName;
		static FoamTransportModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			viscosityModel,
			dictionary,
			(
				const word& name,
				const dictionary& viscosityProperties,
				const volVectorField& U,
				const surfaceScalarField& phi
				),
				(name, viscosityProperties, U, phi)
		);*/

		typedef autoPtr<viscosityModel> (*dictionaryConstructorPtr)(const word& name,
		                                                            const dictionary& viscosityProperties,
		                                                            const volVectorField& U,
		                                                            const surfaceScalarField& phi);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamTransportModels_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamTransportModels_EXPORT void constructdictionaryConstructorTables();
		static FoamTransportModels_EXPORT void destroydictionaryConstructorTables();

		template <class viscosityModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<viscosityModel> New(const word& name, const dictionary& viscosityProperties,
			                                   const volVectorField& U, const surfaceScalarField& phi)
			{
				return autoPtr<viscosityModel>(new viscosityModelType(name, viscosityProperties, U, phi));
			}

			adddictionaryConstructorToTable(const word& lookup = viscosityModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "viscosityModel" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class viscosityModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<viscosityModel> New(const word& name, const dictionary& viscosityProperties,
			                                   const volVectorField& U, const surfaceScalarField& phi)
			{
				return autoPtr<viscosityModel>(new viscosityModelType(name, viscosityProperties, U, phi));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = viscosityModelType::typeName) : lookup_(
				lookup)
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
		FoamTransportModels_EXPORT viscosityModel
		(
			const word& name,
			const dictionary& viscosityProperties,
			const volVectorField& U,
			const surfaceScalarField& phi
		);

		//- Disallow default bitwise copy construction
		FoamTransportModels_EXPORT viscosityModel(const viscosityModel&);


		// Selectors

			//- Return a reference to the selected viscosity model
		static FoamTransportModels_EXPORT autoPtr<viscosityModel> New
		(
			const word& name,
			const dictionary& viscosityProperties,
			const volVectorField& U,
			const surfaceScalarField& phi
		);


		//- Destructor
		virtual ~viscosityModel()
		{}


		// Member Functions

			//- Return the phase transport properties dictionary
		const dictionary& viscosityProperties() const
		{
			return viscosityProperties_;
		}

		//- Return the strain rate
		FoamTransportModels_EXPORT tmp<volScalarField> strainRate() const;

		//- Return the laminar viscosity
		FoamTransportModels_EXPORT virtual tmp<volScalarField> nu() const = 0;

		//- Return the laminar viscosity for patch
		FoamTransportModels_EXPORT virtual tmp<scalarField> nu(const label patchi) const = 0;

		//- Correct the laminar viscosity
		FoamTransportModels_EXPORT virtual void correct() = 0;

		//- Read transportProperties dictionary
		FoamTransportModels_EXPORT virtual bool read(const dictionary& viscosityProperties) = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamTransportModels_EXPORT void operator=(const viscosityModel&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_viscosityModel_Header
