#include <surfaceFieldValue.hxx>

#include <fvMesh.hxx>
#include <cyclicPolyPatch.hxx>
#include <emptyPolyPatch.hxx>
#include <coupledPolyPatch.hxx>
#include <sampledSurface.hxx>
#include <mergePoints.hxx>
#include <indirectPrimitivePatch.hxx>
#include <PatchTools.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <surfaceWriter.hxx>  // added by amir
#include <fvsPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		namespace fieldValues
		{
			defineTypeNameAndDebug(surfaceFieldValue, 0);
			addToRunTimeSelectionTable(fieldValue, surfaceFieldValue, dictionary);
			addToRunTimeSelectionTable(functionObject, surfaceFieldValue, dictionary);
		}
	}
}

//template<>
//const char* tnbLib::NamedEnum
//<
//	tnbLib::functionObjects::fieldValues::surfaceFieldValue::regionTypes,
//	3
//>::names[] =
//{
//	"faceZone",
//	"patch",
//	"sampledSurface"
//};
//
//template<>
//const char* tnbLib::NamedEnum
//<
//	tnbLib::functionObjects::fieldValues::surfaceFieldValue::operationType,
//	17
//>::names[] =
//{
//	"none",
//	"sum",
//	"weightedSum",
//	"sumMag",
//	"sumDirection",
//	"sumDirectionBalance",
//	"average",
//	"weightedAverage",
//	"areaAverage",
//	"weightedAreaAverage",
//	"areaIntegrate",
//	"weightedAreaIntegrate",
//	"min",
//	"max",
//	"CoV",
//	"areaNormalAverage",
//	"areaNormalIntegrate"
//};
//
//const tnbLib::NamedEnum
//<
//	tnbLib::functionObjects::fieldValues::surfaceFieldValue::regionTypes,
//	3
//> tnbLib::functionObjects::fieldValues::surfaceFieldValue::regionTypeNames_;
//
//const tnbLib::NamedEnum
//<
//	tnbLib::functionObjects::fieldValues::surfaceFieldValue::operationType,
//	17
//> tnbLib::functionObjects::fieldValues::surfaceFieldValue::operationTypeNames_;


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::fieldValues::surfaceFieldValue::setFaceZoneFaces()
{
	label zoneId = mesh_.faceZones().findZoneID(regionName_);

	if (zoneId < 0)
	{
		FatalErrorInFunction
			<< type() << " " << name() << ": "
			<< regionTypeNames_[regionType_] << "(" << regionName_ << "):" << nl
			<< "    Unknown face zone name: " << regionName_
			<< ". Valid face zones are: " << mesh_.faceZones().names()
			<< nl << exit(FatalError);
	}

	const faceZone& fZone = mesh_.faceZones()[zoneId];

	DynamicList<label> faceIds(fZone.size());
	DynamicList<label> facePatchIds(fZone.size());
	DynamicList<label> faceSigns(fZone.size());

	forAll(fZone, i)
	{
		label facei = fZone[i];

		label faceId = -1;
		label facePatchId = -1;
		if (mesh_.isInternalFace(facei))
		{
			faceId = facei;
			facePatchId = -1;
		}
		else
		{
			facePatchId = mesh_.boundaryMesh().whichPatch(facei);
			const polyPatch& pp = mesh_.boundaryMesh()[facePatchId];
			if (isA<coupledPolyPatch>(pp))
			{
				if (refCast<const coupledPolyPatch>(pp).owner())
				{
					faceId = pp.whichFace(facei);
				}
				else
				{
					faceId = -1;
				}
			}
			else if (!isA<emptyPolyPatch>(pp))
			{
				faceId = facei - pp.start();
			}
			else
			{
				faceId = -1;
				facePatchId = -1;
			}
		}

		if (faceId >= 0)
		{
			if (fZone.flipMap()[i])
			{
				faceSigns.append(-1);
			}
			else
			{
				faceSigns.append(1);
			}
			faceIds.append(faceId);
			facePatchIds.append(facePatchId);
		}
	}

	faceId_.transfer(faceIds);
	facePatchId_.transfer(facePatchIds);
	faceSign_.transfer(faceSigns);
	nFaces_ = returnReduce(faceId_.size(), sumOp<label>());

	if (debug)
	{
		Pout << "Original face zone size = " << fZone.size()
			<< ", new size = " << faceId_.size() << endl;
	}
}


