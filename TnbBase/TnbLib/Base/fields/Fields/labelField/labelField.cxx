#include <labelField.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void mag(Field<label>& res, const UList<label>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(label, res, =, ::tnbLib::mag, label, f)
	}

	tmp<Field<label>> mag(const UList<label>& f)
	{
		tmp<Field<label>> tRes(new Field<label>(f.size()));
		mag(tRes.ref(), f);
		return tRes;
	}

	tmp<Field<label>> mag(const tmp<Field<label>>& tf)
	{
		tmp<Field<label>> tRes = reuseTmp<label, label>::New(tf);
		mag(tRes.ref(), tf());
		tf.clear();
		return tRes;
	}
		
	void add(Field<label>& res, const label& s1, const UList<label>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(label, res, =, label, s1, +, label, f2)
	}

	tmp<Field<label>> operator +(const label& s1, const UList<label>& f2)
	{
		tmp<Field<label>> tRes(new Field<label>(f2.size()));
		add(tRes.ref(), s1, f2);
		return tRes;
	}

	tmp<Field<label>> operator +(const label& s1, const tmp<Field<label>>& tf2)
	{
		tmp<Field<label>> tRes = reuseTmp<label, label>::New(tf2);
		add(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	} 
	
	void add(Field<label>& res, const UList<label>& f1, const label& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(label, res, =, label, f1, +, label, s2)
	}

	tmp<Field<label>> operator +(const UList<label>& f1, const label& s2)
	{
		tmp<Field<label>> tRes(new Field<label>(f1.size()));
		add(tRes.ref(), f1, s2);
		return tRes;
	}

	tmp<Field<label>> operator +(const tmp<Field<label>>& tf1, const label& s2)
	{
		tmp<Field<label>> tRes = reuseTmp<label, label>::New(tf1);
		add(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}
		
	void subtract(Field<label>& res, const label& s1, const UList<label>& f2)
	{
		TFOR_ALL_F_OP_S_OP_F(label, res, =, label, s1, -, label, f2)
	}

	tmp<Field<label>> operator -(const label& s1, const UList<label>& f2)
	{
		tmp<Field<label>> tRes(new Field<label>(f2.size()));
		subtract(tRes.ref(), s1, f2);
		return tRes;
	}

	tmp<Field<label>> operator -(const label& s1, const tmp<Field<label>>& tf2)
	{
		tmp<Field<label>> tRes = reuseTmp<label, label>::New(tf2);
		subtract(tRes.ref(), s1, tf2());
		tf2.clear();
		return tRes;
	} 
	
	void subtract(Field<label>& res, const UList<label>& f1, const label& s2)
	{
		TFOR_ALL_F_OP_F_OP_S(label, res, =, label, f1, -, label, s2)
	}

	tmp<Field<label>> operator -(const UList<label>& f1, const label& s2)
	{
		tmp<Field<label>> tRes(new Field<label>(f1.size()));
		subtract(tRes.ref(), f1, s2);
		return tRes;
	}

	tmp<Field<label>> operator -(const tmp<Field<label>>& tf1, const label& s2)
	{
		tmp<Field<label>> tRes = reuseTmp<label, label>::New(tf1);
		subtract(tRes.ref(), tf1(), s2);
		tf1.clear();
		return tRes;
	}


		template<>
	tmp<labelField> labelField::component(const direction) const
	{
		return *this;
	}

	template<>
	void component
	(
		labelField& lf,
		const labelUList& f,
		const direction
	)
	{
		lf = f;
	}

	template<>
	void labelField::replace(const direction, const labelUList& lf)
	{
		*this = lf;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>

// ************************************************************************* //