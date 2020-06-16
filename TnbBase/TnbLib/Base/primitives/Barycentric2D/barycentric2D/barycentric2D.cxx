#include <barycentric2D.hxx>

#include <Random.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::barycentric2D tnbLib::barycentric2D01(Random& rndGen)
{
	scalar s = rndGen.scalar01();
	scalar t = rndGen.scalar01();

	// Transform the random point in the unit square to a random point in the
	// unit tri by reflecting across the diagonal

	if (s + t > 1)
	{
		s = 1 - s;
		t = 1 - t;
	}

	return tnbLib::barycentric2D(1 - s - t, s, t);
}


// ************************************************************************* //