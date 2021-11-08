#include <wallNormalInfo.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamDynamicMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
    tnbLib::Ostream& os,
    const tnbLib::wallNormalInfo& wDist
    )
{
    if (os.format() == IOstream::ASCII)
    {
        os << wDist.normal();
    }
    else
    {
        os.write
        (
            reinterpret_cast<const char*>(&wDist.normal_),
            sizeof(vector)
        );
    }

    // Check state of Ostream
    os.check("Ostream& operator<<(Ostream&, const wallNormalInfo&)");
    return os;
}

FoamDynamicMesh_EXPORT tnbLib::Istream& tnbLib::operator>>(tnbLib::Istream& is, tnbLib::wallNormalInfo& wDist)
{
    if (is.format() == IOstream::ASCII)
    {
        is >> wDist.normal_;
    }
    else
    {
        is.read
        (
            reinterpret_cast<char*>(&wDist.normal_),
            sizeof(vector)
        );
    }

    // Check state of Istream
    is.check("Istream& operator>>(Istream&, wallNormalInfo&)");
    return is;
}

// ************************************************************************* //