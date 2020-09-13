#pragma once
#include <runTimeSelectionTables.hxx>
#include <pointMesh.hxx>

#include <GeometricField.hxx>  // added by amir
#include <fvPatchField.hxx>  // added by amir
#include <fvMesh.hxx>  // added by amir
#include <Time.hxx>  // added by amir
#include <polyMeshTetDecomposition.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::AveragingMethod<Type>::updateGrad()
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::AveragingMethod<Type>::AveragingMethod
(
	const IOobject& io,
	const dictionary& dict,
	const fvMesh& mesh,
	const labelList& size
)
	:
	regIOobject(io),
	FieldField<Field, Type>(),
	dict_(dict),
	mesh_(mesh)
{
	forAll(size, i)
	{
		FieldField<Field, Type>::append
		(
			new Field<Type>(size[i], Zero)
		);
	}
}


template<class Type>
tnbLib::AveragingMethod<Type>::AveragingMethod
(
	const AveragingMethod<Type>& am
)
	:
	regIOobject(am),
	FieldField<Field, Type>(am),
	dict_(am.dict_),
	mesh_(am.mesh_)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::autoPtr<tnbLib::AveragingMethod<Type>>
tnbLib::AveragingMethod<Type>::New
(
	const IOobject& io,
	const dictionary& dict,
	const fvMesh& mesh
)
{
	word averageType(dict.lookup(typeName));

	// Info<< "Selecting averaging method "
	//    << averageType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(averageType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown averaging method " << averageType
			<< ", constructor not in hash table" << nl << nl
			<< "    Valid averaging methods are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< abort(FatalError);
	}

	return autoPtr<AveragingMethod<Type>>(cstrIter()(io, dict, mesh));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::AveragingMethod<Type>::~AveragingMethod()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::AveragingMethod<Type>::average()
{
	updateGrad();
}


template<class Type>
void tnbLib::AveragingMethod<Type>::average
(
	const AveragingMethod<scalar>& weight
)
{
	updateGrad();

	*this /= max(weight, small);
}


template<class Type>
bool tnbLib::AveragingMethod<Type>::writeData(Ostream& os) const
{
	return os.good();
}


template<class Type>
bool tnbLib::AveragingMethod<Type>::write(const bool write) const
{
	const pointMesh pointMesh_(mesh_);

	// point volumes
	Field<scalar> pointVolume(mesh_.nPoints(), 0);

	// output fields
	GeometricField<Type, fvPatchField, volMesh> cellValue
	(
		tnbLib::IOobject
		(
			this->name() + ":cellValue",
			this->time().timeName(),
			mesh_
		),
		mesh_,
		dimensioned<Type>("zero", dimless, Zero)
	);
	GeometricField<TypeGrad, fvPatchField, volMesh> cellGrad
	(
		tnbLib::IOobject
		(
			this->name() + ":cellGrad",
			this->time().timeName(),
			mesh_
		),
		mesh_,
		dimensioned<TypeGrad>("zero", dimless, Zero)
	);
	GeometricField<Type, pointPatchField, pointMesh> pointValue
	(
		tnbLib::IOobject
		(
			this->name() + ":pointValue",
			this->time().timeName(),
			mesh_
		),
		pointMesh_,
		dimensioned<Type>("zero", dimless, Zero)
	);
	GeometricField<TypeGrad, pointPatchField, pointMesh> pointGrad
	(
		tnbLib::IOobject
		(
			this->name() + ":pointGrad",
			this->time().timeName(),
			mesh_
		),
		pointMesh_,
		dimensioned<TypeGrad>("zero", dimless, Zero)
	);

	// Barycentric coordinates of the tet vertices
	const FixedList<barycentric, 4>
		tetCrds
		({
			barycentric(1, 0, 0, 0),
			barycentric(0, 1, 0, 0),
			barycentric(0, 0, 1, 0),
			barycentric(0, 0, 0, 1)
			});

	// tet-volume weighted sums
	forAll(mesh_.C(), celli)
	{
		const List<tetIndices> cellTets =
			polyMeshTetDecomposition::cellTetIndices(mesh_, celli);

		forAll(cellTets, tetI)
		{
			const tetIndices& tetIs = cellTets[tetI];
			const triFace triIs = tetIs.faceTriIs(mesh_);
			const scalar v = tetIs.tet(mesh_).mag();

			cellValue[celli] += v * interpolate(tetCrds[0], tetIs);
			cellGrad[celli] += v * interpolateGrad(tetCrds[0], tetIs);

			forAll(triIs, vertexI)
			{
				const label pointi = triIs[vertexI];

				pointVolume[pointi] += v;
				pointValue[pointi] += v * interpolate(tetCrds[vertexI], tetIs);
				pointGrad[pointi] += v * interpolateGrad(tetCrds[vertexI], tetIs);
			}
		}
	}

	// average
	cellValue.primitiveFieldRef() /= mesh_.V();
	cellGrad.primitiveFieldRef() /= mesh_.V();
	pointValue.primitiveFieldRef() /= pointVolume;
	pointGrad.primitiveFieldRef() /= pointVolume;

	// write
	if (!cellValue.write(write)) return false;
	if (!cellGrad.write(write)) return false;
	if (!pointValue.write(write)) return false;
	if (!pointGrad.write(write)) return false;

	return true;
}


// ************************************************************************* //