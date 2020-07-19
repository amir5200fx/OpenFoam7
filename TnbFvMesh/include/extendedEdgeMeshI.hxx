#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::label tnbLib::extendedEdgeMesh::convexStart() const
{
	return convexStart_;
}


inline tnbLib::label tnbLib::extendedEdgeMesh::concaveStart() const
{
	return concaveStart_;
}


inline tnbLib::label tnbLib::extendedEdgeMesh::mixedStart() const
{
	return mixedStart_;
}


inline tnbLib::label tnbLib::extendedEdgeMesh::nonFeatureStart() const
{
	return nonFeatureStart_;
}


inline tnbLib::label tnbLib::extendedEdgeMesh::externalStart() const
{
	return externalStart_;
}


inline tnbLib::label tnbLib::extendedEdgeMesh::internalStart() const
{
	return internalStart_;
}


inline tnbLib::label tnbLib::extendedEdgeMesh::flatStart() const
{
	return flatStart_;
}


inline tnbLib::label tnbLib::extendedEdgeMesh::openStart() const
{
	return openStart_;
}


inline tnbLib::label tnbLib::extendedEdgeMesh::multipleStart() const
{
	return multipleStart_;
}


inline bool tnbLib::extendedEdgeMesh::featurePoint(label ptI) const
{
	return ptI < nonFeatureStart_;
}


inline const tnbLib::vectorField& tnbLib::extendedEdgeMesh::normals() const
{
	return normals_;
}


inline const tnbLib::List<tnbLib::extendedEdgeMesh::sideVolumeType>&
tnbLib::extendedEdgeMesh::normalVolumeTypes() const
{
	return normalVolumeTypes_;
}


inline const tnbLib::vectorField& tnbLib::extendedEdgeMesh::edgeDirections()
const
{
	return edgeDirections_;
}


inline const tnbLib::labelListList&
tnbLib::extendedEdgeMesh::normalDirections() const
{
	return normalDirections_;
}


inline tnbLib::vector tnbLib::extendedEdgeMesh::edgeDirection
(
	label edgeI,
	label ptI
) const
{
	const edge& e = edges()[edgeI];

	if (ptI == e.start())
	{
		return edgeDirections()[edgeI];
	}
	else if (ptI == e.end())
	{
		return -edgeDirections()[edgeI];
	}
	else
	{
		FatalErrorInFunction
			<< "Requested ptI " << ptI << " is not a point on the requested "
			<< "edgeI " << edgeI << ". edgeI start and end: "
			<< e.start() << " " << e.end()
			<< exit(FatalError);

		return Zero;
	}
}


inline const tnbLib::labelListList& tnbLib::extendedEdgeMesh::edgeNormals()
const
{
	return edgeNormals_;
}


inline tnbLib::vectorField tnbLib::extendedEdgeMesh::edgeNormals
(
	const labelList& edgeNormIs
) const
{
	vectorField norms(edgeNormIs.size());

	forAll(edgeNormIs, i)
	{
		norms[i] = normals_[edgeNormIs[i]];
	}

	return norms;
}


inline tnbLib::vectorField tnbLib::extendedEdgeMesh::edgeNormals(label edgeI)
const
{
	return edgeNormals(edgeNormals_[edgeI]);
}


inline const tnbLib::labelListList&
tnbLib::extendedEdgeMesh::featurePointNormals() const
{
	return featurePointNormals_;
}


inline tnbLib::vectorField tnbLib::extendedEdgeMesh::featurePointNormals
(
	label ptI
) const
{
	if (!featurePoint(ptI))
	{
		WarningInFunction
			<< "Requesting the normals of a non-feature point. "
			<< "Returned zero length vectorField."
			<< endl;

		return vectorField(0);
	}

	labelList featPtNormIs(featurePointNormals_[ptI]);

	vectorField norms(featPtNormIs.size());

	forAll(featPtNormIs, i)
	{
		norms[i] = normals_[featPtNormIs[i]];
	}

	return norms;
}


inline const tnbLib::labelListList&
tnbLib::extendedEdgeMesh::featurePointEdges() const
{
	return featurePointEdges_;
}


inline const tnbLib::labelList& tnbLib::extendedEdgeMesh::regionEdges() const
{
	return regionEdges_;
}


inline tnbLib::extendedEdgeMesh::pointStatus
tnbLib::extendedEdgeMesh::getPointStatus(label ptI) const
{
	if (ptI < concaveStart_)
	{
		return CONVEX;
	}
	else if (ptI < mixedStart_)
	{
		return CONCAVE;
	}
	else if (ptI < nonFeatureStart_)
	{
		return MIXED;
	}
	else
	{
		return NONFEATURE;
	}
}


inline tnbLib::extendedEdgeMesh::edgeStatus
tnbLib::extendedEdgeMesh::getEdgeStatus(label edgeI) const
{
	if (edgeI < internalStart_)
	{
		return EXTERNAL;
	}
	else if (edgeI < flatStart_)
	{
		return INTERNAL;
	}
	else if (edgeI < openStart_)
	{
		return FLAT;
	}
	else if (edgeI < multipleStart_)
	{
		return OPEN;
	}
	else
	{
		return MULTIPLE;
	}
}


inline tnbLib::PackedList<2> tnbLib::extendedEdgeMesh::edgeBaffles
(
	label edgeI
) const
{
	const labelList& eNormals = edgeNormals_[edgeI];

	DynamicList<label> edgeBaffles(eNormals.size());

	forAll(eNormals, enI)
	{
		const label normI = eNormals[enI];

		if (normalVolumeTypes_[normI])
		{
			edgeBaffles.append(normI);
		}
	}

	return PackedList<2>(edgeBaffles);
}


// ************************************************************************* //