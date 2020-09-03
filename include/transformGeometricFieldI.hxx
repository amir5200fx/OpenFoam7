#pragma once
#include <transformField.hxx>
#include <transformFieldField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	template<class Type, template<class> class PatchField, class GeoMesh>
	void transform
	(
		GeometricField<Type, PatchField, GeoMesh>& rtf,
		const GeometricField<tensor, PatchField, GeoMesh>& trf,
		const GeometricField<Type, PatchField, GeoMesh>& tf
	)
	{
		transform
		(
			rtf.primitiveFieldRef(),
			trf.primitiveField(),
			tf.primitiveField()
		);
		transform
		(
			rtf.boundaryFieldRef(),
			trf.boundaryField(),
			tf.boundaryField()
		);
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> transform
	(
		const GeometricField<tensor, PatchField, GeoMesh>& trf,
		const GeometricField<Type, PatchField, GeoMesh>& tf
	)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tranf
		(
			GeometricField<Type, PatchField, GeoMesh>::New
			(
				"transform(" + trf.name() + ',' + tf.name() + ')',
				tf.mesh(),
				tf.dimensions()
			)
		);

		transform(tranf.ref(), trf, tf);

		return tranf;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> transform
	(
		const GeometricField<tensor, PatchField, GeoMesh>& trf,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& ttf
	)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tranf =
			transform(trf, ttf());
		ttf.clear();
		return tranf;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> transform
	(
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>& ttrf,
		const GeometricField<Type, PatchField, GeoMesh>& tf
	)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tranf =
			transform(ttrf(), tf);
		ttrf.clear();
		return tranf;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> transform
	(
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>& ttrf,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& ttf
	)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tranf =
			transform(ttrf(), ttf());
		ttf.clear();
		ttrf.clear();
		return tranf;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	void transform
	(
		GeometricField<Type, PatchField, GeoMesh>& rtf,
		const dimensionedTensor& t,
		const GeometricField<Type, PatchField, GeoMesh>& tf
	)
	{
		transform(rtf.primitiveFieldRef(), t.value(), tf.primitiveField());
		transform(rtf.boundaryFieldRef(), t.value(), tf.boundaryField());
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> transform
	(
		const dimensionedTensor& t,
		const GeometricField<Type, PatchField, GeoMesh>& tf
	)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tranf
		(
			GeometricField<Type, PatchField, GeoMesh>::New
			(
				"transform(" + t.name() + ',' + tf.name() + ')',
				tf.mesh(),
				tf.dimensions()
			)
		);

		transform(tranf.ref(), t, tf);

		return tranf;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> transform
	(
		const dimensionedTensor& t,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>& ttf
	)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh>> tranf =
			transform(t, ttf());
		ttf.clear();
		return tranf;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //