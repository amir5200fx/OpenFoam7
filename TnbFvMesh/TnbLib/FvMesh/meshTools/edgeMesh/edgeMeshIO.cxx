#include <edgeMesh.hxx>

#include <boundBox.hxx>
#include <edgeMeshFormat.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::edgeMesh::edgeMesh
(
	const fileName& name,
	const word& ext
)
	:
	points_(0),
	edges_(0),
	pointEdgesPtr_(nullptr)
{
	read(name, ext);
}


tnbLib::edgeMesh::edgeMesh(const fileName& name)
	:
	points_(0),
	edges_(0),
	pointEdgesPtr_(nullptr)
{
	read(name);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::edgeMesh::read(const fileName& name)
{
	word ext = name.ext();
	if (ext == "gz")
	{
		fileName unzipName = name.lessExt();
		return read(unzipName, unzipName.ext());
	}
	else
	{
		return read(name, ext);
	}
}


// Read from file in given format
bool tnbLib::edgeMesh::read
(
	const fileName& name,
	const word& ext
)
{
	// read via selector mechanism
	transfer(New(name, ext)());
	return true;
}


void tnbLib::edgeMesh::write
(
	const fileName& name,
	const edgeMesh& mesh
)
{
	if (debug)
	{
		InfoInFunction << "Writing to " << name << endl;
	}

	const word ext = name.ext();

	writefileExtensionMemberFunctionTable::iterator mfIter =
		writefileExtensionMemberFunctionTablePtr_->find(ext);

	if (mfIter == writefileExtensionMemberFunctionTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown file extension " << ext << nl << nl
			<< "Valid types are :" << endl
			<< writefileExtensionMemberFunctionTablePtr_->sortedToc()
			<< exit(FatalError);
	}
	else
	{
		mfIter()(name, mesh);
	}
}


void tnbLib::edgeMesh::writeStats(Ostream& os) const
{
	os << indent << "points      : " << points().size() << nl;
	os << indent << "edges       : " << edges().size() << nl;
	os << indent << "boundingBox : " << boundBox(this->points()) << endl;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamFvMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const edgeMesh& em)
{
	fileFormats::edgeMeshFormat::write(os, em.points_, em.edges_);

	// Check state of Ostream
	os.check("Ostream& operator<<(Ostream&, const edgeMesh&)");

	return os;
}


FoamFvMesh_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, edgeMesh& em)
{
	fileFormats::edgeMeshFormat::read(is, em.points_, em.edges_);

	em.pointEdgesPtr_.clear();

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, edgeMesh&)");

	return is;
}


// ************************************************************************* //