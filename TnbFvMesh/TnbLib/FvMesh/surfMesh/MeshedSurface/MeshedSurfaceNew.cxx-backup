#include <MeshedSurface.hxx>

#include <UnsortedMeshedSurface.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Face>
tnbLib::autoPtr<tnbLib::MeshedSurface<Face>>
tnbLib::MeshedSurface<Face>::New(const fileName& name, const word& ext)
{
	if (debug)
	{
		InfoInFunction << "Constructing MeshedSurface" << endl;
	}

	typename fileExtensionConstructorTable::iterator cstrIter =
		fileExtensionConstructorTablePtr_->find(ext);

	if (cstrIter == fileExtensionConstructorTablePtr_->end())
	{
		// no direct reader, delegate if possible
		wordHashSet supported = FriendType::readTypes();
		if (supported.found(ext))
		{
			// create indirectly
			autoPtr<MeshedSurface<Face>> surf(new MeshedSurface<Face>);
			surf().transfer(FriendType::New(name, ext)());

			return surf;
		}

		// nothing left to try, issue error
		supported += readTypes();

		FatalErrorInFunction
			<< "Unknown file extension " << ext << nl << nl
			<< "Valid types are :" << nl
			<< supported
			<< exit(FatalError);
	}

	return autoPtr<MeshedSurface<Face>>(cstrIter()(name));
}


template<class Face>
tnbLib::autoPtr<tnbLib::MeshedSurface<Face>>
tnbLib::MeshedSurface<Face>::New(const fileName& name)
{
	word ext = name.ext();
	if (ext == "gz")
	{
		ext = name.lessExt().ext();
	}
	return New(name, ext);
}


// ************************************************************************* //