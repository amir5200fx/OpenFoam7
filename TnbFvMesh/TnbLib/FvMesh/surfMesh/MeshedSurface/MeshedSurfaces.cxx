#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <MeshedSurfaces.hxx>

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


	makeSurface(MeshedSurface, face)
		makeSurface(MeshedSurface, triFace)

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //