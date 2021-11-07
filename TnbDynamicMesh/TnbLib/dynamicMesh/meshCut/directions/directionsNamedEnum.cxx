#define FoamNamedEnum_EXPORT_DEFINE
#include <directions.hxx>

#include <addToRunTimeSelectionTable.hxx>

namespace tnbLib
{
    template<>
    const char* tnbLib::NamedEnum
        <
        tnbLib::directions::directionType,
        3
        >::names[] =
    {
        "tan1",
        "tan2",
        "normal"
    };
}

const tnbLib::NamedEnum<tnbLib::directions::directionType, 3>
tnbLib::directions::directionTypeNames_;