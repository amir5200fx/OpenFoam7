#include <sampledPatch.hxx>

#include <surfaceFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <emptyPointPatchFields.hxx>  // added by amir
#include <indirectPrimitivePatch.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSurfaces
	{
		defineTypeNameAndDebug(patch, 0);
		addToRunTimeSelectionTable(sampledSurface, patch, word);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::patch::patch
(
	const word& name,
	const polyMesh& mesh,
	const wordReList& patchNames,
	const bool triangulate
)
	:
	sampledSurface(name, mesh),
	patchNames_(patchNames),
	triangulate_(triangulate),
	needsUpdate_(true)
{}


tnbLib::sampledSurfaces::patch::patch
(
	const word& name,
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	sampledSurface(name, mesh, dict),
	patchNames_(dict.lookup("patches")),
	triangulate_(dict.lookupOrDefault("triangulate", false)),
	needsUpdate_(true)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::patch::~patch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelList& tnbLib::sampledSurfaces::patch::patchIDs() const
{
	if (patchIDs_.empty())
	{
		patchIDs_ = mesh().boundaryMesh().patchSet
		(
			patchNames_,
			false
		).sortedToc();
	}
	return patchIDs_;
}


bool tnbLib::sampledSurfaces::patch::needsUpdate() const
{
	return needsUpdate_;
}


bool tnbLib::sampledSurfaces::patch::expire()
{
	// already marked as expired
	if (needsUpdate_)
	{
		return false;
	}

	sampledSurface::clearGeom();
	MeshStorage::clear();
	patchIDs_.clear();
	patchIndex_.clear();
	patchFaceLabels_.clear();
	patchStart_.clear();

	needsUpdate_ = true;
	return true;
}


bool tnbLib::sampledSurfaces::patch::update()
{
	if (!needsUpdate_)
	{
		return false;
	}

	label sz = 0;
	forAll(patchIDs(), i)
	{
		label patchi = patchIDs()[i];
		const polyPatch& pp = mesh().boundaryMesh()[patchi];

		if (isA<emptyPolyPatch>(pp))
		{
			FatalErrorInFunction
				<< "Cannot sample an empty patch. Patch " << pp.name()
				<< exit(FatalError);
		}

		sz += pp.size();
	}

	// For every face (or triangle) the originating patch and local face in the
	// patch.
	patchIndex_.setSize(sz);
	patchFaceLabels_.setSize(sz);
	patchStart_.setSize(patchIDs().size());
	labelList meshFaceLabels(sz);

	sz = 0;

	forAll(patchIDs(), i)
	{
		label patchi = patchIDs()[i];

		patchStart_[i] = sz;

		const polyPatch& pp = mesh().boundaryMesh()[patchi];

		forAll(pp, j)
		{
			patchIndex_[sz] = i;
			patchFaceLabels_[sz] = j;
			meshFaceLabels[sz] = pp.start() + j;
			sz++;
		}
	}

	indirectPrimitivePatch allPatches
	(
		IndirectList<face>(mesh().faces(), meshFaceLabels),
		mesh().points()
	);

	this->storedPoints() = allPatches.localPoints();
	this->storedFaces() = allPatches.localFaces();


	// triangulate uses remapFaces()
	// - this is somewhat less efficient since it recopies the faces
	// that we just created, but we probably don't want to do this
	// too often anyhow.
	if (triangulate_)
	{
		MeshStorage::triangulate();
	}

	if (debug)
	{
		print(Pout);
		Pout << endl;
	}

	needsUpdate_ = false;
	return true;
}


// remap action on triangulation
void tnbLib::sampledSurfaces::patch::remapFaces(const labelUList& faceMap)
{
	// recalculate the cells cut
	if (notNull(faceMap) && faceMap.size())
	{
		MeshStorage::remapFaces(faceMap);
		patchFaceLabels_ = labelList
		(
			UIndirectList<label>(patchFaceLabels_, faceMap)
		);
		patchIndex_ = labelList
		(
			UIndirectList<label>(patchIndex_, faceMap)
		);

		// Redo patchStart.
		if (patchIndex_.size() > 0)
		{
			patchStart_[patchIndex_[0]] = 0;
			for (label i = 1; i < patchIndex_.size(); i++)
			{
				if (patchIndex_[i] != patchIndex_[i - 1])
				{
					patchStart_[patchIndex_[i]] = i;
				}
			}
		}
	}
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::sampledSurfaces::patch::sample
(
	const volScalarField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::sampledSurfaces::patch::sample
(
	const volVectorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::sphericalTensorField> tnbLib::sampledSurfaces::patch::sample
(
	const volSphericalTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::symmTensorField> tnbLib::sampledSurfaces::patch::sample
(
	const volSymmTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::tensorField> tnbLib::sampledSurfaces::patch::sample
(
	const volTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::sampledSurfaces::patch::sample
(
	const surfaceScalarField& sField
) const
{
	return sampleField(sField);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::sampledSurfaces::patch::sample
(
	const surfaceVectorField& sField
) const
{
	return sampleField(sField);
}


tnbLib::tmp<tnbLib::sphericalTensorField> tnbLib::sampledSurfaces::patch::sample
(
	const surfaceSphericalTensorField& sField
) const
{
	return sampleField(sField);
}


tnbLib::tmp<tnbLib::symmTensorField> tnbLib::sampledSurfaces::patch::sample
(
	const surfaceSymmTensorField& sField
) const
{
	return sampleField(sField);
}


tnbLib::tmp<tnbLib::tensorField> tnbLib::sampledSurfaces::patch::sample
(
	const surfaceTensorField& sField
) const
{
	return sampleField(sField);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::sampledSurfaces::patch::interpolate
(
	const interpolation<scalar>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::sampledSurfaces::patch::interpolate
(
	const interpolation<vector>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::sphericalTensorField> tnbLib::sampledSurfaces::patch::interpolate
(
	const interpolation<sphericalTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::symmTensorField> tnbLib::sampledSurfaces::patch::interpolate
(
	const interpolation<symmTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::tensorField> tnbLib::sampledSurfaces::patch::interpolate
(
	const interpolation<tensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


void tnbLib::sampledSurfaces::patch::print(Ostream& os) const
{
	os << "patch: " << name() << " :"
		<< "  patches:" << patchNames()
		<< "  faces:" << faces().size()
		<< "  points:" << points().size();
}


// ************************************************************************* //