#include <laplacianScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
		// Define the constructor function hash tables

#define makeLaplacianGTypeScheme(Type, GType)                                  \
    typedef laplacianScheme<Type, GType> laplacianScheme##Type##GType;         \
    defineTemplateRunTimeSelectionTable(laplacianScheme##Type##GType, Istream);

#define makeLaplacianScheme(Type)                                              \
    makeLaplacianGTypeScheme(Type, scalar);                                    \
    makeLaplacianGTypeScheme(Type, symmTensor);                                \
    makeLaplacianGTypeScheme(Type, tensor);

		makeLaplacianScheme(scalar);
		makeLaplacianScheme(vector);
		makeLaplacianScheme(sphericalTensor);
		makeLaplacianScheme(symmTensor);
		makeLaplacianScheme(tensor);

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //