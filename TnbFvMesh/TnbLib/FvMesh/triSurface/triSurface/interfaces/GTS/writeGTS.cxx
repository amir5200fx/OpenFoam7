#include <triSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void triSurface::writeGTS(const bool writeSorted, Ostream& os) const
	{
		// Write header
		os << "# GTS file" << endl
			<< "# Regions:" << endl;

		labelList faceMap;

		surfacePatchList patches(calcPatches(faceMap));

		// Print patch names as comment
		forAll(patches, patchi)
		{
			os << "#     " << patchi << "    "
				<< patches[patchi].name() << endl;
		}
		os << "#" << endl;


		const pointField& ps = points();

		os << "# nPoints  nEdges  nTriangles" << endl
			<< ps.size() << ' ' << nEdges() << ' ' << size() << endl;

		// Write vertex coords

		forAll(ps, pointi)
		{
			os << ps[pointi].x() << ' '
				<< ps[pointi].y() << ' '
				<< ps[pointi].z() << endl;
		}

		// Write edges.
		// Note: edges are in local point labels so convert
		const edgeList& es = edges();
		const labelList& meshPts = meshPoints();

		forAll(es, edgei)
		{
			os << meshPts[es[edgei].start()] + 1 << ' '
				<< meshPts[es[edgei].end()] + 1 << endl;
		}

		// Write faces in terms of edges.
		const labelListList& faceEs = faceEdges();

		if (writeSorted)
		{
			label faceIndex = 0;
			forAll(patches, patchi)
			{
				for
					(
						label patchFacei = 0;
						patchFacei < patches[patchi].size();
						patchFacei++
						)
				{
					const label facei = faceMap[faceIndex++];

					const labelList& fEdges = faceEdges()[facei];

					os << fEdges[0] + 1 << ' '
						<< fEdges[1] + 1 << ' '
						<< fEdges[2] + 1 << ' '
						<< (*this)[facei].region() << endl;
				}
			}
		}
		else
		{
			forAll(faceEs, facei)
			{
				const labelList& fEdges = faceEdges()[facei];

				os << fEdges[0] + 1 << ' '
					<< fEdges[1] + 1 << ' '
					<< fEdges[2] + 1 << ' '
					<< (*this)[facei].region() << endl;
			}
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //