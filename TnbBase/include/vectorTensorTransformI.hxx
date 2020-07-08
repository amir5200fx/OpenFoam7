#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::vectorTensorTransform::vectorTensorTransform()
	:
	t_(Zero),
	R_(sphericalTensor::I),
	hasR_(false)
{}


inline tnbLib::vectorTensorTransform::vectorTensorTransform
(
	const vector& t,
	const tensor& R,
	bool hasR
)
	:
	t_(t),
	R_(R),
	hasR_(hasR)
{}


inline tnbLib::vectorTensorTransform::vectorTensorTransform(const vector& t)
	:
	t_(t),
	R_(sphericalTensor::I),
	hasR_(false)
{}


inline tnbLib::vectorTensorTransform::vectorTensorTransform(const tensor& R)
	:
	t_(Zero),
	R_(R),
	hasR_(true)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::vector& tnbLib::vectorTensorTransform::t() const
{
	return t_;
}


inline const tnbLib::tensor& tnbLib::vectorTensorTransform::R() const
{
	return R_;
}


inline bool tnbLib::vectorTensorTransform::hasR() const
{
	return hasR_;
}


inline tnbLib::vector& tnbLib::vectorTensorTransform::t()
{
	return t_;
}


inline tnbLib::tensor& tnbLib::vectorTensorTransform::R()
{
	// Assume that non-const access to R changes it from I, so set
	// hasR to true

	hasR_ = true;

	return R_;
}


inline tnbLib::vector tnbLib::vectorTensorTransform::transformPosition
(
	const vector& v
) const
{
	if (hasR_)
	{
		return t() + (R() & v);
	}
	else
	{
		return t() + v;
	}
}


inline tnbLib::pointField tnbLib::vectorTensorTransform::transformPosition
(
	const pointField& pts
) const
{
	tmp<pointField> tfld;

	if (hasR_)
	{
		tfld = t() + (R() & pts);
	}
	else
	{
		tfld = t() + pts;
	}
	return tfld();
}


inline tnbLib::vector tnbLib::vectorTensorTransform::invTransformPosition
(
	const vector& v
) const
{
	if (hasR_)
	{
		return (R().T() & (v - t()));
	}
	else
	{
		return v - t();
	}
}


inline tnbLib::pointField tnbLib::vectorTensorTransform::invTransformPosition
(
	const pointField& pts
) const
{
	tmp<pointField> tfld;

	if (hasR_)
	{
		tfld = (R().T() & (pts - t()));
	}
	else
	{
		tfld = pts - t();
	}
	return tfld();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void tnbLib::vectorTensorTransform::operator&=
(
	const vectorTensorTransform& tr
	)
{
	t_ += tr.t_;
	R_ = tr.R_ & R_;

	// If either of the two objects has hasR_ as true, then inherit
	// it, otherwise, these should both be I tensors.
	hasR_ = tr.hasR_ || hasR_;
}


inline void tnbLib::vectorTensorTransform::operator=(const vector& t)
{
	t_ = t;
}


inline void tnbLib::vectorTensorTransform::operator+=(const vector& t)
{
	t_ += t;
}


inline void tnbLib::vectorTensorTransform::operator-=(const vector& t)
{
	t_ -= t;
}


inline void tnbLib::vectorTensorTransform::operator=(const tensor& R)
{
	hasR_ = true;

	R_ = R;
}


inline void tnbLib::vectorTensorTransform::operator&=(const tensor& R)
{
	hasR_ = true;

	R_ = R & R_;
}


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

inline tnbLib::vectorTensorTransform tnbLib::inv(const vectorTensorTransform& tr)
{
	return vectorTensorTransform(-tr.t(), tr.R().T(), tr.hasR());
}


// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

inline bool tnbLib::operator==
(
	const vectorTensorTransform& tr1,
	const vectorTensorTransform& tr2
	)
{
	return (tr1.t() == tr2.t() && tr1.R() == tr2.R());
}


inline bool tnbLib::operator!=
(
	const vectorTensorTransform& tr1,
	const vectorTensorTransform& tr2
	)
{
	return !operator==(tr1, tr2);
}


inline tnbLib::vectorTensorTransform tnbLib::operator+
(
	const vectorTensorTransform& tr,
	const vector& t
	)
{
	return vectorTensorTransform(tr.t() + t, tr.R(), tr.hasR());
}


inline tnbLib::vectorTensorTransform tnbLib::operator+
(
	const vector& t,
	const vectorTensorTransform& tr
	)
{
	return vectorTensorTransform(t + tr.t(), tr.R(), tr.hasR());
}


inline tnbLib::vectorTensorTransform tnbLib::operator-
(
	const vectorTensorTransform& tr,
	const vector& t
	)
{
	return vectorTensorTransform(tr.t() - t, tr.R(), tr.hasR());
}


inline tnbLib::vectorTensorTransform tnbLib::operator&
(
	const vectorTensorTransform& tr1,
	const vectorTensorTransform& tr2
	)
{
	return vectorTensorTransform
	(
		tr1.t() + tr2.t(),
		tr1.R() & tr2.R(),
		(tr1.hasR() || tr2.hasR())
	);
}


// ************************************************************************* //