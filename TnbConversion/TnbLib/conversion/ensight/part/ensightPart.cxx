#define FoamIOPtrList_EXPORT_DEFINE
#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <ensightPart.hxx>

#include <dictionary.hxx>
#include <ListOps.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //
namespace tnbLib
{
	defineTypeNameAndDebug(ensightPart, 0);
	defineTemplateTypeNameAndDebug(IOPtrList<ensightPart>, 0);
	defineRunTimeSelectionTable(ensightPart, istream);
}

const tnbLib::List<tnbLib::word> tnbLib::ensightPart::elemTypes_(0);


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

bool tnbLib::ensightPart::isFieldDefined(const List<scalar>& field) const
{
	forAll(elemLists_, elemI)
	{
		const labelUList& idList = elemLists_[elemI];

		forAll(idList, i)
		{
			const label id = idList[i];

			if (id >= field.size() || std::isnan(field[id]))
			{
				return false;
			}
		}
	}
	return true;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::ensightPart::ensightPart
()
	:
	number_(0),
	name_(""),
	elemLists_(0),
	offset_(0),
	size_(0),
	isCellData_(true),
	matId_(0),
	points_(pointField::null())
{}


tnbLib::ensightPart::ensightPart
(
	label partNumber,
	const string& partDescription
)
	:
	number_(partNumber),
	name_(partDescription),
	elemLists_(0),
	offset_(0),
	size_(0),
	isCellData_(true),
	matId_(0),
	points_(pointField::null())
{}


tnbLib::ensightPart::ensightPart
(
	label partNumber,
	const string& partDescription,
	const pointField& points
)
	:
	number_(partNumber),
	name_(partDescription),
	elemLists_(0),
	offset_(0),
	size_(0),
	isCellData_(true),
	matId_(0),
	points_(points)
{}


tnbLib::ensightPart::ensightPart(const ensightPart& part)
	:
	number_(part.number_),
	name_(part.name_),
	elemLists_(part.elemLists_),
	offset_(part.offset_),
	size_(part.size_),
	isCellData_(part.isCellData_),
	matId_(part.matId_),
	points_(part.points_)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::ensightPart> tnbLib::ensightPart::New(Istream& is)
{
	const word partType(is);

	istreamConstructorTable::iterator cstrIter =
		istreamConstructorTablePtr_->find(partType);

	if (cstrIter == istreamConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction
		(
			is
		) << "unknown ensightPart type "
			<< partType << nl << nl
			<< "Valid ensightPart types are :" << endl
			<< istreamConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<ensightPart>(cstrIter()(is));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::ensightPart::~ensightPart()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::ensightPart::renumber(const labelUList& origId)
{
	// transform to global values first
	if (offset_)
	{
		forAll(elemLists_, elemI)
		{
			labelList& idList = elemLists_[elemI];
			forAll(idList, i)
			{
				idList[i] += offset_;
			}
		}

		offset_ = 0;
	}

	if (origId.size())
	{
		forAll(elemLists_, elemI)
		{
			inplaceRenumber(origId, elemLists_[elemI]);
		}
	}
}


// ************************************************************************* //