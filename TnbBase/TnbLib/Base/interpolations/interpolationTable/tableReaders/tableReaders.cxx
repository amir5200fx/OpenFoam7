#include <tableReaders.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define defineTableReaderType(dataType)                                        \
    defineNamedTemplateTypeNameAndDebug(tableReader<dataType >, 0);            \
    defineTemplatedRunTimeSelectionTable(tableReader, dictionary, dataType);

	defineTableReaderType(scalar);
	defineTableReaderType(vector);
	defineTableReaderType(sphericalTensor);
	defineTableReaderType(symmTensor);
	defineTableReaderType(tensor);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //