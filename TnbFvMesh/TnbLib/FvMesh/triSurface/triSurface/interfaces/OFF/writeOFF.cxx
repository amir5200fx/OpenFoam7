#include <triSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void triSurface::writeOFF(const bool writeSorted, Ostream& os) const
	{
		// Write header
		os << "OFF" << endl
			<< "# Geomview OFF file" << endl
			<< "# Regions:" << endl;

		labelList faceMap;
		surfacePatchList patches(calcPatches(faceMap));

		// Print patch names as comment
		forAll(patches, patchi)
		{
			os << "#     " << patchi << "    "
				<< patches[patchi].name() << endl;
		}
		os << nl << endl;

		const pointField& ps = points();

		os << "# nPoints  nTriangles  nEdges" << endl
			<< ps.size()
			<< ' ' << size()
			<< ' ' << nEdges()
			<< nl << endl;

		// Write vertex coords
		forAll(ps, pointi)
		{
			os << ps[pointi].x() << ' '
				<< ps[pointi].y() << ' '
				<< ps[pointi].z() << " #" << pointi << endl;
		}

		os << endl;

		if (writeSorted)
		{
			label faceIndex = 0;

			forAll(patches, patchi)
			{
				// Print all faces belonging to this patch

				for
					(
						label patchFacei = 0;
						patchFacei < patches[patchi].size();
						patchFacei++
						)
				{
					const label facei = faceMap[faceIndex++];

					os << "3 "
						<< operator[](facei)[0] << ' '
						<< operator[](facei)[1] << ' '
						<< operator[](facei)[2] << ' '
						<< operator[](facei).region()
						<< endl;
				}
			}
		}
		else
		{
			forAll(*this, facei)
			{
				os << "3 "
					<< operator[](facei)[0] << ' '
					<< operator[](facei)[1] << ' '
					<< operator[](facei)[2] << ' '
					<< operator[](facei).region()
					<< endl;
			}
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //