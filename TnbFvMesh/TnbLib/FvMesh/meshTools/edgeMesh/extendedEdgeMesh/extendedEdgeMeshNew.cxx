#include <extendedEdgeMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineRunTimeSelectionTable(extendedEdgeMesh, fileExtension);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::extendedEdgeMesh> tnbLib::extendedEdgeMesh::New
(
	const fileName& name,
	const word& ext
)
{
	fileExtensionConstructorTable::iterator cstrIter =
		fileExtensionConstructorTablePtr_->find(ext);

	if (cstrIter == fileExtensionConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown file extension " << ext
			<< " for file " << name << nl << nl
			<< "Valid extensions are :" << nl
			<< fileExtensionConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<extendedEdgeMesh>(cstrIter()(name));
}


tnbLib::autoPtr<tnbLib::extendedEdgeMesh> tnbLib::extendedEdgeMesh::New
(
	const fileName& name
)
{
	word ext = name.ext();
	if (ext == "gz")
	{
		ext = name.lessExt().ext();
	}
	return New(name, ext);
}


// ************************************************************************* //