#include <searchableSurfaceCollection.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <SortableList.hxx>
#include <Time.hxx>
#include <ListOps.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{

	defineTypeNameAndDebug(searchableSurfaceCollection, 0);
	addToRunTimeSelectionTable
	(
		searchableSurface,
		searchableSurfaceCollection,
		dict
	);

}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::searchableSurfaceCollection::findNearest
(
	const pointField& samples,
	scalarField& minDistSqr,
	List<pointIndexHit>& nearestInfo,
	labelList& nearestSurf
) const
{
	// Initialise
	nearestInfo.setSize(samples.size());
	nearestInfo = pointIndexHit();
	nearestSurf.setSize(samples.size());
	nearestSurf = -1;

	List<pointIndexHit> hitInfo(samples.size());

	const scalarField localMinDistSqr(samples.size(), great);

	forAll(subGeom_, surfI)
	{
		subGeom_[surfI].findNearest
		(
			cmptDivide  // Transform then divide
			(
				transform_[surfI].localPosition(samples),
				scale_[surfI]
			),
			localMinDistSqr,
			hitInfo
		);

		forAll(hitInfo, pointi)
		{
			if (hitInfo[pointi].hit())
			{
				// Rework back into global coordinate sys. Multiply then
				// transform
				point globalPt = transform_[surfI].globalPosition
				(
					cmptMultiply
					(
						hitInfo[pointi].rawPoint(),
						scale_[surfI]
					)
				);

				scalar distSqr = magSqr(globalPt - samples[pointi]);

				if (distSqr < minDistSqr[pointi])
				{
					minDistSqr[pointi] = distSqr;
					nearestInfo[pointi].setPoint(globalPt);
					nearestInfo[pointi].setHit();
					nearestInfo[pointi].setIndex
					(
						hitInfo[pointi].index()
						+ indexOffset_[surfI]
					);
					nearestSurf[pointi] = surfI;
				}
			}
		}
	}
}