void tnbLib::functionObjects::fieldValues::surfaceFieldValue::setPatchFaces()
{
	const label patchid = mesh_.boundaryMesh().findPatchID(regionName_);

	if (patchid < 0)
	{
		FatalErrorInFunction
			<< type() << " " << name() << ": "
			<< regionTypeNames_[regionType_] << "(" << regionName_ << "):" << nl
			<< "    Unknown patch name: " << regionName_
			<< ". Valid patch names are: "
			<< mesh_.boundaryMesh().names() << nl
			<< exit(FatalError);
	}

	const polyPatch& pp = mesh_.boundaryMesh()[patchid];

	label nFaces = pp.size();
	if (isA<emptyPolyPatch>(pp))
	{
		nFaces = 0;
	}

	faceId_.setSize(nFaces);
	facePatchId_.setSize(nFaces);
	faceSign_.setSize(nFaces);
	nFaces_ = returnReduce(faceId_.size(), sumOp<label>());

	forAll(faceId_, facei)
	{
		faceId_[facei] = facei;
		facePatchId_[facei] = patchid;
		faceSign_[facei] = 1;
	}
}


void tnbLib::functionObjects::fieldValues::surfaceFieldValue::sampledSurfaceFaces
(
	const dictionary& dict
)
{
	surfacePtr_ = sampledSurface::New
	(
		name(),
		mesh_,
		dict.subDict("sampledSurfaceDict")
	);
	surfacePtr_().update();
	nFaces_ = returnReduce(surfacePtr_().faces().size(), sumOp<label>());
}


void tnbLib::functionObjects::fieldValues::surfaceFieldValue::combineMeshGeometry
(
	faceList& faces,
	pointField& points
) const
{
	List<faceList> allFaces(Pstream::nProcs());
	List<pointField> allPoints(Pstream::nProcs());

	labelList globalFacesIs(faceId_);
	forAll(globalFacesIs, i)
	{
		if (facePatchId_[i] != -1)
		{
			label patchi = facePatchId_[i];
			globalFacesIs[i] += mesh_.boundaryMesh()[patchi].start();
		}
	}

	// Add local faces and points to the all* lists
	indirectPrimitivePatch pp
	(
		IndirectList<face>(mesh_.faces(), globalFacesIs),
		mesh_.points()
	);
	allFaces[Pstream::myProcNo()] = pp.localFaces();
	allPoints[Pstream::myProcNo()] = pp.localPoints();

	Pstream::gatherList(allFaces);
	Pstream::gatherList(allPoints);

	// Renumber and flatten
	label nFaces = 0;
	label nPoints = 0;
	forAll(allFaces, proci)
	{
		nFaces += allFaces[proci].size();
		nPoints += allPoints[proci].size();
	}

	faces.setSize(nFaces);
	points.setSize(nPoints);

	nFaces = 0;
	nPoints = 0;

	// My own data first
	{
		const faceList& fcs = allFaces[Pstream::myProcNo()];
		forAll(fcs, i)
		{
			const face& f = fcs[i];
			face& newF = faces[nFaces++];
			newF.setSize(f.size());
			forAll(f, fp)
			{
				newF[fp] = f[fp] + nPoints;
			}
		}

		const pointField& pts = allPoints[Pstream::myProcNo()];
		forAll(pts, i)
		{
			points[nPoints++] = pts[i];
		}
	}

	// Other proc data follows
	forAll(allFaces, proci)
	{
		if (proci != Pstream::myProcNo())
		{
			const faceList& fcs = allFaces[proci];
			forAll(fcs, i)
			{
				const face& f = fcs[i];
				face& newF = faces[nFaces++];
				newF.setSize(f.size());
				forAll(f, fp)
				{
					newF[fp] = f[fp] + nPoints;
				}
			}

			const pointField& pts = allPoints[proci];
			forAll(pts, i)
			{
				points[nPoints++] = pts[i];
			}
		}
	}

	// Merge
	labelList oldToNew;
	pointField newPoints;
	bool hasMerged = mergePoints
	(
		points,
		small,
		false,
		oldToNew,
		newPoints
	);

	if (hasMerged)
	{
		if (debug)
		{
			Pout << "Merged from " << points.size()
				<< " down to " << newPoints.size() << " points" << endl;
		}

		points.transfer(newPoints);
		forAll(faces, i)
		{
			inplaceRenumber(oldToNew, faces[i]);
		}
	}
}


