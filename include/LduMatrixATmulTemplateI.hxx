#pragma once
#include <LduInterfaceFieldPtrsListTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<class Type, class LUType>
	class Amultiplier
		:
		public LduInterfaceField<Type>::Amultiplier
	{
		const Field<LUType>& A_;

	public:

		Amultiplier(const Field<LUType>& A)
			:
			A_(A)
		{}

		virtual ~Amultiplier()
		{}

		virtual void addAmul(Field<Type>& Apsi, const Field<Type>& psi) const
		{
			Apsi += A_ * psi;
		}
	};

}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
void tnbLib::LduMatrix<Type, DType, LUType>::Amul
(
	Field<Type>& Apsi,
	const tmp<Field<Type>>& tpsi
) const
{
	Type* __restrict ApsiPtr = Apsi.begin();

	const Field<Type>& psi = tpsi();
	const Type* const __restrict psiPtr = psi.begin();

	const DType* const __restrict diagPtr = diag().begin();

	const label* const __restrict uPtr = lduAddr().upperAddr().begin();
	const label* const __restrict lPtr = lduAddr().lowerAddr().begin();

	const LUType* const __restrict upperPtr = upper().begin();
	const LUType* const __restrict lowerPtr = lower().begin();

	// Initialise the update of interfaced interfaces
	initMatrixInterfaces
	(
		interfacesUpper_,
		psi,
		Apsi
	);

	const label nCells = diag().size();
	for (label cell = 0; cell < nCells; cell++)
	{
		ApsiPtr[cell] = dot(diagPtr[cell], psiPtr[cell]);
	}


	const label nFaces = upper().size();
	for (label face = 0; face < nFaces; face++)
	{
		ApsiPtr[uPtr[face]] += dot(lowerPtr[face], psiPtr[lPtr[face]]);
		ApsiPtr[lPtr[face]] += dot(upperPtr[face], psiPtr[uPtr[face]]);
	}

	// Update interface interfaces
	updateMatrixInterfaces
	(
		interfacesUpper_,
		psi,
		Apsi
	);

	tpsi.clear();
}


template<class Type, class DType, class LUType>
void tnbLib::LduMatrix<Type, DType, LUType>::Tmul
(
	Field<Type>& Tpsi,
	const tmp<Field<Type>>& tpsi
) const
{
	Type* __restrict TpsiPtr = Tpsi.begin();

	const Field<Type>& psi = tpsi();
	const Type* const __restrict psiPtr = psi.begin();

	const DType* const __restrict diagPtr = diag().begin();

	const label* const __restrict uPtr = lduAddr().upperAddr().begin();
	const label* const __restrict lPtr = lduAddr().lowerAddr().begin();

	const LUType* const __restrict lowerPtr = lower().begin();
	const LUType* const __restrict upperPtr = upper().begin();

	// Initialise the update of interfaced interfaces
	initMatrixInterfaces
	(
		interfacesLower_,
		psi,
		Tpsi
	);

	const label nCells = diag().size();
	for (label cell = 0; cell < nCells; cell++)
	{
		TpsiPtr[cell] = dot(diagPtr[cell], psiPtr[cell]);
	}

	const label nFaces = upper().size();
	for (label face = 0; face < nFaces; face++)
	{
		TpsiPtr[uPtr[face]] += dot(upperPtr[face], psiPtr[lPtr[face]]);
		TpsiPtr[lPtr[face]] += dot(lowerPtr[face], psiPtr[uPtr[face]]);
	}

	// Update interface interfaces
	updateMatrixInterfaces
	(
		interfacesLower_,
		psi,
		Tpsi
	);

	tpsi.clear();
}


template<class Type, class DType, class LUType>
void tnbLib::LduMatrix<Type, DType, LUType>::sumA
(
	Field<Type>& sumA
) const
{
	Type* __restrict sumAPtr = sumA.begin();

	const DType* __restrict diagPtr = diag().begin();

	const label* __restrict uPtr = lduAddr().upperAddr().begin();
	const label* __restrict lPtr = lduAddr().lowerAddr().begin();

	const LUType* __restrict lowerPtr = lower().begin();
	const LUType* __restrict upperPtr = upper().begin();

	const label nCells = diag().size();
	const label nFaces = upper().size();

	for (label cell = 0; cell < nCells; cell++)
	{
		sumAPtr[cell] = dot(diagPtr[cell], pTraits<Type>::one);
	}

	for (label face = 0; face < nFaces; face++)
	{
		sumAPtr[uPtr[face]] += dot(lowerPtr[face], pTraits<Type>::one);
		sumAPtr[lPtr[face]] += dot(upperPtr[face], pTraits<Type>::one);
	}

	// Add the interface internal coefficients to diagonal
	// and the interface boundary coefficients to the sum-off-diagonal
	forAll(interfaces_, patchi)
	{
		if (interfaces_.set(patchi))
		{
			const unallocLabelList& pa = lduAddr().patchAddr(patchi);
			const Field<LUType>& pCoeffs = interfacesUpper_[patchi];

			forAll(pa, face)
			{
				sumAPtr[pa[face]] -= dot(pCoeffs[face], pTraits<Type>::one);
			}
		}
	}
}


template<class Type, class DType, class LUType>
void tnbLib::LduMatrix<Type, DType, LUType>::residual
(
	Field<Type>& rA,
	const Field<Type>& psi
) const
{
	Type* __restrict rAPtr = rA.begin();

	const Type* const __restrict psiPtr = psi.begin();
	const DType* const __restrict diagPtr = diag().begin();
	const Type* const __restrict sourcePtr = source().begin();

	const label* const __restrict uPtr = lduAddr().upperAddr().begin();
	const label* const __restrict lPtr = lduAddr().lowerAddr().begin();

	const LUType* const __restrict upperPtr = upper().begin();
	const LUType* const __restrict lowerPtr = lower().begin();

	// Parallel boundary initialisation.
	// Note: there is a change of sign in the coupled
	// interface update to add the contibution to the r.h.s.

	FieldField<Field, LUType> mBouCoeffs(interfacesUpper_.size());

	forAll(mBouCoeffs, patchi)
	{
		if (interfaces_.set(patchi))
		{
			mBouCoeffs.set(patchi, -interfacesUpper_[patchi]);
		}
	}

	// Initialise the update of interfaced interfaces
	initMatrixInterfaces
	(
		mBouCoeffs,
		psi,
		rA
	);

	const label nCells = diag().size();
	for (label cell = 0; cell < nCells; cell++)
	{
		rAPtr[cell] = sourcePtr[cell] - dot(diagPtr[cell], psiPtr[cell]);
	}


	const label nFaces = upper().size();
	for (label face = 0; face < nFaces; face++)
	{
		rAPtr[uPtr[face]] -= dot(lowerPtr[face], psiPtr[lPtr[face]]);
		rAPtr[lPtr[face]] -= dot(upperPtr[face], psiPtr[uPtr[face]]);
	}

	// Update interface interfaces
	updateMatrixInterfaces
	(
		mBouCoeffs,
		psi,
		rA
	);
}


template<class Type, class DType, class LUType>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::LduMatrix<Type, DType, LUType>::residual
(
	const Field<Type>& psi
) const
{
	tmp<Field<Type>> trA(new Field<Type>(psi.size()));
	residual(trA.ref(), psi);
	return trA;
}


// ************************************************************************* //