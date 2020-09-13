#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline const tnbLib::labelListList&
tnbLib::regionModels::regionModel1D::boundaryFaceFaces() const
{
	return boundaryFaceFaces_;
}


inline const tnbLib::labelListList&
tnbLib::regionModels::regionModel1D::boundaryFaceCells() const
{
	return boundaryFaceCells_;
}


inline const tnbLib::labelList&
tnbLib::regionModels::regionModel1D::boundaryFaceOppositeFace() const
{
	return boundaryFaceOppositeFace_;
}


inline const tnbLib::surfaceScalarField&
tnbLib::regionModels::regionModel1D::nMagSf() const
{
	if (!nMagSfPtr_.valid())
	{
		FatalErrorInFunction
			<< "Face normal areas not available" << abort(FatalError);
	}

	return nMagSfPtr_();
}


inline tnbLib::label tnbLib::regionModels::regionModel1D::nLayers() const
{
	return nLayers_;
}


// ************************************************************************* //