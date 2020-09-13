#include <sampledSurfaces.hxx>

#include <PatchTools.hxx>
#include <mapPolyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir

#include <surfaceFields.hxx> // added by amir
#include <volFields.hxx>  // added by amir
#include <fvPatchFields.hxx>  // added by amir


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(sampledSurfaces, 0);

	addToRunTimeSelectionTable
	(
		functionObject,
		sampledSurfaces,
		dictionary
	);
}

bool tnbLib::sampledSurfaces::verbose_ = false;
tnbLib::scalar tnbLib::sampledSurfaces::mergeTol_ = 1e-10;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSurfaces::writeGeometry() const
{
	// Write to time directory under outputPath_
	// Skip surface without faces (eg, a failed cut-plane)
	
	const fileName outputDir = outputPath_ / mesh_.time().timeName();

	forAll(*this, surfI)
	{
		const sampledSurface& s = operator[](surfI);

		if (Pstream::parRun())
		{
			if (Pstream::master() && mergeList_[surfI].faces.size())
			{
				formatter_->write
				(
					outputDir,
					s.name(),
					mergeList_[surfI].points,
					mergeList_[surfI].faces
				);
			}
		}
		else if (s.faces().size())
		{
			formatter_->write
			(
				outputDir,
				s.name(),
				s.points(),
				s.faces()
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::sampledSurfaces
(
	const word& name,
	const Time& t,
	const dictionary& dict
)
	:
	functionObject(name),
	PtrList<sampledSurface>(),
	mesh_
	(
		refCast<const fvMesh>
		(
			t.lookupObject<objectRegistry>
			(
				dict.lookupOrDefault("region", polyMesh::defaultRegion)
				)
			)
	),
	loadFromFiles_(false),
	outputPath_(fileName::null),
	fieldSelection_(),
	interpolationScheme_(word::null),
	mergeList_(),
	formatter_(nullptr)
{
	if (Pstream::parRun())
	{
		outputPath_ = mesh_.time().path() / ".." / "postProcessing" / name;
	}
	else
	{
		outputPath_ = mesh_.time().path() / "postProcessing" / name;
	}
	// Remove ".."
	outputPath_.clean();

	read(dict);
}


tnbLib::sampledSurfaces::sampledSurfaces
(
	const word& name,
	const objectRegistry& obr,
	const dictionary& dict,
	const bool loadFromFiles
)
	:
	functionObject(name),
	PtrList<sampledSurface>(),
	mesh_(refCast<const fvMesh>(obr)),
	loadFromFiles_(loadFromFiles),
	outputPath_(fileName::null),
	fieldSelection_(),
	interpolationScheme_(word::null),
	mergeList_(),
	formatter_(nullptr)
{
	if (Pstream::parRun())
	{
		outputPath_ = mesh_.time().path() / ".." / "postProcessing" / name;
	}
	else
	{
		outputPath_ = mesh_.time().path() / "postProcessing" / name;
	}
	// Remove ".."
	outputPath_.clean();

	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSurfaces::~sampledSurfaces()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::sampledSurfaces::verbose(const bool verbosity)
{
	verbose_ = verbosity;
}


bool tnbLib::sampledSurfaces::execute()
{
	return true;
}


bool tnbLib::sampledSurfaces::write()
{
	if (size())
	{
		// Finalize surfaces, merge points etc.
		update();

		const label nFields = classifyFields();

		if (Pstream::master())
		{
			if (debug)
			{
				Pout << "Creating directory "
					<< outputPath_ / mesh_.time().timeName() << nl << endl;

			}

			mkDir(outputPath_ / mesh_.time().timeName());
		}

		// Write geometry first if required,
		// or when no fields would otherwise be written
		if (nFields == 0 || formatter_->separateGeometry())
		{
			writeGeometry();
		}

		const IOobjectList objects(mesh_, mesh_.time().timeName());

		sampleAndWriteGeoField<volScalarField>(objects);
		sampleAndWriteGeoField<volVectorField>(objects);
		sampleAndWriteGeoField<volSphericalTensorField>(objects);
		sampleAndWriteGeoField<volSymmTensorField>(objects);
		sampleAndWriteGeoField<volTensorField>(objects);

		sampleAndWriteGeoField<surfaceScalarField>(objects);
		sampleAndWriteGeoField<surfaceVectorField>(objects);
		sampleAndWriteGeoField<surfaceSphericalTensorField>(objects);
		sampleAndWriteGeoField<surfaceSymmTensorField>(objects);
		sampleAndWriteGeoField<surfaceTensorField>(objects);
	}
	return true;
}


bool tnbLib::sampledSurfaces::read(const dictionary& dict)
{
	bool surfacesFound = dict.found("surfaces");

	if (surfacesFound)
	{
		dict.lookup("fields") >> fieldSelection_;

		dict.lookup("interpolationScheme") >> interpolationScheme_;
		const word writeType(dict.lookup("surfaceFormat"));

		// Define the surface formatter
		// Optionally defined extra controls for the output formats
		formatter_ = surfaceWriter::New
		(
			writeType,
			dict.subOrEmptyDict("formatOptions").subOrEmptyDict(writeType)
		);

		PtrList<sampledSurface> newList
		(
			dict.lookup("surfaces"),
			sampledSurface::iNew(mesh_)
		);
		transfer(newList);

		if (Pstream::parRun())
		{
			mergeList_.setSize(size());
		}

		// Ensure all surfaces and merge information are expired
		expire();

		if (this->size())
		{
			Info << "Reading surface description:" << nl;
			forAll(*this, surfI)
			{
				Info << "    " << operator[](surfI).name() << nl;
			}
			Info << endl;
		}
	}

	if (Pstream::master() && debug)
	{
		Pout << "sample fields:" << fieldSelection_ << nl
			<< "sample surfaces:" << nl << "(" << nl;

		forAll(*this, surfI)
		{
			Pout << "  " << operator[](surfI) << endl;
		}
		Pout << ")" << endl;
	}

	return true;
}


void tnbLib::sampledSurfaces::updateMesh(const mapPolyMesh& mpm)
{
	if (&mpm.mesh() == &mesh_)
	{
		expire();
	}

	// pointMesh and interpolation will have been reset in mesh.update
}


void tnbLib::sampledSurfaces::movePoints(const polyMesh& mesh)
{
	if (&mesh == &mesh_)
	{
		expire();
	}
}


void tnbLib::sampledSurfaces::readUpdate(const polyMesh::readUpdateState state)
{
	if (state != polyMesh::UNCHANGED)
	{
		expire();
	}
}


bool tnbLib::sampledSurfaces::needsUpdate() const
{
	forAll(*this, surfI)
	{
		if (operator[](surfI).needsUpdate())
		{
			return true;
		}
	}

	return false;
}


bool tnbLib::sampledSurfaces::expire()
{
	bool justExpired = false;

	forAll(*this, surfI)
	{
		if (operator[](surfI).expire())
		{
			justExpired = true;
		}

		// Clear merge information
		if (Pstream::parRun())
		{
			mergeList_[surfI].clear();
		}
	}

	// true if any surfaces just expired
	return justExpired;
}


bool tnbLib::sampledSurfaces::update()
{
	bool updated = false;

	if (!needsUpdate())
	{
		return updated;
	}

	// Serial: quick and easy, no merging required
	if (!Pstream::parRun())
	{
		forAll(*this, surfI)
		{
			if (operator[](surfI).update())
			{
				updated = true;
			}
		}

		return updated;
	}

	// Dimension as fraction of mesh bounding box
	scalar mergeDim = mergeTol_ * mesh_.bounds().mag();

	if (Pstream::master() && debug)
	{
		Pout << nl << "Merging all points within "
			<< mergeDim << " metre" << endl;
	}

	forAll(*this, surfI)
	{
		sampledSurface& s = operator[](surfI);

		if (s.update())
		{
			updated = true;
		}
		else
		{
			continue;
		}

		PatchTools::gatherAndMerge
		(
			mergeDim,
			primitivePatch
			(
				SubList<face>(s.faces(), s.faces().size()),
				s.points()
			),
			mergeList_[surfI].points,
			mergeList_[surfI].faces,
			mergeList_[surfI].pointsMap
		);
	}

	return updated;
}


// ************************************************************************* //