#include <extendedFeatureEdgeMeshFormat.hxx>

#include <edgeMeshFormat.hxx>
#include <IFstream.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fileFormats::extendedFeatureEdgeMeshFormat::extendedFeatureEdgeMeshFormat
(
	const fileName& filename
)
{
	read(filename);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fileFormats::extendedFeatureEdgeMeshFormat::read
(
	const fileName& filename
)
{
	clear();

	IFstream is(filename);
	if (!is.good())
	{
		FatalErrorInFunction
			<< "Cannot read file " << filename
			<< exit(FatalError);
	}

	return fileFormats::edgeMeshFormat::read
	(
		is,
		this->storedPoints(),
		this->storedEdges()
	);
}


// ************************************************************************* //