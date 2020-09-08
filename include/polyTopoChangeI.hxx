#pragma once
#include <face.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline bool tnbLib::polyTopoChange::pointRemoved(const label pointi) const
{
	const point& pt = points_[pointi];

	return
		pt.x() > 0.5*vector::max.x()
		&& pt.y() > 0.5*vector::max.y()
		&& pt.z() > 0.5*vector::max.z();
}


inline bool tnbLib::polyTopoChange::faceRemoved(const label facei) const
{
	return faces_[facei].empty();
}


inline bool tnbLib::polyTopoChange::cellRemoved(const label celli) const
{
	return cellMap_[celli] == -2;
}


inline void tnbLib::polyTopoChange::setNumPatches(const label nPatches)
{
	nPatches_ = nPatches;
}


// ************************************************************************* //