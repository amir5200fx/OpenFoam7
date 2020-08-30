#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::pointField& tnbLib::referredWallFace::points() const
{
	return pts_;
}


tnbLib::pointField& tnbLib::referredWallFace::points()
{
	return pts_;
}


tnbLib::label tnbLib::referredWallFace::patchIndex() const
{
	return patchi_;
}


tnbLib::label& tnbLib::referredWallFace::patchIndex()
{
	return patchi_;
}


// ************************************************************************* //