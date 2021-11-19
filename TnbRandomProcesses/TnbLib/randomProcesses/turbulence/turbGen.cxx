#include <turbGen.hxx>

#include <fft.hxx>
#include <Kmesh.hxx>
#include <primitiveFields.hxx>
#include <Ek.hxx>
#include <mathematicalConstants.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::turbGen::turbGen(const Kmesh& k, const scalar EA, const scalar K0)
	:
	K(k),
	Ea(EA),
	k0(K0),
	RanGen(label(0))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::vectorField tnbLib::turbGen::U()
{
	vectorField s(K.size());
	scalarField rndPhases(K.size());

	forAll(K, i)
	{
		s[i] = RanGen.sample01<vector>();
		rndPhases[i] = RanGen.scalar01();
	}

	s = K ^ s;
	s = s / (mag(s) + 1.0e-20);

	s = Ek(Ea, k0, mag(K))*s;

	complexVectorField up
	(
		fft::reverseTransform
		(
			ComplexField(cos(constant::mathematical::twoPi*rndPhases)*s,
				sin(constant::mathematical::twoPi*rndPhases)*s),
			K.nn()
		)
	);

	return ReImSum(up);
}


// ************************************************************************* //