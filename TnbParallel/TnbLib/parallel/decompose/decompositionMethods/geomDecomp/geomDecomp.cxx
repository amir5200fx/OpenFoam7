#include <geomDecomp.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::geomDecomp::geomDecomp
(
	const dictionary& decompositionDict,
	const word& derivedType
)
	:
	decompositionMethod(decompositionDict),
	geomDecomDict_(decompositionDict.optionalSubDict(derivedType + "Coeffs")),
	n_(geomDecomDict_.lookup("n")),
	delta_(readScalar(geomDecomDict_.lookup("delta"))),
	rotDelta_(I)
{
	// check that the case makes sense :

	if (nProcessors_ != n_.x()*n_.y()*n_.z())
	{
		FatalErrorInFunction
			<< "Wrong number of processor divisions in geomDecomp:" << nl
			<< "Number of domains    : " << nProcessors_ << nl
			<< "Wanted decomposition : " << n_
			<< exit(FatalError);
	}

	scalar d = 1 - 0.5*delta_*delta_;
	scalar d2 = sqr(d);

	scalar a = delta_;
	scalar a2 = sqr(a);

	rotDelta_ = tensor
	(
		d2, -a * d, a,
		a*d - a2 * d, a*a2 + d2, -2 * a*d,
		a*d2 + a2, a*d - a2 * d, d2 - a2
	);
}


// ************************************************************************* //