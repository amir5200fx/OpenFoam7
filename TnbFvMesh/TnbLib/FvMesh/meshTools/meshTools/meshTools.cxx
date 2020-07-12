#include <meshTools.hxx>

#include <polyMesh.hxx>
#include <hexMatcher.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::meshTools::visNormal
(
	const vector& n,
	const vectorField& faceNormals,
	const labelList& faceLabels
)
{
	forAll(faceLabels, i)
	{
		if ((faceNormals[faceLabels[i]] & n) < small)
		{
			// Found normal in different direction from n.
			return false;
		}
	}

	return true;
}


tnbLib::vectorField tnbLib::meshTools::calcBoxPointNormals(const primitivePatch& pp)
{
	vectorField octantNormal(8);
	octantNormal[mXmYmZ] = vector(-1, -1, -1);
	octantNormal[pXmYmZ] = vector(1, -1, -1);
	octantNormal[mXpYmZ] = vector(-1, 1, -1);
	octantNormal[pXpYmZ] = vector(1, 1, -1);

	octantNormal[mXmYpZ] = vector(-1, -1, 1);
	octantNormal[pXmYpZ] = vector(1, -1, 1);
	octantNormal[mXpYpZ] = vector(-1, 1, 1);
	octantNormal[pXpYpZ] = vector(1, 1, 1);

	octantNormal /= mag(octantNormal);


	vectorField pn(pp.nPoints());

	const vectorField& faceNormals = pp.faceNormals();
	const vectorField& pointNormals = pp.pointNormals();
	const labelListList& pointFaces = pp.pointFaces();

	forAll(pointFaces, pointi)
	{
		const labelList& pFaces = pointFaces[pointi];

		if (visNormal(pointNormals[pointi], faceNormals, pFaces))
		{
			pn[pointi] = pointNormals[pointi];
		}
		else
		{
			WarningInFunction
				<< "Average point normal not visible for point:"
				<< pp.meshPoints()[pointi] << endl;

			label visOctant =
				mXmYmZMask
				| pXmYmZMask
				| mXpYmZMask
				| pXpYmZMask
				| mXmYpZMask
				| pXmYpZMask
				| mXpYpZMask
				| pXpYpZMask;

			forAll(pFaces, i)
			{
				const vector& n = faceNormals[pFaces[i]];

				if (n.x() > small)
				{
					// All -x octants become invisible
					visOctant &= ~mXmYmZMask;
					visOctant &= ~mXmYpZMask;
					visOctant &= ~mXpYmZMask;
					visOctant &= ~mXpYpZMask;
				}
				else if (n.x() < -small)
				{
					// All +x octants become invisible
					visOctant &= ~pXmYmZMask;
					visOctant &= ~pXmYpZMask;
					visOctant &= ~pXpYmZMask;
					visOctant &= ~pXpYpZMask;
				}

				if (n.y() > small)
				{
					visOctant &= ~mXmYmZMask;
					visOctant &= ~mXmYpZMask;
					visOctant &= ~pXmYmZMask;
					visOctant &= ~pXmYpZMask;
				}
				else if (n.y() < -small)
				{
					visOctant &= ~mXpYmZMask;
					visOctant &= ~mXpYpZMask;
					visOctant &= ~pXpYmZMask;
					visOctant &= ~pXpYpZMask;
				}

				if (n.z() > small)
				{
					visOctant &= ~mXmYmZMask;
					visOctant &= ~mXpYmZMask;
					visOctant &= ~pXmYmZMask;
					visOctant &= ~pXpYmZMask;
				}
				else if (n.z() < -small)
				{
					visOctant &= ~mXmYpZMask;
					visOctant &= ~mXpYpZMask;
					visOctant &= ~pXmYpZMask;
					visOctant &= ~pXpYpZMask;
				}
			}

			label visI = -1;

			label mask = 1;

			for (label octant = 0; octant < 8; octant++)
			{
				if (visOctant & mask)
				{
					// Take first visible octant found. Note: could use
					// combination of visible octants here.
					visI = octant;

					break;
				}
				mask <<= 1;
			}

			if (visI != -1)
			{
				// Take a vector in this octant.
				pn[pointi] = octantNormal[visI];
			}
			else
			{
				pn[pointi] = Zero;

				WarningInFunction
					<< "No visible octant for point:" << pp.meshPoints()[pointi]
					<< " cooord:" << pp.points()[pp.meshPoints()[pointi]] << nl
					<< "Normal set to " << pn[pointi] << endl;
			}
		}
	}

	return pn;
}


tnbLib::vector tnbLib::meshTools::normEdgeVec
(
	const primitiveMesh& mesh,
	const label edgeI
)
{
	vector eVec = mesh.edges()[edgeI].vec(mesh.points());

	eVec /= mag(eVec);

	return eVec;
}


