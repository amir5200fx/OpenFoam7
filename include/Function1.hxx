#pragma once
#ifndef _Function1_Header
#define _Function1_Header

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
	tnbLib::Function1

Description
	Top level data entry class for use in dictionaries. Provides a mechanism
	to specify a variable as a certain type, e.g. constant or table, and
	provide functions to return the (interpolated) value, and integral between
	limits.

SourceFiles
	Function1.C
	Function1New.C

\*---------------------------------------------------------------------------*/

#include <autoPtr.hxx>  // added by amir
#include <runTimeSelectionTables.hxx>  // added by amir
#include <dictionary.hxx>
#include <Field.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	template<class Type>
	class Function1;

	namespace Function1Types
	{

		template<class Type>
		class Constant;

		template<class Type>
		FoamBase_EXPORT autoPtr<Function1<Type>> createConstant(const word& entryName, Istream& is);

		template<>
		FoamBase_EXPORT autoPtr<Function1<label>> createConstant<label>(const word& entryName, Istream& is);
		template<>
		FoamBase_EXPORT autoPtr<Function1<scalar>> createConstant<scalar>(const word& entryName, Istream& is);
		template<>
		FoamBase_EXPORT autoPtr<Function1<vector>> createConstant<vector>(const word& entryName, Istream& is);
		template<>
		FoamBase_EXPORT autoPtr<Function1<sphericalTensor>> createConstant<sphericalTensor>(const word& entryName, Istream& is);
		template<>
		FoamBase_EXPORT autoPtr<Function1<symmTensor>> createConstant<symmTensor>(const word& entryName, Istream& is);
		template<>
		FoamBase_EXPORT autoPtr<Function1<tensor>> createConstant<tensor>(const word& entryName, Istream& is);
	}

	// Forward declarations
	class Time;

	// Forward declaration of friend functions and operators
	template<class Type> class Function1;
	template<class Type> Ostream& operator<<(Ostream&, const Function1<Type>&);

	/*---------------------------------------------------------------------------*\
							  Class Function1 Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class Function1
		:
		public tmp<Function1<Type>>::refCount
	{

	protected:

		// Protected data

			//- Name of entry
		const word name_;


	public:

		typedef Type returnType;

		//- Runtime type information
		//TypeName("Function1")
		static const char* typeName_() { return "Function1"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; }

		//- Declare runtime constructor selection table
		/*declareRunTimeSelectionTable
		(
			autoPtr,
			Function1,
			dictionary,
			(
				const word& entryName,
				const dictionary& dict
				),
				(entryName, dict)
		);*/

		typedef autoPtr<Function1> (*dictionaryConstructorPtr)(const word& entryName, const dictionary& dict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamBase_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamBase_EXPORT void constructdictionaryConstructorTables();
		static FoamBase_EXPORT void destroydictionaryConstructorTables();

		template <class Function1Type>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<Function1> New(const word& entryName, const dictionary& dict)
			{
				return autoPtr<Function1>(new Function1Type(entryName, dict));
			}

			adddictionaryConstructorToTable(const word& lookup = Function1Type::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "Function1" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class Function1Type>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<Function1> New(const word& entryName, const dictionary& dict)
			{
				return autoPtr<Function1>(new Function1Type(entryName, dict));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = Function1Type::typeName) : lookup_(lookup)
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

			//- Construct from entry name
		Function1(const word& entryName);

		//- Copy constructor
		Function1(const Function1<Type>& f1);

		//- Construct and return a clone
		virtual tmp<Function1<Type>> clone() const = 0;


		//- Selector
		static autoPtr<Function1<Type>> New
		(
			const word& entryName,
			const dictionary& dict
		);


		//- Destructor
		virtual ~Function1();


		// Member Functions

			// Access

				//- Return the name of the entry
		const word& name() const;


		// Manipulation

			//- Convert time
		virtual void convertTimeBase(const Time& t);


		// Evaluation

			//- Return value as a function of (scalar) independent variable
		virtual Type value(const scalar x) const;

		//- Return value as a function of (scalar) independent variable
		virtual tmp<Field<Type>> value(const scalarField& x) const = 0;

		//- Integrate between two (scalar) values
		virtual Type integrate(const scalar x1, const scalar x2) const;

		//- Integrate between two (scalar) values
		virtual tmp<Field<Type>> integrate
		(
			const scalarField& x1,
			const scalarField& x2
		) const = 0;


		// I/O

			//- Ostream Operator
		friend Ostream& operator<< <Type>
			(
				Ostream& os,
				const Function1<Type>& func
				);

		//- Write in dictionary format
		virtual void writeData(Ostream& os) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const Function1<Type>&) = delete;
	};


	template<class Type>
	void writeEntry(Ostream& os, const Function1<Type>& f1);


	/*---------------------------------------------------------------------------*\
							Class FieldFunction1 Declaration
	\*---------------------------------------------------------------------------*/

	template<class Function1Type>
	class FieldFunction1
		:
		public Function1Type
	{

	public:

		typedef typename Function1Type::returnType Type;


		// Constructors

			//- Construct from entry name and dictionary
		FieldFunction1(const word& entryName, const dictionary& dict);

		//- Construct and return a clone
		virtual tmp<Function1<Type>> clone() const;


		//- Destructor
		virtual ~FieldFunction1()
		{}


		// Member Functions

			// Evaluation

		using Function1Type::value;
		using Function1Type::integrate;

		//- Return value as a function of (scalar) independent variable
		virtual tmp<Field<Type>> value(const scalarField& x) const;

		//- Integrate between two (scalar) values
		virtual tmp<Field<Type>> integrate
		(
			const scalarField& x1,
			const scalarField& x2
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeFunction1(Type)                                                    \
                                                                               \
    defineNamedTemplateTypeNameAndDebug(Function1<Type>, 0);                   \
                                                                               \
    defineTemplateRunTimeSelectionTable                                        \
    (                                                                          \
        Function1<Type>,                                                       \
        dictionary                                                             \
    );


#define makeFunction1Type(SS, Type)                                            \
                                                                               \
    defineNamedTemplateTypeNameAndDebug(Function1Types::SS<Type>, 0);          \
                                                                               \
    Function1<Type>::adddictionaryConstructorToTable                           \
        <FieldFunction1<Function1Types::SS<Type>>>                             \
        add##SS##Type##ConstructorToTable_;


#define makeScalarFunction1(SS)                                                \
                                                                               \
    defineTypeNameAndDebug(SS, 0);                                             \
                                                                               \
    Function1<scalar>::adddictionaryConstructorToTable<FieldFunction1<SS>>     \
        add##SS##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <Function1I.hxx>
#include <Function1New_Imp.hxx>

//#ifdef NoRepository
//#include <Function1.cxx>
//#include <Constant.hxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Function1_Header
