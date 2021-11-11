#include <indexedVertex.hxx>

#include <point.hxx>
#include <Istream.hxx>
#include <Ostream.hxx>
#include <OStringStream.hxx>
#include <IStringStream.hxx>

// * * * * * * * * * * * * * * * *  IOStream operators * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>
(
	Istream& is,
	CGAL::Point_3<baseK>& p
	)
{
	//    string data(is);
	//
	//    std::istringstream stdIs;
	//
	//    CGAL::set_ascii_mode(stdIs);
	//
	//    stdIs.str(data);
	//
	//    CGAL::Gmpz xNumer, xDenom;
	//    CGAL::Gmpz yNumer, yDenom;
	//    CGAL::Gmpz zNumer, zDenom;
	//
	//    stdIs >> xNumer >> xDenom >> yNumer >> yDenom >> zNumer >> zDenom;
	//
	//    CGAL::Gmpq x(xNumer, xDenom);
	//    CGAL::Gmpq y(yNumer, yDenom);
	//    CGAL::Gmpq z(zNumer, zDenom);
	//
	//    p = CGAL::Point_3<baseK>
	//    (
	//        CGAL::to_double(x),
	//        CGAL::to_double(y),
	//        CGAL::to_double(z)
	//    );

	tnbLib::point pt;

	is >> pt.x() >> pt.y() >> pt.z();

	p = CGAL::Point_3<baseK>
		(
			pt.x(),
			pt.y(),
			pt.z()
			);

	return is;
}


tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const CGAL::Point_3<baseK>& p
	)
{
	//    CGAL::Gmpq x(CGAL::to_double(p.x()));
	//    CGAL::Gmpq y(CGAL::to_double(p.y()));
	//    CGAL::Gmpq z(CGAL::to_double(p.z()));
	//
	//    std::ostringstream stdOs;
	//
	//    CGAL::set_ascii_mode(stdOs);
	//
	//    stdOs<< x.numerator() << ' ' << x.denominator() << ' '
	//         << y.numerator() << ' ' << y.denominator() << ' '
	//         << z.numerator() << ' ' << z.denominator();
	//
	//    os << stdOs.str();

	os << CGAL::to_double(p.x()) << ' '
		<< CGAL::to_double(p.y()) << ' '
		<< CGAL::to_double(p.z());

	return os;
}


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


// ************************************************************************* //