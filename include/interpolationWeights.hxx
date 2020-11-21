#pragma once
#ifndef _interpolationWeights_Header
#define _interpolationWeights_Header

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
	tnbLib::interpolationWeights

Description
	Abstract base class for interpolating in 1D

SourceFiles
	interpolationWeights.C
	interpolationWeightsTemplates.C

\*---------------------------------------------------------------------------*/

#include <scalarField.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <pointField.hxx>

#include <typeInfo.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;
	class objectRegistry;

	/*---------------------------------------------------------------------------*\
						   Class interpolationWeights Declaration
	\*---------------------------------------------------------------------------*/

	class interpolationWeights
	{

	protected:

		const scalarField& samples_;

	public:

		//- Runtime type information
		//TypeName("interpolationWeights");
		static const char* typeName_() { return "interpolationWeights"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			interpolationWeights,
			word,
			(
				const scalarField& samples
				),
				(samples)
		);*/

		typedef autoPtr<interpolationWeights> (*wordConstructorPtr)(const scalarField& samples);
		typedef HashTable<wordConstructorPtr, word, string::hash> wordConstructorTable;
		static FoamBase_EXPORT wordConstructorTable* wordConstructorTablePtr_;
		static FoamBase_EXPORT void constructwordConstructorTables();
		static FoamBase_EXPORT void destroywordConstructorTables();

		template <class interpolationWeightsType>
		class addwordConstructorToTable
		{
		public:
			static autoPtr<interpolationWeights> New(const scalarField& samples)
			{
				return autoPtr<interpolationWeights>(new interpolationWeightsType(samples));
			}

			addwordConstructorToTable(const word& lookup = interpolationWeightsType::typeName)
			{
				constructwordConstructorTables();
				if (!wordConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "interpolationWeights" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addwordConstructorToTable() { destroywordConstructorTables(); }
		};

		template <class interpolationWeightsType>
		class addRemovablewordConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<interpolationWeights> New(const scalarField& samples)
			{
				return autoPtr<interpolationWeights>(new interpolationWeightsType(samples));
			}

			addRemovablewordConstructorToTable(const word& lookup = interpolationWeightsType::typeName) : lookup_(lookup)
			{
				constructwordConstructorTables();
				wordConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablewordConstructorToTable() { if (wordConstructorTablePtr_) { wordConstructorTablePtr_->erase(lookup_); } }
		};;


		// Constructors

			//- Construct from components
		FoamBase_EXPORT interpolationWeights(const scalarField& samples);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT interpolationWeights(const interpolationWeights&) = delete;


		// Selectors

			//- Return a reference to the selected interpolationWeights
		static FoamBase_EXPORT autoPtr<interpolationWeights> New
		(
			const word& type,
			const scalarField& samples
		);


		//- Destructor
		FoamBase_EXPORT virtual ~interpolationWeights();


		// Member Functions

			//- Calculate weights and indices to calculate t from samples.
			//  Returns true if indices changed.
		FoamBase_EXPORT virtual bool valueWeights
		(
			const scalar t,
			labelList& indices,
			scalarField& weights
		) const = 0;

		//- Calculate weights and indices to calculate integrand of t1..t2
		//  from samples. Returns true if indices changed.
		FoamBase_EXPORT virtual bool integrationWeights
		(
			const scalar t1,
			const scalar t2,
			labelList& indices,
			scalarField& weights
		) const = 0;

		//- Helper: weighted sum
		template<class ListType1, class ListType2>
		static typename outerProduct
			<
			typename ListType1::value_type,
			typename ListType2::value_type
			>::type
			weightedSum(const ListType1& f1, const ListType2& f2);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const interpolationWeights&) = delete;
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <interpolationWeightsI.hxx>

//#ifdef NoRepository
//#include <interpolationWeightsTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_interpolationWeights_Header
