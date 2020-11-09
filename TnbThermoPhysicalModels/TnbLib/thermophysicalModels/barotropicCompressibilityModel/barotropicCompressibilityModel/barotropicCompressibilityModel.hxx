#pragma once
#ifndef _barotropicCompressibilityModel_Header
#define _barotropicCompressibilityModel_Header

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
	tnbLib::compressibilityModels

Description
	Namespace for compressibility models.


Class
	tnbLib::barotropicCompressibilityModel

Description
	Abstract class for barotropic compressibility models

SourceFiles
	barotropicCompressibilityModel.C
	newbarotropicCompressibilityModel.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>
#include <volFields.hxx>
#include <dimensionedScalar.hxx>
#include <autoPtr.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					Class barotropicCompressibilityModel Declaration
	\*---------------------------------------------------------------------------*/

	class barotropicCompressibilityModel
	{
	protected:

		// Protected data

		dictionary compressibilityProperties_;

		volScalarField psi_;
		const volScalarField& gamma_;


	public:

		//- Runtime type information
		//TypeName("barotropicCompressibilityModel");
		static const char* typeName_() { return "barotropicCompressibilityModel"; }
		static FoamThermophysicalModels_EXPORT const ::tnbLib::word typeName;
		static FoamThermophysicalModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			barotropicCompressibilityModel,
			dictionary,
			(
				const dictionary& compressibilityProperties,
				const volScalarField& gamma,
				const word& psiName
				),
				(compressibilityProperties, gamma, psiName)
		);*/

		typedef autoPtr<barotropicCompressibilityModel> (*dictionaryConstructorPtr)(
			const dictionary& compressibilityProperties, const volScalarField& gamma, const word& psiName);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamThermophysicalModels_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamThermophysicalModels_EXPORT void constructdictionaryConstructorTables();
		static FoamThermophysicalModels_EXPORT void destroydictionaryConstructorTables();

		template <class barotropicCompressibilityModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<barotropicCompressibilityModel> New(const dictionary& compressibilityProperties,
			                                                   const volScalarField& gamma, const word& psiName)
			{
				return autoPtr<barotropicCompressibilityModel>(
					new barotropicCompressibilityModelType(compressibilityProperties, gamma, psiName));
			}

			adddictionaryConstructorToTable(const word& lookup = barotropicCompressibilityModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"barotropicCompressibilityModel" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class barotropicCompressibilityModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<barotropicCompressibilityModel> New(const dictionary& compressibilityProperties,
			                                                   const volScalarField& gamma, const word& psiName)
			{
				return autoPtr<barotropicCompressibilityModel>(
					new barotropicCompressibilityModelType(compressibilityProperties, gamma, psiName));
			}

			addRemovabledictionaryConstructorToTable(
				const word& lookup = barotropicCompressibilityModelType::typeName) : lookup_(lookup)
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
		FoamThermophysicalModels_EXPORT barotropicCompressibilityModel
		(
			const dictionary& compressibilityProperties,
			const volScalarField& gamma,
			const word& psiName = "psi"
		);

		//- Disallow default bitwise copy construction
		FoamThermophysicalModels_EXPORT barotropicCompressibilityModel(const barotropicCompressibilityModel&);


		// Selectors

			//- Return a reference to the selected compressibility model
		static FoamThermophysicalModels_EXPORT autoPtr<barotropicCompressibilityModel> New
		(
			const dictionary& compressibilityProperties,
			const volScalarField& gamma,
			const word& psiName = "psi"
		);


		//- Destructor
		virtual ~barotropicCompressibilityModel()
		{}


		// Member Functions

			//- Return the phase transport properties dictionary
		const dictionary& compressibilityProperties() const
		{
			return compressibilityProperties_;
		}

		//- Return the compressibility
		const volScalarField& psi() const
		{
			return psi_;
		}

		//- Correct the compressibility
		FoamThermophysicalModels_EXPORT virtual void correct() = 0;

		//- Read compressibilityProperties dictionary
		FoamThermophysicalModels_EXPORT virtual bool read(const dictionary& compressibilityProperties) = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamThermophysicalModels_EXPORT void operator=(const barotropicCompressibilityModel&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_barotropicCompressibilityModel_Header
