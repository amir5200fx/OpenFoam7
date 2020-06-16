#include <vector2DField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::vector2DField> tnbLib::zip
(
	const tmp<scalarField>& x,
	const tmp<scalarField>& y
)
{
	tmp<vector2DField> txy(new vector2DField(x->size()));
	vector2DField& xy = txy.ref();
	xy.replace(0, x);
	xy.replace(1, y);
	return txy;
}

// ************************************************************************* //