#include <tensor.hxx>

#include <cubicEqn.hxx>
#include <mathematicalConstants.hxx>

using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char* const tnbLib::tensor::vsType::typeName = "tensor";

template<>
const char* const tnbLib::tensor::vsType::componentNames[] =
{
	"xx", "xy", "xz",
	"yx", "yy", "yz",
	"zx", "zy", "zz"
};

template<>
const tnbLib::tensor tnbLib::tensor::vsType::zero(tensor::uniform(0));

template<>
const tnbLib::tensor tnbLib::tensor::vsType::one(tensor::uniform(1));

template<>
const tnbLib::tensor tnbLib::tensor::vsType::max(tensor::uniform(vGreat));

template<>
const tnbLib::tensor tnbLib::tensor::vsType::min(tensor::uniform(-vGreat));

template<>
const tnbLib::tensor tnbLib::tensor::vsType::rootMax(tensor::uniform(rootVGreat));

template<>
const tnbLib::tensor tnbLib::tensor::vsType::rootMin(tensor::uniform(-rootVGreat));

template<>
const tnbLib::tensor tnbLib::tensor::I
(
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::vector tnbLib::eigenValues(const tensor& t)
{
	// Coefficients of the characteristic cubic polynomial (a = 1)
	const scalar b =
		-t.xx() - t.yy() - t.zz();
	const scalar c =
		t.xx()*t.yy() + t.xx()*t.zz() + t.yy()*t.zz()
		- t.xy()*t.yx() - t.yz()*t.zy() - t.zx()*t.xz();
	const scalar d =
		-t.xx()*t.yy()*t.zz()
		- t.xy()*t.yz()*t.zx() - t.xz()*t.zy()*t.yx()
		+ t.xx()*t.yz()*t.zy() + t.yy()*t.zx()*t.xz() + t.zz()*t.xy()*t.yx();

	// Solve
	Roots<3> roots = cubicEqn(1, b, c, d).roots();

	// Check the root types
	vector lambda = vector::zero;
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
	if (lambda.y() > lambda.z())
	{
		Swap(lambda.y(), lambda.z());
	}
	if (lambda.x() > lambda.y())
	{
		Swap(lambda.x(), lambda.y());
	}

	return lambda;
}


tnbLib::vector tnbLib::eigenVector
(
	const tensor& T,
	const scalar lambda,
	const vector& direction1,
	const vector& direction2
)
{
	// Construct the linear system for this eigenvalue
	tensor A(T - lambda * I);

	// Determinants of the 2x2 sub-matrices used to find the eigenvectors
	scalar sd0, sd1, sd2;
	scalar magSd0, magSd1, magSd2;

	// Sub-determinants for a unique eivenvalue
	sd0 = A.yy()*A.zz() - A.yz()*A.zy();
	sd1 = A.zz()*A.xx() - A.zx()*A.xz();
	sd2 = A.xx()*A.yy() - A.xy()*A.yx();
	magSd0 = mag(sd0);
	magSd1 = mag(sd1);
	magSd2 = mag(sd2);

	// Evaluate the eigenvector using the largest sub-determinant
	if (magSd0 >= magSd1 && magSd0 >= magSd2 && magSd0 > small)
	{
		vector ev
		(
			1,
			(A.yz()*A.zx() - A.zz()*A.yx()) / sd0,
			(A.zy()*A.yx() - A.yy()*A.zx()) / sd0
		);

		return ev / mag(ev);
	}
	else if (magSd1 >= magSd2 && magSd1 > small)
	{
		vector ev
		(
			(A.xz()*A.zy() - A.zz()*A.xy()) / sd1,
			1,
			(A.zx()*A.xy() - A.xx()*A.zy()) / sd1
		);

		return ev / mag(ev);
	}
	else if (magSd2 > small)
	{
		vector ev
		(
			(A.xy()*A.yz() - A.yy()*A.xz()) / sd2,
			(A.yx()*A.xz() - A.xx()*A.yz()) / sd2,
			1
		);

		return ev / mag(ev);
	}

	// Sub-determinants for a repeated eigenvalue
	sd0 = A.yy()*direction1.z() - A.yz()*direction1.y();
	sd1 = A.zz()*direction1.x() - A.zx()*direction1.z();
	sd2 = A.xx()*direction1.y() - A.xy()*direction1.x();
	magSd0 = mag(sd0);
	magSd1 = mag(sd1);
	magSd2 = mag(sd2);

	// Evaluate the eigenvector using the largest sub-determinant
	if (magSd0 >= magSd1 && magSd0 >= magSd2 && magSd0 > small)
	{
		vector ev
		(
			1,
			(A.yz()*direction1.x() - direction1.z()*A.yx()) / sd0,
			(direction1.y()*A.yx() - A.yy()*direction1.x()) / sd0
		);

		return ev / mag(ev);
	}
	else if (magSd1 >= magSd2 && magSd1 > small)
	{
		vector ev
		(
			(direction1.z()*A.zy() - A.zz()*direction1.y()) / sd1,
			1,
			(A.zx()*direction1.y() - direction1.x()*A.zy()) / sd1
		);

		return ev / mag(ev);
	}
	else if (magSd2 > small)
	{
		vector ev
		(
			(A.xy()*direction1.z() - direction1.y()*A.xz()) / sd2,
			(direction1.x()*A.xz() - A.xx()*direction1.z()) / sd2,
			1
		);

		return ev / mag(ev);
	}

	// Triple eigenvalue
	return direction1 ^ direction2;
}


tnbLib::tensor tnbLib::eigenVectors(const tensor& T, const vector& lambdas)
{
	vector Ux(1, 0, 0), Uy(0, 1, 0), Uz(0, 0, 1);

	Ux = eigenVector(T, lambdas.x(), Uy, Uz);
	Uy = eigenVector(T, lambdas.y(), Uz, Ux);
	Uz = eigenVector(T, lambdas.z(), Ux, Uy);

	return tensor(Ux, Uy, Uz);
}


tnbLib::tensor tnbLib::eigenVectors(const tensor& T)
{
	const vector lambdas(eigenValues(T));

	return eigenVectors(T, lambdas);
}


tnbLib::vector tnbLib::eigenValues(const symmTensor& T)
{
	return eigenValues(tensor(T));
}


tnbLib::vector tnbLib::eigenVector
(
	const symmTensor& T,
	const scalar lambda,
	const vector& direction1,
	const vector& direction2
)
{
	return eigenVector(tensor(T), lambda, direction1, direction2);
}


tnbLib::tensor tnbLib::eigenVectors(const symmTensor& T, const vector& lambdas)
{
	return eigenVectors(tensor(T), lambdas);
}


tnbLib::tensor tnbLib::eigenVectors(const symmTensor& T)
{
	return eigenVectors(tensor(T));
}


// ************************************************************************* //