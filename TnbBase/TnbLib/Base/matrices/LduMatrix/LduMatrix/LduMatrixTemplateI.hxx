#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
template<class T>
inline void tnbLib::LduMatrix<Type, DType, LUType>::solver::readControl
(
	const dictionary& controlDict,
	T& control,
	const word& controlName
)
{
	if (controlDict.found(controlName))
	{
		controlDict.lookup(controlName) >> control;
	}
}


// ************************************************************************* //