#pragma once
#include <ostringstream.hxx>  // added by Amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class KeyType, class DataType>
tnbLib::PrintTable<KeyType, DataType>::PrintTable()
	:
	table_(),
	title_(string::null)
{}


template<class KeyType, class DataType>
tnbLib::PrintTable<KeyType, DataType>::PrintTable(const string& title)
	:
	table_(),
	title_(title)
{}


template<class KeyType, class DataType>
tnbLib::PrintTable<KeyType, DataType>::PrintTable
(
	const PrintTable<KeyType, DataType>& table
)
	:
	table_(table.table_),
	title_(table.title_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class KeyType, class DataType>
tnbLib::PrintTable<KeyType, DataType>::~PrintTable()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class KeyType, class DataType>
void tnbLib::PrintTable<KeyType, DataType>::print
(
	Ostream& os,
	const bool printSum,
	const bool printAverage
) const
{
	HashTable<HashTable<DataType, label>, KeyType> combinedTable;

	List<HashTableData> procData(Pstream::nProcs(), HashTableData());

	procData[Pstream::myProcNo()] = table_;

	Pstream::gatherList(procData);

	if (Pstream::master())
	{
		label largestKeyLength = 6;
		label largestDataLength = 0;

		List<label> largestProcSize(Pstream::nProcs(), 0);

		forAll(procData, proci)
		{
			const HashTableData& procIData = procData[proci];

			for
				(
					typename HashTableData::const_iterator iter = procIData.begin();
					iter != procIData.end();
					++iter
					)
			{
				if (!combinedTable.found(iter.key()))
				{
					combinedTable.insert
					(
						iter.key(),
						HashTable<DataType, label>()
					);
				}

				HashTable<DataType, label>& key = combinedTable[iter.key()];

				key.insert(proci, iter());

				for
					(
						typename HashTable<DataType, label>
						::const_iterator dataIter = key.begin();
						dataIter != key.end();
						++dataIter
						)
				{
					std::ostringstream buf;
					buf << dataIter();

					largestDataLength = max
					(
						largestDataLength,
						label(buf.str().length())
					);
				}

				std::ostringstream buf;
				buf << iter.key();

				largestKeyLength = max
				(
					largestKeyLength,
					label(buf.str().length())
				);
			}
		}

		os.width(largestKeyLength);
		os << nl << indent << tab << "# " << title_.c_str() << endl;

		os.width(largestKeyLength);
		os << indent << "# Proc";

		forAll(procData, proci)
		{
			os << tab;
			os.width(largestDataLength);
			os << proci;
		}

		if (printSum)
		{
			os << tab;
			os.width(largestDataLength);
			os << "Sum";
		}

		if (printAverage)
		{
			os << tab;
			os.width(largestDataLength);
			os << "Average";
		}

		os << endl;

		const List<KeyType>& sortedTable = combinedTable.sortedToc();

		forAll(sortedTable, keyI)
		{
			const HashTable<DataType, label>& procDataList
				= combinedTable[sortedTable[keyI]];

			os.width(largestKeyLength);
			os << indent << sortedTable[keyI];

			forAll(procDataList, elemI)
			{
				os << tab;
				os.width(largestDataLength);
				os << procDataList[elemI];
			}

			if (printSum)
			{
				DataType sum = 0;
				forAll(procDataList, elemI)
				{
					sum += procDataList[elemI];
				}

				os << tab;
				os.width(largestDataLength);
				os << sum;

				if (printAverage)
				{
					os << tab;
					os.width(largestDataLength);
					os << sum / Pstream::nProcs();
				}
			}

			os << endl;
		}
	}
}


// ************************************************************************* //