// Sort hits into per-surface bins. Misses are rejected. Maintains map back
// to position
void tnbLib::searchableSurfaceCollection::sortHits
(
	const List<pointIndexHit>& info,
	List<List<pointIndexHit>>& surfInfo,
	labelListList& infoMap
) const
{
	// Count hits per surface.
	labelList nHits(subGeom_.size(), 0);

	forAll(info, pointi)
	{
		if (info[pointi].hit())
		{
			label index = info[pointi].index();
			label surfI = findLower(indexOffset_, index + 1);
			nHits[surfI]++;
		}
	}

	// Per surface the hit
	surfInfo.setSize(subGeom_.size());
	// Per surface the original position
	infoMap.setSize(subGeom_.size());

	forAll(surfInfo, surfI)
	{
		surfInfo[surfI].setSize(nHits[surfI]);
		infoMap[surfI].setSize(nHits[surfI]);
	}
	nHits = 0;

	forAll(info, pointi)
	{
		if (info[pointi].hit())
		{
			label index = info[pointi].index();
			label surfI = findLower(indexOffset_, index + 1);

			// Store for correct surface and adapt indices back to local
			// ones
			label localI = nHits[surfI]++;
			surfInfo[surfI][localI] = pointIndexHit
			(
				info[pointi].hit(),
				info[pointi].rawPoint(),
				index - indexOffset_[surfI]
			);
			infoMap[surfI][localI] = pointi;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::searchableSurfaceCollection::searchableSurfaceCollection
(
	const IOobject& io,
	const dictionary& dict
)
	:
	searchableSurface(io),
	instance_(dict.size()),
	scale_(dict.size()),
	transform_(dict.size()),
	subGeom_(dict.size()),
	mergeSubRegions_(dict.lookup("mergeSubRegions")),
	indexOffset_(dict.size() + 1)
{
	Info << "SearchableCollection : " << name() << endl;

	label surfI = 0;
	label startIndex = 0;
	forAllConstIter(dictionary, dict, iter)
	{
		if (dict.isDict(iter().keyword()))
		{
			instance_[surfI] = iter().keyword();

			const dictionary& subDict = dict.subDict(instance_[surfI]);

			scale_[surfI] = subDict.lookup("scale");
			transform_.set
			(
				surfI,
				coordinateSystem::New
				(
					subDict.subDict("transform")
				)
			);

			const word subGeomName(subDict.lookup("surface"));
			// Pout<< "Trying to find " << subGeomName << endl;

			const searchableSurface& s =
				io.db().lookupObject<searchableSurface>(subGeomName);

			// I don't know yet how to handle the globalSize combined with
			// regionOffset. Would cause non-consecutive indices locally
			// if all indices offset by globalSize() of the local region...
			if (s.size() != s.globalSize())
			{
				FatalErrorInFunction
					<< "Cannot use a distributed surface in a collection."
					<< exit(FatalError);
			}

			subGeom_.set(surfI, &const_cast<searchableSurface&>(s));

			indexOffset_[surfI] = startIndex;
			startIndex += subGeom_[surfI].size();

			Info << "    instance : " << instance_[surfI] << endl;
			Info << "    surface  : " << s.name() << endl;
			Info << "    scale    : " << scale_[surfI] << endl;
			Info << "    coordsys : " << transform_[surfI] << endl;

			surfI++;
		}
	}
	indexOffset_[surfI] = startIndex;

	instance_.setSize(surfI);
	scale_.setSize(surfI);
	transform_.setSize(surfI);
	subGeom_.setSize(surfI);
	indexOffset_.setSize(surfI + 1);

	// Bounds is the overall bounds
	bounds() = boundBox(point::max, point::min);

	forAll(subGeom_, surfI)
	{
		const boundBox& surfBb = subGeom_[surfI].bounds();

		// Transform back to global coordinate sys.
		const point surfBbMin = transform_[surfI].globalPosition
		(
			cmptMultiply
			(
				surfBb.min(),
				scale_[surfI]
			)
		);
		const point surfBbMax = transform_[surfI].globalPosition
		(
			cmptMultiply
			(
				surfBb.max(),
				scale_[surfI]
			)
		);

		bounds().min() = min(bounds().min(), surfBbMin);
		bounds().max() = max(bounds().max(), surfBbMax);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::searchableSurfaceCollection::~searchableSurfaceCollection()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::wordList& tnbLib::searchableSurfaceCollection::regions() const
{
	if (regions_.size() == 0)
	{
		regionOffset_.setSize(subGeom_.size());

		DynamicList<word> allRegions;
		forAll(subGeom_, surfI)
		{
			regionOffset_[surfI] = allRegions.size();

			if (mergeSubRegions_)
			{
				// Single name regardless how many regions subsurface has
				allRegions.append(instance_[surfI] + "_" + tnbLib::name(surfI));
			}
			else
			{
				const wordList& subRegions = subGeom_[surfI].regions();

				forAll(subRegions, i)
				{
					allRegions.append(instance_[surfI] + "_" + subRegions[i]);
				}
			}
		}
		regions_.transfer(allRegions.shrink());
	}
	return regions_;
}


tnbLib::label tnbLib::searchableSurfaceCollection::size() const
{
	return indexOffset_.last();
}


tnbLib::tmp<tnbLib::pointField>
tnbLib::searchableSurfaceCollection::coordinates() const
{
	tmp<pointField> tCtrs = tmp<pointField>(new pointField(size()));
	pointField& ctrs = tCtrs.ref();

	// Append individual coordinates
	label coordI = 0;

	forAll(subGeom_, surfI)
	{
		const pointField subCoords(subGeom_[surfI].coordinates());

		forAll(subCoords, i)
		{
			ctrs[coordI++] = transform_[surfI].globalPosition
			(
				cmptMultiply
				(
					subCoords[i],
					scale_[surfI]
				)
			);
		}
	}

	return tCtrs;
}


void tnbLib::searchableSurfaceCollection::boundingSpheres
(
	pointField& centres,
	scalarField& radiusSqr
) const
{
	centres.setSize(size());
	radiusSqr.setSize(centres.size());

	// Append individual coordinates
	label coordI = 0;

	forAll(subGeom_, surfI)
	{
		scalar maxScale = cmptMax(scale_[surfI]);

		pointField subCentres;
		scalarField subRadiusSqr;
		subGeom_[surfI].boundingSpheres(subCentres, subRadiusSqr);

		forAll(subCentres, i)
		{
			centres[coordI] = transform_[surfI].globalPosition
			(
				cmptMultiply
				(
					subCentres[i],
					scale_[surfI]
				)
			);
			radiusSqr[coordI] = maxScale * subRadiusSqr[i];
			coordI++;
		}
	}
}


tnbLib::tmp<tnbLib::pointField>
tnbLib::searchableSurfaceCollection::points() const
{
	// Get overall size
	label nPoints = 0;

	forAll(subGeom_, surfI)
	{
		nPoints += subGeom_[surfI].points()().size();
	}

	tmp<pointField> tPts(new pointField(nPoints));
	pointField& pts = tPts.ref();

	// Append individual coordinates
	nPoints = 0;

	forAll(subGeom_, surfI)
	{
		const pointField subCoords(subGeom_[surfI].points());

		forAll(subCoords, i)
		{
			pts[nPoints++] = transform_[surfI].globalPosition
			(
				cmptMultiply
				(
					subCoords[i],
					scale_[surfI]
				)
			);
		}
	}

	return tPts;
}


void tnbLib::searchableSurfaceCollection::findNearest
(
	const pointField& samples,
	const scalarField& nearestDistSqr,
	List<pointIndexHit>& nearestInfo
) const
{
	// How to scale distance?
	scalarField minDistSqr(nearestDistSqr);

	labelList nearestSurf;
	findNearest
	(
		samples,
		minDistSqr,
		nearestInfo,
		nearestSurf
	);
}


void tnbLib::searchableSurfaceCollection::findLine
(
	const pointField& start,
	const pointField& end,
	List<pointIndexHit>& info
) const
{
	info.setSize(start.size());
	info = pointIndexHit();

	// Current nearest (to start) intersection
	pointField nearest(end);

	List<pointIndexHit> hitInfo(start.size());

	forAll(subGeom_, surfI)
	{
		// Starting point
		tmp<pointField> e0 = cmptDivide
		(
			transform_[surfI].localPosition
			(
				start
			),
			scale_[surfI]
		);

		// Current best end point
		tmp<pointField> e1 = cmptDivide
		(
			transform_[surfI].localPosition
			(
				nearest
			),
			scale_[surfI]
		);

		subGeom_[surfI].findLine(e0, e1, hitInfo);

		forAll(hitInfo, pointi)
		{
			if (hitInfo[pointi].hit())
			{
				// Transform back to global coordinate sys.
				nearest[pointi] = transform_[surfI].globalPosition
				(
					cmptMultiply
					(
						hitInfo[pointi].rawPoint(),
						scale_[surfI]
					)
				);
				info[pointi] = hitInfo[pointi];
				info[pointi].rawPoint() = nearest[pointi];
				info[pointi].setIndex
				(
					hitInfo[pointi].index()
					+ indexOffset_[surfI]
				);
			}
		}
	}


	// Debug check
	if (false)
	{
		forAll(info, pointi)
		{
			if (info[pointi].hit())
			{
				vector n(end[pointi] - start[pointi]);
				scalar magN = mag(n);

				if (magN > small)
				{
					n /= mag(n);

					scalar s = ((info[pointi].rawPoint() - start[pointi])&n);

					if (s < 0 || s > 1)
					{
						FatalErrorInFunction
							<< "point:" << info[pointi]
							<< " s:" << s
							<< " outside vector "
							<< " start:" << start[pointi]
							<< " end:" << end[pointi]
							<< abort(FatalError);
					}
				}
			}
		}
	}
}


void tnbLib::searchableSurfaceCollection::findLineAny
(
	const pointField& start,
	const pointField& end,
	List<pointIndexHit>& info
) const
{
	// To be done ...
	findLine(start, end, info);
}


void tnbLib::searchableSurfaceCollection::findLineAll
(
	const pointField& start,
	const pointField& end,
	List<List<pointIndexHit>>& info
) const
{
	// To be done. Assume for now only one intersection.
	List<pointIndexHit> nearestInfo;
	findLine(start, end, nearestInfo);

	info.setSize(start.size());
	forAll(info, pointi)
	{
		if (nearestInfo[pointi].hit())
		{
			info[pointi].setSize(1);
			info[pointi][0] = nearestInfo[pointi];
		}
		else
		{
			info[pointi].clear();
		}
	}
}


void tnbLib::searchableSurfaceCollection::getRegion
(
	const List<pointIndexHit>& info,
	labelList& region
) const
{
	if (subGeom_.size() == 0)
	{
	}
	else if (subGeom_.size() == 1)
	{
		if (mergeSubRegions_)
		{
			region.setSize(info.size());
			region = regionOffset_[0];
		}
		else
		{
			subGeom_[0].getRegion(info, region);
		}
	}
	else
	{
		// Multiple surfaces. Sort by surface.

		// Per surface the hit
		List<List<pointIndexHit>> surfInfo;
		// Per surface the original position
		List<List<label>> infoMap;
		sortHits(info, surfInfo, infoMap);

		region.setSize(info.size());
		region = -1;

		// Do region tests

		if (mergeSubRegions_)
		{
			// Actually no need for surfInfo. Just take region for surface.
			forAll(infoMap, surfI)
			{
				const labelList& map = infoMap[surfI];
				forAll(map, i)
				{
					region[map[i]] = regionOffset_[surfI];
				}
			}
		}
		else
		{
			forAll(infoMap, surfI)
			{
				labelList surfRegion;
				subGeom_[surfI].getRegion(surfInfo[surfI], surfRegion);

				const labelList& map = infoMap[surfI];
				forAll(map, i)
				{
					region[map[i]] = regionOffset_[surfI] + surfRegion[i];
				}
			}
		}
	}
}


void tnbLib::searchableSurfaceCollection::getNormal
(
	const List<pointIndexHit>& info,
	vectorField& normal
) const
{
	if (subGeom_.size() == 0)
	{
	}
	else if (subGeom_.size() == 1)
	{
		subGeom_[0].getNormal(info, normal);
	}
	else
	{
		// Multiple surfaces. Sort by surface.

		// Per surface the hit
		List<List<pointIndexHit>> surfInfo;
		// Per surface the original position
		List<List<label>> infoMap;
		sortHits(info, surfInfo, infoMap);

		normal.setSize(info.size());

		// Do region tests
		forAll(surfInfo, surfI)
		{
			vectorField surfNormal;
			subGeom_[surfI].getNormal(surfInfo[surfI], surfNormal);

			// Transform back to global coordinate sys.
			surfNormal = transform_[surfI].globalVector(surfNormal);

			const labelList& map = infoMap[surfI];
			forAll(map, i)
			{
				normal[map[i]] = surfNormal[i];
			}
		}
	}
}


void tnbLib::searchableSurfaceCollection::getVolumeType
(
	const pointField& points,
	List<volumeType>& volType
) const
{
	FatalErrorInFunction
		<< "Volume type not supported for collection."
		<< exit(FatalError);
}


void tnbLib::searchableSurfaceCollection::distribute
(
	const List<treeBoundBox>& bbs,
	const bool keepNonLocal,
	autoPtr<mapDistribute>& faceMap,
	autoPtr<mapDistribute>& pointMap
)
{
	forAll(subGeom_, surfI)
	{
		// Note:Transform the bounding boxes? Something like
		// pointField bbPoints =
		// cmptDivide
		// (
		//     transform_[surfI].localPosition
		//     (
		//         bbs[i].points()
		//     ),
		//     scale_[surfI]
		// );
		// treeBoundBox newBb(bbPoints);

		// Note: what to do with faceMap, pointMap from multiple surfaces?
		subGeom_[surfI].distribute
		(
			bbs,
			keepNonLocal,
			faceMap,
			pointMap
		);
	}
}


void tnbLib::searchableSurfaceCollection::setField(const labelList& values)
{
	forAll(subGeom_, surfI)
	{
		subGeom_[surfI].setField
		(
			static_cast<const labelList&>
			(
				SubList<label>
				(
					values,
					subGeom_[surfI].size(),
					indexOffset_[surfI]
					)
				)
		);
	}
}


void tnbLib::searchableSurfaceCollection::getField
(
	const List<pointIndexHit>& info,
	labelList& values
) const
{
	if (subGeom_.size() == 0)
	{
	}
	else if (subGeom_.size() == 1)
	{
		subGeom_[0].getField(info, values);
	}
	else
	{
		// Multiple surfaces. Sort by surface.

		// Per surface the hit
		List<List<pointIndexHit>> surfInfo;
		// Per surface the original position
		List<List<label>> infoMap;
		sortHits(info, surfInfo, infoMap);

		// Do surface tests
		forAll(surfInfo, surfI)
		{
			labelList surfValues;
			subGeom_[surfI].getField(surfInfo[surfI], surfValues);

			if (surfValues.size())
			{
				// Size values only when we have a surface that supports it.
				values.setSize(info.size());

				const labelList& map = infoMap[surfI];
				forAll(map, i)
				{
					values[map[i]] = surfValues[i];
				}
			}
		}
	}
}


// ************************************************************************* //