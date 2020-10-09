#pragma once
#ifndef _ILUPreconditioner_Header
#define _ILUPreconditioner_Header

#include <lduMatrix.hxx>

#include <tuple>

namespace tnbLib
{

	class ILUPreconditioner
		: public lduMatrix::preconditioner
	{

		/*Private Data*/

		//- The reciprocal preconditioned diagonal
		scalarField rD_;
		scalarField rL_;

	public:

		//- Runtime type information
		TypeName("ILU");

		// Constructors

			//- Construct from matrix components and preconditioner solver controls
		ILUPreconditioner
		(
			const lduMatrix::solver&,
			const dictionary& solverControlsUnused
		);


		//- Destructor
		virtual ~ILUPreconditioner()
		{}

		// Member Functions

		static std::tuple<bool, label> 
			isZero
			(
				const label row, 
				const label start, const label end,
				const labelUList& addr
			);

		static scalar 
			multiplyInColumn
			(
				const label i, const label j,
				const label start, const label end,
				const scalarField& rL, const labelUList& addr
			);

		//- Calculate the reciprocal of the preconditioned diagonal
		static void calcReciprocalLD(scalarField& rD, scalarField& rL, const lduMatrix& matrix);

		//- Return wA the preconditioned form of residual rA
		virtual void precondition
		(
			scalarField& wA,
			const scalarField& rA,
			const direction cmpt = 0
		) const;

		//- Return wT the transpose-matrix preconditioned form of residual rT.
		virtual void preconditionT
		(
			scalarField& wT,
			const scalarField& rT,
			const direction cmpt = 0
		) const;
	};
}

#endif // !_ILUPreconditioner_Header