void tnbLib::meshTools::writeOBJ
(
	Ostream& os,
	const point& pt
)
{
	os << "v " << pt.x() << ' ' << pt.y() << ' ' << pt.z() << endl;
}


void tnbLib::meshTools::writeOBJ
(
	Ostream& os,
	const triad& t,
	const point& pt
)
{
	forAll(t, dirI)
	{
		writeOBJ(os, pt, pt + t[dirI]);
	}
}


void tnbLib::meshTools::writeOBJ
(
	Ostream& os,
	const point& p1,
	const point& p2,
	label& count
)
{
	os << "v" << ' ' << p1.x() << ' ' << p1.y() << ' ' << p1.z() << endl;
	os << "v" << ' ' << p2.x() << ' ' << p2.y() << ' ' << p2.z() << endl;

	os << "l" << " " << (count + 1) << " " << (count + 2) << endl;

	count += 2;
}


void tnbLib::meshTools::writeOBJ
(
	Ostream& os,
	const point& p1,
	const point& p2
)
{
	os << "v" << ' ' << p1.x() << ' ' << p1.y() << ' ' << p1.z() << endl;

	os << "vn"
		<< ' ' << p2.x() - p1.x()
		<< ' ' << p2.y() - p1.y()
		<< ' ' << p2.z() - p1.z() << endl;
}


void tnbLib::meshTools::writeOBJ
(
	Ostream& os,
	const cellList& cells,
	const faceList& faces,
	const pointField& points,
	const labelList& cellLabels
)
{
	labelHashSet usedFaces(4 * cellLabels.size());

	forAll(cellLabels, i)
	{
		const cell& cFaces = cells[cellLabels[i]];

		forAll(cFaces, j)
		{
			usedFaces.insert(cFaces[j]);
		}
	}

	writeOBJ(os, faces, points, usedFaces.toc());
}


bool tnbLib::meshTools::edgeOnCell
(
	const primitiveMesh& mesh,
	const label celli,
	const label edgeI
)
{
	return findIndex(mesh.edgeCells(edgeI), celli) != -1;
}


bool tnbLib::meshTools::edgeOnFace
(
	const primitiveMesh& mesh,
	const label facei,
	const label edgeI
)
{
	return findIndex(mesh.faceEdges(facei), edgeI) != -1;
}


// Return true if facei part of celli
bool tnbLib::meshTools::faceOnCell
(
	const primitiveMesh& mesh,
	const label celli,
	const label facei
)
{
	if (mesh.isInternalFace(facei))
	{
		if
			(
			(mesh.faceOwner()[facei] == celli)
				|| (mesh.faceNeighbour()[facei] == celli)
				)
		{
			return true;
		}
	}
	else
	{
		if (mesh.faceOwner()[facei] == celli)
		{
			return true;
		}
	}
	return false;
}


tnbLib::label tnbLib::meshTools::findEdge
(
	const edgeList& edges,
	const labelList& candidates,
	const label v0,
	const label v1
)
{
	forAll(candidates, i)
	{
		label edgeI = candidates[i];

		const edge& e = edges[edgeI];

		if ((e[0] == v0 && e[1] == v1) || (e[0] == v1 && e[1] == v0))
		{
			return edgeI;
		}
	}
	return -1;
}


tnbLib::label tnbLib::meshTools::findEdge
(
	const primitiveMesh& mesh,
	const label v0,
	const label v1
)
{
	const edgeList& edges = mesh.edges();

	const labelList& v0Edges = mesh.pointEdges()[v0];

	forAll(v0Edges, i)
	{
		label edgeI = v0Edges[i];

		const edge& e = edges[edgeI];

		if ((e.start() == v1) || (e.end() == v1))
		{
			return edgeI;
		}
	}
	return -1;
}


tnbLib::label tnbLib::meshTools::getSharedEdge
(
	const primitiveMesh& mesh,
	const label f0,
	const label f1
)
{
	const labelList& f0Edges = mesh.faceEdges()[f0];
	const labelList& f1Edges = mesh.faceEdges()[f1];

	forAll(f0Edges, f0EdgeI)
	{
		label edge0 = f0Edges[f0EdgeI];

		forAll(f1Edges, f1EdgeI)
		{
			label edge1 = f1Edges[f1EdgeI];

			if (edge0 == edge1)
			{
				return edge0;
			}
		}
	}
	FatalErrorInFunction
		<< "Faces " << f0 << " and " << f1 << " do not share an edge"
		<< abort(FatalError);

	return -1;

}


