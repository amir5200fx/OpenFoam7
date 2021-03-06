#pragma once
#ifndef _lduMatrix_Header
#define _lduMatrix_Header

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
	tnbLib::lduMatrix

Description
	lduMatrix is a general matrix class in which the coefficients are
	stored as three arrays, one for the upper triangle, one for the
	lower triangle and a third for the diagonal.

	Addressing arrays must be supplied for the upper and lower triangles.

	It might be better if this class were organised as a hierarchy starting
	from an empty matrix, then deriving diagonal, symmetric and asymmetric
	matrices.

SourceFiles
	lduMatrixATmul.C
	lduMatrix.C
	lduMatrixTemplates.C
	lduMatrixOperations.C
	lduMatrixSolver.C
	lduMatrixPreconditioner.C
	lduMatrixTests.C
	lduMatrixUpdateMatrixInterfaces.C

\*---------------------------------------------------------------------------*/

#include <lduMesh.hxx>
#include <primitiveFieldsFwd.hxx>
#include <FieldField.hxx>
#include <lduInterfaceFieldPtrsList.hxx>
#include <typeInfo.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <solverPerformance.hxx>
#include <InfoProxy.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class lduMatrix;

	FoamBase_EXPORT Ostream& operator<<(Ostream&, const lduMatrix&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const InfoProxy<lduMatrix>&);


	/*---------------------------------------------------------------------------*\
							   Class lduMatrix Declaration
	\*---------------------------------------------------------------------------*/

	class lduMatrix
	{
		// private data

			//- LDU mesh reference
		const lduMesh& lduMesh_;

		//- Coefficients (not including interfaces)
		scalarField *lowerPtr_, *diagPtr_, *upperPtr_;


	public:

		//- Abstract base-class for lduMatrix solvers
		class solver
		{
		protected:

			// Protected data

			word fieldName_;
			const lduMatrix& matrix_;
			const FieldField<Field, scalar>& interfaceBouCoeffs_;
			const FieldField<Field, scalar>& interfaceIntCoeffs_;
			lduInterfaceFieldPtrsList interfaces_;

			//- Dictionary of controls
			dictionary controlDict_;

			//- Default maximum number of iterations in the solver
			static FoamBase_EXPORT const label defaultMaxIter_;

			//- Maximum number of iterations in the solver
			label maxIter_;

			//- Minimum number of iterations in the solver
			label minIter_;

			//- Final convergence tolerance
			scalar tolerance_;

			//- Convergence tolerance relative to the initial
			scalar relTol_;


			// Protected Member Functions

				//- Read the control parameters from the controlDict_
			FoamBase_EXPORT virtual void readControls();


		public:

			//- Runtime type information
			FoamBase_EXPORT virtual const word& type() const = 0;


			// Declare run-time constructor selection tables

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				solver,
				symMatrix,
				(
					const word& fieldName,
					const lduMatrix& matrix,
					const FieldField<Field, scalar>& interfaceBouCoeffs,
					const FieldField<Field, scalar>& interfaceIntCoeffs,
					const lduInterfaceFieldPtrsList& interfaces,
					const dictionary& solverControls
					),
					(
						fieldName,
						matrix,
						interfaceBouCoeffs,
						interfaceIntCoeffs,
						interfaces,
						solverControls
						)
			);*/

			typedef autoPtr<solver>(*symMatrixConstructorPtr)(const word& fieldName, const lduMatrix& matrix,
				const FieldField<Field, scalar>& interfaceBouCoeffs,
				const FieldField<Field, scalar>& interfaceIntCoeffs,
				const lduInterfaceFieldPtrsList& interfaces,
				const dictionary& solverControls);
			typedef HashTable<symMatrixConstructorPtr, word, string::hash> symMatrixConstructorTable;
			static FoamBase_EXPORT symMatrixConstructorTable* symMatrixConstructorTablePtr_;
			static FoamBase_EXPORT void constructsymMatrixConstructorTables();
			static FoamBase_EXPORT void destroysymMatrixConstructorTables();

			template <class solverType>
			class addsymMatrixConstructorToTable
			{
			public:
				static autoPtr<solver> New(const word& fieldName, const lduMatrix& matrix,
					const FieldField<Field, scalar>& interfaceBouCoeffs,
					const FieldField<Field, scalar>& interfaceIntCoeffs,
					const lduInterfaceFieldPtrsList& interfaces, const dictionary& solverControls)
				{
					return autoPtr<solver>(new solverType(fieldName, matrix, interfaceBouCoeffs, interfaceIntCoeffs, interfaces,
						solverControls));
				}

				addsymMatrixConstructorToTable(const word& lookup = solverType::typeName)
				{
					constructsymMatrixConstructorTables();
					if (!symMatrixConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "solver" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addsymMatrixConstructorToTable() { destroysymMatrixConstructorTables(); }
			};

			template <class solverType>
			class addRemovablesymMatrixConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<solver> New(const word& fieldName, const lduMatrix& matrix,
					const FieldField<Field, scalar>& interfaceBouCoeffs,
					const FieldField<Field, scalar>& interfaceIntCoeffs,
					const lduInterfaceFieldPtrsList& interfaces, const dictionary& solverControls)
				{
					return autoPtr<solver>(new solverType(fieldName, matrix, interfaceBouCoeffs, interfaceIntCoeffs, interfaces,
						solverControls));
				}

				addRemovablesymMatrixConstructorToTable(const word& lookup = solverType::typeName) : lookup_(lookup)
				{
					constructsymMatrixConstructorTables();
					symMatrixConstructorTablePtr_->set(lookup, New);
				}

				~addRemovablesymMatrixConstructorToTable()
				{
					if (symMatrixConstructorTablePtr_) { symMatrixConstructorTablePtr_->erase(lookup_); }
				}
			};;

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				solver,
				asymMatrix,
				(
					const word& fieldName,
					const lduMatrix& matrix,
					const FieldField<Field, scalar>& interfaceBouCoeffs,
					const FieldField<Field, scalar>& interfaceIntCoeffs,
					const lduInterfaceFieldPtrsList& interfaces,
					const dictionary& solverControls
					),
					(
						fieldName,
						matrix,
						interfaceBouCoeffs,
						interfaceIntCoeffs,
						interfaces,
						solverControls
						)
			);*/

			typedef autoPtr<solver>(*asymMatrixConstructorPtr)(const word& fieldName, const lduMatrix& matrix,
				const FieldField<Field, scalar>& interfaceBouCoeffs,
				const FieldField<Field, scalar>& interfaceIntCoeffs,
				const lduInterfaceFieldPtrsList& interfaces,
				const dictionary& solverControls);
			typedef HashTable<asymMatrixConstructorPtr, word, string::hash> asymMatrixConstructorTable;
			static FoamBase_EXPORT asymMatrixConstructorTable* asymMatrixConstructorTablePtr_;
			static FoamBase_EXPORT void constructasymMatrixConstructorTables();
			static FoamBase_EXPORT void destroyasymMatrixConstructorTables();

			template <class solverType>
			class addasymMatrixConstructorToTable
			{
			public:
				static autoPtr<solver> New(const word& fieldName, const lduMatrix& matrix,
					const FieldField<Field, scalar>& interfaceBouCoeffs,
					const FieldField<Field, scalar>& interfaceIntCoeffs,
					const lduInterfaceFieldPtrsList& interfaces, const dictionary& solverControls)
				{
					return autoPtr<solver>(new solverType(fieldName, matrix, interfaceBouCoeffs, interfaceIntCoeffs, interfaces,
						solverControls));
				}

				addasymMatrixConstructorToTable(const word& lookup = solverType::typeName)
				{
					constructasymMatrixConstructorTables();
					if (!asymMatrixConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "solver" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addasymMatrixConstructorToTable() { destroyasymMatrixConstructorTables(); }
			};

			template <class solverType>
			class addRemovableasymMatrixConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<solver> New(const word& fieldName, const lduMatrix& matrix,
					const FieldField<Field, scalar>& interfaceBouCoeffs,
					const FieldField<Field, scalar>& interfaceIntCoeffs,
					const lduInterfaceFieldPtrsList& interfaces, const dictionary& solverControls)
				{
					return autoPtr<solver>(new solverType(fieldName, matrix, interfaceBouCoeffs, interfaceIntCoeffs, interfaces,
						solverControls));
				}

				addRemovableasymMatrixConstructorToTable(const word& lookup = solverType::typeName) : lookup_(lookup)
				{
					constructasymMatrixConstructorTables();
					asymMatrixConstructorTablePtr_->set(lookup, New);
				}

				~addRemovableasymMatrixConstructorToTable()
				{
					if (asymMatrixConstructorTablePtr_) { asymMatrixConstructorTablePtr_->erase(lookup_); }
				}
			};;


			// Constructors

			FoamBase_EXPORT solver
			(
				const word& fieldName,
				const lduMatrix& matrix,
				const FieldField<Field, scalar>& interfaceBouCoeffs,
				const FieldField<Field, scalar>& interfaceIntCoeffs,
				const lduInterfaceFieldPtrsList& interfaces,
				const dictionary& solverControls
			);

			// Selectors

				//- Return a new solver
			static FoamBase_EXPORT autoPtr<solver> New
			(
				const word& fieldName,
				const lduMatrix& matrix,
				const FieldField<Field, scalar>& interfaceBouCoeffs,
				const FieldField<Field, scalar>& interfaceIntCoeffs,
				const lduInterfaceFieldPtrsList& interfaces,
				const dictionary& solverControls
			);



			//- Destructor
			virtual ~solver()
			{}


			// Member Functions

				// Access

			const word& fieldName() const
			{
				return fieldName_;
			}

			const lduMatrix& matrix() const
			{
				return matrix_;
			}

			const FieldField<Field, scalar>& interfaceBouCoeffs() const
			{
				return interfaceBouCoeffs_;
			}

			const FieldField<Field, scalar>& interfaceIntCoeffs() const
			{
				return interfaceIntCoeffs_;
			}

			const lduInterfaceFieldPtrsList& interfaces() const
			{
				return interfaces_;
			}


			//- Read and reset the solver parameters from the given stream
			FoamBase_EXPORT virtual void read(const dictionary&);

			FoamBase_EXPORT virtual solverPerformance solve
			(
				scalarField& psi,
				const scalarField& source,
				const direction cmpt = 0
			) const = 0;

			//- Return the matrix norm used to normalise the residual for the
			//  stopping criterion
			FoamBase_EXPORT scalar normFactor
			(
				const scalarField& psi,
				const scalarField& source,
				const scalarField& Apsi,
				scalarField& tmpField
			) const;
		};


		//- Abstract base-class for lduMatrix smoothers
		class smoother
		{
		protected:

			// Protected data

			word fieldName_;
			const lduMatrix& matrix_;
			const FieldField<Field, scalar>& interfaceBouCoeffs_;
			const FieldField<Field, scalar>& interfaceIntCoeffs_;
			const lduInterfaceFieldPtrsList& interfaces_;


		public:

			//- Find the smoother name (directly or from a sub-dictionary)
			static FoamBase_EXPORT word getName(const dictionary&);

			//- Runtime type information
			FoamBase_EXPORT virtual const word& type() const = 0;


			// Declare run-time constructor selection tables

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				smoother,
				symMatrix,
				(
					const word& fieldName,
					const lduMatrix& matrix,
					const FieldField<Field, scalar>& interfaceBouCoeffs,
					const FieldField<Field, scalar>& interfaceIntCoeffs,
					const lduInterfaceFieldPtrsList& interfaces
					),
					(
						fieldName,
						matrix,
						interfaceBouCoeffs,
						interfaceIntCoeffs,
						interfaces
						)
			);*/

			typedef autoPtr<smoother>(*symMatrixConstructorPtr)(const word& fieldName, const lduMatrix& matrix,
				const FieldField<Field, scalar>& interfaceBouCoeffs,
				const FieldField<Field, scalar>& interfaceIntCoeffs,
				const lduInterfaceFieldPtrsList& interfaces);
			typedef HashTable<symMatrixConstructorPtr, word, string::hash> symMatrixConstructorTable;
			static FoamBase_EXPORT symMatrixConstructorTable* symMatrixConstructorTablePtr_;
			static FoamBase_EXPORT void constructsymMatrixConstructorTables();
			static FoamBase_EXPORT void destroysymMatrixConstructorTables();

			template <class smootherType>
			class addsymMatrixConstructorToTable
			{
			public:
				static autoPtr<smoother> New(const word& fieldName, const lduMatrix& matrix,
					const FieldField<Field, scalar>& interfaceBouCoeffs,
					const FieldField<Field, scalar>& interfaceIntCoeffs,
					const lduInterfaceFieldPtrsList& interfaces)
				{
					return autoPtr<smoother>(new smootherType(fieldName, matrix, interfaceBouCoeffs, interfaceIntCoeffs, interfaces));
				}

				addsymMatrixConstructorToTable(const word& lookup = smootherType::typeName)
				{
					constructsymMatrixConstructorTables();
					if (!symMatrixConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "smoother" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addsymMatrixConstructorToTable() { destroysymMatrixConstructorTables(); }
			};

			template <class smootherType>
			class addRemovablesymMatrixConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<smoother> New(const word& fieldName, const lduMatrix& matrix,
					const FieldField<Field, scalar>& interfaceBouCoeffs,
					const FieldField<Field, scalar>& interfaceIntCoeffs,
					const lduInterfaceFieldPtrsList& interfaces)
				{
					return autoPtr<smoother>(new smootherType(fieldName, matrix, interfaceBouCoeffs, interfaceIntCoeffs, interfaces));
				}

				addRemovablesymMatrixConstructorToTable(const word& lookup = smootherType::typeName) : lookup_(lookup)
				{
					constructsymMatrixConstructorTables();
					symMatrixConstructorTablePtr_->set(lookup, New);
				}

				~addRemovablesymMatrixConstructorToTable()
				{
					if (symMatrixConstructorTablePtr_) { symMatrixConstructorTablePtr_->erase(lookup_); }
				}
			};;

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				smoother,
				asymMatrix,
				(
					const word& fieldName,
					const lduMatrix& matrix,
					const FieldField<Field, scalar>& interfaceBouCoeffs,
					const FieldField<Field, scalar>& interfaceIntCoeffs,
					const lduInterfaceFieldPtrsList& interfaces
					),
					(
						fieldName,
						matrix,
						interfaceBouCoeffs,
						interfaceIntCoeffs,
						interfaces
						)
			);*/

			typedef autoPtr<smoother>(*asymMatrixConstructorPtr)(const word& fieldName, const lduMatrix& matrix,
				const FieldField<Field, scalar>& interfaceBouCoeffs,
				const FieldField<Field, scalar>& interfaceIntCoeffs,
				const lduInterfaceFieldPtrsList& interfaces);
			typedef HashTable<asymMatrixConstructorPtr, word, string::hash> asymMatrixConstructorTable;
			static FoamBase_EXPORT asymMatrixConstructorTable* asymMatrixConstructorTablePtr_;
			static FoamBase_EXPORT void constructasymMatrixConstructorTables();
			static FoamBase_EXPORT void destroyasymMatrixConstructorTables();

			template <class smootherType>
			class addasymMatrixConstructorToTable
			{
			public:
				static autoPtr<smoother> New(const word& fieldName, const lduMatrix& matrix,
					const FieldField<Field, scalar>& interfaceBouCoeffs,
					const FieldField<Field, scalar>& interfaceIntCoeffs,
					const lduInterfaceFieldPtrsList& interfaces)
				{
					return autoPtr<smoother>(new smootherType(fieldName, matrix, interfaceBouCoeffs, interfaceIntCoeffs, interfaces));
				}

				addasymMatrixConstructorToTable(const word& lookup = smootherType::typeName)
				{
					constructasymMatrixConstructorTables();
					if (!asymMatrixConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "smoother" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addasymMatrixConstructorToTable() { destroyasymMatrixConstructorTables(); }
			};

			template <class smootherType>
			class addRemovableasymMatrixConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<smoother> New(const word& fieldName, const lduMatrix& matrix,
					const FieldField<Field, scalar>& interfaceBouCoeffs,
					const FieldField<Field, scalar>& interfaceIntCoeffs,
					const lduInterfaceFieldPtrsList& interfaces)
				{
					return autoPtr<smoother>(new smootherType(fieldName, matrix, interfaceBouCoeffs, interfaceIntCoeffs, interfaces));
				}

				addRemovableasymMatrixConstructorToTable(const word& lookup = smootherType::typeName) : lookup_(lookup)
				{
					constructasymMatrixConstructorTables();
					asymMatrixConstructorTablePtr_->set(lookup, New);
				}

				~addRemovableasymMatrixConstructorToTable()
				{
					if (asymMatrixConstructorTablePtr_) { asymMatrixConstructorTablePtr_->erase(lookup_); }
				}
			};;


			// Constructors

			FoamBase_EXPORT smoother
			(
				const word& fieldName,
				const lduMatrix& matrix,
				const FieldField<Field, scalar>& interfaceBouCoeffs,
				const FieldField<Field, scalar>& interfaceIntCoeffs,
				const lduInterfaceFieldPtrsList& interfaces
			);


			// Selectors

				//- Return a new smoother
			static FoamBase_EXPORT autoPtr<smoother> New
			(
				const word& fieldName,
				const lduMatrix& matrix,
				const FieldField<Field, scalar>& interfaceBouCoeffs,
				const FieldField<Field, scalar>& interfaceIntCoeffs,
				const lduInterfaceFieldPtrsList& interfaces,
				const dictionary& solverControls
			);


			//- Destructor
			virtual ~smoother()
			{}


			// Member Functions

				// Access

			const word& fieldName() const
			{
				return fieldName_;
			}

			const lduMatrix& matrix() const
			{
				return matrix_;
			}

			const FieldField<Field, scalar>& interfaceBouCoeffs() const
			{
				return interfaceBouCoeffs_;
			}

			const FieldField<Field, scalar>& interfaceIntCoeffs() const
			{
				return interfaceIntCoeffs_;
			}

			const lduInterfaceFieldPtrsList& interfaces() const
			{
				return interfaces_;
			}


			//- Smooth the solution for a given number of sweeps
			FoamBase_EXPORT virtual void smooth
			(
				scalarField& psi,
				const scalarField& source,
				const direction cmpt,
				const label nSweeps
			) const = 0;
		};


		//- Abstract base-class for lduMatrix preconditioners
		class preconditioner
		{
		protected:

			// Protected data

				//- Reference to the base-solver this preconditioner is used with
			const solver& solver_;


		public:

			//- Find the preconditioner name (directly or from a sub-dictionary)
			static FoamBase_EXPORT word getName(const dictionary&);

			//- Runtime type information
			FoamBase_EXPORT virtual const word& type() const = 0;


			// Declare run-time constructor selection tables

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				preconditioner,
				symMatrix,
				(
					const solver& sol,
					const dictionary& solverControls
					),
					(sol, solverControls)
			);*/

			typedef autoPtr<preconditioner>(*symMatrixConstructorPtr)(const solver& sol, const dictionary& solverControls);
			typedef HashTable<symMatrixConstructorPtr, word, string::hash> symMatrixConstructorTable;
			static FoamBase_EXPORT symMatrixConstructorTable* symMatrixConstructorTablePtr_;
			static FoamBase_EXPORT void constructsymMatrixConstructorTables();
			static FoamBase_EXPORT void destroysymMatrixConstructorTables();

			template <class preconditionerType>
			class addsymMatrixConstructorToTable
			{
			public:
				static autoPtr<preconditioner> New(const solver& sol, const dictionary& solverControls)
				{
					return autoPtr<preconditioner>(new preconditionerType(sol, solverControls));
				}

				addsymMatrixConstructorToTable(const word& lookup = preconditionerType::typeName)
				{
					constructsymMatrixConstructorTables();
					if (!symMatrixConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "preconditioner" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addsymMatrixConstructorToTable() { destroysymMatrixConstructorTables(); }
			};

			template <class preconditionerType>
			class addRemovablesymMatrixConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<preconditioner> New(const solver& sol, const dictionary& solverControls)
				{
					return autoPtr<preconditioner>(new preconditionerType(sol, solverControls));
				}

				addRemovablesymMatrixConstructorToTable(const word& lookup = preconditionerType::typeName) : lookup_(lookup)
				{
					constructsymMatrixConstructorTables();
					symMatrixConstructorTablePtr_->set(lookup, New);
				}

				~addRemovablesymMatrixConstructorToTable()
				{
					if (symMatrixConstructorTablePtr_) { symMatrixConstructorTablePtr_->erase(lookup_); }
				}
			};;

			/*declareRunTimeSelectionTable
			(
				autoPtr,
				preconditioner,
				asymMatrix,
				(
					const solver& sol,
					const dictionary& solverControls
					),
					(sol, solverControls)
			);*/

			typedef autoPtr<preconditioner>(*asymMatrixConstructorPtr)(const solver& sol, const dictionary& solverControls);
			typedef HashTable<asymMatrixConstructorPtr, word, string::hash> asymMatrixConstructorTable;
			static FoamBase_EXPORT asymMatrixConstructorTable* asymMatrixConstructorTablePtr_;
			static FoamBase_EXPORT void constructasymMatrixConstructorTables();
			static FoamBase_EXPORT void destroyasymMatrixConstructorTables();

			template <class preconditionerType>
			class addasymMatrixConstructorToTable
			{
			public:
				static autoPtr<preconditioner> New(const solver& sol, const dictionary& solverControls)
				{
					return autoPtr<preconditioner>(new preconditionerType(sol, solverControls));
				}

				addasymMatrixConstructorToTable(const word& lookup = preconditionerType::typeName)
				{
					constructasymMatrixConstructorTables();
					if (!asymMatrixConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "preconditioner" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addasymMatrixConstructorToTable() { destroyasymMatrixConstructorTables(); }
			};

			template <class preconditionerType>
			class addRemovableasymMatrixConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<preconditioner> New(const solver& sol, const dictionary& solverControls)
				{
					return autoPtr<preconditioner>(new preconditionerType(sol, solverControls));
				}

				addRemovableasymMatrixConstructorToTable(const word& lookup = preconditionerType::typeName) : lookup_(lookup)
				{
					constructasymMatrixConstructorTables();
					asymMatrixConstructorTablePtr_->set(lookup, New);
				}

				~addRemovableasymMatrixConstructorToTable()
				{
					if (asymMatrixConstructorTablePtr_) { asymMatrixConstructorTablePtr_->erase(lookup_); }
				}
			};;


			// Constructors

			preconditioner
			(
				const solver& sol
			)
				:
				solver_(sol)
			{}


			// Selectors

				//- Return a new preconditioner
			static FoamBase_EXPORT autoPtr<preconditioner> New
			(
				const solver& sol,
				const dictionary& solverControls
			);


			//- Destructor
			virtual ~preconditioner()
			{}


			// Member Functions

				//- Read and reset the preconditioner parameters
				//  from the given stream
			virtual void read(const dictionary&)
			{}

			//- Return wA the preconditioned form of residual rA
			FoamBase_EXPORT virtual void precondition
			(
				scalarField& wA,
				const scalarField& rA,
				const direction cmpt = 0
			) const = 0;

			//- Return wT the transpose-matrix preconditioned form of
			//  residual rT.
			//  This is only required for preconditioning asymmetric matrices.
			virtual void preconditionT
			(
				scalarField& wT,
				const scalarField& rT,
				const direction cmpt = 0
			) const
			{
				NotImplemented;
			}
		};


		// Static data

			// Declare name of the class and its debug switch
		//ClassName("lduMatrix");
		static const char* typeName_() { return "lduMatrix"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;


		// Constructors

			//- Construct given an LDU addressed mesh.
			//  The coefficients are initially empty for subsequent setting.
		FoamBase_EXPORT lduMatrix(const lduMesh&);

		//- Copy constructor
		FoamBase_EXPORT lduMatrix(const lduMatrix&);

		//- Copy constructor or re-use as specified.
		FoamBase_EXPORT lduMatrix(lduMatrix&, bool reuse);

		//- Construct given an LDU addressed mesh and an Istream
		//  from which the coefficients are read
		FoamBase_EXPORT lduMatrix(const lduMesh&, Istream&);


		//- Destructor
		FoamBase_EXPORT ~lduMatrix();


		// Member Functions

			// Access to addressing

				//- Return the LDU mesh from which the addressing is obtained
		const lduMesh& mesh() const
		{
			return lduMesh_;
		}

		//- Return the LDU addressing
		const lduAddressing& lduAddr() const
		{
			return lduMesh_.lduAddr();
		}

		//- Return the patch evaluation schedule
		const lduSchedule& patchSchedule() const
		{
			return lduAddr().patchSchedule();
		}


		// Access to coefficients

		FoamBase_EXPORT scalarField& lower();
		FoamBase_EXPORT scalarField& diag();
		FoamBase_EXPORT scalarField& upper();

		// Size with externally provided sizes (for constructing with 'fake'
		// mesh in GAMG)

		FoamBase_EXPORT scalarField& lower(const label size);
		FoamBase_EXPORT scalarField& diag(const label nCoeffs);
		FoamBase_EXPORT scalarField& upper(const label nCoeffs);


		FoamBase_EXPORT const scalarField& lower() const;
		FoamBase_EXPORT const scalarField& diag() const;
		FoamBase_EXPORT const scalarField& upper() const;

		bool hasDiag() const
		{
			return (diagPtr_);
		}

		bool hasUpper() const
		{
			return (upperPtr_);
		}

		bool hasLower() const
		{
			return (lowerPtr_);
		}

		bool diagonal() const
		{
			return (diagPtr_ && !lowerPtr_ && !upperPtr_);
		}

		bool symmetric() const
		{
			return (diagPtr_ && (!lowerPtr_ && upperPtr_));
		}

		bool asymmetric() const
		{
			return (diagPtr_ && lowerPtr_ && upperPtr_);
		}


		// operations

		FoamBase_EXPORT void sumDiag();
		FoamBase_EXPORT void negSumDiag();

		FoamBase_EXPORT void sumMagOffDiag(scalarField& sumOff) const;

		//- Matrix multiplication with updated interfaces.
		FoamBase_EXPORT void Amul
		(
			scalarField&,
			const tmp<scalarField>&,
			const FieldField<Field, scalar>&,
			const lduInterfaceFieldPtrsList&,
			const direction cmpt
		) const;

		//- Matrix transpose multiplication with updated interfaces.
		FoamBase_EXPORT void Tmul
		(
			scalarField&,
			const tmp<scalarField>&,
			const FieldField<Field, scalar>&,
			const lduInterfaceFieldPtrsList&,
			const direction cmpt
		) const;


		//- Sum the coefficients on each row of the matrix
		FoamBase_EXPORT void sumA
		(
			scalarField&,
			const FieldField<Field, scalar>&,
			const lduInterfaceFieldPtrsList&
		) const;


		FoamBase_EXPORT void residual
		(
			scalarField& rA,
			const scalarField& psi,
			const scalarField& source,
			const FieldField<Field, scalar>& interfaceBouCoeffs,
			const lduInterfaceFieldPtrsList& interfaces,
			const direction cmpt
		) const;

		FoamBase_EXPORT tmp<scalarField> residual
		(
			const scalarField& psi,
			const scalarField& source,
			const FieldField<Field, scalar>& interfaceBouCoeffs,
			const lduInterfaceFieldPtrsList& interfaces,
			const direction cmpt
		) const;


		//- Initialise the update of interfaced interfaces
		//  for matrix operations
		FoamBase_EXPORT void initMatrixInterfaces
		(
			const FieldField<Field, scalar>& interfaceCoeffs,
			const lduInterfaceFieldPtrsList& interfaces,
			const scalarField& psiif,
			scalarField& result,
			const direction cmpt
		) const;

		//- Update interfaced interfaces for matrix operations
		FoamBase_EXPORT void updateMatrixInterfaces
		(
			const FieldField<Field, scalar>& interfaceCoeffs,
			const lduInterfaceFieldPtrsList& interfaces,
			const scalarField& psiif,
			scalarField& result,
			const direction cmpt
		) const;


		template<class Type>
		tmp<Field<Type>> H(const Field<Type>&) const;

		template<class Type>
		tmp<Field<Type>> H(const tmp<Field<Type>>&) const;

		FoamBase_EXPORT tmp<scalarField> H1() const;

		template<class Type>
		tmp<Field<Type>> faceH(const Field<Type>&) const;

		template<class Type>
		tmp<Field<Type>> faceH(const tmp<Field<Type>>&) const;


		// Info

			//- Return info proxy.
			//  Used to print matrix information to a stream
		InfoProxy<lduMatrix> info() const
		{
			return *this;
		}


		// Member Operators

		FoamBase_EXPORT void operator=(const lduMatrix&);

		FoamBase_EXPORT void negate();

		FoamBase_EXPORT void operator+=(const lduMatrix&);
		FoamBase_EXPORT void operator-=(const lduMatrix&);

		FoamBase_EXPORT void operator*=(const scalarField&);
		FoamBase_EXPORT void operator*=(scalar);


		// Ostream operator

		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const lduMatrix&);
		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const InfoProxy<lduMatrix>&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <lduMatrixTemplates_Imp.hxx>

//#ifdef NoRepository
//#include <lduMatrixTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_lduMatrix_Header
