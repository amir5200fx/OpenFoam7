#include <wordIOList.hxx>

#include <token.hxx>  // added by amir
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineCompoundTypeName(List<word>, wordList);
	addCompoundToRunTimeSelectionTable(List<word>, wordList);

	defineTemplateTypeNameAndDebugWithName(wordIOList, "wordList", 0);
	defineTemplateTypeNameAndDebugWithName(wordListIOList, "wordListList", 0);
}


void tnbLib::printTable
(
	const List<wordList>& wll,
	List<string::size_type>& columnWidth,
	Ostream& os
)
{
	if (!wll.size()) return;

	// Find the maximum word length for each column
	columnWidth.setSize(wll[0].size(), string::size_type(0));
	forAll(columnWidth, j)
	{
		forAll(wll, i)
		{
			columnWidth[j] = max(columnWidth[j], wll[i][j].size());
		}
	}

	// Print the rows adding spacing for the columns
	forAll(wll, i)
	{
		forAll(wll[i], j)
		{
			os << wll[i][j];
			for
				(
					string::size_type k = 0;
					k < columnWidth[j] - wll[i][j].size() + 2;
					k++
					)
			{
				os << ' ';
			}
		}
		os << nl;

		if (i == 0) os << nl;
	}
}


void tnbLib::printTable(const List<wordList>& wll, Ostream& os)
{
	List<string::size_type> columnWidth;
	printTable(wll, columnWidth, os);
}


// ************************************************************************* //