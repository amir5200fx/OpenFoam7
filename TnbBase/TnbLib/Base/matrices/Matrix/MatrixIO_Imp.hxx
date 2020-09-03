#pragma once
#include <Istream.hxx>
#include <Ostream.hxx>
#include <token.hxx>
#include <contiguous.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Form, class Type>
tnbLib::Matrix<Form, Type>::Matrix(Istream& is)
	:
	mRows_(0),
	nCols_(0),
	v_(nullptr)
{
	operator>>(is, *this);
}


template<class Form, class Type>
tnbLib::Istream& tnbLib::operator>>(Istream& is, Matrix<Form, Type>& M)
{
	// Anull matrix
	M.clear();

	is.fatalCheck("operator>>(Istream&, Matrix<Form, Type>&)");

	token firstToken(is);

	is.fatalCheck
	(
		"operator>>(Istream&, Matrix<Form, Type>&) : reading first token"
	);

	if (firstToken.isLabel())
	{
		M.mRows_ = firstToken.labelToken();
		M.nCols_ = readLabel(is);

		label mn = M.mRows_*M.nCols_;

		// Read list contents depending on data format
		if (is.format() == IOstream::ASCII || !contiguous<Type>())
		{
			// Read beginning of contents
			char listDelimiter = is.readBeginList("Matrix");

			if (mn)
			{
				M.allocate();
				Type* v = M.v_;

				if (listDelimiter == token::BEGIN_LIST)
				{
					label k = 0;

					// loop over rows
					for (label i = 0; i < M.m(); i++)
					{
						listDelimiter = is.readBeginList("MatrixRow");

						for (label j = 0; j < M.n(); j++)
						{
							is >> v[k++];

							is.fatalCheck
							(
								"operator>>(Istream&, Matrix<Form, Type>&) : "
								"reading entry"
							);
						}

						is.readEndList("MatrixRow");
					}
				}
				else
				{
					Type element;
					is >> element;

					is.fatalCheck
					(
						"operator>>(Istream&, Matrix<Form, Type>&) : "
						"reading the single entry"
					);

					for (label i = 0; i < mn; i++)
					{
						v[i] = element;
					}
				}
			}

			// Read end of contents
			is.readEndList("Matrix");
		}
		else
		{
			if (mn)
			{
				M.allocate();
				Type* v = M.v_;

				is.read(reinterpret_cast<char*>(v), mn * sizeof(Type));

				is.fatalCheck
				(
					"operator>>(Istream&, Matrix<Form, Type>&) : "
					"reading the binary block"
				);
			}
		}
	}
	else
	{
		FatalIOErrorInFunction(is)
			<< "incorrect first token, expected <int>, found "
			<< firstToken.info()
			<< exit(FatalIOError);
	}

	return is;
}


template<class Form, class Type>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const Matrix<Form, Type>& M)
{
	label mn = M.mRows_*M.nCols_;

	os << M.m() << token::SPACE << M.n();

	// Write list contents depending on data format
	if (os.format() == IOstream::ASCII || !contiguous<Type>())
	{
		if (mn)
		{
			bool uniform = false;

			const Type* v = M.v_;

			if (mn > 1 && contiguous<Type>())
			{
				uniform = true;

				for (label i = 0; i < mn; i++)
				{
					if (v[i] != v[0])
					{
						uniform = false;
						break;
					}
				}
			}

			if (uniform)
			{
				// Write size of list and start contents delimiter
				os << token::BEGIN_BLOCK;

				// Write list contents
				os << v[0];

				// Write end of contents delimiter
				os << token::END_BLOCK;
			}
			else if (mn < 10 && contiguous<Type>())
			{
				// Write size of list and start contents delimiter
				os << token::BEGIN_LIST;

				label k = 0;

				// loop over rows
				for (label i = 0; i < M.m(); i++)
				{
					os << token::BEGIN_LIST;

					// Write row
					for (label j = 0; j < M.n(); j++)
					{
						if (j > 0) os << token::SPACE;
						os << v[k++];
					}

					os << token::END_LIST;
				}

				// Write end of contents delimiter
				os << token::END_LIST;
			}
			else
			{
				// Write size of list and start contents delimiter
				os << nl << token::BEGIN_LIST;

				label k = 0;

				// loop over rows
				for (label i = 0; i < M.m(); i++)
				{
					os << nl << token::BEGIN_LIST;

					// Write row
					for (label j = 0; j < M.n(); j++)
					{
						os << nl << v[k++];
					}

					os << nl << token::END_LIST;
				}

				// Write end of contents delimiter
				os << nl << token::END_LIST << nl;
			}
		}
		else
		{
			os << token::BEGIN_LIST << token::END_LIST << nl;
		}
	}
	else
	{
		if (mn)
		{
			os.write(reinterpret_cast<const char*>(M.v_), mn * sizeof(Type));
		}
	}

	// Check state of IOstream
	os.check("Ostream& operator<<(Ostream&, const Matrix&)");

	return os;
}


// ************************************************************************* //