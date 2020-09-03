#pragma once
#include <dimensionedType.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	// check mesh for two fields
//#define checkField(df1, df2, op)                                    \
//if (&(df1).mesh() != &(df2).mesh())                                 \
//{                                                                   \
//    FatalErrorInFunction                                            \
//        << "different mesh for fields "                             \
//        << (df1).name() << " and " << (df2).name()                  \
//        << " during operatrion " <<  op                             \
//        << abort(FatalError);                                       \
//}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type, class GeoMesh>
	DimensionedField<Type, GeoMesh>::DimensionedField
	(
		const IOobject& io,
		const Mesh& mesh,
		const dimensionSet& dims,
		const Field<Type>& field
	)
		:
		regIOobject(io),
		Field<Type>(field),
		mesh_(mesh),
		dimensions_(dims)
	{
		if (field.size() && field.size() != GeoMesh::size(mesh))
		{
			FatalErrorInFunction
				<< "size of field = " << field.size()
				<< " is not the same as the size of mesh = "
				<< GeoMesh::size(mesh)
				<< abort(FatalError);
		}
	}


	template<class Type, class GeoMesh>
	DimensionedField<Type, GeoMesh>::DimensionedField
	(
		const IOobject& io,
		const Mesh& mesh,
		const dimensionSet& dims,
		const bool checkIOFlags
	)
		:
		regIOobject(io),
		Field<Type>(GeoMesh::size(mesh)),
		mesh_(mesh),
		dimensions_(dims)
	{
		if (checkIOFlags)
		{
			readIfPresent();
		}
	}


	template<class Type, class GeoMesh>
	DimensionedField<Type, GeoMesh>::DimensionedField
	(
		const IOobject& io,
		const Mesh& mesh,
		const dimensioned<Type>& dt,
		const bool checkIOFlags
	)
		:
		regIOobject(io),
		Field<Type>(GeoMesh::size(mesh), dt.value()),
		mesh_(mesh),
		dimensions_(dt.dimensions())
	{
		if (checkIOFlags)
		{
			readIfPresent();
		}
	}


	template<class Type, class GeoMesh>
	DimensionedField<Type, GeoMesh>::DimensionedField
	(
		const DimensionedField<Type, GeoMesh>& df
	)
		:
		regIOobject(df),
		Field<Type>(df),
		mesh_(df.mesh_),
		dimensions_(df.dimensions_)
	{}


	template<class Type, class GeoMesh>
	DimensionedField<Type, GeoMesh>::DimensionedField
	(
		DimensionedField<Type, GeoMesh>& df,
		bool reuse
	)
		:
		regIOobject(df, reuse),
		Field<Type>(df, reuse),
		mesh_(df.mesh_),
		dimensions_(df.dimensions_)
	{}


	template<class Type, class GeoMesh>
	DimensionedField<Type, GeoMesh>::DimensionedField
	(
		DimensionedField<Type, GeoMesh>&& df
	)
		:
		regIOobject(move(df), true),
		Field<Type>(move(df)),
		mesh_(df.mesh_),
		dimensions_(move(df.dimensions_))
	{}


	template<class Type, class GeoMesh>
	DimensionedField<Type, GeoMesh>::DimensionedField
	(
		const tmp<DimensionedField<Type, GeoMesh>>& tdf
	)
		:
		regIOobject(tdf(), tdf.isTmp()),
		Field<Type>
		(
			const_cast<DimensionedField<Type, GeoMesh>&>(tdf()),
			tdf.isTmp()
			),
		mesh_(tdf().mesh_),
		dimensions_(tdf().dimensions_)
	{
		tdf.clear();
	}


	template<class Type, class GeoMesh>
	DimensionedField<Type, GeoMesh>::DimensionedField
	(
		const IOobject& io,
		const DimensionedField<Type, GeoMesh>& df
	)
		:
		regIOobject(io),
		Field<Type>(df),
		mesh_(df.mesh_),
		dimensions_(df.dimensions_)
	{}


	template<class Type, class GeoMesh>
	DimensionedField<Type, GeoMesh>::DimensionedField
	(
		const IOobject& io,
		DimensionedField<Type, GeoMesh>& df,
		bool reuse
	)
		:
		regIOobject(io, df),
		Field<Type>(df, reuse),
		mesh_(df.mesh_),
		dimensions_(df.dimensions_)
	{}


	template<class Type, class GeoMesh>
	DimensionedField<Type, GeoMesh>::DimensionedField
	(
		const word& newName,
		const DimensionedField<Type, GeoMesh>& df
	)
		:
		regIOobject(newName, df, newName != df.name()),
		Field<Type>(df),
		mesh_(df.mesh_),
		dimensions_(df.dimensions_)
	{}


	template<class Type, class GeoMesh>
	DimensionedField<Type, GeoMesh>::DimensionedField
	(
		const word& newName,
		DimensionedField<Type, GeoMesh>& df,
		bool reuse
	)
		:
		regIOobject(newName, df, true),
		Field<Type>(df, reuse),
		mesh_(df.mesh_),
		dimensions_(df.dimensions_)
	{}


	template<class Type, class GeoMesh>
	DimensionedField<Type, GeoMesh>::DimensionedField
	(
		const word& newName,
		const tmp<DimensionedField<Type, GeoMesh>>& tdf
	)
		:
		regIOobject(newName, tdf(), true),
		Field<Type>
		(
			const_cast<DimensionedField<Type, GeoMesh>&>(tdf()),
			tdf.isTmp()
			),
		mesh_(tdf().mesh_),
		dimensions_(tdf().dimensions_)
	{
		tdf.clear();
	}


	template<class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>>
		DimensionedField<Type, GeoMesh>::clone() const
	{
		return tmp<DimensionedField<Type, GeoMesh>>
			(
				new DimensionedField<Type, GeoMesh>(*this)
				);
	}


	template<class Type, class GeoMesh>
	tnbLib::tmp<tnbLib::DimensionedField<Type, GeoMesh>>
		DimensionedField<Type, GeoMesh>::New
		(
			const word& name,
			const Mesh& mesh,
			const dimensionSet& ds
		)
	{
		return tmp<DimensionedField<Type, GeoMesh>>
			(
				new DimensionedField<Type, GeoMesh>
				(
					IOobject
					(
						name,
						mesh.time().timeName(),
						mesh,
						IOobject::NO_READ,
						IOobject::NO_WRITE,
						false
					),
					mesh,
					ds,
					false
					)
				);
	}


	template<class Type, class GeoMesh>
	tnbLib::tmp<tnbLib::DimensionedField<Type, GeoMesh>>
		DimensionedField<Type, GeoMesh>::New
		(
			const word& name,
			const Mesh& mesh,
			const dimensioned<Type>& dt
		)
	{
		return tmp<DimensionedField<Type, GeoMesh>>
			(
				new DimensionedField<Type, GeoMesh>
				(
					IOobject
					(
						name,
						mesh.time().timeName(),
						mesh,
						IOobject::NO_READ,
						IOobject::NO_WRITE,
						false
					),
					mesh,
					dt,
					false
					)
				);
	}


	template<class Type, class GeoMesh>
	tnbLib::tmp<tnbLib::DimensionedField<Type, GeoMesh>>
		DimensionedField<Type, GeoMesh>::New
		(
			const word& newName,
			const DimensionedField<Type, GeoMesh>& df
		)
	{
		return tmp<DimensionedField<Type, GeoMesh>>
			(
				new DimensionedField<Type, GeoMesh>
				(
					IOobject
					(
						newName,
						df.instance(),
						df.local(),
						df.db(),
						IOobject::NO_READ,
						IOobject::NO_WRITE,
						false
					),
					df
					)
				);
	}


	template<class Type, class GeoMesh>
	tnbLib::tmp<tnbLib::DimensionedField<Type, GeoMesh>>
		DimensionedField<Type, GeoMesh>::New
		(
			const word& newName,
			const tmp<DimensionedField<Type, GeoMesh>>& tdf
		)
	{
		return tmp<DimensionedField<Type, GeoMesh>>
			(
				new DimensionedField<Type, GeoMesh>
				(
					IOobject
					(
						newName,
						tdf().instance(),
						tdf().local(),
						tdf().db(),
						IOobject::NO_READ,
						IOobject::NO_WRITE,
						false
					),
					tdf
					)
				);
	}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	template<class Type, class GeoMesh>
	DimensionedField<Type, GeoMesh>::~DimensionedField()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type, class GeoMesh>
	tmp
		<
		DimensionedField
		<typename DimensionedField<Type, GeoMesh>::cmptType, GeoMesh>
		>
		DimensionedField<Type, GeoMesh>::component
		(
			const direction d
		) const
	{
		tmp<DimensionedField<cmptType, GeoMesh>> result
		(
			DimensionedField<cmptType, GeoMesh>::New
			(
				name() + ".component(" + ::tnbLib::name(d) + ')',
				mesh_,
				dimensions_
			)
		);

		tnbLib::component(result(), *this, d);

		return result;
	}


	template<class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::replace
	(
		const direction d,
		const DimensionedField
		<typename DimensionedField<Type, GeoMesh>::cmptType, GeoMesh>& df
	)
	{
		Field<Type>::replace(d, df);
	}


	template<class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::replace
	(
		const direction d,
		const tmp
		<
		DimensionedField
		<typename DimensionedField<Type, GeoMesh>::cmptType, GeoMesh>
		>& tdf
	)
	{
		replace(d, tdf());
		tdf.clear();
	}


	template<class Type, class GeoMesh>
	tmp<DimensionedField<Type, GeoMesh>>
		DimensionedField<Type, GeoMesh>::T() const
	{
		tmp<DimensionedField<Type, GeoMesh>> result
		(
			DimensionedField<Type, GeoMesh>::New
			(
				name() + ".T()",
				mesh_,
				dimensions_
			)
		);

		tnbLib::T(result(), *this);

		return result;
	}


	template<class Type, class GeoMesh>
	dimensioned<Type> DimensionedField<Type, GeoMesh>::average() const
	{
		dimensioned<Type> Average
		(
			this->name() + ".average()",
			this->dimensions(),
			gAverage(field())
		);

		return Average;
	}


	template<class Type, class GeoMesh>
	dimensioned<Type> DimensionedField<Type, GeoMesh>::weightedAverage
	(
		const DimensionedField<scalar, GeoMesh>& weightField
	) const
	{
		return
			(
				dimensioned<Type>
				(
					this->name() + ".weightedAverage(weights)",
					this->dimensions(),
					gSum(weightField*field()) / gSum(weightField)
					)
				);
	}


	template<class Type, class GeoMesh>
	dimensioned<Type> DimensionedField<Type, GeoMesh>::weightedAverage
	(
		const tmp<DimensionedField<scalar, GeoMesh>>& tweightField
	) const
	{
		dimensioned<Type> wa = weightedAverage(tweightField());
		tweightField.clear();
		return wa;
	}


	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	template<class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator=
		(
			const DimensionedField<Type, GeoMesh>& df
			)
	{
		// Check for assignment to self
		if (this == &df)
		{
			FatalErrorInFunction
				<< "attempted assignment to self"
				<< abort(FatalError);
		}

		if (&(*this).mesh() != &(df).mesh())
		{
			FatalErrorInFunction << "different mesh for fields " << (*this).name() << " and " << (df).name() <<
				" during operatrion " << "=" << abort(FatalError);
		};

		dimensions_ = df.dimensions();
		Field<Type>::operator=(df);
	}


	template<class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator=
		(
			DimensionedField<Type, GeoMesh>&& df
			)
	{
		// Check for assignment to self
		if (this == &df)
		{
			FatalErrorInFunction
				<< "attempted assignment to self"
				<< abort(FatalError);
		}

		if (&(*this).mesh() != &(df).mesh())
		{
			FatalErrorInFunction << "different mesh for fields " << (*this).name() << " and " << (df).name() <<
				" during operatrion " << "=" << abort(FatalError);
		};

		dimensions_ = move(df.dimensions());
		Field<Type>::operator=(move(df));
	}


	template<class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator=
		(
			const tmp<DimensionedField<Type, GeoMesh>>& tdf
			)
	{
		const DimensionedField<Type, GeoMesh>& df = tdf();

		// Check for assignment to self
		if (this == &df)
		{
			FatalErrorInFunction
				<< "attempted assignment to self"
				<< abort(FatalError);
		}

		if (&(*this).mesh() != &(df).mesh())
		{
			FatalErrorInFunction << "different mesh for fields " << (*this).name() << " and " << (df).name() <<
				" during operatrion " << "=" << abort(FatalError);
		};

		dimensions_ = df.dimensions();
		this->transfer(const_cast<DimensionedField<Type, GeoMesh>&>(df));
		tdf.clear();
	}


	template<class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator=
		(
			const dimensioned<Type>& dt
			)
	{
		dimensions_ = dt.dimensions();
		Field<Type>::operator=(dt.value());
	}


	template<class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator=(const zero&)
	{
		Field<Type>::operator=(Zero);
	}


	template <class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator +=(const DimensionedField<Type, GeoMesh>& df)
	{
		if (&(*this).mesh() != &(df).mesh())
		{
			FatalErrorInFunction << "different mesh for fields " << (*this).name() << " and " << (df).name() <<
				" during operatrion " << "+=" << abort(FatalError);
		};
		dimensions_ += df.dimensions();
		Field<Type>::operator +=(df);
	}

	template <class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator +=(const tmp<DimensionedField<Type, GeoMesh>>& tdf)
	{
		operator +=(tdf());
		tdf.clear();
	}

	template <class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator +=(const dimensioned<Type>& dt)
	{
		dimensions_ += dt.dimensions();
		Field<Type>::operator +=(dt.value());
	}

	template <class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator -=(const DimensionedField<Type, GeoMesh>& df)
	{
		if (&(*this).mesh() != &(df).mesh())
		{
			FatalErrorInFunction << "different mesh for fields " << (*this).name() << " and " << (df).name() <<
				" during operatrion " << "-=" << abort(FatalError);
		};
		dimensions_ -= df.dimensions();
		Field<Type>::operator -=(df);
	}

	template <class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator -=(const tmp<DimensionedField<Type, GeoMesh>>& tdf)
	{
		operator -=(tdf());
		tdf.clear();
	}

	template <class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator -=(const dimensioned<Type>& dt)
	{
		dimensions_ -= dt.dimensions();
		Field<Type>::operator -=(dt.value());
	}

	template <class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator *=(const DimensionedField<scalar, GeoMesh>& df)
	{
		if (&(*this).mesh() != &(df).mesh())
		{
			FatalErrorInFunction << "different mesh for fields " << (*this).name() << " and " << (df).name() <<
				" during operatrion " << "*=" << abort(FatalError);
		};
		dimensions_ *= df.dimensions();
		Field<Type>::operator *=(df);
	}

	template <class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator *=(const tmp<DimensionedField<scalar, GeoMesh>>& tdf)
	{
		operator *=(tdf());
		tdf.clear();
	}

	template <class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator *=(const dimensioned<scalar>& dt)
	{
		dimensions_ *= dt.dimensions();
		Field<Type>::operator *=(dt.value());
	}

	template <class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator /=(const DimensionedField<scalar, GeoMesh>& df)
	{
		if (&(*this).mesh() != &(df).mesh())
		{
			FatalErrorInFunction << "different mesh for fields " << (*this).name() << " and " << (df).name() <<
				" during operatrion " << "/=" << abort(FatalError);
		};
		dimensions_ /= df.dimensions();
		Field<Type>::operator /=(df);
	}

	template <class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator /=(const tmp<DimensionedField<scalar, GeoMesh>>& tdf)
	{
		operator /=(tdf());
		tdf.clear();
	}

	template <class Type, class GeoMesh>
	void DimensionedField<Type, GeoMesh>::operator /=(const dimensioned<scalar>& dt)
	{
		dimensions_ /= dt.dimensions();
		Field<Type>::operator /=(dt.value());
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#undef checkField

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //