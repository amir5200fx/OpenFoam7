#pragma once
#ifndef _TurbulenceModelTemplate_Header
#define _TurbulenceModelTemplate_Header

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
	tnbLib::TurbulenceModel

Description
	Templated abstract base class for turbulence models

SourceFiles
	TurbulenceModel.C

\*---------------------------------------------------------------------------*/

#include <turbulenceModel.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

#ifdef FoamTurbulence_EXPORT_DEFINE
#define FoamTurbulenceModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamTurbulenceModel_EXPORT_DEFINE
#define FoamTurbulenceModel_EXPORT __declspec(dllexport)
#else
#define FoamTurbulenceModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class TurbulenceModel Declaration
	\*---------------------------------------------------------------------------*/

	template
		<
		class Alpha,
		class Rho,
		class BasicTurbulenceModel,
		class TransportModel
		>
		class TurbulenceModel
		:
		public BasicTurbulenceModel
	{

	public:

		typedef Alpha alphaField;
		typedef Rho rhoField;
		typedef TransportModel transportModel;


	protected:

		// Protected data

		const alphaField& alpha_;
		const transportModel& transport_;


	public:

		// Declare run-time constructor selection table

		/*declareRunTimeNewSelectionTable
		(
			autoPtr,
			TurbulenceModel,
			dictionary,
			(
				const alphaField& alpha,
				const rhoField& rho,
				const volVectorField& U,
				const surfaceScalarField& alphaRhoPhi,
				const surfaceScalarField& phi,
				const transportModel& transport,
				const word& propertiesName
				),
				(alpha, rho, U, alphaRhoPhi, phi, transport, propertiesName)
		);*/

		typedef autoPtr<TurbulenceModel> (*dictionaryConstructorPtr)(const alphaField& alpha, const rhoField& rho,
		                                                             const volVectorField& U,
		                                                             const surfaceScalarField& alphaRhoPhi,
		                                                             const surfaceScalarField& phi,
		                                                             const transportModel& transport,
		                                                             const word& propertiesName);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamTurbulenceModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamTurbulenceModel_EXPORT void constructdictionaryConstructorTables();
		static FoamTurbulenceModel_EXPORT void destroydictionaryConstructorTables();

		template <class TurbulenceModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<TurbulenceModel> NewTurbulenceModel(const alphaField& alpha, const rhoField& rho,
			                                                   const volVectorField& U,
			                                                   const surfaceScalarField& alphaRhoPhi,
			                                                   const surfaceScalarField& phi,
			                                                   const transportModel& transport,
			                                                   const word& propertiesName)
			{
				return autoPtr<TurbulenceModel>(
					TurbulenceModelType::New(alpha, rho, U, alphaRhoPhi, phi, transport, propertiesName).ptr());
			}

			adddictionaryConstructorToTable(const word& lookup = TurbulenceModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, NewTurbulenceModel))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "TurbulenceModel" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class TurbulenceModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<TurbulenceModel> NewTurbulenceModel(const alphaField& alpha, const rhoField& rho,
			                                                   const volVectorField& U,
			                                                   const surfaceScalarField& alphaRhoPhi,
			                                                   const surfaceScalarField& phi,
			                                                   const transportModel& transport,
			                                                   const word& propertiesName)
			{
				return autoPtr<TurbulenceModel>(
					TurbulenceModelType::New(alpha, rho, U, alphaRhoPhi, phi, transport, propertiesName).ptr());
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = TurbulenceModelType::typeName) : lookup_(
				lookup)
			{
				constructdictionaryConstructorTables();
				dictionaryConstructorTablePtr_->set(lookup, NewTurbulenceModel);
			}

			~addRemovabledictionaryConstructorToTable()
			{
				if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct
		TurbulenceModel
		(
			const alphaField& alpha,
			const rhoField& rho,
			const volVectorField& U,
			const surfaceScalarField& alphaRhoPhi,
			const surfaceScalarField& phi,
			const transportModel& transport,
			const word& propertiesName
		);

		//- Disallow default bitwise copy construction
		TurbulenceModel(const TurbulenceModel&) = delete;


		// Selectors

			//- Return a reference to the selected turbulence model
		static autoPtr<TurbulenceModel> New
		(
			const alphaField& alpha,
			const rhoField& rho,
			const volVectorField& U,
			const surfaceScalarField& alphaRhoPhi,
			const surfaceScalarField& phi,
			const transportModel& transport,
			const word& propertiesName = turbulenceModel::propertiesName
		);


		//- Destructor
		virtual ~TurbulenceModel()
		{}


		// Member Functions

			//- Access function to phase fraction
		const alphaField& alpha() const
		{
			return alpha_;
		}

		//- Access function to incompressible transport model
		const transportModel& transport() const
		{
			return transport_;
		}

		//- Return the laminar viscosity
		virtual tmp<volScalarField> nu() const
		{
			return transport_.nu();
		}

		//- Return the laminar viscosity on patchi
		virtual tmp<scalarField> nu(const label patchi) const
		{
			return transport_.nu(patchi);
		}


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const TurbulenceModel&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <TurbulenceModelTemplateI.hxx>

//#ifdef NoRepository
//#include <TurbulenceModelTemplate.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_TurbulenceModelTemplate_Header
