#pragma once
#ifndef _engineTime_Header
#define _engineTime_Header

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
	tnbLib::engineTime

Description
	An abstract class for the time description of the piston motion

SourceFiles
	engineTime.C

\*---------------------------------------------------------------------------*/

#include <Engine_Module.hxx>

#include <Time.hxx>
#include <IOdictionary.hxx>
#include <dimensionedScalar.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class engineTime Declaration
	\*---------------------------------------------------------------------------*/

	class engineTime
		:
		public Time
	{

	protected:

		const IOdictionary dict_;


	public:

		//- Runtime type information
		/*TypeName("engineTime");*/
		static const char* typeName_() { return "engineTime"; }
		static FoamEngine_EXPORT const ::tnbLib::word typeName;
		static FoamEngine_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			engineTime,
			dictionary,
			(
				const word& name,
				const fileName& rootPath,
				const fileName& caseName,
				const fileName& systemName,
				const fileName& constantName,
				const fileName& dictName
				),
				(name, rootPath, caseName, systemName, constantName, dictName)
		);*/
		typedef autoPtr<engineTime> (*dictionaryConstructorPtr)(const word& name, const fileName& rootPath,
		                                                        const fileName& caseName, const fileName& systemName,
		                                                        const fileName& constantName, const fileName& dictName);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamEngine_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamEngine_EXPORT void constructdictionaryConstructorTables();
		static FoamEngine_EXPORT void destroydictionaryConstructorTables();

		template <class engineTimeType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<engineTime> New(const word& name, const fileName& rootPath, const fileName& caseName,
			                               const fileName& systemName, const fileName& constantName,
			                               const fileName& dictName)
			{
				return autoPtr<engineTime>(
					new engineTimeType(name, rootPath, caseName, systemName, constantName, dictName));
			}

			adddictionaryConstructorToTable(const word& lookup = engineTimeType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "engineTime" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class engineTimeType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<engineTime> New(const word& name, const fileName& rootPath, const fileName& caseName,
			                               const fileName& systemName, const fileName& constantName,
			                               const fileName& dictName)
			{
				return autoPtr<engineTime>(
					new engineTimeType(name, rootPath, caseName, systemName, constantName, dictName));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = engineTimeType::typeName) : lookup_(lookup)
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

			//- Construct from objectRegistry arguments
		FoamEngine_EXPORT engineTime
		(
			const word& name,
			const fileName& rootPath,
			const fileName& caseName,
			const fileName& systemName = "system",
			const fileName& constantName = "constant",
			const fileName& dictName = "engineGeometry"
		);


		// Selector

		static FoamEngine_EXPORT autoPtr<engineTime> New
		(
			const word& name,
			const fileName& rootPath,
			const fileName& caseName,
			const fileName& systemName = "system",
			const fileName& constantName = "constant",
			const fileName& dictName = "engineGeometry"
		);


		//- Destructor
		virtual ~engineTime()
		{}


		// Member Functions
			// Conversion

				//- Calculate the piston position from the engine geometry
				//  and given timr (CA or s)
		virtual scalar pistonPosition(const scalar theta) const = 0;


		// Access

			//- Return the engine geometry dictionary
		inline const IOdictionary& engineDict() const
		{
			return dict_;
		}

		//- Return current engine time
		//  (value might be expressed in CA or s depending on the model)
		virtual scalar theta() const = 0;

		//- Return time unit
		virtual word unit() const = 0;

		//- Return engine time increment
		//  (value might be expressed in CA or s depending on the model)
		virtual scalar deltaTheta() const = 0;

		//- Return current piston position
		FoamEngine_EXPORT dimensionedScalar pistonPosition() const;

		//- Return piston displacement for current time step
		FoamEngine_EXPORT dimensionedScalar pistonDisplacement() const;

		//- Return piston speed for current time step
		FoamEngine_EXPORT dimensionedScalar pistonSpeed() const;


		// Member Functions overriding the virtual functions in time

			//- Read the control dictionary and set the write controls etc.
		FoamEngine_EXPORT virtual void readDict();


		// Edit

			//- Read the controlDict and set all the parameters
		FoamEngine_EXPORT virtual bool read();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_engineTime_Header
