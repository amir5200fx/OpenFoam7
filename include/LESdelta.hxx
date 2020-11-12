#pragma once
#ifndef _LESdelta_Header
#define _LESdelta_Header

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
	tnbLib::LESdelta

Description
	Abstract base class for LES deltas

SourceFiles
	LESdelta.C

\*---------------------------------------------------------------------------*/

#include <turbulenceModel.hxx>
#include <volFields.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							  Class LESdelta Declaration
	\*---------------------------------------------------------------------------*/

	class LESdelta
	{
	protected:

		// Protected data

		const turbulenceModel& turbulenceModel_;

		volScalarField delta_;


	public:

		//- Runtime type information
		//TypeName("LESdelta");
		static const char* typeName_() { return "LESdelta"; }
		static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
		static FoamTurbulence_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			LESdelta,
			dictionary,
			(
				const word& name,
				const turbulenceModel& turbulence,
				const dictionary& dict
				),
				(name, turbulence, dict)
		);*/

		typedef autoPtr<LESdelta> (*dictionaryConstructorPtr)(const word& name, const turbulenceModel& turbulence,
		                                                      const dictionary& dict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamTurbulence_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamTurbulence_EXPORT void constructdictionaryConstructorTables();
		static FoamTurbulence_EXPORT void destroydictionaryConstructorTables();

		template <class LESdeltaType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<LESdelta> New(const word& name, const turbulenceModel& turbulence, const dictionary& dict)
			{
				return autoPtr<LESdelta>(new LESdeltaType(name, turbulence, dict));
			}

			adddictionaryConstructorToTable(const word& lookup = LESdeltaType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "LESdelta" << std::
						endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class LESdeltaType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<LESdelta> New(const word& name, const turbulenceModel& turbulence, const dictionary& dict)
			{
				return autoPtr<LESdelta>(new LESdeltaType(name, turbulence, dict));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = LESdeltaType::typeName) : lookup_(lookup)
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

			//- Construct from name, turbulenceModel and dictionary
		FoamTurbulence_EXPORT LESdelta
		(
			const word& name,
			const turbulenceModel& turbulence
		);

		//- Disallow default bitwise copy construction
		FoamTurbulence_EXPORT LESdelta(const LESdelta&) = delete;


		// Selectors

			//- Return a reference to the selected LES delta
		static FoamTurbulence_EXPORT autoPtr<LESdelta> New
		(
			const word& name,
			const turbulenceModel& turbulence,
			const dictionary& dict
		);

		//- Return a reference to the selected LES delta
		static FoamTurbulence_EXPORT autoPtr<LESdelta> New
		(
			const word& name,
			const turbulenceModel& turbulence,
			const dictionary& dict,
			const dictionaryConstructorTable&
		);


		//- Destructor
		virtual ~LESdelta()
		{}


		// Member Functions

			//- Return turbulenceModel reference
		const turbulenceModel& turbulence() const
		{
			return turbulenceModel_;
		}

		//- Read the LESdelta dictionary
		FoamTurbulence_EXPORT virtual void read(const dictionary&) = 0;

		// Correct values
		FoamTurbulence_EXPORT virtual void correct() = 0;


		// Member Operators

		FoamTurbulence_EXPORT void operator=(const LESdelta&) = delete;

		virtual operator const volScalarField&() const
		{
			return delta_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_LESdelta_Header
