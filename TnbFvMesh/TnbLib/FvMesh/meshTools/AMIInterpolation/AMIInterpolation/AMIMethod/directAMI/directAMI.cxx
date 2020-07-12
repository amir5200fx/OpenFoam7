#include <directAMI.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(directAMI, 0);
	addToRunTimeSelectionTable(AMIMethod, directAMI, components);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::directAMI::appendToDirectSeeds
(
	labelList& mapFlag,
	labelList& srcTgtSeed,
	DynamicList<label>& srcSeeds,
	DynamicList<label>& nonOverlapFaces,
	label& srcFacei,
	label& tgtFacei
) const
{
	const labelList& srcNbr = this->srcPatch_.faceFaces()[srcFacei];
	const labelList& tgtNbr = this->tgtPatch_.faceFaces()[tgtFacei];

	const pointField& srcPoints = this->srcPatch_.points();
	const pointField& tgtPoints = this->tgtPatch_.points();

	const vectorField& srcCf = this->srcPatch_.faceCentres();

	forAll(srcNbr, i)
	{
		label srcI = srcNbr[i];

		if ((mapFlag[srcI] == 0) && (srcTgtSeed[srcI] == -1))
		{
			// first attempt: match by comparing face centres
			const face& srcF = this->srcPatch_[srcI];
			const point& srcC = srcCf[srcI];

			scalar tol = great;
			forAll(srcF, fpI)
			{
				const point& p = srcPoints[srcF[fpI]];
				scalar d2 = magSqr(p - srcC);
				if (d2 < tol)
				{
					tol = d2;
				}
			}
			tol = max(small, 0.0001*sqrt(tol));

			bool found = false;
			forAll(tgtNbr, j)
			{
				label tgtI = tgtNbr[j];
				const face& tgtF = this->tgtPatch_[tgtI];
				const point tgtC = tgtF.centre(tgtPoints);

				if (mag(srcC - tgtC) < tol)
				{
					// new match - append to lists
					found = true;

					srcTgtSeed[srcI] = tgtI;
					srcSeeds.append(srcI);

					break;
				}
			}

			// second attempt: match by shooting a ray into the tgt face
			if (!found)
			{
				const vector srcN = srcF.area(srcPoints);

				forAll(tgtNbr, j)
				{
					label tgtI = tgtNbr[j];
					const face& tgtF = this->tgtPatch_[tgtI];
					pointHit ray = tgtF.ray(srcCf[srcI], srcN, tgtPoints);

					if (ray.hit())
					{
						// new match - append to lists
						found = true;

						srcTgtSeed[srcI] = tgtI;
						srcSeeds.append(srcI);

						break;
					}
				}
			}

			// no match available for source face srcI
			if (!found)
			{
				mapFlag[srcI] = -1;
				nonOverlapFaces.append(srcI);

				if (debug)
				{
					Pout << "source face not found: id=" << srcI
						<< " centre=" << srcCf[srcI]
						<< " area=" << srcF.area(srcPoints)
						<< " points=" << srcF.points(srcPoints)
						<< endl;

					Pout << "target neighbours:" << nl;
					forAll(tgtNbr, j)
					{
						label tgtI = tgtNbr[j];
						const face& tgtF = this->tgtPatch_[tgtI];

						Pout << "face id: " << tgtI
							<< " centre=" << tgtF.centre(tgtPoints)
							<< " area=" << tgtF.area(tgtPoints)
							<< " points=" << tgtF.points(tgtPoints)
							<< endl;
					}
				}
			}
		}
	}

	if (srcSeeds.size())
	{
		srcFacei = srcSeeds.remove();
		tgtFacei = srcTgtSeed[srcFacei];
	}
	else
	{
		srcFacei = -1;
		tgtFacei = -1;
	}
}


void tnbLib::directAMI::restartAdvancingFront
(
	labelList& mapFlag,
	DynamicList<label>& nonOverlapFaces,
	label& srcFacei,
	label& tgtFacei
) const
{
	forAll(mapFlag, facei)
	{
		if (mapFlag[facei] == 0)
		{
			tgtFacei = this->findTargetFace(facei);

			if (tgtFacei < 0)
			{
				mapFlag[facei] = -1;
				nonOverlapFaces.append(facei);
			}
			else
			{
				srcFacei = facei;
				break;
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::directAMI::directAMI
(
	const primitivePatch& srcPatch,
	const primitivePatch& tgtPatch,
	const scalarField& srcMagSf,
	const scalarField& tgtMagSf,
	const faceAreaIntersect::triangulationMode& triMode,
	const bool reverseTarget,
	const bool requireMatch
)
	:
	AMIMethod
	(
		srcPatch,
		tgtPatch,
		srcMagSf,
		tgtMagSf,
		triMode,
		reverseTarget,
		requireMatch
	)
{}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

tnbLib::directAMI::~directAMI()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::directAMI::calculate
(
	labelListList& srcAddress,
	scalarListList& srcWeights,
	labelListList& tgtAddress,
	scalarListList& tgtWeights,
	label srcFacei,
	label tgtFacei
)
{
	bool ok =
		this->initialise
		(
			srcAddress,
			srcWeights,
			tgtAddress,
			tgtWeights,
			srcFacei,
			tgtFacei
		);

	if (!ok)
	{
		return;
	}


	// temporary storage for addressing and weights
	List<DynamicList<label>> srcAddr(this->srcPatch_.size());
	List<DynamicList<label>> tgtAddr(this->tgtPatch_.size());


	// construct weights and addressing
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// list of faces currently visited for srcFacei to avoid multiple hits
	DynamicList<label> srcSeeds(10);

	// list to keep track of tgt faces used to seed src faces
	labelList srcTgtSeed(srcAddr.size(), -1);
	srcTgtSeed[srcFacei] = tgtFacei;

	// list to keep track of whether src face can be mapped
	// 1 = mapped, 0 = untested, -1 = cannot map
	labelList mapFlag(srcAddr.size(), 0);

	label nTested = 0;
	DynamicList<label> nonOverlapFaces;
	do
	{
		srcAddr[srcFacei].append(tgtFacei);
		tgtAddr[tgtFacei].append(srcFacei);

		mapFlag[srcFacei] = 1;

		nTested++;

		// Do advancing front starting from srcFacei, tgtFacei
		appendToDirectSeeds
		(
			mapFlag,
			srcTgtSeed,
			srcSeeds,
			nonOverlapFaces,
			srcFacei,
			tgtFacei
		);

		if (srcFacei < 0 && nTested < this->srcPatch_.size())
		{
			restartAdvancingFront(mapFlag, nonOverlapFaces, srcFacei, tgtFacei);
		}

	} while (srcFacei >= 0);

	if (nonOverlapFaces.size() != 0)
	{
		Pout << "    AMI: " << nonOverlapFaces.size()
			<< " non-overlap faces identified"
			<< endl;

		this->srcNonOverlap_.transfer(nonOverlapFaces);
	}

	// transfer data to persistent storage
	forAll(srcAddr, i)
	{
		srcAddress[i].transfer(srcAddr[i]);
		srcWeights[i] = scalarList(1, 1.0);
	}
	forAll(tgtAddr, i)
	{
		tgtAddress[i].transfer(tgtAddr[i]);
		tgtWeights[i] = scalarList(1, 1.0);
	}
}


// ************************************************************************* //