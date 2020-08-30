#include <searchableSurfaces.hxx>

#include <searchableSurfacesQueries.hxx>
#include <ListOps.hxx>
#include <Time.hxx>
#include <DynamicField.hxx>
#include <PatchTools.hxx>
#include <triSurfaceMesh.hxx>

#include <PstreamReduceOps.hxx>  // added by amir
#include <OFstream.hxx> // added by amir
#include <coordSet.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(searchableSurfaces, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::searchableSurfaces::connected
(
	const triSurface& s,
	const label edgeI,
	const pointIndexHit& hit
)
{
	const triFace& localFace = s.localFaces()[hit.index()];
	const edge& e = s.edges()[edgeI];

	forAll(localFace, i)
	{
		if (e.otherVertex(localFace[i]) != -1)
		{
			return true;
		}
	}

	return false;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct with length.
tnbLib::searchableSurfaces::searchableSurfaces(const label size)
	:
	PtrList<searchableSurface>(size),
	regionNames_(size),
	allSurfaces_(identity(size))
{}


//tnbLib::searchableSurfaces::searchableSurfaces
//(
//    const IOobject& io,
//    const PtrList<dictionary>& dicts
//)
//:
//    PtrList<searchableSurface>(dicts.size()),
//    regionNames_(dicts.size()),
//    allSurfaces_(identity(dicts.size()))
//{
//    forAll(dicts, surfI)
//    {
//        const dictionary& dict = dicts[surfI];
//
//        // Make IOobject with correct name
//        autoPtr<IOobject> namedIO(io.clone());
//        namedIO().rename(dict.lookup("name"));
//
//        // Create and hook surface
//        set
//        (
//            surfI,
//            searchableSurface::New
//            (
//                dict.lookup("type"),
//                namedIO(),
//                dict
//            )
//        );
//        const searchableSurface& s = operator[](surfI);
//
//        // Construct default region names by prepending surface name
//        // to region name.
//        const wordList& localNames = s.regions();
//
//        wordList globalNames(localNames.size());
//        forAll(localNames, regionI)
//        {
//            globalNames[regionI] = s.name() + '_' + localNames[regionI];
//        }
//
//        // See if dictionary provides any global region names.
//        if (dict.found("regions"))
//        {
//            const dictionary& regionsDict = dict.subDict("regions");
//
//            forAllConstIter(dictionary, regionsDict, iter)
//            {
//                const word& key = iter().keyword();
//
//                if (regionsDict.isDict(key))
//                {
//                    // Get the dictionary for region iter.key()
//                    const dictionary& regionDict = regionsDict.subDict(key);
//
//                    label index = findIndex(localNames, key);
//
//                    if (index == -1)
//                    {
//                        FatalErrorInFunction
//                            << "Unknown region name " << key
//                            << " for surface " << s.name() << endl
//                            << "Valid region names are " << localNames
//                            << exit(FatalError);
//                    }
//
//                    globalNames[index] = word(regionDict.lookup("name"));
//                }
//            }
//        }
//
//        // Now globalNames contains the names of the regions.
//        Info<< "Surface:" << s.name() << " has regions:"
//            << endl;
//        forAll(globalNames, regionI)
//        {
//            Info<< "    " << globalNames[regionI] << endl;
//        }
//
//        // Create reverse lookup
//        forAll(globalNames, regionI)
//        {
//            regionNames_.insert
//            (
//                globalNames[regionI],
//                labelPair(surfI, regionI)
//            );
//        }
//    }
//}


tnbLib::searchableSurfaces::searchableSurfaces
(
	const IOobject& io,
	const dictionary& topDict,
	const bool singleRegionName
)
	:
	PtrList<searchableSurface>(topDict.size()),
	names_(topDict.size()),
	regionNames_(topDict.size()),
	allSurfaces_(identity(topDict.size()))
{
	label surfI = 0;
	forAllConstIter(dictionary, topDict, iter)
	{
		const word& key = iter().keyword();

		if (!topDict.isDict(key))
		{
			FatalErrorInFunction
				<< "Found non-dictionary entry " << iter()
				<< " in top-level dictionary " << topDict
				<< exit(FatalError);
		}

		const dictionary& dict = topDict.subDict(key);

		names_[surfI] = key;
		dict.readIfPresent("name", names_[surfI]);

		// Make IOobject with correct name
		autoPtr<IOobject> namedIO(io.clone());
		// Note: we would like to e.g. register triSurface 'sphere.stl' as
		// 'sphere'. Unfortunately
		// no support for having object read from different location than
		// their object name. Maybe have stlTriSurfaceMesh which appends .stl
		// when reading/writing?
		namedIO().rename(key);  // names_[surfI]

		// Create and hook surface
		set
		(
			surfI,
			searchableSurface::New
			(
				dict.lookup("type"),
				namedIO(),
				dict
			)
		);
		const searchableSurface& s = operator[](surfI);

		// Construct default region names by prepending surface name
		// to region name.
		const wordList& localNames = s.regions();

		wordList& rNames = regionNames_[surfI];
		rNames.setSize(localNames.size());

		if (singleRegionName && localNames.size() == 1)
		{
			rNames[0] = names_[surfI];
		}
		else
		{
			forAll(localNames, regionI)
			{
				rNames[regionI] = names_[surfI] + '_' + localNames[regionI];
			}
		}

		// See if dictionary provides any global region names.
		if (dict.found("regions"))
		{
			const dictionary& regionsDict = dict.subDict("regions");

			forAllConstIter(dictionary, regionsDict, iter)
			{
				const word& key = iter().keyword();

				if (regionsDict.isDict(key))
				{
					// Get the dictionary for region iter.keyword()
					const dictionary& regionDict = regionsDict.subDict(key);

					label index = findIndex(localNames, key);

					if (index == -1)
					{
						FatalErrorInFunction
							<< "Unknown region name " << key
							<< " for surface " << s.name() << endl
							<< "Valid region names are " << localNames
							<< exit(FatalError);
					}

					rNames[index] = word(regionDict.lookup("name"));
				}
			}
		}

		surfI++;
	}

	// Trim (not really necessary since we don't allow non-dictionary entries)
	PtrList<searchableSurface>::setSize(surfI);
	names_.setSize(surfI);
	regionNames_.setSize(surfI);
	allSurfaces_.setSize(surfI);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::searchableSurfaces::findSurfaceID
(
	const word& wantedName
) const
{
	return findIndex(names_, wantedName);
}


tnbLib::label tnbLib::searchableSurfaces::findSurfaceRegionID
(
	const word& surfaceName,
	const word& regionName
) const
{
	label surfaceIndex = findSurfaceID(surfaceName);

	return findIndex(this->operator[](surfaceIndex).regions(), regionName);
}


// Find any intersection
void tnbLib::searchableSurfaces::findAnyIntersection
(
	const pointField& start,
	const pointField& end,
	labelList& hitSurfaces,
	List<pointIndexHit>& hitInfo
) const
{
	searchableSurfacesQueries::findAnyIntersection
	(
		*this,
		allSurfaces_,
		start,
		end,
		hitSurfaces,
		hitInfo
	);
}


void tnbLib::searchableSurfaces::findAllIntersections
(
	const pointField& start,
	const pointField& end,
	labelListList& hitSurfaces,
	List<List<pointIndexHit>>& hitInfo
) const
{
	searchableSurfacesQueries::findAllIntersections
	(
		*this,
		allSurfaces_,
		start,
		end,
		hitSurfaces,
		hitInfo
	);
}


//Find intersections of edge nearest to both endpoints.
void tnbLib::searchableSurfaces::findNearestIntersection
(
	const pointField& start,
	const pointField& end,
	labelList& surface1,
	List<pointIndexHit>& hit1,
	labelList& surface2,
	List<pointIndexHit>& hit2
) const
{
	searchableSurfacesQueries::findNearestIntersection
	(
		*this,
		allSurfaces_,
		start,
		end,
		surface1,
		hit1,
		surface2,
		hit2
	);
}


void tnbLib::searchableSurfaces::findNearest
(
	const pointField& samples,
	const scalarField& nearestDistSqr,
	labelList& nearestSurfaces,
	List<pointIndexHit>& nearestInfo
) const
{
	searchableSurfacesQueries::findNearest
	(
		*this,
		allSurfaces_,
		samples,
		nearestDistSqr,
		nearestSurfaces,
		nearestInfo
	);
}


void tnbLib::searchableSurfaces::findNearest
(
	const pointField& samples,
	const scalarField& nearestDistSqr,
	const labelList& regionIndices,
	labelList& nearestSurfaces,
	List<pointIndexHit>& nearestInfo
) const
{
	searchableSurfacesQueries::findNearest
	(
		*this,
		allSurfaces_,
		samples,
		nearestDistSqr,
		regionIndices,
		nearestSurfaces,
		nearestInfo
	);
}


tnbLib::boundBox tnbLib::searchableSurfaces::bounds() const
{
	return searchableSurfacesQueries::bounds
	(
		*this,
		allSurfaces_
	);
}


bool tnbLib::searchableSurfaces::checkClosed(const bool report) const
{
	if (report)
	{
		Info << "Checking for closedness." << endl;
	}

	bool hasError = false;

	forAll(*this, surfI)
	{
		if (!operator[](surfI).hasVolumeType())
		{
			hasError = true;

			if (report)
			{
				Info << "    " << names()[surfI]
					<< " : not closed" << endl;
			}

			if (isA<triSurface>(operator[](surfI)))
			{
				const triSurface& s = dynamic_cast<const triSurface&>
					(
						operator[](surfI)
						);
				const labelListList& edgeFaces = s.edgeFaces();

				label nSingleEdges = 0;
				forAll(edgeFaces, edgeI)
				{
					if (edgeFaces[edgeI].size() == 1)
					{
						nSingleEdges++;
					}
				}

				label nMultEdges = 0;
				forAll(edgeFaces, edgeI)
				{
					if (edgeFaces[edgeI].size() > 2)
					{
						nMultEdges++;
					}
				}

				if (report && (nSingleEdges != 0 || nMultEdges != 0))
				{
					Info << "        connected to one face : "
						<< nSingleEdges << nl
						<< "        connected to >2 faces : "
						<< nMultEdges << endl;
				}
			}
		}
	}

	if (report)
	{
		Info << endl;
	}

	return returnReduce(hasError, orOp<bool>());
}


bool tnbLib::searchableSurfaces::checkNormalOrientation(const bool report) const
{
	if (report)
	{
		Info << "Checking for normal orientation." << endl;
	}

	bool hasError = false;

	forAll(*this, surfI)
	{
		if (isA<triSurface>(operator[](surfI)))
		{
			const triSurface& s = dynamic_cast<const triSurface&>
				(
					operator[](surfI)
					);

			labelHashSet borderEdge(s.size() / 1000);
			PatchTools::checkOrientation(s, false, &borderEdge);
			// Colour all faces into zones using borderEdge
			labelList normalZone;
			label nZones = PatchTools::markZones(s, borderEdge, normalZone);
			if (nZones > 1)
			{
				hasError = true;

				if (report)
				{
					Info << "    " << names()[surfI]
						<< " : has multiple orientation zones ("
						<< nZones << ")" << endl;
				}
			}
		}
	}

	if (report)
	{
		Info << endl;
	}

	return returnReduce(hasError, orOp<bool>());
}


bool tnbLib::searchableSurfaces::checkSizes
(
	const scalar maxRatio,
	const bool report
) const
{
	if (report)
	{
		Info << "Checking for size." << endl;
	}

	bool hasError = false;

	forAll(*this, i)
	{
		const boundBox& bb = operator[](i).bounds();

		for (label j = i + 1; j < size(); j++)
		{
			scalar ratio = bb.mag() / operator[](j).bounds().mag();

			if (ratio > maxRatio || ratio < 1.0 / maxRatio)
			{
				hasError = true;

				if (report)
				{
					Info << "    " << names()[i]
						<< " bounds differ from " << names()[j]
						<< " by more than a factor 100:" << nl
						<< "        bounding box : " << bb << nl
						<< "        bounding box : " << operator[](j).bounds()
						<< endl;
				}
				break;
			}
		}
	}

	if (report)
	{
		Info << endl;
	}

	return returnReduce(hasError, orOp<bool>());
}


bool tnbLib::searchableSurfaces::checkIntersection
(
	const scalar tolerance,
	const autoPtr<writer<scalar>>& setWriter,
	const bool report
) const
{
	if (report)
	{
		Info << "Checking for intersection." << endl;
	}

	// cpuTime timer;

	bool hasError = false;

	forAll(*this, i)
	{
		if (isA<triSurfaceMesh>(operator[](i)))
		{
			const triSurfaceMesh& s0 = dynamic_cast<const triSurfaceMesh&>
				(
					operator[](i)
					);
			const edgeList& edges0 = s0.edges();
			const pointField& localPoints0 = s0.localPoints();

			// Collect all the edge vectors
			pointField start(edges0.size());
			pointField end(edges0.size());
			forAll(edges0, edgeI)
			{
				const edge& e = edges0[edgeI];
				start[edgeI] = localPoints0[e[0]];
				end[edgeI] = localPoints0[e[1]];
			}

			// Test all other surfaces for intersection
			forAll(*this, j)
			{
				List<pointIndexHit> hits;

				if (i == j)
				{
					// Slightly shorten the edges to prevent finding lots of
					// intersections. The fast triangle intersection routine
					// has problems with rays passing through a point of the
					// triangle.
					vectorField d
					(
						max(tolerance, 10 * s0.tolerance())
						*(end - start)
					);
					start += d;
					end -= d;
				}

				operator[](j).findLineAny(start, end, hits);

				label nHits = 0;
				DynamicField<point> intersections(edges0.size() / 100);
				DynamicField<scalar> intersectionEdge(intersections.capacity());

				forAll(hits, edgeI)
				{
					if
						(
							hits[edgeI].hit()
							&& (i != j || !connected(s0, edgeI, hits[edgeI]))
							)
					{
						intersections.append(hits[edgeI].hitPoint());
						intersectionEdge.append(1.0*edgeI);
						nHits++;
					}
				}

				if (nHits > 0)
				{
					if (report)
					{
						Info << "    " << names()[i]
							<< " intersects " << names()[j]
							<< " at " << nHits
							<< " locations."
							<< endl;

						// vtkSetWriter<scalar> setWriter;
						if (setWriter.valid())
						{
							scalarField dist(mag(intersections));
							coordSet track
							(
								names()[i] + '_' + names()[j],
								"xyz",
								move(intersections),
								dist
							);
							wordList valueSetNames(1, "edgeIndex");
							List<const scalarField*> valueSets
							(
								1,
								&intersectionEdge
							);

							fileName fName
							(
								setWriter().getFileName(track, valueSetNames)
							);
							Info << "    Writing intersection locations to "
								<< fName << endl;
							OFstream os
							(
								s0.searchableSurface::time().path()
								/ fName
							);
							setWriter().write
							(
								track,
								valueSetNames,
								valueSets,
								os
							);
						}
					}

					hasError = true;
					break;
				}
			}
		}
	}

	if (report)
	{
		Info << endl;
	}

	return returnReduce(hasError, orOp<bool>());
}


bool tnbLib::searchableSurfaces::checkQuality
(
	const scalar minQuality,
	const bool report
) const
{
	if (report)
	{
		Info << "Checking for triangle quality." << endl;
	}

	bool hasError = false;

	forAll(*this, surfI)
	{
		if (isA<triSurface>(operator[](surfI)))
		{
			const triSurface& s = dynamic_cast<const triSurface&>
				(
					operator[](surfI)
					);

			label nBadTris = 0;
			forAll(s, facei)
			{
				const labelledTri& f = s[facei];

				scalar q = triPointRef
				(
					s.points()[f[0]],
					s.points()[f[1]],
					s.points()[f[2]]
				).quality();

				if (q < minQuality)
				{
					nBadTris++;
				}
			}

			if (nBadTris > 0)
			{
				hasError = true;

				if (report)
				{
					Info << "    " << names()[surfI]
						<< " : has " << nBadTris << " bad quality triangles "
						<< " (quality < " << minQuality << ")" << endl;
				}
			}
		}
	}

	if (report)
	{
		Info << endl;
	}

	return returnReduce(hasError, orOp<bool>());

}


// Check all surfaces. Return number of failures.
tnbLib::label tnbLib::searchableSurfaces::checkTopology
(
	const bool report
) const
{
	label noFailedChecks = 0;

	if (checkClosed(report))
	{
		noFailedChecks++;
	}

	if (checkNormalOrientation(report))
	{
		noFailedChecks++;
	}
	return noFailedChecks;
}


tnbLib::label tnbLib::searchableSurfaces::checkGeometry
(
	const scalar maxRatio,
	const scalar tol,
	const autoPtr<writer<scalar>>& setWriter,
	const scalar minQuality,
	const bool report
) const
{
	label noFailedChecks = 0;

	if (maxRatio > 0 && checkSizes(maxRatio, report))
	{
		noFailedChecks++;
	}

	if (checkIntersection(tol, setWriter, report))
	{
		noFailedChecks++;
	}

	if (checkQuality(minQuality, report))
	{
		noFailedChecks++;
	}

	return noFailedChecks;
}


void tnbLib::searchableSurfaces::writeStats
(
	const List<wordList>& patchTypes,
	Ostream& os
) const
{
	Info << "Statistics." << endl;
	forAll(*this, surfI)
	{
		Info << "    " << names()[surfI] << ':' << endl;

		const searchableSurface& s = operator[](surfI);

		Info << "        type      : " << s.type() << nl
			<< "        size      : " << s.globalSize() << nl;
		if (isA<triSurfaceMesh>(s))
		{
			const triSurfaceMesh& ts = dynamic_cast<const triSurfaceMesh&>(s);
			Info << "        edges     : " << ts.nEdges() << nl
				<< "        points    : " << ts.points()().size() << nl;
		}
		Info << "        bounds    : " << s.bounds() << nl
			<< "        closed    : " << Switch(s.hasVolumeType()) << endl;

		if (patchTypes.size() && patchTypes[surfI].size() >= 1)
		{
			wordList unique(HashSet<word>(patchTypes[surfI]).sortedToc());
			Info << "        patches   : ";
			forAll(unique, i)
			{
				Info << unique[i];
				if (i < unique.size() - 1)
				{
					Info << ',';
				}
			}
			Info << endl;
		}
	}
	Info << endl;
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

const tnbLib::searchableSurface& tnbLib::searchableSurfaces::operator[]
(
	const word& surfName
	) const
{
	const label surfI = findSurfaceID(surfName);

	if (surfI < 0)
	{
		FatalErrorInFunction
			<< "Surface named " << surfName << " not found." << nl
			<< "Available surface names: " << names_ << endl
			<< abort(FatalError);
	}

	return operator[](surfI);
}


tnbLib::searchableSurface& tnbLib::searchableSurfaces::operator[]
(
	const word& surfName
	)
{
	const label surfI = findSurfaceID(surfName);

	if (surfI < 0)
	{
		FatalErrorInFunction
			<< "Surface named " << surfName << " not found." << nl
			<< "Available surface names: " << names_ << endl
			<< abort(FatalError);
	}

	return operator[](surfI);
}


// ************************************************************************* //