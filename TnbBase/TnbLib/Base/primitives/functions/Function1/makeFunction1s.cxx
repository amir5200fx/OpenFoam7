#include <Constant.hxx>
#include <UniformTemplate.hxx>
#include <ZeroConstant.hxx>
#include <OneConstant.hxx>
#include <PolynomialEntry.hxx>
#include <Sine.hxx>
#include <Square.hxx>
#include <CSV.hxx>
#include <Table.hxx>
#include <TableFile.hxx>
#include <Scale.hxx>

#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeFunction1s(Type)                                                   \
    makeFunction1(Type);                                                       \
    makeFunction1Type(Constant, Type);                                         \
    makeFunction1Type(Uniform, Type);                                          \
    makeFunction1Type(ZeroConstant, Type);                                     \
    makeFunction1Type(OneConstant, Type);                                      \
    makeFunction1Type(Polynomial, Type);                                       \
    makeFunction1Type(Sine, Type);                                             \
    makeFunction1Type(Square, Type);                                           \
    makeFunction1Type(CSV, Type);                                              \
    makeFunction1Type(Table, Type);                                            \
    makeFunction1Type(TableFile, Type);                                        \
    makeFunction1Type(Scale, Type);

namespace tnbLib
{
	makeFunction1(label);
	makeFunction1Type(Constant, label);

	makeFunction1s(scalar);
	makeFunction1s(vector);
	makeFunction1s(sphericalTensor);
	makeFunction1s(symmTensor);
	makeFunction1s(tensor);
}


template<>
tnbLib::tmp<tnbLib::Field<tnbLib::label>>
tnbLib::Function1Types::Constant<tnbLib::label>::integrate
(
	const scalarField& x1,
	const scalarField& x2
) const
{
	FatalErrorInFunction
		<< "Evaluation is not defined for " << type() << " functions"
		<< exit(FatalError);

	return tmp<Field<label>>(new Field<label>(x1.size()));
}


// ************************************************************************* //