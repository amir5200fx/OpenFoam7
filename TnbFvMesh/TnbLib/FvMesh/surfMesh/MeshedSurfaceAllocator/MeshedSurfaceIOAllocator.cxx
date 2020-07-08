#include <MeshedSurfaceIOAllocator.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::MeshedSurfaceIOAllocator::MeshedSurfaceIOAllocator
(
	const IOobject& ioPoints,
	const IOobject& ioFaces,
	const IOobject& ioZones
)
	:
	points_(ioPoints),
	faces_(ioFaces),
	zones_(ioZones)
{}


tnbLib::MeshedSurfaceIOAllocator::MeshedSurfaceIOAllocator
(
	const IOobject& ioPoints,
	const pointField& points,
	const IOobject& ioFaces,
	const faceList& faces,
	const IOobject& ioZones,
	const surfZoneList& zones
)
	:
	points_(ioPoints, points),
	faces_(ioFaces, faces),
	zones_(ioZones, zones)
{}


tnbLib::MeshedSurfaceIOAllocator::MeshedSurfaceIOAllocator
(
	const IOobject& ioPoints,
	pointField&& points,
	const IOobject& ioFaces,
	faceList&& faces,
	const IOobject& ioZones,
	surfZoneList&& zones
)
	:
	points_(ioPoints, move(points)),
	faces_(ioFaces, move(faces)),
	zones_(ioZones, move(zones))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::MeshedSurfaceIOAllocator::clear()
{
	points_.clear();
	faces_.clear();
	zones_.clear();
}


void tnbLib::MeshedSurfaceIOAllocator::resetFaces
(
	List<face>&& faces,
	surfZoneList&& zones
)
{
	if (notNull(faces))
	{
		faces_.transfer(faces);
	}

	if (notNull(zones))
	{
		zones_.transfer(zones);
	}
}


void tnbLib::MeshedSurfaceIOAllocator::reset
(
	pointField&& points,
	faceList&& faces,
	surfZoneList&& zones
)
{
	// Take over new primitive data.
	// Optimized to avoid overwriting data at all
	if (notNull(points))
	{
		points_.transfer(points);
	}

	resetFaces(move(faces), move(zones));
}


void tnbLib::MeshedSurfaceIOAllocator::reset
(
	List<point>&& points,
	faceList&& faces,
	surfZoneList&& zones
)
{
	// Take over new primitive data.
	// Optimized to avoid overwriting data at all
	if (notNull(points))
	{
		points_.transfer(points);
	}

	resetFaces(move(faces), move(zones));
}


// ************************************************************************* //