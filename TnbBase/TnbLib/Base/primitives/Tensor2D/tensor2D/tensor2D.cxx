#include <tensor2D.hxx>

#include <quadraticEqn.hxx>
#include <UList.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::tensor2D::vsType::typeName = "tensor2D";

template<>
const char* const tnbLib::tensor2D::vsType::componentNames[] =
{
	"xx", "xy",
	"yx", "yy"
};

template<>
const tnbLib::tensor2D tnbLib::tensor2D::vsType::vsType::zero
(
	tensor2D::uniform(0)
);

template<>
const tnbLib::tensor2D tnbLib::tensor2D::vsType::one
(
	tensor2D::uniform(1)
);

template<>
const tnbLib::tensor2D tnbLib::tensor2D::vsType::max
(
	tensor2D::uniform(vGreat)
);

template<>
const tnbLib::tensor2D tnbLib::tensor2D::vsType::min
(
	tensor2D::uniform(-vGreat)
);

template<>
const tnbLib::tensor2D tnbLib::tensor2D::vsType::rootMax
(
	tensor2D::uniform(rootVGreat)
);

template<>
const tnbLib::tensor2D tnbLib::tensor2D::vsType::rootMin
(
	tensor2D::uniform(-rootVGreat)
);

template<>
const tnbLib::tensor2D tnbLib::tensor2D::I
(
	1, 0,
	0, 1
);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::vector2D tnbLib::eigenValues(const tensor2D& t)
{
	// Coefficients of the characteristic quadratic polynomial (a = 1)
	const scalar b = -t.xx() - t.yy();
	const scalar c = t.xx()*t.yy() - t.xy()*t.yx();

	// Solve
	Roots<2> roots = quadraticEqn(1, b, c).roots();

	// Check the root types
	vector2D lambda = vector2D::zero;
	forAll(roots, i)
	{
		switch (roots.type(i))
		{
		case rootType::real:
			lambda[i] = roots[i];
			break;
		case rootType::complex:
			WarningInFunction
				<< "Complex eigenvalues detected for tensor: " << t
				<< endl;
			lambda[i] = 0;
			break;
		case rootType::posInf:
			lambda[i] = vGreat;
			break;
		case rootType::negInf:
			lambda[i] = -vGreat;
			break;
		case rootType::nan:
			FatalErrorInFunction
				<< "Eigenvalue calculation failed for tensor: " << t
				<< exit(FatalError);
		}
	}

	// Sort the eigenvalues into ascending order
	if (lambda.x() > lambda.y())
	{
		Swap(lambda.x(), lambda.y());
	}

	return lambda;
}


tnbLib::vector2D tnbLib::eigenVector
(
	const tensor2D& T,
	const scalar lambda,
	const vector2D& direction1
)
{
	// Construct the linear system for this eigenvalue
	tensor2D A(T - lambda * tensor2D::I);

	// Evaluate the eigenvector using the largest divisor
	if (mag(A.yy()) > mag(A.xx()) && mag(A.yy()) > small)
	{
		vector2D ev(1, -A.yx() / A.yy());

		return ev / mag(ev);
	}
	else if (mag(A.xx()) > small)
	{
		vector2D ev(-A.xy() / A.xx(), 1);

		return ev / mag(ev);
	}

	// Repeated eigenvalue
	return vector2D(-direction1.y(), direction1.x());
}


tnbLib::tensor2D tnbLib::eigenVectors(const tensor2D& T, const vector2D& lambdas)
{
	vector2D Ux(1, 0), Uy(0, 1);

	Ux = eigenVector(T, lambdas.x(), Uy);
	Uy = eigenVector(T, lambdas.y(), Ux);

	return tensor2D(Ux, Uy);
}


tnbLib::tensor2D tnbLib::eigenVectors(const tensor2D& T)
{
	const vector2D lambdas(eigenValues(T));

	return eigenVectors(T, lambdas);
}


// ************************************************************************* //