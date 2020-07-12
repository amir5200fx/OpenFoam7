#include <writers.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define defineSetWriterType(dataType)                                          \
    defineNamedTemplateTypeNameAndDebug(writer<dataType >, 0);                 \
    defineTemplatedRunTimeSelectionTable(writer, word, dataType);

	defineSetWriterType(scalar);
	defineSetWriterType(vector);
	defineSetWriterType(sphericalTensor);
	defineSetWriterType(symmTensor);
	defineSetWriterType(tensor);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //