#include <dimensionedTensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<>
	dimensionedTensor dimensionedTensor::T() const
	{
		return dimensionedTensor
		(
			name() + ".T()",
			dimensions(),
			value().T()
		);
	}


	// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

	dimensionedScalar tr(const dimensionedTensor& dt)
	{
		return dimensionedScalar
		(
			"tr(" + dt.name() + ')',
			dt.dimensions(),
			tr(dt.value())
		);
	}


	dimensionedTensor dev(const dimensionedTensor& dt)
	{
		return dimensionedTensor
		(
			"dev(" + dt.name() + ')',
			dt.dimensions(),
			dev(dt.value())
		);
	}


	dimensionedTensor dev2(const dimensionedTensor& dt)
	{
		return dimensionedTensor
		(
			"dev2(" + dt.name() + ')',
			dt.dimensions(),
			dev2(dt.value())
		);
	}


	dimensionedScalar det(const dimensionedTensor& dt)
	{
		return dimensionedScalar
		(
			"det(" + dt.name() + ')',
			pow(dt.dimensions(), tensor::dim),
			det(dt.value())
		);
	}


	dimensionedTensor cof(const dimensionedTensor& dt)
	{
		return dimensionedTensor
		(
			"cof(" + dt.name() + ')',
			pow(dt.dimensions(), tensor::dim - 1),
			cof(dt.value())
		);
	}


	dimensionedTensor inv(const dimensionedTensor& dt)
	{
		return dimensionedTensor
		(
			"inv(" + dt.name() + ')',
			inv(dt.dimensions()),
			inv(dt.value())
		);
	}


	dimensionedSymmTensor symm(const dimensionedTensor& dt)
	{
		return dimensionedSymmTensor
		(
			"symm(" + dt.name() + ')',
			dt.dimensions(),
			symm(dt.value())
		);
	}

	dimensionedSymmTensor twoSymm(const dimensionedTensor& dt)
	{
		return dimensionedSymmTensor
		(
			"twoSymm(" + dt.name() + ')',
			dt.dimensions(),
			twoSymm(dt.value())
		);
	}

	dimensionedTensor skew(const dimensionedTensor& dt)
	{
		return dimensionedTensor
		(
			"skew(" + dt.name() + ')',
			dt.dimensions(),
			skew(dt.value())
		);
	}


	dimensionedVector eigenValues(const dimensionedTensor& dt)
	{
		return dimensionedVector
		(
			"eigenValues(" + dt.name() + ')',
			dt.dimensions(),
			eigenValues(dt.value())
		);
	}


	dimensionedTensor eigenVectors(const dimensionedTensor& dt)
	{
		return dimensionedTensor
		(
			"eigenVectors(" + dt.name() + ')',
			dimless,
			eigenVectors(dt.value())
		);
	}


	dimensionedVector eigenValues(const dimensionedSymmTensor& dt)
	{
		return dimensionedVector
		(
			"eigenValues(" + dt.name() + ')',
			dt.dimensions(),
			eigenValues(dt.value())
		);
	}


	dimensionedTensor eigenVectors(const dimensionedSymmTensor& dt)
	{
		return dimensionedTensor
		(
			"eigenVectors(" + dt.name() + ')',
			dimless,
			eigenVectors(dt.value())
		);
	}


	// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

	dimensionedVector operator*(const dimensionedTensor& dt)
	{
		return dimensionedVector
		(
			"*" + dt.name(),
			dt.dimensions(),
			*dt.value()
		);
	}


	dimensionedTensor operator*(const dimensionedVector& dv)
	{
		return dimensionedTensor
		(
			"*" + dv.name(),
			dv.dimensions(),
			*dv.value()
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //