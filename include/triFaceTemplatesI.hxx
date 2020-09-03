#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
Type tnbLib::triFace::average
(
	const pointField& meshPoints,
	const Field<Type>& fld
) const
{
	// a triangle, do a direct calculation
	return
		(
		(1.0 / 3.0)
			*
			(
				fld[operator[](0)]
				+ fld[operator[](1)]
				+ fld[operator[](2)]
				)
			);
}

// ************************************************************************* //