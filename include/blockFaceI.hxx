#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::face& tnbLib::blockFace::vertices() const
{
	return vertices_;
}


inline bool tnbLib::blockFace::compare(const blockFace& bf) const
{
	return compare(bf.vertices());
}


inline bool tnbLib::blockFace::compare(const face& vertices) const
{
	return face::sameVertices(vertices_, vertices);
}


// ************************************************************************* //