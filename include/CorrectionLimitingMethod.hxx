#pragma once
#ifndef _CorrectionLimitingMethod_Header
#define _CorrectionLimitingMethod_Header

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
	tnbLib::CorrectionLimitingMethod

Description
	Base class for correction limiting methods.

SourceFiles
	CorrectionLimitingMethod.C

\*---------------------------------------------------------------------------*/

#include <volFieldsFwd.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class CorrectionLimitingMethod Declaration
	\*---------------------------------------------------------------------------*/

	class CorrectionLimitingMethod
	{
	public:

		//- Runtime type information
		//TypeName("correctionLimitingMethod");
		static const char* typeName_() { return "correctionLimitingMethod"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			CorrectionLimitingMethod,
			dictionary,
			(const dictionary& dict),
			(dict)
		);*/
		
		typedef autoPtr<CorrectionLimitingMethod> (*dictionaryConstructorPtr)(const dictionary& dict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
		static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

		template <class CorrectionLimitingMethodType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<CorrectionLimitingMethod> New(const dictionary& dict)
			{
				return autoPtr<CorrectionLimitingMethod>(new CorrectionLimitingMethodType(dict));
			}

			adddictionaryConstructorToTable(const word& lookup = CorrectionLimitingMethodType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
						"CorrectionLimitingMethod" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class CorrectionLimitingMethodType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<CorrectionLimitingMethod> New(const dictionary& dict)
			{
				return autoPtr<CorrectionLimitingMethod>(new CorrectionLimitingMethodType(dict));
			}

			addRemovabledictionaryConstructorToTable(
				const word& lookup = CorrectionLimitingMethodType::typeName) : lookup_(lookup)
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

			//- Construct from components
		FoamLagrangian_EXPORT CorrectionLimitingMethod(const dictionary& dict);

		//- Copy constructor
		FoamLagrangian_EXPORT CorrectionLimitingMethod(const CorrectionLimitingMethod& cl);

		//- Construct and return a clone
		FoamLagrangian_EXPORT virtual autoPtr<CorrectionLimitingMethod> clone() const = 0;


		//- Selector
		static FoamLagrangian_EXPORT autoPtr<CorrectionLimitingMethod> New
		(
			const dictionary& dict
		);


		//- Destructor
		FoamLagrangian_EXPORT virtual ~CorrectionLimitingMethod();


		// Member Functions

			//- Return the limited velocity
		FoamLagrangian_EXPORT virtual vector limitedVelocity
		(
			const vector uP,
			const vector dU,
			const vector uMean
		) const = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamLagrangian_EXPORT void operator=(const CorrectionLimitingMethod&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CorrectionLimitingMethod_Header
