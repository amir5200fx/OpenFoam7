#include <faceSet.hxx>

#include <mapPolyMesh.hxx>
#include <polyMesh.hxx>
#include <syncTools.hxx>

#include <addToRunTimeSelectionTable.hxx>

#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTypeNameAndDebug(faceSet, 0);

	addToRunTimeSelectionTable(topoSet, faceSet, word);
	addToRunTimeSelectionTable(topoSet, faceSet, size);
	addToRunTimeSelectionTable(topoSet, faceSet, set);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	faceSet::faceSet(const IOobject& obj)
		:
		topoSet(obj, typeName)
	{}


	faceSet::faceSet
	(
		const polyMesh& mesh,
		const word& name,
		readOption r,
		writeOption w
	)
		:
		topoSet(mesh, typeName, name, r, w)
	{
		check(mesh.nFaces());
	}


	faceSet::faceSet
	(
		const polyMesh& mesh,
		const word& name,
		const label size,
		writeOption w
	)
		:
		topoSet(mesh, name, size, w)
	{}


	faceSet::faceSet
	(
		const polyMesh& mesh,
		const word& name,
		const topoSet& set,
		writeOption w
	)
		:
		topoSet(mesh, name, set, w)
	{}


	faceSet::faceSet
	(
		const polyMesh& mesh,
		const word& name,
		const labelHashSet& set,
		writeOption w
	)
		:
		topoSet(mesh, name, set, w)
	{}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	faceSet::~faceSet()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void faceSet::sync(const polyMesh& mesh)
	{
		boolList set(mesh.nFaces(), false);

		forAllConstIter(faceSet, *this, iter)
		{
			set[iter.key()] = true;
		}
		syncTools::syncFaceList(mesh, set, orEqOp<bool>());

		label nAdded = 0;

		forAll(set, facei)
		{
			if (set[facei])
			{
				if (insert(facei))
				{
					nAdded++;
				}
			}
			else if (found(facei))
			{
				FatalErrorInFunction
					<< "Problem : syncing removed faces from set."
					<< abort(FatalError);
			}
		}

		reduce(nAdded, sumOp<label>());
		if (debug && nAdded > 0)
		{
			Info << "Added an additional " << nAdded
				<< " faces on coupled patches. "
				<< "(processorPolyPatch, cyclicPolyPatch)" << endl;
		}
	}


	label faceSet::maxSize(const polyMesh& mesh) const
	{
		return mesh.nFaces();
	}


	void faceSet::updateMesh(const mapPolyMesh& morphMap)
	{
		updateLabels(morphMap.reverseFaceMap());
	}


	void faceSet::writeDebug
	(
		Ostream& os,
		const primitiveMesh& mesh,
		const label maxLen
	) const
	{
		topoSet::writeDebug(os, mesh.faceCentres(), maxLen);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //