#include <sampledPlane.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSurfaces
	{
		defineTypeNameAndDebug(plane, 0);
		addToRunTimeSelectionTable(sampledSurface, plane, word);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::plane::plane
(
	const word& name,
	const polyMesh& mesh,
	const plane& planeDesc,
	const keyType& zoneKey,
	const bool triangulate
)
	:
	sampledSurface(name, mesh),
	cuttingPlane(planeDesc),
	zoneKey_(zoneKey),
	triangulate_(triangulate),
	needsUpdate_(true)
{
	if (debug && zoneKey_.size() && mesh.cellZones().findIndex(zoneKey_) < 0)
	{
		Info << "cellZone " << zoneKey_
			<< " not found - using entire mesh" << endl;
	}
}


tnbLib::sampledSurfaces::plane::plane
(
	const word& name,
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	sampledSurface(name, mesh, dict),
	cuttingPlane(tnbLib::plane(dict)),
	zoneKey_(keyType::null),
	triangulate_(dict.lookupOrDefault("triangulate", true)),
	needsUpdate_(true)
{
	// Make plane relative to the coordinateSystem (Cartesian)
	// allow lookup from global coordinate systems
	if (dict.found("coordinateSystem"))
	{
		coordinateSystem cs(mesh, dict.subDict("coordinateSystem"));

		point  base = cs.globalPosition(planeDesc().refPoint());
		vector norm = cs.globalVector(planeDesc().normal());

		// Assign the plane description
		static_cast<tnbLib::plane&>(*this) = tnbLib::plane(base, norm);
	}

	dict.readIfPresent("zone", zoneKey_);

	if (debug && zoneKey_.size() && mesh.cellZones().findIndex(zoneKey_) < 0)
	{
		Info << "cellZone " << zoneKey_
			<< " not found - using entire mesh" << endl;
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::plane::~plane()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::sampledSurfaces::plane::needsUpdate() const
{
	return needsUpdate_;
}


bool tnbLib::sampledSurfaces::plane::expire()
{
	// Already marked as expired
	if (needsUpdate_)
	{
		return false;
	}

	sampledSurface::clearGeom();

	needsUpdate_ = true;
	return true;
}


bool tnbLib::sampledSurfaces::plane::update()
{
	if (!needsUpdate_)
	{
		return false;
	}

	sampledSurface::clearGeom();

	labelList selectedCells = mesh().cellZones().findMatching(zoneKey_).used();

	if (selectedCells.empty())
	{
		reCut(mesh(), triangulate_);
	}
	else
	{
		reCut(mesh(), triangulate_, selectedCells);
	}

	if (debug)
	{
		print(Pout);
		Pout << endl;
	}

	needsUpdate_ = false;
	return true;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::sampledSurfaces::plane::sample
(
	const volScalarField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::sampledSurfaces::plane::sample
(
	const volVectorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::sphericalTensorField> tnbLib::sampledSurfaces::plane::sample
(
	const volSphericalTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::symmTensorField> tnbLib::sampledSurfaces::plane::sample
(
	const volSymmTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::tensorField> tnbLib::sampledSurfaces::plane::sample
(
	const volTensorField& vField
) const
{
	return sampleField(vField);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::sampledSurfaces::plane::interpolate
(
	const interpolation<scalar>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::sampledSurfaces::plane::interpolate
(
	const interpolation<vector>& interpolator
) const
{
	return interpolateField(interpolator);
}

tnbLib::tmp<tnbLib::sphericalTensorField> tnbLib::sampledSurfaces::plane::interpolate
(
	const interpolation<sphericalTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::symmTensorField> tnbLib::sampledSurfaces::plane::interpolate
(
	const interpolation<symmTensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


tnbLib::tmp<tnbLib::tensorField> tnbLib::sampledSurfaces::plane::interpolate
(
	const interpolation<tensor>& interpolator
) const
{
	return interpolateField(interpolator);
}


void tnbLib::sampledSurfaces::plane::print(Ostream& os) const
{
	os << "plane: " << name() << " :"
		<< "  base:" << refPoint()
		<< "  normal:" << normal()
		<< "  triangulate:" << triangulate_
		<< "  faces:" << faces().size()
		<< "  points:" << points().size();
}


// ************************************************************************* //