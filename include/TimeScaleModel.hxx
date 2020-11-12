#pragma once
#ifndef _TimeScaleModel_Header
#define _TimeScaleModel_Header

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
	tnbLib::TimeScaleModel

Description
	Base class for time scale models.

SourceFiles
	TimeScaleModel.C

\*---------------------------------------------------------------------------*/

#include <constants.hxx>
#include <Field.hxx>
#include <FieldField.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class TimeScaleModel Declaration
	\*---------------------------------------------------------------------------*/

	class TimeScaleModel
	{
		// Private member functions

			//- Disallow default bitwise assignment
		FoamLagrangian_EXPORT void operator=(const TimeScaleModel&) = delete;


	protected:

		// Protected data

			//- Close pack volume fraction
		scalar alphaPacked_;

		//- Coefficient of restitution
		scalar e_;


	public:

		//- Runtime type information
		//TypeName("timeScaleModel");
		static const char* typeName_() { return "timeScaleModel"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			TimeScaleModel,
			dictionary,
			(const dictionary& dict),
			(dict)
		);*/
		
		typedef autoPtr<TimeScaleModel> (*dictionaryConstructorPtr)(const dictionary& dict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamLagrangian_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamLagrangian_EXPORT void constructdictionaryConstructorTables();
		static FoamLagrangian_EXPORT void destroydictionaryConstructorTables();

		template <class TimeScaleModelType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<TimeScaleModel> New(const dictionary& dict)
			{
				return autoPtr<TimeScaleModel>(new TimeScaleModelType(dict));
			}

			adddictionaryConstructorToTable(const word& lookup = TimeScaleModelType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "TimeScaleModel" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class TimeScaleModelType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<TimeScaleModel> New(const dictionary& dict)
			{
				return autoPtr<TimeScaleModel>(new TimeScaleModelType(dict));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = TimeScaleModelType::typeName) : lookup_(
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


		//- Constructors

			//- Construct from components
		TimeScaleModel(const dictionary& dict);

		//- Construct a copy
		TimeScaleModel(const TimeScaleModel& sm);

		//- Construct and return a clone
		virtual autoPtr<TimeScaleModel> clone() const = 0;


		//- Selector
		static autoPtr<TimeScaleModel> New
		(
			const dictionary& dict
		);


		//- Destructor
		virtual ~TimeScaleModel();


		//- Member Functions

			//- Time scale
		virtual tmp<FieldField<Field, scalar>> oneByTau
		(
			const FieldField<Field, scalar>& alpha,
			const FieldField<Field, scalar>& r32,
			const FieldField<Field, scalar>& uSqr,
			const FieldField<Field, scalar>& f
		) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_TimeScaleModel_Header
