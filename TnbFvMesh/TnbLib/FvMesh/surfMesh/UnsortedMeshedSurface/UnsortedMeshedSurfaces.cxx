#include <UnsortedMeshedSurfaces.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define makeSurface(surfType, faceType)                                        \
    defineNamedTemplateTypeNameAndDebug(surfType<faceType>, 0);                \
    defineTemplatedRunTimeSelectionTable(surfType,fileExtension,faceType);     \
    defineTemplatedMemberFunctionSelectionTable                                \
    (                                                                          \
        surfType,                                                              \
        write,                                                                 \
        fileExtension,                                                         \
        faceType                                                               \
    );


	makeSurface(UnsortedMeshedSurface, face)
		makeSurface(UnsortedMeshedSurface, triFace)

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //