#define  FoamNamedEnum_EXPORT_DEFINE
#include "channelIndex.hxx"

namespace tnbLib
{
    template<>
    const char* tnbLib::NamedEnum
        <
        tnbLib::vector::components,
        3
        >::names[] =
    {
        "x",
        "y",
        "z"
    };
}

const tnbLib::NamedEnum<tnbLib::vector::components, 3>
tnbLib::channelIndex::vectorComponentsNames_;