#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::pointToPointPlanarInterpolation::interpolate
(
	const Field<Type>& sourceFld
) const
{
	if (nPoints_ != sourceFld.size())
	{
		FatalErrorInFunction
			<< "Number of source points = " << nPoints_
			<< " number of values = " << sourceFld.size()
			<< exit(FatalError);
	}

	tmp<Field<Type>> tfld(new Field<Type>(nearestVertex_.size()));
	Field<Type>& fld = tfld.ref();

	forAll(fld, i)
	{
		const FixedList<label, 3>& verts = nearestVertex_[i];
		const FixedList<scalar, 3>& w = nearestVertexWeight_[i];

		if (verts[2] == -1)
		{
			if (verts[1] == -1)
			{
				// Use vertex0 only
				fld[i] = sourceFld[verts[0]];
			}
			else
			{
				// Use vertex 0,1
				fld[i] =
					w[0] * sourceFld[verts[0]]
					+ w[1] * sourceFld[verts[1]];
			}
		}
		else
		{
			fld[i] =
				w[0] * sourceFld[verts[0]]
				+ w[1] * sourceFld[verts[1]]
				+ w[2] * sourceFld[verts[2]];
		}
	}
	return tfld;
}


// ************************************************************************* //