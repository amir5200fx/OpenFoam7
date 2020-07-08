#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type, class GeoMesh>
inline const tnbLib::DimensionedField<Type, GeoMesh>&
tnbLib::DimensionedField<Type, GeoMesh>::null()
{
	return NullObjectRef<DimensionedField<Type, GeoMesh>>();
}


template<class Type, class GeoMesh>
inline const typename GeoMesh::Mesh&
tnbLib::DimensionedField<Type, GeoMesh>::mesh() const
{
	return mesh_;
}


template<class Type, class GeoMesh>
inline const tnbLib::dimensionSet&
tnbLib::DimensionedField<Type, GeoMesh>::dimensions() const
{
	return dimensions_;
}

template<class Type, class GeoMesh>
inline tnbLib::dimensionSet&
tnbLib::DimensionedField<Type, GeoMesh>::dimensions()
{
	return dimensions_;
}


template<class Type, class GeoMesh>
inline const tnbLib::Field<Type>&
tnbLib::DimensionedField<Type, GeoMesh>::field() const
{
	return *this;
}

template<class Type, class GeoMesh>
inline tnbLib::Field<Type>&
tnbLib::DimensionedField<Type, GeoMesh>::field()
{
	return *this;
}


// ************************************************************************* //