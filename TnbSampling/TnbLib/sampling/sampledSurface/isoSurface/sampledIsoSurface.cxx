#include <sampledIsoSurface.hxx>

#include <isoSurface.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx>  // added by amir
#include <volPointInterpolation.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSurfaces
	{
		defineTypeNameAndDebug(isoSurface, 0);
		addToRunTimeSelectionTable(sampledSurface, isoSurface, word);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::sampledSurfaces::isoSurface::updateGeometry() const
{
	const fvMesh& fvm = static_cast<const fvMesh&>(mesh());

	// no update needed
	if (fvm.time().timeIndex() == prevTimeIndex_)
	{
		return false;
	}

	prevTimeIndex_ = fvm.time().timeIndex();

	// Clear derived data
	sampledSurface::clearGeom();

	// Optionally read volScalarField
	autoPtr<volScalarField> readFieldPtr_;

	// 1. see if field in database
	// 2. see if field can be read
	const volScalarField* cellFldPtr = nullptr;
	if (fvm.foundObject<volScalarField>(isoField_))
	{
		if (debug)
		{
			InfoInFunction << "Lookup " << isoField_ << endl;
		}

		cellFldPtr = &fvm.lookupObject<volScalarField>(isoField_);
	}
	else
	{
		// Bit of a hack. Read field and store.

		if (debug)
		{
			InfoInFunction
				<< "Reading " << isoField_
				<< " from time " << fvm.time().timeName()
				<< endl;
		}

		readFieldPtr_.reset
		(
			new volScalarField
			(
				IOobject
				(
					isoField_,
					fvm.time().timeName(),
					fvm,
					IOobject::MUST_READ,
					IOobject::NO_WRITE,
					false
				),
				fvm
			)
		);

		cellFldPtr = readFieldPtr_.operator->();
	}
	const volScalarField& cellFld = *cellFldPtr;

	tmp<pointScalarField> pointFld
	(
		volPointInterpolation::New(fvm).interpolate(cellFld)
	);

	PtrList<tnbLib::isoSurface> isos(isoVals_.size());
	forAll(isos, isoi)
	{
		isos.set
		(
			isoi,
			new tnbLib::isoSurface
			(
				fvm,
				cellFld.primitiveField(),
				pointFld().primitiveField(),
				isoVals_[isoi],
				regularise_
				? tnbLib::isoSurface::DIAGCELL
				: tnbLib::isoSurface::NONE
			)
		);
	}

	if (isos.size() == 1)
	{
		// Straight transfer
		const_cast<isoSurface&>
			(
				*this
				).MeshedSurface<face>::transfer(isos[0]);
		meshCells_ = isos[0].meshCells();
	}
	else
	{
		label nFaces = 0;
		label nPoints = 0;
		forAll(isos, isoi)
		{
			nFaces += isos[isoi].size();
			nPoints += isos[isoi].points().size();
		}

		faceList allFaces(nFaces);
		labelList allMeshCells(nFaces);
		pointField allPoints(nPoints);

		nFaces = 0;
		nPoints = 0;
		forAll(isos, isoi)
		{
			tnbLib::isoSurface& iso = isos[isoi];

			SubList<face> subAll(allFaces, iso.size(), nFaces);
			subAll = iso;
			// Offset point indices
			if (nPoints > 0)
			{
				forAll(subAll, i)
				{
					face& f = subAll[i];
					forAll(f, fp)
					{
						f[fp] += nPoints;
					}
				}
			}
			SubList<label>(allMeshCells, iso.size(), nFaces) = iso.meshCells();
			nFaces += iso.size();

			const pointField& pts = iso.points();
			SubList<point>(allPoints, pts.size(), nPoints) = pts;
			nPoints += pts.size();

			// Clear out asap
			isos.set(isoi, nullptr);
		}

		if (nFaces != allFaces.size() || nPoints != allPoints.size())
		{
			FatalErrorInFunction << "nFaces:" << nFaces
				<< " nPoints:" << nPoints << exit(FatalError);
		}


		surfZoneList allZones(1);
		allZones[0] = surfZone
		(
			"allFaces",
			allFaces.size(),    // size
			0,                  // start
			0                   // index
		);

		// Transfer
		const_cast<isoSurface&>
			(
				*this
				).MeshedSurface<face>::reset
				(
					move(allPoints),
					move(allFaces),
					move(allZones)
				);
		meshCells_.transfer(allMeshCells);
	}
	if (debug)
	{
		Pout << "sampledSurfaces::isoSurface::updateGeometry() : "
			"constructed iso:"
			<< nl
			<< "    regularise     : " << regularise_ << nl
			<< "    isoField       : " << isoField_ << nl;
		if (isoVals_.size() == 1)
		{
			Pout << "    isoValue       : " << isoVals_[0] << nl;
		}
		else
		{
			Pout << "    isoValues      : " << isoVals_ << nl;
		}
		Pout << "    points         : " << points().size() << nl
			<< "    faces          : " << faces().size() << nl
			<< "    cut cells      : " << meshCells_.size() << endl;
	}

	return true;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::isoSurface::isoSurface
(
	const word& name,
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	sampledSurface(name, mesh, dict),
	isoField_(dict.lookup("isoField")),
	isoVals_
	(
		dict.found("isoValues")
		? scalarField(dict.lookup("isoValues"))
		: scalarField(1, readScalar(dict.lookup("isoValue")))
	),
	regularise_(dict.lookupOrDefault("regularise", true)),
	zoneKey_(keyType::null),
	prevTimeIndex_(-1),
	meshCells_(0)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::isoSurface::~isoSurface()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::sampledSurfaces::isoSurface::needsUpdate() const
{
	const fvMesh& fvm = static_cast<const fvMesh&>(mesh());

	return fvm.time().timeIndex() != prevTimeIndex_;
}


bool tnbLib::sampledSurfaces::isoSurface::expire()
{
	// Clear derived data
	sampledSurface::clearGeom();
	MeshedSurface<face>::clearGeom();

	// already marked as expired
	if (prevTimeIndex_ == -1)
	{
		return false;
	}

	// force update
	prevTimeIndex_ = -1;
	return true;
}


bool tnbLib::sampledSurfaces::isoSurface::update()
{
	return updateGeometry();
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::sampledSurfaces::isoSurface::sample
(
	const volScalarField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::vectorField>
tnbLib::sampledSurfaces::isoSurface::sample
(
	const volVectorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::sphericalTensorField>
tnbLib::sampledSurfaces::isoSurface::sample
(
	const volSphericalTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::symmTensorField>
tnbLib::sampledSurfaces::isoSurface::sample
(
	const volSymmTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::tensorField>
tnbLib::sampledSurfaces::isoSurface::sample
(
	const volTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::sampledSurfaces::isoSurface::interpolate
(
	const interpolation<scalar>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::vectorField>
tnbLib::sampledSurfaces::isoSurface::interpolate
(
	const interpolation<vector>& interpolator
) const
{
	return interpolateField(interpolator);
}

tnbLib::tmp<tnbLib::sphericalTensorField>
tnbLib::sampledSurfaces::isoSurface::interpolate
(
	const interpolation<sphericalTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::symmTensorField>
tnbLib::sampledSurfaces::isoSurface::interpolate
(
	const interpolation<symmTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::tensorField>
tnbLib::sampledSurfaces::isoSurface::interpolate
(
	const interpolation<tensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


void tnbLib::sampledSurfaces::isoSurface::print(Ostream& os) const
{
	os << "isoSurface: " << name() << " :"
		<< "  field:" << isoField_;
	if (isoVals_.size() == 1)
	{
		os << "  value:" << isoVals_[0];
	}
	else
	{
		os << "  values:" << isoVals_;
	}
	os << "  faces:" << faces().size()
		<< "  points:" << points().size();
}


// ************************************************************************* //