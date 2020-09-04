#include <MeshedSurface.hxx>

#include <boundBox.hxx>
#include <Ostream.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Face>
void tnbLib::MeshedSurface<Face>::writeStats(Ostream& os) const
{
	os << "points      : " << this->points().size() << nl;
	if (MeshedSurface<Face>::isTri())
	{
		os << "triangles   : " << this->size() << nl;
	}
	else
	{
		label nTri = 0;
		label nQuad = 0;
		forAll(*this, i)
		{
			const label n = this->operator[](i).size();

			if (n == 3)
			{
				nTri++;
			}
			else if (n == 4)
			{
				nQuad++;
			}
		}

		os << "faces       : " << this->size()
			<< "  (tri:" << nTri << " quad:" << nQuad
			<< " poly:" << (this->size() - nTri - nQuad) << ")" << nl;
	}

	os << "boundingBox : " << boundBox(this->points()) << endl;
}


// ************************************************************************* //