#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline Type tnbLib::interpolationPointMVC<Type>::interpolate
(
	const pointMVCWeight& cpw
) const
{
	return cpw.interpolate(psip_);
}


template<class Type>
inline Type tnbLib::interpolationPointMVC<Type>::interpolate
(
	const vector& position,
	const label celli,
	const label facei
) const
{
	return interpolate
	(
		pointMVCWeight(this->pMesh_, position, celli, facei)
	);
}


// ************************************************************************* //