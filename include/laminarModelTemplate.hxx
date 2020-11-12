#pragma once
#ifndef _laminarModel_Header
#define _laminarModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::laminarModel

Description
	Templated abstract base class for laminar transport models

SourceFiles
	laminarModel.C

\*---------------------------------------------------------------------------*/

#include <TurbulenceModelTemplate.hxx>
#include <Switch.hxx>  // added by amir
#include <dictionary.hxx> // added by amir

#ifdef FoamTurbulence_EXPORT_DEFINE
#define FoamlaminarModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamlaminarModel_EXPORT_DEFINE
#define FoamlaminarModel_EXPORT __declspec(dllexport)
#else
#define FoamlaminarModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class laminarModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class BasicTurbulenceModel>
	class laminarModel
		:
		public BasicTurbulenceModel
	{

	protected:

		// Protected data

			//- laminar coefficients dictionary
		dictionary laminarDict_;

		//- Flag to print the model coeffs at run-time
		Switch printCoeffs_;

		//- Model coefficients dictionary
		dictionary coeffDict_;


		// Protected Member Functions

			//- Print model coefficients
		virtual void printCoeffs(const word& type);


	public:

		typedef typename BasicTurbulenceModel::alphaField alphaField;
		typedef typename BasicTurbulenceModel::rhoField rhoField;
		typedef typename BasicTurbulenceModel::transportModel transportModel;


		//- Runtime type information
		//TypeName("laminar");
		static const char* typeName_() { return "laminar"; }
		static FoamlaminarModel_EXPORT const ::tnbLib::word typeName;
		static FoamlaminarModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			laminarModel,
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

		typedef autoPtr<laminarModel> (*dictionaryConstructorPtr)(const alphaField& alpha, const rhoField& rho,
		                                                          const volVectorField& U,
		                                                          const surfaceScalarField& alphaRhoPhi,
		                                                          const surfaceScalarField& phi,
		                                                          const transportModel& transport,
		                                                          const word& propertiesName);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamlaminarModel_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamlaminarModel_EXPORT void constructdictionaryConstructorTables();
		static void destroydictionaryConstructorTables();

		template <class laminarModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<laminarModel> New(const alphaField& alpha, const rhoField& rho, const volVectorField& U,
			                                 const surfaceScalarField& alphaRhoPhi, const surfaceScalarField& phi,
			                                 const transportModel& transport, const word& propertiesName)
			{
				return autoPtr<laminarModel>(
					new laminarModelType(alpha, rho, U, alphaRhoPhi, phi, transport, propertiesName));
			}

			adddictionaryConstructorToTable(const word& lookup = laminarModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "laminarModel" << std
						::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class laminarModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<laminarModel> New(const alphaField& alpha, const rhoField& rho, const volVectorField& U,
			                                 const surfaceScalarField& alphaRhoPhi, const surfaceScalarField& phi,
			                                 const transportModel& transport, const word& propertiesName)
			{
				return autoPtr<laminarModel>(
					new laminarModelType(alpha, rho, U, alphaRhoPhi, phi, transport, propertiesName));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = laminarModelType::typeName) : lookup_(lookup)
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
		laminarModel
		(
			const word& type,
			const alphaField& alpha,
			const rhoField& rho,
			const volVectorField& U,
			const surfaceScalarField& alphaRhoPhi,
			const surfaceScalarField& phi,
			const transportModel& transport,
			const word& propertiesName
		);

		//- Disallow default bitwise copy construction
		laminarModel(const laminarModel&) = delete;


		// Selectors

			//- Return a reference to the selected laminar model
		static autoPtr<laminarModel> New
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
		virtual ~laminarModel()
		{}


		// Member Functions

			//- Read model coefficients if they have changed
		virtual bool read();


		// Access

			//- Const access to the coefficients dictionary
		virtual const dictionary& coeffDict() const
		{
			return coeffDict_;
		}

		//- Return the turbulence viscosity, i.e. 0 for laminar flow
		virtual tmp<volScalarField> nut() const;

		//- Return the turbulence viscosity on patch
		virtual tmp<scalarField> nut(const label patchi) const;

		//- Return the effective viscosity, i.e. the laminar viscosity
		virtual tmp<volScalarField> nuEff() const;

		//- Return the effective viscosity on patch
		virtual tmp<scalarField> nuEff(const label patchi) const;

		//- Return the turbulence kinetic energy, i.e. 0 for laminar flow
		virtual tmp<volScalarField> k() const;

		//- Return the turbulence kinetic energy dissipation rate,
		//  i.e. 0 for laminar flow
		virtual tmp<volScalarField> epsilon() const;

		//- Return the Reynolds stress tensor, i.e. 0 for laminar flow
		virtual tmp<volSymmTensorField> R() const;

		//- Correct the laminar transport
		virtual void correct();


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const laminarModel&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <laminarModelTemplateI.hxx>

//#ifdef NoRepository
//#include <laminarModelTemplate.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_laminarModel_Header
