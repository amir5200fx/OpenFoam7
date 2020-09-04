#include <MeshedSurfaceProxy.hxx>

#include <Time.hxx>
#include <surfMesh.hxx>
#include <OFstream.hxx>
#include <ListOps.hxx>

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

template<class Face>
tnbLib::wordHashSet tnbLib::MeshedSurfaceProxy<Face>::writeTypes()
{
	return wordHashSet(*writefileExtensionMemberFunctionTablePtr_);
}


template<class Face>
bool tnbLib::MeshedSurfaceProxy<Face>::canWriteType
(
	const word& ext,
	const bool verbose
)
{
	return fileFormats::surfaceFormatsCore::checkSupport
	(
		writeTypes(), ext, verbose, "writing"
	);
}


template<class Face>
void tnbLib::MeshedSurfaceProxy<Face>::write
(
	const fileName& name,
	const MeshedSurfaceProxy& surf
)
{
	if (debug)
	{
		InfoInFunction << "Writing to " << name << endl;
	}

	word ext = name.ext();

	typename writefileExtensionMemberFunctionTable::iterator mfIter =
		writefileExtensionMemberFunctionTablePtr_->find(ext);

	if (mfIter == writefileExtensionMemberFunctionTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown file extension " << ext << nl << nl
			<< "Valid types are :" << endl
			<< writeTypes()
			<< exit(FatalError);
	}

	mfIter()(name, surf);
}


template<class Face>
void tnbLib::MeshedSurfaceProxy<Face>::write
(
	const Time& t,
	const word& surfName
) const
{
	// the surface name to be used
	word name(surfName.size() ? surfName : surfaceRegistry::defaultName);

	if (debug)
	{
		InfoInFunction << "Writing to " << name << endl;
	}


	// The local location
	const fileName objectDir
	(
		t.timePath() / surfaceRegistry::prefix / name / surfMesh::meshSubDir
	);

	if (!isDir(objectDir))
	{
		mkDir(objectDir);
	}


	// write surfMesh/points
	{
		pointIOField io
		(
			IOobject
			(
				"points",
				t.timeName(),
				surfMesh::meshSubDir,
				t,
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			)
		);

		OFstream os
		(
			objectDir / io.name(),
			t.writeFormat(),
			IOstream::currentVersion,
			t.writeCompression()
		);

		io.writeHeader(os);

		os << this->points();

		io.writeEndDivider(os);
	}


	// write surfMesh/faces
	{
		faceCompactIOList io
		(
			IOobject
			(
				"faces",
				t.timeName(),
				surfMesh::meshSubDir,
				t,
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			)
		);

		OFstream os
		(
			objectDir / io.name(),
			t.writeFormat(),
			IOstream::currentVersion,
			t.writeCompression()
		);
		io.writeHeader(os);

		if (this->useFaceMap())
		{
			// this is really a bit annoying (and wasteful) but no other way
			os << reorder(this->faceMap(), this->faces());
		}
		else
		{
			os << this->faces();
		}

		io.writeEndDivider(os);
	}


	// write surfMesh/surfZones
	{
		surfZoneIOList io
		(
			IOobject
			(
				"surfZones",
				t.timeName(),
				surfMesh::meshSubDir,
				t,
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			)
		);

		// write as ascii
		OFstream os(objectDir / io.name());
		io.writeHeader(os);

		os << this->surfZones();

		io.writeEndDivider(os);
	}

}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Face>
tnbLib::MeshedSurfaceProxy<Face>::MeshedSurfaceProxy
(
	const pointField& pointLst,
	const List<Face>& faceLst,
	const List<surfZone>& zoneLst,
	const List<label>& faceMap
)
	:
	points_(pointLst),
	faces_(faceLst),
	zones_(zoneLst),
	faceMap_(faceMap)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Face>
tnbLib::MeshedSurfaceProxy<Face>::~MeshedSurfaceProxy()
{}


// ************************************************************************* //