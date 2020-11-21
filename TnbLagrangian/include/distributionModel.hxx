#pragma once
#ifndef _distributionModel_Header
#define _distributionModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::distributionModel

Description
	A library of runtime-selectable distribution models.

	Returns a sampled value given the expectation (nu) and variance (sigma^2)

	Current distribution models include:
	- exponential
	- fixedValue
	- general
	- multi-normal
	- normal
	- Rosin-Rammler
	- Mass-based Rosin-Rammler
	- uniform

	The distributionModel is tabulated in equidistant nPoints, in an interval.
	These values are integrated to obtain the cumulated distribution model,
	which is then used to change the distribution from unifrom to
	the actual distributionModel.

SourceFiles
	distributionModel.C
	distributionModelNew.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <autoPtr.hxx>
#include <Random.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class distributionModel Declaration
	\*---------------------------------------------------------------------------*/

	class distributionModel
	{

	protected:

		// Protected data

			//- Coefficients dictionary
		const dictionary distributionModelDict_;

		//- Reference to the random number generator
		Random& rndGen_;


		// Protected Member Functions

			//- Check that the distribution model is valid
		virtual void check() const;


	public:

		//-Runtime type information
		//TypeName("distributionModel");
		static const char* typeName_() { return "distributionModel"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			distributionModel,
			dictionary,
			(
				const dictionary& dict,
				Random& rndGen
				),
				(dict, rndGen)
		);*/
		
		typedef autoPtr<distributionModel> (*dictionaryConstructorPtr)(const dictionary& dict, Random& rndGen);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
		static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

		template <class distributionModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<distributionModel> New(const dictionary& dict, Random& rndGen)
			{
				return autoPtr<distributionModel>(new distributionModelType(dict, rndGen));
			}

			adddictionaryConstructorToTable(const word& lookup = distributionModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "distributionModel"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class distributionModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<distributionModel> New(const dictionary& dict, Random& rndGen)
			{
				return autoPtr<distributionModel>(new distributionModelType(dict, rndGen));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = distributionModelType::typeName) : lookup_(
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

		//- Construct from dictionary
		FoamLagrangian_EXPORT distributionModel
		(
			const word& name,
			const dictionary& dict,
			Random& rndGen
		);

		//- Construct copy
		FoamLagrangian_EXPORT distributionModel(const distributionModel& p);

		//- Construct and return a clone
		FoamLagrangian_EXPORT virtual autoPtr<distributionModel> clone() const = 0;


		//- Selector
		static FoamLagrangian_EXPORT autoPtr<distributionModel> New
		(
			const dictionary& dict,
			Random& rndGen
		);


		//- Destructor
		FoamLagrangian_EXPORT virtual ~distributionModel();


		// Member Functions

			//- Sample the distributionModel
		FoamLagrangian_EXPORT virtual scalar sample() const = 0;

		//- Return the minimum value
		FoamLagrangian_EXPORT virtual scalar minValue() const = 0;

		//- Return the maximum value
		FoamLagrangian_EXPORT virtual scalar maxValue() const = 0;

		//- Return the maximum value
		FoamLagrangian_EXPORT virtual scalar meanValue() const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_distributionModel_Header
