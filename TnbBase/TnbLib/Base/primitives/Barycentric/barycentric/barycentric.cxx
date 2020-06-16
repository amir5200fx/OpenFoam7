#include <barycentric.hxx>

#include <Random.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::barycentric tnbLib::barycentric01(Random& rndGen)
{
	scalar s = rndGen.scalar01();
	scalar t = rndGen.scalar01();
	scalar u = rndGen.scalar01();

	// Transform the random point in the unit cube to a random point in the
	// unit tet by means of a series of reflections. See
	// <http://vcg.isti.cnr.it/jgt/tetra.htm> for details.

	if (s + t > 1)
	{
		s = 1 - s;
		t = 1 - t;
	}

	if (s + t + u > 1)
	{
		tnbLib::scalar temp = u;

		if (t + u > 1)
		{
			u = 1 - s - t;
			t = 1 - temp;
		}
		else
		{
			u = s + t + u - 1;
			s = 1 - t - temp;
		}
	}

	return tnbLib::barycentric(1 - s - t - u, s, t, u);
}


// ************************************************************************* //