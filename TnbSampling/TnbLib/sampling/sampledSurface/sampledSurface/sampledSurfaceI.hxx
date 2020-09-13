#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
bool tnbLib::sampledSurface::checkFieldSize(const Field<Type>& field) const
{
	if (faces().empty() || field.empty())
	{
		return false;
	}

	if (field.size() != faces().size())
	{
		FatalErrorInFunction
			<< "size mismatch: "
			<< "field (" << field.size()
			<< ") != surface (" << faces().size() << ")"
			<< exit(FatalError);
	}

	return true;
}


template<class Type>
Type tnbLib::sampledSurface::integrate(const Field<Type>& field) const
{
	Type value = Zero;

	if (checkFieldSize(field))
	{
		value = sum(field*magSf());
	}

	reduce(value, sumOp<Type>());
	return value;
}


template<class Type>
Type tnbLib::sampledSurface::integrate(const tmp<Field<Type>>& field) const
{
	Type value = integrate(field());
	field.clear();
	return value;
}


template<class Type>
Type tnbLib::sampledSurface::average(const Field<Type>& field) const
{
	Type value = Zero;

	if (checkFieldSize(field))
	{
		value = sum(field*magSf());
	}

	reduce(value, sumOp<Type>());

	// avoid divide-by-zero
	if (area())
	{
		return value / area();
	}
	else
	{
		return Zero;
	}
}


template<class Type>
Type tnbLib::sampledSurface::average(const tmp<Field<Type>>& field) const
{
	Type value = average(field());
	field.clear();
	return value;
}


template<class ReturnType, class Type>
void tnbLib::sampledSurface::project
(
	Field<ReturnType>& res,
	const Field<Type>& field
) const
{
	if (checkFieldSize(field))
	{
		const vectorField& norm = Sf();

		forAll(norm, facei)
		{
			res[facei] = field[facei] & (norm[facei] / mag(norm[facei]));
		}
	}
	else
	{
		res.clear();
	}
}


template<class ReturnType, class Type>
void tnbLib::sampledSurface::project
(
	Field<ReturnType>& res,
	const tmp<Field<Type>>& field
) const
{
	project(res, field());
	field.clear();
}


template<class ReturnType, class Type>
tnbLib::tmp<tnbLib::Field<ReturnType>>
tnbLib::sampledSurface::project
(
	const tmp<Field<Type>>& field
) const
{
	tmp<Field<ReturnType>> tRes(new Field<ReturnType>(faces().size()));
	project(tRes(), field);
	return tRes;
}


template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh>>
tnbLib::sampledSurface::pointAverage
(
	const GeometricField<Type, pointPatchField, pointMesh>& pfld
) const
{
	const fvMesh& mesh = dynamic_cast<const fvMesh&>(pfld.mesh()());

	tmp<GeometricField<Type, fvPatchField, volMesh>> tcellAvg
	(
		new GeometricField<Type, fvPatchField, volMesh>
		(
			IOobject
			(
				"cellAvg",
				mesh.time().timeName(),
				pfld.db(),
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			),
			mesh,
			dimensioned<Type>("zero", dimless, Zero)
			)
	);
	GeometricField<Type, fvPatchField, volMesh>& cellAvg = tcellAvg.ref();

	labelField nPointCells(mesh.nCells(), 0);
	{
		for (label pointi = 0; pointi < mesh.nPoints(); pointi++)
		{
			const labelList& pCells = mesh.pointCells(pointi);

			forAll(pCells, i)
			{
				label celli = pCells[i];

				cellAvg[celli] += pfld[pointi];
				nPointCells[celli]++;
			}
		}
	}
	forAll(cellAvg, celli)
	{
		cellAvg[celli] /= nPointCells[celli];
	}
	// Give value to calculatedFvPatchFields
	cellAvg.correctBoundaryConditions();

	return tcellAvg;
}


// ************************************************************************* //