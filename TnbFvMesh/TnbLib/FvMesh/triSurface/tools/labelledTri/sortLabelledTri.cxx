#include <sortLabelledTri.hxx>

#include <labelledTri.hxx>
#include <triSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Private Classes * * * * * * * * * * * * * * //

	inline bool surfAndLabel::less::operator()
		(
			const surfAndLabel& one,
			const surfAndLabel& two
			) const
	{
		const triSurface& surf = *one.surfPtr_;
		return surf[one.index_].region() < surf[two.index_].region();
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from components
	sortLabelledTri::sortLabelledTri(const triSurface& surf)
		:
		List<surfAndLabel>(surf.size(), surfAndLabel(surf, -1))
	{

		// Set the face label
		forAll(surf, facei)
		{
			operator[](facei).index_ = facei;
		}

		// Sort according to region number.
		sort(*this, surfAndLabel::less());
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void sortLabelledTri::indices(labelList& newIndices) const
	{
		newIndices.setSize(size());

		forAll(newIndices, i)
		{
			newIndices[i] = operator[](i).index_;
		}
	}


	labelList sortLabelledTri::indices() const
	{
		labelList newIndices(size());
		indices(newIndices);
		return newIndices;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //