#include <writePatchGraph.hxx>

#include <volFields.hxx>
#include <fvMesh.hxx>
#include <graph.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void writePatchGraph
	(
		const volScalarField& vsf,
		const label patchLabel,
		const direction d,
		const word& graphFormat
	)
	{
		graph
		(
			vsf.name(),
			"position",
			vsf.name(),
			vsf.mesh().boundary()[patchLabel].Cf().component(d),
			vsf.boundaryField()[patchLabel]
		).write(vsf.time().timePath() / vsf.name(), graphFormat);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //