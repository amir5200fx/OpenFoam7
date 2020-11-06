#define FoamIOPtrList_EXPORT_DEFINE
#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <coordinateSystems.hxx>

#include <IOPtrList.hxx>
#include <Time.hxx>
#include <stringListOps.hxx>

namespace tnbLib
{
	defineTemplateTypeNameAndDebug(IOPtrList<coordinateSystem>, 0);
}