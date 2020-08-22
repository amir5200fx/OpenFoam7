#include <attachPolyTopoChanger.hxx>

#include <polyMesh.hxx>
#include <polyTopoChange.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::attachPolyTopoChanger::attachPolyTopoChanger
(
	const IOobject& io,
	polyMesh& mesh
)
	:
	polyTopoChanger(io, mesh)
{}


tnbLib::attachPolyTopoChanger::attachPolyTopoChanger
(
	polyMesh& mesh
)
	:
	polyTopoChanger(mesh)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::attachPolyTopoChanger::attach(const bool removeEmptyPatches)
{
	if (debug)
	{
		Pout << "void attachPolyTopoChanger::attach(): "
			<< "Attaching mesh" << endl;
	}

	// Save current file instance
	const fileName oldInst = mesh_.facesInstance();

	// Execute all polyMeshModifiers
	changeMesh(false);  // no inflation

	const pointField p = mesh_.oldPoints();

	mesh_.movePoints(p);

	if (debug)
	{
		Pout << "Clearing mesh." << endl;
	}

	if (removeEmptyPatches)
	{
		// Re-do the boundary patches, removing the ones with zero size
		const polyBoundaryMesh& oldPatches = mesh_.boundaryMesh();

		List<polyPatch*> newPatches(oldPatches.size());
		label nNewPatches = 0;

		forAll(oldPatches, patchi)
		{
			if (oldPatches[patchi].size())
			{
				newPatches[nNewPatches] = oldPatches[patchi].clone
				(
					mesh_.boundaryMesh(),
					nNewPatches,
					oldPatches[patchi].size(),
					oldPatches[patchi].start()
				).ptr();

				nNewPatches++;
			}
			else
			{
				if (debug)
				{
					Pout << "Removing zero-sized patch " << patchi
						<< " named " << oldPatches[patchi].name() << endl;
				}
			}
		}

		newPatches.setSize(nNewPatches);

		mesh_.removeBoundary();
		mesh_.addPatches(newPatches);
	}

	// Reset the file instance to overwrite the original mesh
	mesh_.setInstance(oldInst);

	if (debug)
	{
		Pout << "void attachPolyTopoChanger::attach(): "
			<< "Finished attaching mesh" << endl;
	}

	mesh_.checkMesh();
}


// ************************************************************************* //