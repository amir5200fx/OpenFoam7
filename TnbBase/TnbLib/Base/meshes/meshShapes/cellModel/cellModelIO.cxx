#include <cellModel.hxx>

#include <dictionaryEntry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::cellModel::cellModel(Istream& is)
{
	dictionaryEntry entry(dictionary::null, is);
	name_ = entry.keyword();
	entry.lookup("index") >> index_;
	entry.lookup("numberOfPoints") >> nPoints_;
	entry.lookup("faces") >> faces_;
	entry.lookup("edges") >> edges_;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const cellModel& c)
{
	os << "name" << tab << c.name_ << tab
		<< "index" << tab << c.index_ << tab
		<< "numberOfPoints" << tab << c.nPoints_ << tab
		<< "faces" << tab << c.faces_ << tab
		<< "edges" << tab << c.edges_ << endl;

	return os;
}


template<>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const InfoProxy<cellModel>& ip)
{
	const cellModel& cm = ip.t_;

	os << "name = " << cm.name() << ", "
		<< "index = " << cm.index() << ", "
		<< "number of points = " << cm.nPoints() << ", "
		<< "number of faces = " << cm.nFaces() << ", "
		<< "number of edges = " << cm.nEdges()
		<< endl;

	return os;
}


// ************************************************************************* //