tnbLib::label tnbLib::meshTools::getSharedFace
(
	const primitiveMesh& mesh,
	const label cell0I,
	const label cell1I
)
{
	const cell& cFaces = mesh.cells()[cell0I];

	forAll(cFaces, cFacei)
	{
		label facei = cFaces[cFacei];

		if
			(
				mesh.isInternalFace(facei)
				&& (
					mesh.faceOwner()[facei] == cell1I
					|| mesh.faceNeighbour()[facei] == cell1I
					)
				)
		{
			return facei;
		}
	}


	FatalErrorInFunction
		<< "No common face for"
		<< "  cell0I:" << cell0I << "  faces:" << cFaces
		<< "  cell1I:" << cell1I << "  faces:"
		<< mesh.cells()[cell1I]
		<< abort(FatalError);

	return -1;
}


// Get the two faces on celli using edgeI.
void tnbLib::meshTools::getEdgeFaces
(
	const primitiveMesh& mesh,
	const label celli,
	const label edgeI,
	label& face0,
	label& face1
)
{
	const labelList& eFaces = mesh.edgeFaces(edgeI);

	face0 = -1;
	face1 = -1;

	forAll(eFaces, eFacei)
	{
		label facei = eFaces[eFacei];

		if (faceOnCell(mesh, celli, facei))
		{
			if (face0 == -1)
			{
				face0 = facei;
			}
			else
			{
				face1 = facei;

				return;
			}
		}
	}

	if ((face0 == -1) || (face1 == -1))
	{
		FatalErrorInFunction
			<< "Can not find faces using edge " << mesh.edges()[edgeI]
			<< " on cell " << celli << abort(FatalError);
	}
}


// Return label of other edge connected to vertex
tnbLib::label tnbLib::meshTools::otherEdge
(
	const primitiveMesh& mesh,
	const labelList& edgeLabels,
	const label thisEdgeI,
	const label thisVertI
)
{
	forAll(edgeLabels, edgeLabelI)
	{
		label edgeI = edgeLabels[edgeLabelI];

		if (edgeI != thisEdgeI)
		{
			const edge& e = mesh.edges()[edgeI];

			if ((e.start() == thisVertI) || (e.end() == thisVertI))
			{
				return edgeI;
			}
		}
	}

	FatalErrorInFunction
		<< "Can not find edge in "
		<< UIndirectList<edge>(mesh.edges(), edgeLabels)()
		<< " connected to edge "
		<< thisEdgeI << " with vertices " << mesh.edges()[thisEdgeI]
		<< " on side " << thisVertI << abort(FatalError);

	return -1;
}


// Return face on other side of edgeI
tnbLib::label tnbLib::meshTools::otherFace
(
	const primitiveMesh& mesh,
	const label celli,
	const label facei,
	const label edgeI
)
{
	label face0;
	label face1;

	getEdgeFaces(mesh, celli, edgeI, face0, face1);

	if (face0 == facei)
	{
		return face1;
	}
	else
	{
		return face0;
	}
}


// Return face on other side of edgeI
tnbLib::label tnbLib::meshTools::otherCell
(
	const primitiveMesh& mesh,
	const label otherCelli,
	const label facei
)
{
	if (!mesh.isInternalFace(facei))
	{
		FatalErrorInFunction
			<< "Face " << facei << " is not internal"
			<< abort(FatalError);
	}

	label newCelli = mesh.faceOwner()[facei];

	if (newCelli == otherCelli)
	{
		newCelli = mesh.faceNeighbour()[facei];
	}
	return newCelli;
}


// Returns label of edge nEdges away from startEdge (in the direction of
// startVertI)
tnbLib::label tnbLib::meshTools::walkFace
(
	const primitiveMesh& mesh,
	const label facei,
	const label startEdgeI,
	const label startVertI,
	const label nEdges
)
{
	const labelList& fEdges = mesh.faceEdges(facei);

	label edgeI = startEdgeI;

	label vertI = startVertI;

	for (label iter = 0; iter < nEdges; iter++)
	{
		edgeI = otherEdge(mesh, fEdges, edgeI, vertI);

		vertI = mesh.edges()[edgeI].otherVertex(vertI);
	}

	return edgeI;
}


void tnbLib::meshTools::constrainToMeshCentre
(
	const polyMesh& mesh,
	point& pt
)
{
	const Vector<label>& dirs = mesh.geometricD();

	const point& min = mesh.bounds().min();
	const point& max = mesh.bounds().max();

	for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
	{
		if (dirs[cmpt] == -1)
		{
			pt[cmpt] = 0.5*(min[cmpt] + max[cmpt]);
		}
	}
}


void tnbLib::meshTools::constrainToMeshCentre
(
	const polyMesh& mesh,
	pointField& pts
)
{
	const Vector<label>& dirs = mesh.geometricD();

	const point& min = mesh.bounds().min();
	const point& max = mesh.bounds().max();

	bool isConstrained = false;
	for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
	{
		if (dirs[cmpt] == -1)
		{
			isConstrained = true;
			break;
		}
	}

	if (isConstrained)
	{
		forAll(pts, i)
		{
			for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
			{
				if (dirs[cmpt] == -1)
				{
					pts[i][cmpt] = 0.5*(min[cmpt] + max[cmpt]);
				}
			}
		}
	}
}


