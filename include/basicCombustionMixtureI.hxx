#pragma once
inline tnbLib::scalar tnbLib::basicCombustionMixture::fres
(
	const scalar ft,
	const scalar stoicRatio
) const
{
	return max(ft - (scalar(1) - ft) / stoicRatio, scalar(0));
}


inline tnbLib::tmp<tnbLib::volScalarField> tnbLib::basicCombustionMixture::fres
(
	const volScalarField& ft,
	const dimensionedScalar& stoicRatio
) const
{
	return max(ft - (scalar(1) - ft) / stoicRatio.value(), scalar(0));
}


// ************************************************************************* //