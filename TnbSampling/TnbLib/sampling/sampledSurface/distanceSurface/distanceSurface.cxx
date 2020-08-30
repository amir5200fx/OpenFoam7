#include <distanceSurface.hxx>

#include <addToRunTimeSelectionTable.hxx>

#include <volFields.hxx>  // added by amir
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSurfaces
	{
		defineTypeNameAndDebug(distanceSurface, 0);
		addToRunTimeSelectionTable(sampledSurface, distanceSurface, word);
	}
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSurfaces::distanceSurface::createGeometry()
{
	if (debug)
	{
		Pout << "distanceSurface::createGeometry :updating geometry." << endl;
	}

	// Clear any stored topologies
	isoSurfPtr_.clear();

	// Clear derived data
	clearGeom();

	const fvMesh& mesh = static_cast<const fvMesh&>(this->mesh());

	// Distance to cell centres
	// ~~~~~~~~~~~~~~~~~~~~~~~~

	cellDistancePtr_.reset
	(
		new volScalarField
		(
			IOobject
			(
				"cellDistance",
				mesh.time().timeName(),
				mesh.time(),
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			),
			mesh,
			dimensionedScalar(dimLength, 0)
		)
	);
	volScalarField& cellDistance = cellDistancePtr_();

	// Internal field
	{
		const pointField& cc = mesh.C();
		scalarField& fld = cellDistance.primitiveFieldRef();

		List<pointIndexHit> nearest;
		surfPtr_().findNearest
		(
			cc,
			scalarField(cc.size(), great),
			nearest
		);

		if (signed_)
		{
			List<volumeType> volType;

			surfPtr_().getVolumeType(cc, volType);

			forAll(volType, i)
			{
				volumeType vT = volType[i];

				if (vT == volumeType::outside)
				{
					fld[i] = tnbLib::mag(cc[i] - nearest[i].hitPoint());
				}
				else if (vT == volumeType::inside)
				{
					fld[i] = -tnbLib::mag(cc[i] - nearest[i].hitPoint());
				}
				else
				{
					FatalErrorInFunction
						<< "getVolumeType failure, neither INSIDE or OUTSIDE"
						<< exit(FatalError);
				}
			}
		}
		else
		{
			forAll(nearest, i)
			{
				fld[i] = tnbLib::mag(cc[i] - nearest[i].hitPoint());
			}
		}
	}

	volScalarField::Boundary& cellDistanceBf =
		cellDistance.boundaryFieldRef();

	// Patch fields
	{
		forAll(mesh.C().boundaryField(), patchi)
		{
			const pointField& cc = mesh.C().boundaryField()[patchi];
			fvPatchScalarField& fld = cellDistanceBf[patchi];

			List<pointIndexHit> nearest;
			surfPtr_().findNearest
			(
				cc,
				scalarField(cc.size(), great),
				nearest
			);

			if (signed_)
			{
				List<volumeType> volType;

				surfPtr_().getVolumeType(cc, volType);

				forAll(volType, i)
				{
					volumeType vT = volType[i];

					if (vT == volumeType::outside)
					{
						fld[i] = tnbLib::mag(cc[i] - nearest[i].hitPoint());
					}
					else if (vT == volumeType::inside)
					{
						fld[i] = -tnbLib::mag(cc[i] - nearest[i].hitPoint());
					}
					else
					{
						FatalErrorInFunction
							<< "getVolumeType failure, "
							<< "neither INSIDE or OUTSIDE"
							<< exit(FatalError);
					}
				}
			}
			else
			{
				forAll(nearest, i)
				{
					fld[i] = tnbLib::mag(cc[i] - nearest[i].hitPoint());
				}
			}
		}
	}


	// On processor patches the mesh.C() will already be the cell centre
	// on the opposite side so no need to swap cellDistance.


	// Distance to points
	pointDistance_.setSize(mesh.nPoints());
	{
		const pointField& pts = mesh.points();

		List<pointIndexHit> nearest;
		surfPtr_().findNearest
		(
			pts,
			scalarField(pts.size(), great),
			nearest
		);

		if (signed_)
		{
			List<volumeType> volType;

			surfPtr_().getVolumeType(pts, volType);

			forAll(volType, i)
			{
				volumeType vT = volType[i];

				if (vT == volumeType::outside)
				{
					pointDistance_[i] =
						tnbLib::mag(pts[i] - nearest[i].hitPoint());
				}
				else if (vT == volumeType::inside)
				{
					pointDistance_[i] =
						-tnbLib::mag(pts[i] - nearest[i].hitPoint());
				}
				else
				{
					FatalErrorInFunction
						<< "getVolumeType failure, neither INSIDE or OUTSIDE"
						<< exit(FatalError);
				}
			}
		}
		else
		{
			forAll(nearest, i)
			{
				pointDistance_[i] = tnbLib::mag(pts[i] - nearest[i].hitPoint());
			}
		}
	}


	if (debug)
	{
		Pout << "Writing cell distance:" << cellDistance.objectPath() << endl;
		cellDistance.write();
		pointScalarField pDist
		(
			IOobject
			(
				"pointDistance",
				mesh.time().timeName(),
				mesh.time(),
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			),
			pointMesh::New(mesh),
			dimensionedScalar(dimLength, 0)
		);
		pDist.primitiveFieldRef() = pointDistance_;

		Pout << "Writing point distance:" << pDist.objectPath() << endl;
		pDist.write();
	}


	//- Direct from cell field and point field.
	isoSurfPtr_.reset
	(
		new isoSurface
		(
			mesh,
			cellDistance,
			pointDistance_,
			distance_,
			regularise_ ? isoSurface::DIAGCELL : isoSurface::NONE
		)
	);

	if (debug)
	{
		print(Pout);
		Pout << endl;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::distanceSurface::distanceSurface
(
	const word& name,
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	sampledSurface(name, mesh, dict),
	surfPtr_
	(
		searchableSurface::New
		(
			dict.lookup("surfaceType"),
			IOobject
			(
				dict.lookupOrDefault("surfaceName", name),  // name
				mesh.time().constant(),                     // directory
				"triSurface",                               // instance
				mesh.time(),                                // registry
				IOobject::MUST_READ,
				IOobject::NO_WRITE
			),
			dict
		)
	),
	distance_(readScalar(dict.lookup("distance"))),
	signed_(readBool(dict.lookup("signed"))),
	regularise_(dict.lookupOrDefault("regularise", true)),
	average_(dict.lookupOrDefault("average", false)),
	zoneKey_(keyType::null),
	needsUpdate_(true),
	isoSurfPtr_(nullptr)
{}


tnbLib::sampledSurfaces::distanceSurface::distanceSurface
(
	const word& name,
	const polyMesh& mesh,
	const bool interpolate,
	const word& surfaceType,
	const word& surfaceName,
	const scalar distance,
	const bool signedDistance,
	const Switch regularise,
	const Switch average
)
	:
	sampledSurface(name, mesh, interpolate),
	surfPtr_
	(
		searchableSurface::New
		(
			surfaceType,
			IOobject
			(
				surfaceName,  // name
				mesh.time().constant(),                     // directory
				"triSurface",                               // instance
				mesh.time(),                                // registry
				IOobject::MUST_READ,
				IOobject::NO_WRITE
			),
			dictionary()
		)
	),
	distance_(distance),
	signed_(signedDistance),
	regularise_(regularise),
	average_(average),
	zoneKey_(keyType::null),
	needsUpdate_(true),
	isoSurfPtr_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::distanceSurface::~distanceSurface()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::sampledSurfaces::distanceSurface::needsUpdate() const
{
	return needsUpdate_;
}


bool tnbLib::sampledSurfaces::distanceSurface::expire()
{
	if (debug)
	{
		Pout << "distanceSurface::expire :"
			<< " needsUpdate_:" << needsUpdate_ << endl;
	}

	// Clear derived data
	clearGeom();

	// already marked as expired
	if (needsUpdate_)
	{
		return false;
	}

	needsUpdate_ = true;
	return true;
}


bool tnbLib::sampledSurfaces::distanceSurface::update()
{
	if (debug)
	{
		Pout << "distanceSurface::update :"
			<< " needsUpdate_:" << needsUpdate_ << endl;
	}

	if (!needsUpdate_)
	{
		return false;
	}

	createGeometry();

	needsUpdate_ = false;
	return true;
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::sampledSurfaces::distanceSurface::sample
(
	const volScalarField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::vectorField>
tnbLib::sampledSurfaces::distanceSurface::sample
(
	const volVectorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::sphericalTensorField>
tnbLib::sampledSurfaces::distanceSurface::sample
(
	const volSphericalTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::symmTensorField>
tnbLib::sampledSurfaces::distanceSurface::sample
(
	const volSymmTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::tensorField>
tnbLib::sampledSurfaces::distanceSurface::sample
(
	const volTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::sampledSurfaces::distanceSurface::interpolate
(
	const interpolation<scalar>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::vectorField>
tnbLib::sampledSurfaces::distanceSurface::interpolate
(
	const interpolation<vector>& interpolator
) const
{
	return interpolateField(interpolator);
}

tnbLib::tmp<tnbLib::sphericalTensorField>
tnbLib::sampledSurfaces::distanceSurface::interpolate
(
	const interpolation<sphericalTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::symmTensorField>
tnbLib::sampledSurfaces::distanceSurface::interpolate
(
	const interpolation<symmTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::tensorField>
tnbLib::sampledSurfaces::distanceSurface::interpolate
(
	const interpolation<tensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


void tnbLib::sampledSurfaces::distanceSurface::print(Ostream& os) const
{
	os << "distanceSurface: " << name() << " :"
		<< "  surface:" << surfPtr_().name()
		<< "  distance:" << distance_
		<< "  faces:" << faces().size()
		<< "  points:" << points().size();
}


// ************************************************************************* //