void tnbLib::meshTools::constrainDirection
(
	const polyMesh& mesh,
	const Vector<label>& dirs,
	vector& d
)
{
	for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
	{
		if (dirs[cmpt] == -1)
		{
			d[cmpt] = 0.0;
		}
	}
}


void tnbLib::meshTools::constrainDirection
(
	const polyMesh& mesh,
	const Vector<label>& dirs,
	vectorField& d
)
{
	bool isConstrained = false;
	for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
	{
		if (dirs[cmpt] == -1)
		{
			isConstrained = true;
			break;
		}
	}

	if (isConstrained)
	{
		forAll(d, i)
		{
			for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
			{
				if (dirs[cmpt] == -1)
				{
					d[i][cmpt] = 0.0;
				}
			}
		}
	}
}


void tnbLib::meshTools::getParallelEdges
(
	const primitiveMesh& mesh,
	const label celli,
	const label e0,
	label& e1,
	label& e2,
	label& e3
)
{
	// Go to any face using e0
	label facei = meshTools::otherFace(mesh, celli, -1, e0);

	// Opposite edge on face
	e1 = meshTools::walkFace(mesh, facei, e0, mesh.edges()[e0].end(), 2);

	facei = meshTools::otherFace(mesh, celli, facei, e1);

	e2 = meshTools::walkFace(mesh, facei, e1, mesh.edges()[e1].end(), 2);

	facei = meshTools::otherFace(mesh, celli, facei, e2);

	e3 = meshTools::walkFace(mesh, facei, e2, mesh.edges()[e2].end(), 2);
}


tnbLib::vector tnbLib::meshTools::edgeToCutDir
(
	const primitiveMesh& mesh,
	const label celli,
	const label startEdgeI
)
{
	if (!hexMatcher().isA(mesh, celli))
	{
		FatalErrorInFunction
			<< "Not a hex : cell:" << celli << abort(FatalError);
	}


	vector avgVec(normEdgeVec(mesh, startEdgeI));

	label edgeI = startEdgeI;

	label facei = -1;

	for (label i = 0; i < 3; i++)
	{
		// Step to next face, next edge
		facei = meshTools::otherFace(mesh, celli, facei, edgeI);

		vector eVec(normEdgeVec(mesh, edgeI));

		if ((eVec & avgVec) > 0)
		{
			avgVec += eVec;
		}
		else
		{
			avgVec -= eVec;
		}

		label vertI = mesh.edges()[edgeI].end();

		edgeI = meshTools::walkFace(mesh, facei, edgeI, vertI, 2);
	}

	avgVec /= mag(avgVec) + vSmall;

	return avgVec;
}


// Find edges most aligned with cutDir
tnbLib::label tnbLib::meshTools::cutDirToEdge
(
	const primitiveMesh& mesh,
	const label celli,
	const vector& cutDir
)
{
	if (!hexMatcher().isA(mesh, celli))
	{
		FatalErrorInFunction
			<< "Not a hex : cell:" << celli << abort(FatalError);
	}

	const labelList& cEdges = mesh.cellEdges()[celli];

	labelHashSet doneEdges(2 * cEdges.size());

	scalar maxCos = -great;
	label maxEdgeI = -1;

	for (label i = 0; i < 4; i++)
	{
		forAll(cEdges, cEdgeI)
		{
			label e0 = cEdges[cEdgeI];

			if (!doneEdges.found(e0))
			{
				vector avgDir(edgeToCutDir(mesh, celli, e0));

				scalar cosAngle = mag(avgDir & cutDir);

				if (cosAngle > maxCos)
				{
					maxCos = cosAngle;
					maxEdgeI = e0;
				}

				// Mark off edges in cEdges.
				label e1, e2, e3;
				getParallelEdges(mesh, celli, e0, e1, e2, e3);

				doneEdges.insert(e0);
				doneEdges.insert(e1);
				doneEdges.insert(e2);
				doneEdges.insert(e3);
			}
		}
	}

	forAll(cEdges, cEdgeI)
	{
		if (!doneEdges.found(cEdges[cEdgeI]))
		{
			FatalErrorInFunction
				<< "Cell:" << celli << " edges:" << cEdges << endl
				<< "Edge:" << cEdges[cEdgeI] << " not yet handled"
				<< abort(FatalError);
		}
	}

	if (maxEdgeI == -1)
	{
		FatalErrorInFunction
			<< "Problem : did not find edge aligned with " << cutDir
			<< " on cell " << celli << abort(FatalError);
	}

	return maxEdgeI;
}


// ************************************************************************* //