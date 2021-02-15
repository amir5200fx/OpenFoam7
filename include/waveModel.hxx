#pragma once
#ifndef _waveModel_Header
#define _waveModel_Header

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
	tnbLib::waveModel

Description
	Generic base class for waves. Derived classes must implement field
	functions which return the elevation above the wave surface and the
	velocity field, both as a function of position.

SourceFiles
	waveModel.C

\*---------------------------------------------------------------------------*/

#include <Wave_Module.hxx>
#include <objectRegistry.hxx>
#include <Function1.hxx>
#include <runTimeSelectionTables.hxx>
#include <vectorField.hxx>
#include <vector2DField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class waveModel Declaration
	\*---------------------------------------------------------------------------*/

	class waveModel
	{
		// Private Data

			//- Reference to the database
		const objectRegistry& db_;

		//- Peak-to-mean amplitude [m]
		autoPtr<Function1<scalar>> amplitude_;


	public:
		
		//- Runtime type information
		//TypeName("waveModel");
		static const char* typeName_() { return "waveModel"; }

		static FoamWave_EXPORT const ::tnbLib::word typeName;
		static FoamWave_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare runtime construction
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			waveModel,
			objectRegistry,
			(const objectRegistry& db, const dictionary& dict),
			(db, dict)
		);*/

		typedef autoPtr<waveModel> (*objectRegistryConstructorPtr)(const objectRegistry& db, const dictionary& dict);
		typedef HashTable<objectRegistryConstructorPtr, word, string::hash> objectRegistryConstructorTable;
		static objectRegistryConstructorTable* objectRegistryConstructorTablePtr_;
		static FoamWave_EXPORT void constructobjectRegistryConstructorTables();
		static FoamWave_EXPORT void destroyobjectRegistryConstructorTables();

		template <class waveModelType>
		class addobjectRegistryConstructorToTable
		{
		public:
			static autoPtr<waveModel> New(const objectRegistry& db, const dictionary& dict)
			{
				return autoPtr<waveModel>(new waveModelType(db, dict));
			}

			addobjectRegistryConstructorToTable(const word& lookup = waveModelType::typeName)
			{
				constructobjectRegistryConstructorTables();
				if (!objectRegistryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "waveModel" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addobjectRegistryConstructorToTable() { destroyobjectRegistryConstructorTables(); }
		};

		template <class waveModelType>
		class addRemovableobjectRegistryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<waveModel> New(const objectRegistry& db, const dictionary& dict)
			{
				return autoPtr<waveModel>(new waveModelType(db, dict));
			}

			addRemovableobjectRegistryConstructorToTable(const word& lookup = waveModelType::typeName) : lookup_(lookup)
			{
				constructobjectRegistryConstructorTables();
				objectRegistryConstructorTablePtr_->set(lookup, New);
			}

			~addRemovableobjectRegistryConstructorToTable()
			{
				if (objectRegistryConstructorTablePtr_) { objectRegistryConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct a copy
		FoamWave_EXPORT waveModel(const waveModel& wave);

		//- Construct from a database and a dictionary
		FoamWave_EXPORT waveModel(const objectRegistry& db, const dictionary& dict);

		//- Construct a clone
		virtual autoPtr<waveModel> clone() const = 0;


		// Selectors

			//- Select
		static FoamWave_EXPORT autoPtr<waveModel> New
		(
			const objectRegistry& db,
			const dictionary& dict
		);

		//- Select
		static FoamWave_EXPORT autoPtr<waveModel> New
		(
			const word& type,
			const objectRegistry& db,
			const dictionary& dict
		);


		//- Destructor
		FoamWave_EXPORT virtual ~waveModel();


		// Member Functions

			// Access

				//- Get the amplitude
		scalar amplitude(const scalar t) const
		{
			return amplitude_->value(t);
		}

		//- Get the (scalar) value of gravity.
		FoamWave_EXPORT scalar g() const;

		//- Get the wave elevation at a given time and local coordinates. Local
		//  x is aligned with the direction of propagation.
		virtual tmp<scalarField> elevation
		(
			const scalar t,
			const scalarField& x
		) const = 0;

		//- Get the wave velocity at a given time and local coordinates. Local
		//  x is aligned with the direction of propagation, and z with negative
		//  gravity.
		virtual tmp<vector2DField> velocity
		(
			const scalar t,
			const vector2DField& xz
		) const = 0;

		//- Get the wave pressure at a given time and local coordinates. Local
		//  x is aligned with the direction of propagation, and z with negative
		//  gravity.
		virtual tmp<scalarField> pressure
		(
			const scalar t,
			const vector2DField& xz
		) const = 0;

		//- Write
		FoamWave_EXPORT virtual void write(Ostream& os) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_waveModel_Header
