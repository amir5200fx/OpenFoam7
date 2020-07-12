#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type, template<class> class PatchField, class GeoMesh>
inline const tnbLib::GeometricField<Type, PatchField, GeoMesh>&
tnbLib::GeometricField<Type, PatchField, GeoMesh>::null()
{
	return NullObjectRef<GeometricField<Type, PatchField, GeoMesh>>();
}


template<class Type, template<class> class PatchField, class GeoMesh>
inline
const typename
tnbLib::GeometricField<Type, PatchField, GeoMesh>::Internal&
tnbLib::GeometricField<Type, PatchField, GeoMesh>::
internalField() const
{
	return *this;
}


//template<class Type, template<class> class PatchField, class GeoMesh>
//inline
//const typename
//tnbLib::GeometricField<Type, PatchField, GeoMesh>::Internal::FieldType&
//tnbLib::GeometricField<Type, PatchField, GeoMesh>::primitiveField() const
//{
//	return *this;
//}


template<class Type, template<class> class PatchField, class GeoMesh>
inline const typename tnbLib::GeometricField<Type, PatchField, GeoMesh>::
Boundary&
tnbLib::GeometricField<Type, PatchField, GeoMesh>::boundaryField() const
{
	return boundaryField_;
}


template<class Type, template<class> class PatchField, class GeoMesh>
inline tnbLib::label
tnbLib::GeometricField<Type, PatchField, GeoMesh>::timeIndex() const
{
	return timeIndex_;
}


template<class Type, template<class> class PatchField, class GeoMesh>
inline tnbLib::label&
tnbLib::GeometricField<Type, PatchField, GeoMesh>::timeIndex()
{
	return timeIndex_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type, template<class> class PatchField, class GeoMesh>
inline
const typename
tnbLib::GeometricField<Type, PatchField, GeoMesh>::Internal&
tnbLib::GeometricField<Type, PatchField, GeoMesh>::
operator()() const
{
	return *this;
}


// ************************************************************************* //