#include <edgeMesh.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::edgeMesh> tnbLib::edgeMesh::New
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

	return autoPtr<edgeMesh>(cstrIter()(name));
}


tnbLib::autoPtr<tnbLib::edgeMesh> tnbLib::edgeMesh::New(const fileName& name)
{
	word ext = name.ext();
	if (ext == "gz")
	{
		ext = name.lessExt().ext();
	}
	return New(name, ext);
}


// ************************************************************************* //