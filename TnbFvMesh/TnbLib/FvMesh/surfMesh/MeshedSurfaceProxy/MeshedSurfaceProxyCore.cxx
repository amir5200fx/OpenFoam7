#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <MeshedSurfaceProxy.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define makeSurface(surfType, faceType)                                        \
    defineNamedTemplateTypeNameAndDebug(surfType<faceType>, 0);                \
    defineTemplatedMemberFunctionSelectionTable                                \
    (                                                                          \
        surfType,                                                              \
        write,                                                                 \
        fileExtension,                                                         \
        faceType                                                               \
    );


	makeSurface(MeshedSurfaceProxy, face)
		makeSurface(MeshedSurfaceProxy, triFace)

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //