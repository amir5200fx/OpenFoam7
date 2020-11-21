#include <triSurface.hxx>

#include <STLtriangle.hxx>
#include <primitivePatch.hxx>
#include <HashTable.hxx>
#include <hashSignedLabel.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::triSurface::writeSTLASCII(const bool writeSorted, Ostream& os) const
{
	labelList faceMap;

	surfacePatchList patches(calcPatches(faceMap));

	if (writeSorted)
	{
		label faceIndex = 0;
		forAll(patches, patchi)
		{
			// Print all faces belonging to this region
			const surfacePatch& patch = patches[patchi];

			os << "solid " << patch.name() << endl;

			for
				(
					label patchFacei = 0;
					patchFacei < patch.size();
					patchFacei++
					)
			{
				const label facei = faceMap[faceIndex++];

				const vector& n = faceNormals()[facei];

				os << "  facet normal "
					<< n.x() << ' ' << n.y() << ' ' << n.z() << nl
					<< "    outer loop" << endl;

				const labelledTri& f = (*this)[facei];
				const point& pa = points()[f[0]];
				const point& pb = points()[f[1]];
				const point& pc = points()[f[2]];

				os << "       vertex "
					<< pa.x() << ' ' << pa.y() << ' ' << pa.z() << nl
					<< "       vertex "
					<< pb.x() << ' ' << pb.y() << ' ' << pb.z() << nl
					<< "       vertex "
					<< pc.x() << ' ' << pc.y() << ' ' << pc.z() << nl
					<< "    endloop" << nl
					<< "  endfacet" << endl;
			}

			os << "endsolid " << patch.name() << endl;
		}
	}
	else
	{
		// Get patch (=compact region) per face
		labelList patchIDs(size());
		forAll(patches, patchi)
		{
			label facei = patches[patchi].start();

			forAll(patches[patchi], i)
			{
				patchIDs[faceMap[facei++]] = patchi;
			}
		}

		label currentPatchi = -1;

		forAll(*this, facei)
		{
			if (currentPatchi != patchIDs[facei])
			{
				if (currentPatchi != -1)
				{
					// Have already valid patch. Close it.
					os << "endsolid " << patches[currentPatchi].name()
						<< nl;
				}
				currentPatchi = patchIDs[facei];
				os << "solid " << patches[currentPatchi].name() << nl;
			}

			const vector& n = faceNormals()[facei];

			os << "  facet normal "
				<< n.x() << ' ' << n.y() << ' ' << n.z() << nl
				<< "    outer loop" << endl;

			const labelledTri& f = (*this)[facei];
			const point& pa = points()[f[0]];
			const point& pb = points()[f[1]];
			const point& pc = points()[f[2]];

			os << "       vertex "
				<< pa.x() << ' ' << pa.y() << ' ' << pa.z() << nl
				<< "       vertex "
				<< pb.x() << ' ' << pb.y() << ' ' << pb.z() << nl
				<< "       vertex "
				<< pc.x() << ' ' << pc.y() << ' ' << pc.z() << nl
				<< "    endloop" << nl
				<< "  endfacet" << endl;
		}

		if (currentPatchi != -1)
		{
			os << "endsolid " << patches[currentPatchi].name()
				<< nl;
		}
	}
}


void tnbLib::triSurface::writeSTLBINARY(std::ostream& os) const
{
	// Write the STL header
	string header("tnbLib binary STL");
	header.resize(STLheaderSize);
	os.write(header.c_str(), STLheaderSize);

	label nTris = size();
	os.write(reinterpret_cast<char*>(&nTris), sizeof(unsigned int));

	const vectorField& normals = faceNormals();

	forAll(*this, facei)
	{
		const labelledTri& f = (*this)[facei];

		// Convert vector into STL single precision
		STLpoint n(normals[facei]);
		STLpoint pa(points()[f[0]]);
		STLpoint pb(points()[f[1]]);
		STLpoint pc(points()[f[2]]);

		STLtriangle stlTri(n, pa, pb, pc, f.region());

		stlTri.write(os);
	}
}


// ************************************************************************* //