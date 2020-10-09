#pragma once
#include <Time.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Residuals<Type>::Residuals(const polyMesh& mesh)
	:
	MeshObject<polyMesh, GeometricMeshObject, Residuals<Type>>(mesh),
	prevTimeIndex_(-1)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::List<tnbLib::word> tnbLib::Residuals<Type>::fieldNames(const polyMesh& mesh)
{
	return MeshObject<polyMesh, GeometricMeshObject, Residuals<Type>>::New
	(
		mesh
	).HashTable<DynamicList<SolverPerformance<Type>>>::toc();
}


template<class Type>
bool tnbLib::Residuals<Type>::found(const polyMesh& mesh, const word& fieldName)
{
	return MeshObject<polyMesh, GeometricMeshObject, Residuals<Type>>::New
	(
		mesh
	).HashTable<DynamicList<SolverPerformance<Type>>>::found(fieldName);
}


template<class Type>
const tnbLib::DynamicList<tnbLib::SolverPerformance<Type>>&
tnbLib::Residuals<Type>::field
(
	const polyMesh& mesh,
	const word& fieldName
)
{
	return MeshObject<polyMesh, GeometricMeshObject, Residuals<Type>>::New
	(
		mesh
	)[fieldName];
}


template<class Type>
void tnbLib::Residuals<Type>::append
(
	const polyMesh& mesh,
	const SolverPerformance<Type>& sp
)
{
	Residuals<Type>& residuals = const_cast<Residuals<Type>&>
		(
			MeshObject<polyMesh, GeometricMeshObject, Residuals<Type>>::New
			(
				mesh
			)
			);

	HashTable<DynamicList<SolverPerformance<Type>>>& table = residuals;

	const label timeIndex =
		mesh.time().subCycling()
		? mesh.time().prevTimeState().timeIndex()
		: mesh.time().timeIndex();

	if (residuals.prevTimeIndex_ != timeIndex)
	{
		// Reset solver performance between iterations
		residuals.prevTimeIndex_ = timeIndex;
		table.clear();
	}

	if (table.found(sp.fieldName()))
	{
		table[sp.fieldName()].append(sp);
	}
	else
	{
		table.insert
		(
			sp.fieldName(),
			DynamicList<SolverPerformance<Type>>(1, sp)
		);
	}
}


// ************************************************************************* //