#include <dimensionedSymmTensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<>
	dimensionedSymmTensor dimensionedSymmTensor::T() const
	{
		return dimensionedSymmTensor
		(
			name() + ".T()",
			dimensions(),
			value().T()
		);
	}


	// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

	dimensionedSymmTensor sqr(const dimensionedVector& dv)
	{
		return dimensionedSymmTensor
		(
			"sqr(" + dv.name() + ')',
			sqr(dv.dimensions()),
			sqr(dv.value())
		);
	}


	dimensionedSymmTensor innerSqr(const dimensionedSymmTensor& dt)
	{
		return dimensionedSymmTensor
		(
			"innerSqr(" + dt.name() + ')',
			sqr(dt.dimensions()),
			innerSqr(dt.value())
		);
	}


	dimensionedScalar tr(const dimensionedSymmTensor& dt)
	{
		return dimensionedScalar
		(
			"tr(" + dt.name() + ')',
			dt.dimensions(),
			tr(dt.value())
		);
	}


	dimensionedSymmTensor symm(const dimensionedSymmTensor& dt)
	{
		return dimensionedSymmTensor
		(
			"symm(" + dt.name() + ')',
			dt.dimensions(),
			symm(dt.value())
		);
	}


	dimensionedSymmTensor twoSymm(const dimensionedSymmTensor& dt)
	{
		return dimensionedSymmTensor
		(
			"twoSymm(" + dt.name() + ')',
			dt.dimensions(),
			twoSymm(dt.value())
		);
	}


	dimensionedSymmTensor dev(const dimensionedSymmTensor& dt)
	{
		return dimensionedSymmTensor
		(
			"dev(" + dt.name() + ')',
			dt.dimensions(),
			dev(dt.value())
		);
	}


	dimensionedSymmTensor dev2(const dimensionedSymmTensor& dt)
	{
		return dimensionedSymmTensor
		(
			"dev2(" + dt.name() + ')',
			dt.dimensions(),
			dev2(dt.value())
		);
	}


	dimensionedScalar det(const dimensionedSymmTensor& dt)
	{
		return dimensionedScalar
		(
			"det(" + dt.name() + ')',
			pow(dt.dimensions(), symmTensor::dim),
			det(dt.value())
		);
	}


	dimensionedSymmTensor cof(const dimensionedSymmTensor& dt)
	{
		return dimensionedSymmTensor
		(
			"cof(" + dt.name() + ')',
			pow(dt.dimensions(), symmTensor::dim - 1),
			cof(dt.value())
		);
	}


	dimensionedSymmTensor inv(const dimensionedSymmTensor& dt)
	{
		return dimensionedSymmTensor
		(
			"inv(" + dt.name() + ')',
			dimless / dt.dimensions(),
			inv(dt.value())
		);
	}


	// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

	dimensionedVector operator*(const dimensionedSymmTensor& dt)
	{
		return dimensionedVector
		(
			"*" + dt.name(),
			dt.dimensions(),
			*dt.value()
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //