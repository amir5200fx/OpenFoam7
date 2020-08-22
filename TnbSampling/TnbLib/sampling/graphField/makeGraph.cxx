#include <makeGraph.hxx>

#include <volFields.hxx>
#include <fvMesh.hxx>
#include <graph.hxx>
#include <writeFile.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void makeGraph
	(
		const scalarField& x,
		const volScalarField& vsf,
		const word& graphFormat
	)
	{
		makeGraph(x, vsf, vsf.name(), graphFormat);
	}


	void makeGraph
	(
		const scalarField& x,
		const volScalarField& vsf,
		const word& name,
		const word& graphFormat
	)
	{
		fileName path
		(
			vsf.rootPath()
			/ vsf.caseName()
			/ functionObjects::writeFile::outputPrefix
			/ "graphs"
			/ vsf.instance()
		);
		mkDir(path);

		makeGraph
		(
			x,
			vsf.primitiveField(),
			name,
			path,
			graphFormat
		);
	}


	void makeGraph
	(
		const scalarField& x,
		const scalarField& sf,
		const word& name,
		const fileName& path,
		const word& graphFormat
	)
	{
		graph
		(
			name,
			"x",
			name,
			x,
			sf
		).write(path / name, graphFormat);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //