#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline const tnbLib::word&
tnbLib::fv::interRegionOption::nbrRegionName() const
{
	return nbrRegionName_;
}


inline const tnbLib::meshToMesh&
tnbLib::fv::interRegionOption::meshInterp() const
{
	if (!meshInterpPtr_.valid())
	{
		FatalErrorInFunction
			<< "Interpolation object not set"
			<< abort(FatalError);
	}

	return meshInterpPtr_();
}



// ************************************************************************* //