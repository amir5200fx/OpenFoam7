#include <tnbVersion.hxx>

const char* const tnbLib::FOAMversion = "VERSION_STRING";
const char* const tnbLib::FOAMbuild = "BUILD_STRING";

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Setup an error handler for the global new operator

#include <new.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <jobInfo.hxx>

bool tnbLib::jobInfo::constructed(false);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Global error definitions (initialised by construction)

