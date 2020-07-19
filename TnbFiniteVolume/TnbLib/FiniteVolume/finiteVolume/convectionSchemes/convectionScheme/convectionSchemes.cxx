#include <convectionScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
		// Define the constructor function hash tables

#define makeBaseConvectionScheme(Type)                                         \
                                                                               \
defineTemplateRunTimeSelectionTable                                            \
(                                                                              \
    convectionScheme<Type>,                                                    \
    Istream                                                                    \
);                                                                             \
                                                                               \
defineTemplateRunTimeSelectionTable                                            \
(                                                                              \
    convectionScheme<Type>,                                                    \
    Multivariate                                                               \
);


		makeBaseConvectionScheme(scalar)
			makeBaseConvectionScheme(vector)
			makeBaseConvectionScheme(sphericalTensor)
			makeBaseConvectionScheme(symmTensor)
			makeBaseConvectionScheme(tensor)


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //