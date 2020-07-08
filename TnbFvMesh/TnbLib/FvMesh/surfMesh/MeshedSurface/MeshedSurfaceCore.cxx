#include <MeshedSurface.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

namespace tnbLib
{

	// specialization: from face -> triFace
	template<>
	void tnbLib::MeshedSurface<triFace>::transcribe(MeshedSurface<face>& surf)
	{
		// first triangulate
		surf.triangulate();
		this->storedPoints().transfer(surf.storedPoints());
		this->storedZones().transfer(surf.storedZones());

		// transcribe from face -> triFace
		List<face>&    origFaces = surf.storedFaces();
		List<triFace>  newFaces(origFaces.size());
		forAll(origFaces, facei)
		{
			newFaces[facei] = triFace
			(
				static_cast<const labelUList&>(origFaces[facei])
			);
		}
		surf.clear();

		this->storedFaces().transfer(newFaces);
	}


	// specialization: from face -> face
	template<>
	void tnbLib::MeshedSurface<face>::transcribe(MeshedSurface<face>& surf)
	{
		this->transfer(surf);
	}


}  // end of namespace tnbLib


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //