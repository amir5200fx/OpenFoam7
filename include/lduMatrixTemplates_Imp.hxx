#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::lduMatrix::H(const Field<Type>& psi) const
{
	tmp<Field<Type>> tHpsi
	(
		new Field<Type>(lduAddr().size(), Zero)
	);

	if (lowerPtr_ || upperPtr_)
	{
		Field<Type> & Hpsi = tHpsi.ref();

		Type* __restrict HpsiPtr = Hpsi.begin();

		const Type* __restrict psiPtr = psi.begin();

		const label* __restrict uPtr = lduAddr().upperAddr().begin();
		const label* __restrict lPtr = lduAddr().lowerAddr().begin();

		const scalar* __restrict lowerPtr = lower().begin();
		const scalar* __restrict upperPtr = upper().begin();

		const label nFaces = upper().size();

		for (label face = 0; face < nFaces; face++)
		{
			HpsiPtr[uPtr[face]] -= lowerPtr[face] * psiPtr[lPtr[face]];
			HpsiPtr[lPtr[face]] -= upperPtr[face] * psiPtr[uPtr[face]];
		}
	}

	return tHpsi;
}

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::lduMatrix::H(const tmp<Field<Type>>& tpsi) const
{
	tmp<Field<Type>> tHpsi(H(tpsi()));
	tpsi.clear();
	return tHpsi;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::lduMatrix::faceH(const Field<Type>& psi) const
{
	if (lowerPtr_ || upperPtr_)
	{
		const scalarField& Lower = const_cast<const lduMatrix&>(*this).lower();
		const scalarField& Upper = const_cast<const lduMatrix&>(*this).upper();

		const labelUList& l = lduAddr().lowerAddr();
		const labelUList& u = lduAddr().upperAddr();

		tmp<Field<Type>> tfaceHpsi(new Field<Type>(Lower.size()));
		Field<Type> & faceHpsi = tfaceHpsi.ref();

		for (label face = 0; face < l.size(); face++)
		{
			faceHpsi[face] =
				Upper[face] * psi[u[face]]
				- Lower[face] * psi[l[face]];
		}

		return tfaceHpsi;
	}
	else
	{
		FatalErrorInFunction
			<< "Cannot calculate faceH"
			" the matrix does not have any off-diagonal coefficients."
			<< exit(FatalError);

		return tmp<Field<Type>>(nullptr);
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::lduMatrix::faceH(const tmp<Field<Type>>& tpsi) const
{
	tmp<Field<Type>> tfaceHpsi(faceH(tpsi()));
	tpsi.clear();
	return tfaceHpsi;
}


// ************************************************************************* //