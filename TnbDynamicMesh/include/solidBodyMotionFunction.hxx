#pragma once
#ifndef _solidBodyMotionFunction_Header
#define _solidBodyMotionFunction_Header

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
	tnbLib::solidBodyMotionFunctions

Description
	Namespace for solid-body motions


Class
	tnbLib::solidBodyMotionFunction

Description
	Base class for defining solid-body motions

SourceFiles
	solidBodyMotionFunction.C
	dynamicFvMeshNew.C

\*---------------------------------------------------------------------------*/

#include <Time.hxx>
#include <dictionary.hxx>
#include <septernion.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
	 s                  Class solidBodyMotionFunction Declaration
	\*---------------------------------------------------------------------------*/

	class solidBodyMotionFunction
	{
	protected:

		// Protected data

		dictionary SBMFCoeffs_;
		const Time& time_;


	public:

		//- Runtime type information
		//TypeName("solidBodyMotionFunction");
		static const char* typeName_() { return "solidBodyMotionFunction"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			solidBodyMotionFunction,
			dictionary,
			(const dictionary& SBMFCoeffs, const Time& runTime),
			(SBMFCoeffs, runTime)
		);*/

		typedef autoPtr<solidBodyMotionFunction> (*dictionaryConstructorPtr)(
			const dictionary& SBMFCoeffs, const Time& runTime);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamDynamicMesh_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamDynamicMesh_EXPORT void constructdictionaryConstructorTables();
		static FoamDynamicMesh_EXPORT void destroydictionaryConstructorTables();

		template <class solidBodyMotionFunctionType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<solidBodyMotionFunction> New(const dictionary& SBMFCoeffs, const Time& runTime)
			{
				return autoPtr<solidBodyMotionFunction>(new solidBodyMotionFunctionType(SBMFCoeffs, runTime));
			}

			adddictionaryConstructorToTable(const word& lookup = solidBodyMotionFunctionType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"solidBodyMotionFunction" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class solidBodyMotionFunctionType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<solidBodyMotionFunction> New(const dictionary& SBMFCoeffs, const Time& runTime)
			{
				return autoPtr<solidBodyMotionFunction>(new solidBodyMotionFunctionType(SBMFCoeffs, runTime));
			}

			addRemovabledictionaryConstructorToTable(
				const word& lookup = solidBodyMotionFunctionType::typeName) : lookup_(lookup)
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

			//- Construct from the SBMFCoeffs dictionary and Time
		FoamDynamicMesh_EXPORT solidBodyMotionFunction
		(
			const dictionary& SBMFCoeffs,
			const Time& runTime
		);

		//- Disallow default bitwise copy construction
		solidBodyMotionFunction(const solidBodyMotionFunction&) = delete;

		//- Construct and return a clone
		virtual autoPtr<solidBodyMotionFunction> clone() const = 0;


		// Selectors

			//- Select constructed from the SBMFCoeffs dictionary and Time
		static FoamDynamicMesh_EXPORT autoPtr<solidBodyMotionFunction> New
		(
			const dictionary& SBMFCoeffs,
			const Time& runTime
		);


		//- Destructor
		FoamDynamicMesh_EXPORT virtual ~solidBodyMotionFunction();


		// Member Functions

			//- Return the solid-body motion transformation septernion
		virtual septernion transformation() const = 0;

		//- Update properties from given dictionary
		virtual bool read(const dictionary& SBMFCoeffs) = 0;

		//- Write in dictionary format
		virtual FoamDynamicMesh_EXPORT void writeData(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const solidBodyMotionFunction&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_solidBodyMotionFunction_Header
