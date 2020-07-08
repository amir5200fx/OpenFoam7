#include <triSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void triSurface::writeSMESH(const bool writeSorted, Ostream& os) const
	{
		const pointField& ps = points();

		// Write header
		os << "# tetgen .smesh file" << endl
			<< ps.size() << " 3" << endl;   // 3 dimensions

		// Write vertex coords
		forAll(ps, pointi)
		{
			os << pointi << ' '
				<< ps[pointi].x() << ' '
				<< ps[pointi].y() << ' '
				<< ps[pointi].z() << endl;
		}

		if (writeSorted)
		{
			labelList faceMap;

			surfacePatchList patches(calcPatches(faceMap));

			os << size() << " 1" << endl;   // 1 attribute: region number

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

					os << "3 " // triangles
						<< operator[](facei)[0] << ' '
						<< operator[](facei)[1] << ' '
						<< operator[](facei)[2] << ' '
						<< operator[](facei).region()   // region number
						<< endl;
				}
			}

			os << '0' << endl      // holes
				<< '0' << endl;     // regions
		}
		else
		{
			os << size() << " 1" << endl;   // 1 attribute: region number

			forAll(*this, facei)
			{
				os << "3 "
					<< operator[](facei)[0] << ' '
					<< operator[](facei)[1] << ' '
					<< operator[](facei)[2] << ' '
					<< operator[](facei).region()       // region number
					<< endl;
			}

			os << '0' << endl      // holes
				<< '0' << endl;     // regions
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