void tnbLib::functionObjects::fieldValues::surfaceFieldValue::
combineSurfaceGeometry
(
	faceList& faces,
	pointField& points
) const
{
	if (surfacePtr_.valid())
	{
		const sampledSurface& s = surfacePtr_();

		if (Pstream::parRun())
		{
			// Dimension as fraction of mesh bounding box
			scalar mergeDim = 1e-10*mesh_.bounds().mag();

			labelList pointsMap;

			PatchTools::gatherAndMerge
			(
				mergeDim,
				primitivePatch
				(
					SubList<face>(s.faces(), s.faces().size()),
					s.points()
				),
				points,
				faces,
				pointsMap
			);
		}
		else
		{
			faces = s.faces();
			points = s.points();
		}
	}
}


tnbLib::scalar
tnbLib::functionObjects::fieldValues::surfaceFieldValue::totalArea() const
{
	scalar totalArea;

	if (surfacePtr_.valid())
	{
		totalArea = gSum(surfacePtr_().magSf());
	}
	else
	{
		totalArea = gSum(filterField(mesh_.magSf(), false));
	}

	return totalArea;
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::fieldValues::surfaceFieldValue::initialise
(
	const dictionary& dict
)
{
	dict.lookup("name") >> regionName_;

	switch (regionType_)
	{
	case regionTypes::faceZone:
	{
		setFaceZoneFaces();
		break;
	}
	case regionTypes::patch:
	{
		setPatchFaces();
		break;
	}
	case regionTypes::sampledSurface:
	{
		sampledSurfaceFaces(dict);
		break;
	}
	default:
	{
		FatalErrorInFunction
			<< type() << " " << name() << ": "
			<< regionTypeNames_[regionType_] << "(" << regionName_ << "):"
			<< nl << "    Unknown region type. Valid region types are:"
			<< regionTypeNames_.sortedToc() << nl << exit(FatalError);
	}
	}

	if (nFaces_ == 0)
	{
		FatalErrorInFunction
			<< type() << " " << name() << ": "
			<< regionTypeNames_[regionType_] << "(" << regionName_ << "):" << nl
			<< "    Region has no faces" << exit(FatalError);
	}

	if (surfacePtr_.valid())
	{
		surfacePtr_().update();
	}

	totalArea_ = totalArea();

	Info << type() << " " << name() << ":" << nl
		<< "    total faces  = " << nFaces_
		<< nl
		<< "    total area   = " << totalArea_
		<< nl;

	if (dict.readIfPresent("weightField", weightFieldName_))
	{
		Info << "    weight field = " << weightFieldName_ << nl;

		if (regionType_ == regionTypes::sampledSurface)
		{
			FatalIOErrorInFunction(dict)
				<< "Cannot use weightField for a sampledSurface"
				<< exit(FatalIOError);
		}
	}

	if (dict.found("orientedWeightField"))
	{
		if (weightFieldName_ == "none")
		{
			dict.lookup("orientedWeightField") >> weightFieldName_;
			Info << "    weight field = " << weightFieldName_ << nl;
			orientWeightField_ = true;
		}
		else
		{
			FatalIOErrorInFunction(dict)
				<< "Either weightField or orientedWeightField can be supplied, "
				<< "but not both"
				<< exit(FatalIOError);
		}
	}

	List<word> orientedFields;
	if (dict.readIfPresent("orientedFields", orientedFields))
	{
		orientedFieldsStart_ = fields_.size();
		fields_.append(orientedFields);
	}

	if (dict.readIfPresent("scaleFactor", scaleFactor_))
	{
		Info << "    scale factor = " << scaleFactor_ << nl;
	}

	Info << nl << endl;

	if (writeFields_)
	{
		const word surfaceFormat(dict.lookup("surfaceFormat"));

		surfaceWriterPtr_.reset
		(
			surfaceWriter::New
			(
				surfaceFormat,
				dict.subOrEmptyDict("formatOptions").
				subOrEmptyDict(surfaceFormat)
			).ptr()
		);
	}
}


void tnbLib::functionObjects::fieldValues::surfaceFieldValue::writeFileHeader
(
	const label i
)
{
	if (operation_ != operationType::none)
	{
		writeCommented(file(), "Region type : ");
		file() << regionTypeNames_[regionType_] << " " << regionName_ << endl;
		writeCommented(file(), "Faces  : ");
		file() << nFaces_ << endl;
		writeCommented(file(), "Area   : ");
		file() << totalArea_ << endl;

		writeCommented(file(), "Time");
		if (writeArea_)
		{
			file() << tab << "Area";
		}

		forAll(fields_, fieldi)
		{
			file()
				<< tab << operationTypeNames_[operation_]
				<< "(" << fields_[fieldi] << ")";
		}

		file() << endl;
	}
}


template<>
tnbLib::scalar tnbLib::functionObjects::fieldValues::surfaceFieldValue::
processValues
(
	const Field<scalar>& values,
	const vectorField& Sf,
	const scalarField& weightField
) const
{
	switch (operation_)
	{
	case operationType::sumDirection:
	{
		vector n(dict_.lookup("direction"));
		return sum(pos0(values*(Sf & n))*mag(values));
	}
	case operationType::sumDirectionBalance:
	{
		vector n(dict_.lookup("direction"));
		const scalarField nv(values*(Sf & n));

		return sum(pos0(nv)*mag(values) - neg(nv)*mag(values));
	}
	default:
	{
		// Fall through to other operations
		return processSameTypeValues(values, Sf, weightField);
	}
	}
}


template<>
tnbLib::vector tnbLib::functionObjects::fieldValues::surfaceFieldValue::
processValues
(
	const Field<vector>& values,
	const vectorField& Sf,
	const scalarField& weightField
) const
{
	switch (operation_)
	{
	case operationType::sumDirection:
	{
		vector n(dict_.lookup("direction"));
		n /= mag(n) + rootVSmall;
		const scalarField nv(n & values);

		return sum(pos0(nv)*n*(nv));
	}
	case operationType::sumDirectionBalance:
	{
		vector n(dict_.lookup("direction"));
		n /= mag(n) + rootVSmall;
		const scalarField nv(n & values);

		return sum(pos0(nv)*n*(nv));
	}
	case operationType::areaNormalAverage:
	{
		scalar result = sum(values & Sf) / sum(mag(Sf));
		return vector(result, 0.0, 0.0);
	}
	case operationType::areaNormalIntegrate:
	{
		scalar result = sum(values & Sf);
		return vector(result, 0.0, 0.0);
	}
	default:
	{
		// Fall through to other operations
		return processSameTypeValues(values, Sf, weightField);
	}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldValues::surfaceFieldValue::surfaceFieldValue
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fieldValue(name, runTime, dict, typeName),
	surfaceWriterPtr_(nullptr),
	regionType_(regionTypeNames_.read(dict.lookup("regionType"))),
	operation_(operationTypeNames_.read(dict.lookup("operation"))),
	weightFieldName_("none"),
	orientWeightField_(false),
	orientedFieldsStart_(labelMax),
	scaleFactor_(1.0),
	writeArea_(dict.lookupOrDefault("writeArea", false)),
	nFaces_(0),
	faceId_(),
	facePatchId_(),
	faceSign_()
{
	read(dict);
}

tnbLib::functionObjects::fieldValues::surfaceFieldValue::surfaceFieldValue
(
	const word& name,
	const objectRegistry& obr,
	const dictionary& dict
)
	:
	fieldValue(name, obr, dict, typeName),
	surfaceWriterPtr_(nullptr),
	regionType_(regionTypeNames_.read(dict.lookup("regionType"))),
	operation_(operationTypeNames_.read(dict.lookup("operation"))),
	weightFieldName_("none"),
	orientWeightField_(false),
	orientedFieldsStart_(labelMax),
	scaleFactor_(1.0),
	writeArea_(dict.lookupOrDefault("writeArea", false)),
	nFaces_(0),
	faceId_(),
	facePatchId_(),
	faceSign_()
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldValues::surfaceFieldValue::~surfaceFieldValue()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::fieldValues::surfaceFieldValue::read
(
	const dictionary& dict
)
{
	fieldValue::read(dict);
	initialise(dict);

	return true;
}


bool tnbLib::functionObjects::fieldValues::surfaceFieldValue::write()
{
	if (operation_ != operationType::none)
	{
		fieldValue::write();
	}

	if (surfacePtr_.valid())
	{
		surfacePtr_().update();
	}

	if (operation_ != operationType::none && Pstream::master())
	{
		writeTime(file());
	}

	if (writeArea_)
	{
		totalArea_ = totalArea();
		if (operation_ != operationType::none && Pstream::master())
		{
			file() << tab << totalArea_;
		}
		TnbLog << "    total area = " << totalArea_ << endl;
	}

	// Write the surface geometry
	if (surfaceWriterPtr_.valid())
	{
		faceList faces;
		pointField points;

		if (surfacePtr_.valid())
		{
			combineSurfaceGeometry(faces, points);
		}
		else
		{
			combineMeshGeometry(faces, points);
		}

		if (Pstream::master())
		{
			surfaceWriterPtr_->write
			(
				outputDir(),
				regionTypeNames_[regionType_] + ("_" + regionName_),
				points,
				faces,
				false
			);
		}
	}

	// Construct weight field. Note: zero size means weight = 1
	scalarField weightField;
	if (weightFieldName_ != "none")
	{
		weightField =
			getFieldValues<scalar>
			(
				weightFieldName_,
				true,
				orientWeightField_
				);
	}

	// Combine onto master
	combineFields(weightField);

	// Process the fields
	forAll(fields_, i)
	{
		const word& fieldName = fields_[i];
		bool ok = false;

		bool orient = i >= orientedFieldsStart_;
		ok = ok || writeValues<scalar>(fieldName, weightField, orient);
		ok = ok || writeValues<vector>(fieldName, weightField, orient);
		ok = ok
			|| writeValues<sphericalTensor>(fieldName, weightField, orient);
		ok = ok || writeValues<symmTensor>(fieldName, weightField, orient);
		ok = ok || writeValues<tensor>(fieldName, weightField, orient);

		if (!ok)
		{
			WarningInFunction
				<< "Requested field " << fieldName
				<< " not found in database and not processed"
				<< endl;
		}
	}

	if (operation_ != operationType::none && Pstream::master())
	{
		file() << endl;
	}

	TnbLog << endl;

	return true;
}


// ************************************************************************* //