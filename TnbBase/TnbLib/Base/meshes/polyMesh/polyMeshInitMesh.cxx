#include <polyMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::polyMesh::initMesh()
{
	if (debug)
	{
		InfoInFunction << "initialising primitiveMesh" << endl;
	}

	// For backward compatibility check if the neighbour array is the same
	// length as the owner and shrink to remove the -1s padding
	if (neighbour_.size() == owner_.size())
	{
		label nInternalFaces = 0;

		forAll(neighbour_, facei)
		{
			if (neighbour_[facei] == -1)
			{
				break;
			}
			else
			{
				nInternalFaces++;
			}
		}

		neighbour_.setSize(nInternalFaces);
	}

	label nCells = -1;

	forAll(owner_, facei)
	{
		if (owner_[facei] < 0)
		{
			FatalErrorInFunction
				<< "Illegal cell label " << owner_[facei]
				<< " in neighbour addressing for face " << facei
				<< exit(FatalError);
		}
		nCells = max(nCells, owner_[facei]);
	}

	// The neighbour array may or may not be the same length as the owner
	forAll(neighbour_, facei)
	{
		if (neighbour_[facei] < 0)
		{
			FatalErrorInFunction
				<< "Illegal cell label " << neighbour_[facei]
				<< " in neighbour addressing for face " << facei
				<< exit(FatalError);
		}
		nCells = max(nCells, neighbour_[facei]);
	}

	nCells++;

	// Reset the primitiveMesh with the sizes of the primitive arrays
	primitiveMesh::reset
	(
		points_.size(),
		neighbour_.size(),
		owner_.size(),
		nCells
	);

	string meshInfo =
		"nPoints:" + tnbLib::name(nPoints())
		+ "  nCells:" + tnbLib::name(this->nCells())
		+ "  nFaces:" + tnbLib::name(nFaces())
		+ "  nInternalFaces:" + tnbLib::name(nInternalFaces());

	owner_.note() = meshInfo;
	neighbour_.note() = meshInfo;
}


void tnbLib::polyMesh::initMesh(cellList& c)
{
	if (debug)
	{
		InfoInFunction << "Calculating owner-neighbour arrays" << endl;
	}

	owner_.setSize(faces_.size(), -1);
	neighbour_.setSize(faces_.size(), -1);

	boolList markedFaces(faces_.size(), false);

	label nInternalFaces = 0;

	forAll(c, celli)
	{
		// get reference to face labels for current cell
		const labelList& cellfaces = c[celli];

		forAll(cellfaces, facei)
		{
			if (cellfaces[facei] < 0)
			{
				FatalErrorInFunction
					<< "Illegal face label " << cellfaces[facei]
					<< " in cell " << celli
					<< exit(FatalError);
			}

			if (!markedFaces[cellfaces[facei]])
			{
				// First visit: owner
				owner_[cellfaces[facei]] = celli;
				markedFaces[cellfaces[facei]] = true;
			}
			else
			{
				// Second visit: neighbour
				neighbour_[cellfaces[facei]] = celli;
				nInternalFaces++;
			}
		}
	}

	// The neighbour array is initialised with the same length as the owner
	// padded with -1s and here it is truncated to the correct size of the
	// number of internal faces.
	neighbour_.setSize(nInternalFaces);

	// Reset the primitiveMesh
	primitiveMesh::reset
	(
		points_.size(),
		neighbour_.size(),
		owner_.size(),
		c.size(),
		c
	);

	string meshInfo =
		"nPoints: " + tnbLib::name(nPoints())
		+ " nCells: " + tnbLib::name(nCells())
		+ " nFaces: " + tnbLib::name(nFaces())
		+ " nInternalFaces: " + tnbLib::name(this->nInternalFaces());

	owner_.note() = meshInfo;
	neighbour_.note() = meshInfo;
}


// ************************************************************************* //