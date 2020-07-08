#include <UnsortedMeshedSurface.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Face>
tnbLib::autoPtr<tnbLib::UnsortedMeshedSurface<Face>>
tnbLib::UnsortedMeshedSurface<Face>::New(const fileName& name, const word& ext)
{
	if (debug)
	{
		InfoInFunction << "Constructing UnsortedMeshedSurface" << endl;
	}

	typename fileExtensionConstructorTable::iterator cstrIter =
		fileExtensionConstructorTablePtr_->find(ext);

	if (cstrIter == fileExtensionConstructorTablePtr_->end())
	{
		// no direct reader, use the parent if possible
		wordHashSet supported = ParentType::readTypes();
		if (supported.found(ext))
		{
			// create indirectly
			autoPtr<UnsortedMeshedSurface<Face>> surf
			(
				new UnsortedMeshedSurface<Face>
			);
			surf().transfer(ParentType::New(name, ext)());

			return surf;
		}

		// nothing left but to issue an error
		supported += readTypes();

		FatalErrorInFunction
			<< "Unknown file extension " << ext << nl << nl
			<< "Valid types are:" << nl
			<< supported
			<< exit(FatalError);
	}

	return autoPtr<UnsortedMeshedSurface<Face>>(cstrIter()(name));
}


template<class Face>
tnbLib::autoPtr<tnbLib::UnsortedMeshedSurface<Face>>
tnbLib::UnsortedMeshedSurface<Face>::New(const fileName& name)
{
	word ext = name.ext();
	if (ext == "gz")
	{
		ext = name.lessExt().ext();
	}

	return New(name, ext);
}


// ************************************************************************* //