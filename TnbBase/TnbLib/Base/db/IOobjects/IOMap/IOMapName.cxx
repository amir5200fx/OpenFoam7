#include <IOMap.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //
namespace tnbLib
{
	defineTemplateTypeNameAndDebug(IOMap<dictionary>, 0);

	//- Template specialisation for obtaining filePath
	template<>
	fileName typeFilePath<IOMap<dictionary>>(const IOobject& io)
	{
		return io.globalFilePath(IOMap<dictionary>::typeName);
	}
}

// ************************************************************************* //