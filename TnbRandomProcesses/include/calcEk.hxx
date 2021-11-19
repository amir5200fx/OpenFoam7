#pragma once
#ifndef _calcEk_Header
#define _calcEk_Header

#include <RandomProcesses_Module.hxx>
#include <volFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class graph;
	class Kmesh;

	FoamRandomProcesses_EXPORT graph calcEk
	(
		const volVectorField& U,
		const Kmesh& K
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

#endif // !_calcEk_Header
