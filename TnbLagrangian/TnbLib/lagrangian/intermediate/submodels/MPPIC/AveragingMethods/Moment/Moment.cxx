#include <Moment.hxx>

#include <fvMesh.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir
#include <volFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::AveragingMethods::Moment<Type>::Moment
(
	const IOobject& io,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	AveragingMethod<Type>(io, dict, mesh, labelList(4, mesh.nCells())),
	data_(FieldField<Field, Type>::operator[](0)),
	dataX_(FieldField<Field, Type>::operator[](1)),
	dataY_(FieldField<Field, Type>::operator[](2)),
	dataZ_(FieldField<Field, Type>::operator[](3)),
	transform_(mesh.nCells(), Zero),
	scale_(0.5*pow(mesh.V(), 1.0 / 3.0))
{
	scalar a = 1.0 / 24.0;
	scalar b = 0.5854101966249685;
	scalar c = 0.1381966011250105;

	scalarField wQ(4);
	wQ[0] = a;
	wQ[1] = a;
	wQ[2] = a;
	wQ[3] = a;

	vectorField xQ(4);
	xQ[0] = vector(b, c, c);
	xQ[1] = vector(c, b, c);
	xQ[2] = vector(c, c, b);
	xQ[3] = vector(c, c, c);

	forAll(mesh.C(), celli)
	{
		const List<tetIndices> cellTets =
			polyMeshTetDecomposition::cellTetIndices(mesh, celli);

		symmTensor A(Zero);

		forAll(cellTets, tetI)
		{
			const tetIndices& tetIs = cellTets[tetI];
			const triFace triIs = tetIs.faceTriIs(mesh);

			const tensor T
			(
				tensor
				(
					mesh.points()[triIs[0]] - mesh.C()[celli],
					mesh.points()[triIs[1]] - mesh.C()[celli],
					mesh.points()[triIs[2]] - mesh.C()[celli]
				).T()
			);

			const vectorField d((T & xQ) / scale_[celli]);

			const scalar v(6.0*tetIs.tet(mesh).mag() / mesh.V()[celli]);

			A += v * sum(wQ*sqr(d));
		}

		transform_[celli] = inv(A);
	}
}


template<class Type>
tnbLib::AveragingMethods::Moment<Type>::Moment
(
	const Moment<Type>& am
)
	:
	AveragingMethod<Type>(am),
	data_(FieldField<Field, Type>::operator[](0)),
	dataX_(FieldField<Field, Type>::operator[](1)),
	dataY_(FieldField<Field, Type>::operator[](2)),
	dataZ_(FieldField<Field, Type>::operator[](3)),
	transform_(am.transform_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::AveragingMethods::Moment<Type>::~Moment()
{}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::AveragingMethods::Moment<Type>::updateGrad()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::AveragingMethods::Moment<Type>::add
(
	const barycentric& coordinates,
	const tetIndices& tetIs,
	const Type& value
)
{
	const label celli = tetIs.cell();
	const triFace triIs = tetIs.faceTriIs(this->mesh_);

	const point delta =
		(coordinates[0] - 1)*this->mesh_.C()[celli]
		+ coordinates[1] * this->mesh_.points()[triIs[0]]
		+ coordinates[2] * this->mesh_.points()[triIs[1]]
		+ coordinates[3] * this->mesh_.points()[triIs[2]];

	const Type v = value / this->mesh_.V()[celli];
	const TypeGrad dv = transform_[celli] & (v*delta / scale_[celli]);

	data_[celli] += v;
	dataX_[celli] += v + dv.x();
	dataY_[celli] += v + dv.y();
	dataZ_[celli] += v + dv.z();
}


template<class Type>
Type tnbLib::AveragingMethods::Moment<Type>::interpolate
(
	const barycentric& coordinates,
	const tetIndices& tetIs
) const
{
	const label celli = tetIs.cell();
	const triFace triIs = tetIs.faceTriIs(this->mesh_);

	const point delta =
		(coordinates[0] - 1)*this->mesh_.C()[celli]
		+ coordinates[1] * this->mesh_.points()[triIs[0]]
		+ coordinates[2] * this->mesh_.points()[triIs[1]]
		+ coordinates[3] * this->mesh_.points()[triIs[2]];

	return
		data_[celli]
		+ (
			TypeGrad
			(
				dataX_[celli] - data_[celli],
				dataY_[celli] - data_[celli],
				dataZ_[celli] - data_[celli]
			)
			& delta / scale_[celli]
			);
}


template<class Type>
typename tnbLib::AveragingMethods::Moment<Type>::TypeGrad
tnbLib::AveragingMethods::Moment<Type>::interpolateGrad
(
	const barycentric& coordinates,
	const tetIndices& tetIs
) const
{
	const label celli(tetIs.cell());

	return
		TypeGrad
		(
			dataX_[celli] - data_[celli],
			dataY_[celli] - data_[celli],
			dataZ_[celli] - data_[celli]
		) / scale_[celli];
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::AveragingMethods::Moment<Type>::primitiveField() const
{
	return tmp<Field<Type>>(data_);
}


// ************************************************************************* //