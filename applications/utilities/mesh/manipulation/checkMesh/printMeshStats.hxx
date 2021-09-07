#pragma once
#ifndef _printMeshStats_Header
#define _printMeshStats_Header

#include <includeAllModules.hxx>

namespace tnbLib
{
	class polyMesh;

	void printMeshStats(const polyMesh& mesh, const bool allTopology);
}

#endif // !_printMeshStats_Header

