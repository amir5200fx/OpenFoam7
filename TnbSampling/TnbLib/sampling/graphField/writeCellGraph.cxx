#include <writeCellGraph.hxx>

#include <volFields.hxx>
#include <fvMesh.hxx>
#include <graph.hxx>
#include <writeFile.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void writeCellGraph
	(
		const volScalarField& vsf,
		const word& graphFormat
	)
	{
		fileName path
		(
			vsf.time().path()
			/ functionObjects::writeFile::outputPrefix
			/ "graphs"
			/ vsf.time().timeName()
		);
		mkDir(path);

		graph
		(
			vsf.name(),
			"x",
			vsf.name(),
			vsf.mesh().C().primitiveField().component(vector::X),
			vsf.primitiveField()
		).write(path / vsf.name(), graphFormat);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //