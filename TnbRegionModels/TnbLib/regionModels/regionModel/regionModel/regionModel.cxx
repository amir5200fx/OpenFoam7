#include <regionModel.hxx>

#include <fvMesh.hxx>
#include <Time.hxx>
#include <mappedWallPolyPatch.hxx>
#include <zeroGradientFvPatchFields.hxx>

#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		defineTypeNameAndDebug(regionModel, 0);
	}
}

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void tnbLib::regionModels::regionModel::constructMeshObjects()
{
	// construct region mesh
	if (!time_.foundObject<fvMesh>(regionName_))
	{
		regionMeshPtr_.reset
		(
			new fvMesh
			(
				IOobject
				(
					regionName_,
					time_.timeName(),
					time_,
					IOobject::MUST_READ
				)
			)
		);
	}
}


void tnbLib::regionModels::regionModel::initialise()
{
	if (debug)
	{
		Pout << "regionModel::initialise()" << endl;
	}

	label nBoundaryFaces = 0;
	DynamicList<label> primaryPatchIDs;
	DynamicList<label> intCoupledPatchIDs;
	const polyBoundaryMesh& rbm = regionMesh().boundaryMesh();

	forAll(rbm, patchi)
	{
		const polyPatch& regionPatch = rbm[patchi];
		if (isA<mappedPatchBase>(regionPatch))
		{
			if (debug)
			{
				Pout << "found " << mappedWallPolyPatch::typeName
					<< " " << regionPatch.name() << endl;
			}

			intCoupledPatchIDs.append(patchi);

			nBoundaryFaces += regionPatch.faceCells().size();

			const mappedPatchBase& mapPatch =
				refCast<const mappedPatchBase>(regionPatch);

			if
				(
					primaryMesh_.time().foundObject<polyMesh>
					(
						mapPatch.sampleRegion()
						)
					)
			{

				const label primaryPatchi = mapPatch.samplePolyPatch().index();
				primaryPatchIDs.append(primaryPatchi);
			}
		}
	}

	primaryPatchIDs_.transfer(primaryPatchIDs);
	intCoupledPatchIDs_.transfer(intCoupledPatchIDs);

	if (returnReduce(nBoundaryFaces, sumOp<label>()) == 0)
	{
		WarningInFunction
			<< "Region model has no mapped boundary conditions - transfer "
			<< "between regions will not be possible" << endl;
	}

	if (!outputPropertiesPtr_.valid())
	{
		const fileName uniformPath(word("uniform") / "regionModels");

		outputPropertiesPtr_.reset
		(
			new IOdictionary
			(
				IOobject
				(
					regionName_ + "OutputProperties",
					time_.timeName(),
					uniformPath / regionName_,
					primaryMesh_,
					IOobject::READ_IF_PRESENT,
					IOobject::NO_WRITE
				)
			)
		);
	}
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

bool tnbLib::regionModels::regionModel::read()
{
	if (regIOobject::read())
	{
		if (active_)
		{
			if (const dictionary* dictPtr = subDictPtr(modelName_ + "Coeffs"))
			{
				coeffs_ <<= *dictPtr;
			}

			infoOutput_.readIfPresent("infoOutput", *this);
		}

		return true;
	}
	else
	{
		return false;
	}
}


bool tnbLib::regionModels::regionModel::read(const dictionary& dict)
{
	if (active_)
	{
		if (const dictionary* dictPtr = dict.subDictPtr(modelName_ + "Coeffs"))
		{
			coeffs_ <<= *dictPtr;
		}

		infoOutput_.readIfPresent("infoOutput", dict);

		return true;
	}
	else
	{
		return false;
	}
}


const tnbLib::AMIInterpolation&
tnbLib::regionModels::regionModel::interRegionAMI
(
	const regionModel& nbrRegion,
	const label regionPatchi,
	const label nbrPatchi,
	const bool flip
) const
{
	label nbrRegionID = findIndex(interRegionAMINames_, nbrRegion.name());

	const fvMesh& nbrRegionMesh = nbrRegion.regionMesh();

	if (nbrRegionID != -1)
	{
		if (!interRegionAMI_[nbrRegionID].set(regionPatchi))
		{
			const polyPatch& p = regionMesh().boundaryMesh()[regionPatchi];
			const polyPatch& nbrP = nbrRegionMesh.boundaryMesh()[nbrPatchi];

			int oldTag = UPstream::msgType();
			UPstream::msgType() = oldTag + 1;

			interRegionAMI_[nbrRegionID].set
			(
				regionPatchi,
				new AMIInterpolation
				(
					p,
					nbrP,
					faceAreaIntersect::tmMesh,
					true,
					AMIInterpolation::imFaceAreaWeight,
					-1,
					flip
				)
			);

			UPstream::msgType() = oldTag;
		}

		return interRegionAMI_[nbrRegionID][regionPatchi];
	}
	else
	{
		label nbrRegionID = interRegionAMINames_.size();

		interRegionAMINames_.append(nbrRegion.name());

		const polyPatch& p = regionMesh().boundaryMesh()[regionPatchi];
		const polyPatch& nbrP = nbrRegionMesh.boundaryMesh()[nbrPatchi];

		label nPatch = regionMesh().boundaryMesh().size();


		interRegionAMI_.resize(nbrRegionID + 1);

		interRegionAMI_.set
		(
			nbrRegionID,
			new PtrList<AMIInterpolation>(nPatch)
		);

		int oldTag = UPstream::msgType();
		UPstream::msgType() = oldTag + 1;

		interRegionAMI_[nbrRegionID].set
		(
			regionPatchi,
			new AMIInterpolation
			(
				p,
				nbrP,
				faceAreaIntersect::tmMesh,
				true,
				AMIInterpolation::imFaceAreaWeight,
				-1,
				flip
			)
		);

		UPstream::msgType() = oldTag;

		return interRegionAMI_[nbrRegionID][regionPatchi];
	}
}


tnbLib::label tnbLib::regionModels::regionModel::nbrCoupledPatchID
(
	const regionModel& nbrRegion,
	const label regionPatchi
) const
{
	label nbrPatchi = -1;

	// region
	const fvMesh& nbrRegionMesh = nbrRegion.regionMesh();

	// boundary mesh
	const polyBoundaryMesh& nbrPbm = nbrRegionMesh.boundaryMesh();

	const polyBoundaryMesh& pbm = regionMesh().boundaryMesh();

	if (regionPatchi > pbm.size() - 1)
	{
		FatalErrorInFunction
			<< "region patch index out of bounds: "
			<< "region patch index = " << regionPatchi
			<< ", maximum index = " << pbm.size() - 1
			<< abort(FatalError);
	}

	const polyPatch& pp = regionMesh().boundaryMesh()[regionPatchi];

	if (!isA<mappedPatchBase>(pp))
	{
		FatalErrorInFunction
			<< "Expected a " << mappedPatchBase::typeName
			<< " patch, but found a " << pp.type() << abort(FatalError);
	}

	const mappedPatchBase& mpb = refCast<const mappedPatchBase>(pp);

	// sample patch name on the primary region
	const word& primaryPatchName = mpb.samplePatch();

	// find patch on nbr region that has the same sample patch name
	forAll(nbrRegion.intCoupledPatchIDs(), j)
	{
		const label nbrRegionPatchi = nbrRegion.intCoupledPatchIDs()[j];

		const mappedPatchBase& mpb =
			refCast<const mappedPatchBase>(nbrPbm[nbrRegionPatchi]);

		if (mpb.samplePatch() == primaryPatchName)
		{
			nbrPatchi = nbrRegionPatchi;
			break;
		}
	}

	if (nbrPatchi == -1)
	{
		const polyPatch& p = regionMesh().boundaryMesh()[regionPatchi];

		FatalErrorInFunction
			<< "Unable to find patch pair for local patch "
			<< p.name() << " and region " << nbrRegion.name()
			<< abort(FatalError);
	}

	return nbrPatchi;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::regionModels::regionModel::regionModel
(
	const fvMesh& mesh,
	const word& regionType
)
	:
	IOdictionary
	(
		IOobject
		(
			regionType + "Properties",
			mesh.time().constant(),
			mesh.time(),
			IOobject::NO_READ,
			IOobject::NO_WRITE
		)
	),
	primaryMesh_(mesh),
	time_(mesh.time()),
	active_(false),
	infoOutput_(false),
	modelName_("none"),
	regionMeshPtr_(nullptr),
	coeffs_(dictionary::null),
	outputPropertiesPtr_(nullptr),
	primaryPatchIDs_(),
	intCoupledPatchIDs_(),
	regionName_("none"),
	functions_(*this),
	interRegionAMINames_(),
	interRegionAMI_()
{}


tnbLib::regionModels::regionModel::regionModel
(
	const fvMesh& mesh,
	const word& regionType,
	const word& modelName,
	bool readFields
)
	:
	IOdictionary
	(
		IOobject
		(
			regionType + "Properties",
			mesh.time().constant(),
			mesh.time(),
			IOobject::MUST_READ,
			IOobject::NO_WRITE
		)
	),
	primaryMesh_(mesh),
	time_(mesh.time()),
	active_(lookup("active")),
	infoOutput_(true),
	modelName_(modelName),
	regionMeshPtr_(nullptr),
	coeffs_(subOrEmptyDict(modelName + "Coeffs")),
	outputPropertiesPtr_(nullptr),
	primaryPatchIDs_(),
	intCoupledPatchIDs_(),
	regionName_(lookup("regionName")),
	functions_(*this, subOrEmptyDict("functions"))
{
	if (active_)
	{
		constructMeshObjects();
		initialise();

		if (readFields)
		{
			read();
		}
	}
}


tnbLib::regionModels::regionModel::regionModel
(
	const fvMesh& mesh,
	const word& regionType,
	const word& modelName,
	const dictionary& dict,
	bool readFields
)
	:
	IOdictionary
	(
		IOobject
		(
			regionType + "Properties",
			mesh.time().constant(),
			mesh.time(),
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			true
		),
		dict
	),
	primaryMesh_(mesh),
	time_(mesh.time()),
	active_(dict.lookup("active")),
	infoOutput_(false),
	modelName_(modelName),
	regionMeshPtr_(nullptr),
	coeffs_(dict.subOrEmptyDict(modelName + "Coeffs")),
	outputPropertiesPtr_(nullptr),
	primaryPatchIDs_(),
	intCoupledPatchIDs_(),
	regionName_(dict.lookup("regionName")),
	functions_(*this, subOrEmptyDict("functions"))
{
	if (active_)
	{
		constructMeshObjects();
		initialise();

		if (readFields)
		{
			read(dict);
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::regionModels::regionModel::~regionModel()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::regionModels::regionModel::evolve()
{
	if (active_)
	{
		Info << "\nEvolving " << modelName_ << " for region "
			<< regionMesh().name() << endl;

		// read();

		preEvolveRegion();

		evolveRegion();

		postEvolveRegion();

		// Provide some feedback
		if (infoOutput_)
		{
			Info << incrIndent;
			info();
			Info << endl << decrIndent;
		}

		if (time_.writeTime())
		{
			outputProperties().writeObject
			(
				IOstream::ASCII,
				IOstream::currentVersion,
				time_.writeCompression(),
				true
			);
		}
	}
}


void tnbLib::regionModels::regionModel::preEvolveRegion()
{
	functions_.preEvolveRegion();
}


void tnbLib::regionModels::regionModel::evolveRegion()
{}


void tnbLib::regionModels::regionModel::postEvolveRegion()
{
	functions_.postEvolveRegion();
}


void tnbLib::regionModels::regionModel::info()
{}


// ************************************************************************* //