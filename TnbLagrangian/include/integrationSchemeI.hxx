#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline Type tnbLib::integrationScheme::explicitDelta
(
	const Type& phi,
	const scalar dtEff,
	const Type& Alpha,
	const scalar Beta
)
{
	return (Alpha - Beta * phi)*dtEff;
}


template<class Type>
inline Type tnbLib::integrationScheme::delta
(
	const Type& phi,
	const scalar dt,
	const Type& Alpha,
	const scalar Beta
) const
{
	return explicitDelta(phi, dtEff(dt, Beta), Alpha, Beta);
}


template<class Type>
inline Type tnbLib::integrationScheme::partialDelta
(
	const Type& phi,
	const scalar dt,
	const Type& Alpha,
	const scalar Beta,
	const Type& alphai,
	const scalar betai
) const
{
	return
		explicitDelta(phi, dt, alphai, betai)
		- explicitDelta(phi, sumDtEff(dt, Beta), Alpha, Beta)*betai;
}


// ************************************************************************* //