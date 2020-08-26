#pragma once
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline const tnbLib::fvMesh&
tnbLib::regionModels::regionModel::primaryMesh() const
{
	return primaryMesh_;
}


inline const tnbLib::Time& tnbLib::regionModels::regionModel::time() const
{
	return time_;
}


inline const tnbLib::Switch& tnbLib::regionModels::regionModel::active() const
{
	return active_;
}


inline const tnbLib::Switch& tnbLib::regionModels::regionModel::infoOutput() const
{
	return infoOutput_;
}


inline const tnbLib::word& tnbLib::regionModels::regionModel::modelName() const
{
	return modelName_;
}


inline const tnbLib::fvMesh& tnbLib::regionModels::regionModel::regionMesh() const
{
	if (time_.foundObject<fvMesh>(regionName_))
	{
		return time_.lookupObject<fvMesh>(regionName_);
	}
	else if (!regionMeshPtr_.valid())
	{
		FatalErrorInFunction
			<< "Region mesh not available" << abort(FatalError);
	}

	return regionMeshPtr_();
}


inline tnbLib::fvMesh& tnbLib::regionModels::regionModel::regionMesh()
{
	if (time_.foundObject<fvMesh>(regionName_))
	{
		return const_cast<fvMesh&>
			(
				time_.lookupObject<fvMesh>(regionName_)
				);
	}
	else if (!regionMeshPtr_.valid())
	{
		FatalErrorInFunction
			<< "Region mesh not available" << abort(FatalError);
	}

	return regionMeshPtr_();
}


inline const tnbLib::dictionary& tnbLib::regionModels::regionModel::coeffs() const
{
	return coeffs_;
}


inline const tnbLib::dictionary&
tnbLib::regionModels::regionModel::solution() const
{
	return regionMesh().solutionDict();
}


inline const tnbLib::IOdictionary&
tnbLib::regionModels::regionModel::outputProperties() const
{
	if (!outputPropertiesPtr_.valid())
	{
		FatalErrorInFunction
			<< "outputProperties dictionary not available"
			<< abort(FatalError);
	}

	return outputPropertiesPtr_();
}


inline tnbLib::IOdictionary&
tnbLib::regionModels::regionModel::outputProperties()
{
	if (!outputPropertiesPtr_.valid())
	{
		FatalErrorInFunction
			<< "outputProperties dictionary not available"
			<< abort(FatalError);
	}

	return outputPropertiesPtr_();
}


inline bool tnbLib::regionModels::regionModel::isCoupledPatch
(
	const label regionPatchi
) const
{
	forAll(intCoupledPatchIDs_, i)
	{
		if (intCoupledPatchIDs_[i] == regionPatchi)
		{
			return true;
		}
	}

	return false;
}


inline bool tnbLib::regionModels::regionModel::isRegionPatch
(
	const label primaryPatchi
) const
{
	forAll(primaryPatchIDs_, i)
	{
		if (primaryPatchIDs_[i] == primaryPatchi)
		{
			return true;
		}
	}

	return false;
}


inline const tnbLib::labelList&
tnbLib::regionModels::regionModel::primaryPatchIDs() const
{
	return primaryPatchIDs_;
}


inline const tnbLib::labelList&
tnbLib::regionModels::regionModel::intCoupledPatchIDs() const
{
	return intCoupledPatchIDs_;
}


inline tnbLib::label tnbLib::regionModels::regionModel::regionPatchID
(
	const label primaryPatchID
) const
{
	forAll(primaryPatchIDs_, i)
	{
		if (primaryPatchIDs_[i] == primaryPatchID)
		{
			return intCoupledPatchIDs_[i];
		}
	}

	return -1;
}


// ************************************************************************* //