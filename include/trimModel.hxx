#pragma once
#ifndef _trimModel_Header
#define _trimModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::trimModel

Description
	Trim model base class

SourceFiles
	trimModel.C

\*---------------------------------------------------------------------------*/

#include <rotorDiskSource.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class trimModel Declaration
	\*---------------------------------------------------------------------------*/

	class trimModel
	{

	protected:

		// Protected data

			//- Reference to the rotor source model
		const fv::rotorDiskSource& rotor_;

		//- Name of model
		const word name_;

		//- Coefficients dictionary
		dictionary coeffs_;


	public:

		//- Run-time type information
		//TypeName("trimModel");
		static const char* typeName_() { return "trimModel"; }
		static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
		static FoamFvOptions_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare runtime constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			trimModel,
			dictionary,
			(
				const fv::rotorDiskSource& rotor,
				const dictionary& dict
				),
				(rotor, dict)
		);*/

		typedef autoPtr<trimModel> (*dictionaryConstructorPtr)(const fv::rotorDiskSource& rotor, const dictionary& dict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamFvOptions_EXPORT void constructdictionaryConstructorTables();
		static FoamFvOptions_EXPORT void destroydictionaryConstructorTables();

		template <class trimModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<trimModel> New(const fv::rotorDiskSource& rotor, const dictionary& dict)
			{
				return autoPtr<trimModel>(new trimModelType(rotor, dict));
			}

			adddictionaryConstructorToTable(const word& lookup = trimModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "trimModel" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class trimModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<trimModel> New(const fv::rotorDiskSource& rotor, const dictionary& dict)
			{
				return autoPtr<trimModel>(new trimModelType(rotor, dict));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = trimModelType::typeName) : lookup_(lookup)
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
		FoamFvOptions_EXPORT trimModel
		(
			const fv::rotorDiskSource& rotor,
			const dictionary& dict,
			const word& name
		);


		// Selectors

			//- Return a reference to the selected trim model
		static FoamFvOptions_EXPORT autoPtr<trimModel> New
		(
			const fv::rotorDiskSource& rotor,
			const dictionary& dict
		);


		//- Destructor
		FoamFvOptions_EXPORT virtual ~trimModel();


		// Member Functions

			//- Read
		FoamFvOptions_EXPORT virtual void read(const dictionary& dict);

		//- Return the geometric angle of attack [rad]
		virtual tmp<scalarField> thetag() const = 0;

		//- Correct the model
		virtual void correct
		(
			const vectorField& U,
			vectorField& force
		) = 0;

		//- Correct the model for compressible flow
		virtual void correct
		(
			const volScalarField rho,
			const vectorField& U,
			vectorField& force
		) = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_trimModel_Header
