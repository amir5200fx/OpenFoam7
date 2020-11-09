#pragma once
#ifndef _ODESolver_Header
#define _ODESolver_Header

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
	tnbLib::ODESolver

Description
	Abstract base-class for ODE system solvers

SourceFiles
	ODESolver.C

\*---------------------------------------------------------------------------*/

#include <ODESystem.hxx>
#include <typeInfo.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class ODESolver Declaration
	\*---------------------------------------------------------------------------*/

	class ODESolver
	{

	protected:

		// Protected data

			//- Reference to ODESystem
		const ODESystem& odes_;

		//- Maximum size of the ODESystem
		const label maxN_;

		//- Size of the ODESystem (adjustable)
		mutable label n_;

		//- Absolute convergence tolerance per step
		scalarField absTol_;

		//- Relative convergence tolerance per step
		scalarField relTol_;

		//- The maximum number of sub-steps allowed for the integration step
		label maxSteps_;


		// Protected Member Functions

			//- Return the nomalized scalar error
		FoamODE_EXPORT scalar normalizeError
		(
			const scalarField& y0,
			const scalarField& y,
			const scalarField& err
		) const;


	public:

		friend class ODESystem;

		//- Runtime type information
		//TypeName("ODESolver");
		static const char* typeName_() { return "ODESolver"; }
		static FoamODE_EXPORT const ::tnbLib::word typeName;
		static FoamODE_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		class stepState
		{
		public:

			const bool forward;
			scalar dxTry;
			scalar dxDid;
			bool first;
			bool last;
			bool reject;
			bool prevReject;

			stepState(const scalar dx)
				:
				forward(dx > 0 ? true : false),
				dxTry(dx),
				dxDid(0),
				first(true),
				last(false),
				reject(false),
				prevReject(false)
			{}
		};


		// Declare run-time constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			ODESolver,
			dictionary,
			(const ODESystem& ode, const dictionary& dict),
			(ode, dict)
		);*/

		typedef autoPtr<ODESolver> (*dictionaryConstructorPtr)(const ODESystem& ode, const dictionary& dict);
		typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
		static FoamODE_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
		static FoamODE_EXPORT void constructdictionaryConstructorTables();
		static FoamODE_EXPORT void destroydictionaryConstructorTables();

		template <class ODESolverType>
		class adddictionaryConstructorToTable
		{
		public:
			static autoPtr<ODESolver> New(const ODESystem& ode, const dictionary& dict)
			{
				return autoPtr<ODESolver>(new ODESolverType(ode, dict));
			}

			adddictionaryConstructorToTable(const word& lookup = ODESolverType::typeName)
			{
				constructdictionaryConstructorTables();
				if (!dictionaryConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "ODESolver" <<
						std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
		};

		template <class ODESolverType>
		class addRemovabledictionaryConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<ODESolver> New(const ODESystem& ode, const dictionary& dict)
			{
				return autoPtr<ODESolver>(new ODESolverType(ode, dict));
			}

			addRemovabledictionaryConstructorToTable(const word& lookup = ODESolverType::typeName) : lookup_(lookup)
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

			//- Construct for given ODESystem
		FoamODE_EXPORT ODESolver(const ODESystem& ode, const dictionary& dict);

		//- Construct for given ODESystem specifying tolerances
		FoamODE_EXPORT ODESolver
		(
			const ODESystem& ode,
			const scalarField& absTol,
			const scalarField& relTol
		);

		//- Disallow default bitwise copy construction
		FoamODE_EXPORT ODESolver(const ODESolver&) = delete;


		// Selectors

			//- Select null constructed
		static FoamODE_EXPORT autoPtr<ODESolver> New
		(
			const ODESystem& ode,
			const dictionary& dict
		);


		//- Destructor
		virtual ~ODESolver()
		{}


		// Member Functions

			//- Return the number of equations to solve
		inline label nEqns() const;

		//- Return access to the absolute tolerance field
		inline scalarField& absTol();

		//- Return access to the relative tolerance field
		inline scalarField& relTol();

		//- Resize the ODE solver
		virtual bool resize() = 0;

		template<class Type>
		static inline void resizeField(UList<Type>& f, const label n);

		template<class Type>
		inline void resizeField(UList<Type>& f) const;

		inline void resizeMatrix(scalarSquareMatrix& m) const;

		//- Solve the ODE system as far as possible up to dxTry
		//  adjusting the step as necessary to provide a solution within
		//  the specified tolerance.
		//  Update the state and return an estimate for the next step in dxTry
		FoamODE_EXPORT virtual void solve
		(
			scalar& x,
			scalarField& y,
			scalar& dxTry
		) const;

		//- Solve the ODE system as far as possible up to dxTry
		//  adjusting the step as necessary to provide a solution within
		//  the specified tolerance.
		//  Update the state and return an estimate for the next step in dxTry
		FoamODE_EXPORT virtual void solve
		(
			scalar& x,
			scalarField& y,
			stepState& step
		) const;

		//- Solve the ODE system from xStart to xEnd, update the state
		//  and return an estimate for the next step in dxTry
		FoamODE_EXPORT virtual void solve
		(
			const scalar xStart,
			const scalar xEnd,
			scalarField& y,
			scalar& dxEst
		) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamODE_EXPORT void operator=(const ODESolver&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <ODESolverI.hxx>

#endif // !_ODESolver_Header
