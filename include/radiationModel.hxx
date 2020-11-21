#pragma once
#ifndef _radiationModel_Header
#define _radiationModel_Header

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
	tnbLib::radiationModel

Description
	Top level model for radiation modelling

SourceFiles
	radiationModel.C
	radiationModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <volFields.hxx>
#include <fvMatricesFwd.hxx>
#include <Switch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class basicThermo;
	class fvMesh;

	namespace radiationModels
	{
		class absorptionEmissionModel;
		class scatterModel;
		class sootModel;
	}

	/*---------------------------------------------------------------------------*\
						   Class radiationModel Declaration
	\*---------------------------------------------------------------------------*/

	class radiationModel
		:
		public IOdictionary
	{
	protected:

		// Protected data

			//- Reference to the mesh database
		const fvMesh& mesh_;

		//- Reference to the time database
		const Time& time_;

		//- Reference to the temperature field
		const volScalarField& T_;

		//- Radiation model dictionary
		dictionary coeffs_;

		//- Radiation solver frequency - number flow solver iterations per
		//  radiation solver iteration
		label solverFreq_;

		//- Flag to enable radiation model to be evaluated on first iteration
		bool firstIter_;


		// References to the radiation sub-models

			//- Absorption/emission model
		autoPtr<radiationModels::absorptionEmissionModel>
			absorptionEmission_;

		//- Scatter model
		autoPtr<radiationModels::scatterModel> scatter_;

		//- Soot model
		autoPtr<radiationModels::sootModel> soot_;


	private:

		// Private Member Functions

			//- Create IO object if dictionary is present
		FoamRadiationModels_EXPORT IOobject createIOobject(const fvMesh& mesh) const;

		//- Initialise
		FoamRadiationModels_EXPORT void initialise();


	public:

		//- Runtime type information
		//TypeName("radiationModel");
		static const char* typeName_() { return "radiationModel"; }
		static FoamRadiationModels_EXPORT const ::tnbLib::word typeName;
		static FoamRadiationModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare runtime constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			radiationModel,
			T,
			(
				const volScalarField& T
				),
				(T)
		);*/

		typedef autoPtr<radiationModel> (*TConstructorPtr)(const volScalarField& T);
		typedef HashTable<TConstructorPtr, word, string::hash> TConstructorTable;
		static FoamRadiationModels_EXPORT TConstructorTable* TConstructorTablePtr_;
		static FoamRadiationModels_EXPORT void constructTConstructorTables();
		static FoamRadiationModels_EXPORT void destroyTConstructorTables();

		template <class radiationModelType>
		class addTConstructorToTable
		{
		public:
			static autoPtr<radiationModel> New(const volScalarField& T)
			{
				return autoPtr<radiationModel>(new radiationModelType(T));
			}

			addTConstructorToTable(const word& lookup = radiationModelType::typeName)
			{
				constructTConstructorTables();
				if (!TConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "radiationModel" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addTConstructorToTable() { destroyTConstructorTables(); }
		};

		template <class radiationModelType>
		class addRemovableTConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<radiationModel> New(const volScalarField& T)
			{
				return autoPtr<radiationModel>(new radiationModelType(T));
			}

			addRemovableTConstructorToTable(const word& lookup = radiationModelType::typeName) : lookup_(lookup)
			{
				constructTConstructorTables();
				TConstructorTablePtr_->set(lookup, New);
			}

			~addRemovableTConstructorToTable() { if (TConstructorTablePtr_) { TConstructorTablePtr_->erase(lookup_); } }
		};

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			radiationModel,
			dictionary,
			(
				const dictionary& dict,
				const volScalarField& T
				),
				(dict, T)
		);*/

		typedef autoPtr<radiationModel> (*dictionaryConstructorPtr)(const dictionary& dict, const volScalarField& T);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamRadiationModels_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamRadiationModels_EXPORT void constructdictionaryConstructorTables();
		static FoamRadiationModels_EXPORT void destroydictionaryConstructorTables();

		template <class radiationModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<radiationModel> New(const dictionary& dict, const volScalarField& T)
			{
				return autoPtr<radiationModel>(new radiationModelType(dict, T));
			}

			adddictionaryConstructorToTable(const word& lookup = radiationModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "radiationModel" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class radiationModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<radiationModel> New(const dictionary& dict, const volScalarField& T)
			{
				return autoPtr<radiationModel>(new radiationModelType(dict, T));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = radiationModelType::typeName) : lookup_(
				lookup)
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

			//- Null constructor
		FoamRadiationModels_EXPORT radiationModel(const volScalarField& T);

		//- Construct from components
		FoamRadiationModels_EXPORT radiationModel(const word& type, const volScalarField& T);

		//- Construct from components
		FoamRadiationModels_EXPORT radiationModel
		(
			const word& type,
			const dictionary& dict,
			const volScalarField& T
		);

		//- Disallow default bitwise copy construction
		FoamRadiationModels_EXPORT radiationModel(const radiationModel&) = delete;


		// Selectors

			//- Return a reference to the selected radiation model
		static FoamRadiationModels_EXPORT autoPtr<radiationModel> New(const volScalarField& T);

		//- Return a reference to the selected radiation model
		static FoamRadiationModels_EXPORT autoPtr<radiationModel> New
		(
			const dictionary& dict,
			const volScalarField& T
		);


		//- Destructor
		FoamRadiationModels_EXPORT virtual ~radiationModel();


		// Member Functions

			// Edit

				//- Main update/correction routine
		FoamRadiationModels_EXPORT virtual void correct();

		//- Solve radiation equation(s)
		FoamRadiationModels_EXPORT virtual void calculate() = 0;

		//- Read radiationProperties dictionary
		FoamRadiationModels_EXPORT virtual bool read() = 0;


		// Access

			//- Source term component (for power of T^4)
		FoamRadiationModels_EXPORT virtual tmp<volScalarField> Rp() const = 0;

		//- Source term component (constant)
		FoamRadiationModels_EXPORT virtual tmp<volScalarField::Internal> Ru() const = 0;

		//- Energy source term
		FoamRadiationModels_EXPORT virtual tmp<fvScalarMatrix> Sh
		(
			const basicThermo& thermo,
			const volScalarField& he
		) const;

		//- Temperature source term
		FoamRadiationModels_EXPORT virtual tmp<fvScalarMatrix> ST
		(
			const dimensionedScalar& rhoCp,
			volScalarField& T
		) const;

		//- Access to absorptionEmission model
		FoamRadiationModels_EXPORT const radiationModels::absorptionEmissionModel&
			absorptionEmission() const;

		//- Access to soot Model
		FoamRadiationModels_EXPORT const radiationModels::sootModel& soot() const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamRadiationModels_EXPORT void operator=(const radiationModel&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define addToRadiationRunTimeSelectionTables(model)                            \
                                                                               \
    addToRunTimeSelectionTable                                                 \
    (                                                                          \
        radiationModel,                                                        \
        model,                                                                 \
        dictionary                                                             \
    );                                                                         \
                                                                               \
    addToRunTimeSelectionTable                                                 \
    (                                                                          \
        radiationModel,                                                        \
        model,                                                                 \
        T                                                                      \
    );

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_radiationModel_Header
