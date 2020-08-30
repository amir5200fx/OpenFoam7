#include <meshWriter.hxx>

#include <cellModeller.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::string tnbLib::meshWriter::defaultMeshName = "meshExport";


const tnbLib::cellModel* tnbLib::meshWriter::unknownModel = tnbLib::cellModeller::
lookup
(
	"unknown"
);


const tnbLib::cellModel* tnbLib::meshWriter::tetModel = tnbLib::cellModeller::
lookup
(
	"tet"
);


const tnbLib::cellModel* tnbLib::meshWriter::pyrModel = tnbLib::cellModeller::
lookup
(
	"pyr"
);


const tnbLib::cellModel* tnbLib::meshWriter::prismModel = tnbLib::cellModeller::
lookup
(
	"prism"
);


const tnbLib::cellModel* tnbLib::meshWriter::hexModel = tnbLib::cellModeller::
lookup
(
	"hex"
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::meshWriter::meshWriter(const polyMesh& mesh, const scalar scaleFactor)
	:
	mesh_(mesh),
	scaleFactor_(scaleFactor),
	writeBoundary_(true),
	boundaryRegion_(),
	cellTable_(),
	cellTableId_()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::meshWriter::~meshWriter()
{}


// ************************************************************************* //