#pragma once
#include <point.hxx>
#include <Istream.hxx>
#include <Ostream.hxx>
#include <OStringStream.hxx>
#include <IStringStream.hxx>

template<class Gt, class Vb>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const CGAL::indexedVertex<Gt, Vb>& p
	)
{
	os << p.point() << ' '
		<< p.index() << ' '
		<< static_cast<int>(p.type()) << ' '
		<< p.procIndex() << ' '
		<< p.alignment() << ' '
		<< p.targetCellSize() << ' '
		<< static_cast<int>(p.fixed());

	return os;
}


template<class Gt, class Vb>
tnbLib::Istream& tnbLib::operator>>
(
	Istream& is,
	CGAL::indexedVertex<Gt, Vb>& p
	)
{
	is >> p.point()
		>> p.index();

	int type;
	is >> type;
	p.type() = static_cast<tnbLib::indexedVertexEnum::vertexType>(type);

	is >> p.procIndex()
		>> p.alignment()
		>> p.targetCellSize();

	int fixed;
	is >> fixed;
	p.fixed() = static_cast<bool>(fixed);

	return is;
}


template<class Gt, class Vb>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const InfoProxy<CGAL::indexedVertex<Gt, Vb>>& p
	)
{
	const CGAL::indexedVertex<Gt, Vb>& iv = p.t_;

	const tnbLib::point pt
	(
		CGAL::to_double(iv.point().x()),
		CGAL::to_double(iv.point().y()),
		CGAL::to_double(iv.point().z())
	);

	string fixed
	(
		iv.vertexFixed_
		? string(" fixed, ")
		: string(" free, ")
	);

	string referred
	(
		Pstream::myProcNo() == iv.processor_
		? string(" (local)")
		: string(" (from " + name(iv.processor_) + ")")
	);

	os << iv.index_ << " "
		<< CGAL::indexedVertex<Gt, Vb>::vertexTypeNames_[iv.type_]
		<< " at:" << pt
		<< " size:" << iv.targetCellSize_
		<< " alignment:" << iv.alignment_
		<< fixed
		<< referred.c_str()
		<< endl;

	return os;
}