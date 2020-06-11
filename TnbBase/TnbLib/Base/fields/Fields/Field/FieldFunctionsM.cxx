#include <FieldM.hxx>
#include <FieldReuseFunctions.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define UNARY_FUNCTION(ReturnType, Type, Func)                                 \
                                                                               \
TEMPLATE                                                                       \
void Func(Field<ReturnType>& res, const UList<Type>& f)                        \
{                                                                              \
    TFOR_ALL_F_OP_FUNC_F(ReturnType, res, =, ::tnbLib::Func, Type, f)            \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> Func(const UList<Type>& f)                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes(new Field<ReturnType>(f.size()));              \
    Func(tRes.ref(), f);                                                       \
    return tRes;                                                               \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> Func(const tmp<Field<Type>>& tf)                        \
{                                                                              \
    tmp<Field<ReturnType>> tRes = reuseTmp<ReturnType, Type>::New(tf);         \
    Func(tRes.ref(), tf());                                                    \
    tf.clear();                                                                \
    return tRes;                                                               \
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define UNARY_OPERATOR(ReturnType, Type, Op, OpFunc)                           \
                                                                               \
TEMPLATE                                                                       \
void OpFunc(Field<ReturnType>& res, const UList<Type>& f)                      \
{                                                                              \
    TFOR_ALL_F_OP_OP_F(ReturnType, res, =, Op, Type, f)                        \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> operator Op(const UList<Type>& f)                       \
{                                                                              \
    tmp<Field<ReturnType>> tRes(new Field<ReturnType>(f.size()));              \
    OpFunc(tRes.ref(), f);                                                     \
    return tRes;                                                               \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> operator Op(const tmp<Field<Type>>& tf)                 \
{                                                                              \
    tmp<Field<ReturnType>> tRes = reuseTmp<ReturnType, Type>::New(tf);         \
    OpFunc(tRes.ref(), tf());                                                  \
    tf.clear();                                                                \
    return tRes;                                                               \
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define BINARY_FUNCTION(ReturnType, Type1, Type2, Func)                        \
                                                                               \
TEMPLATE                                                                       \
void Func                                                                      \
(                                                                              \
    Field<ReturnType>& res,                                                    \
    const UList<Type1>& f1,                                                    \
    const UList<Type2>& f2                                                     \
)                                                                              \
{                                                                              \
    TFOR_ALL_F_OP_FUNC_F_F                                                     \
    (                                                                          \
        ReturnType, res, =, ::tnbLib::Func, Type1, f1, Type2, f2                 \
    )                                                                          \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> Func                                                    \
(                                                                              \
    const UList<Type1>& f1,                                                    \
    const UList<Type2>& f2                                                     \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes(new Field<ReturnType>(f1.size()));             \
    Func(tRes.ref(), f1, f2);                                                  \
    return tRes;                                                               \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> Func                                                    \
(                                                                              \
    const UList<Type1>& f1,                                                    \
    const tmp<Field<Type2>>& tf2                                               \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes = reuseTmp<ReturnType, Type2>::New(tf2);       \
    Func(tRes.ref(), f1, tf2());                                               \
    tf2.clear();                                                               \
    return tRes;                                                               \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> Func                                                    \
(                                                                              \
    const tmp<Field<Type1>>& tf1,                                              \
    const UList<Type2>& f2                                                     \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes = reuseTmp<ReturnType, Type1>::New(tf1);       \
    Func(tRes.ref(), tf1(), f2);                                               \
    tf1.clear();                                                               \
    return tRes;                                                               \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> Func                                                    \
(                                                                              \
    const tmp<Field<Type1>>& tf1,                                              \
    const tmp<Field<Type2>>& tf2                                               \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes =                                              \
        reuseTmpTmp<ReturnType, Type1, Type1, Type2>::New(tf1, tf2);           \
    Func(tRes.ref(), tf1(), tf2());                                            \
    tf1.clear();                                                               \
    tf2.clear();                                                               \
    return tRes;                                                               \
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define BINARY_TYPE_FUNCTION_SF(ReturnType, Type1, Type2, Func)                \
                                                                               \
TEMPLATE                                                                       \
void Func                                                                      \
(                                                                              \
    Field<ReturnType>& res,                                                    \
    const Type1& s1,                                                           \
    const UList<Type2>& f2                                                     \
)                                                                              \
{                                                                              \
    TFOR_ALL_F_OP_FUNC_S_F                                                     \
    (                                                                          \
        ReturnType, res, =, ::tnbLib::Func, Type1, s1, Type2, f2                 \
    )                                                                          \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> Func                                                    \
(                                                                              \
    const Type1& s1,                                                           \
    const UList<Type2>& f2                                                     \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes(new Field<ReturnType>(f2.size()));             \
    Func(tRes.ref(), s1, f2);                                                  \
    return tRes;                                                               \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> Func                                                    \
(                                                                              \
    const Type1& s1,                                                           \
    const tmp<Field<Type2>>& tf2                                               \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes = reuseTmp<ReturnType, Type2>::New(tf2);       \
    Func(tRes.ref(), s1, tf2());                                               \
    tf2.clear();                                                               \
    return tRes;                                                               \
}


#define BINARY_TYPE_FUNCTION_FS(ReturnType, Type1, Type2, Func)                \
                                                                               \
TEMPLATE                                                                       \
void Func                                                                      \
(                                                                              \
    Field<ReturnType>& res,                                                    \
    const UList<Type1>& f1,                                                    \
    const Type2& s2                                                            \
)                                                                              \
{                                                                              \
    TFOR_ALL_F_OP_FUNC_F_S                                                     \
    (                                                                          \
        ReturnType, res, =, ::tnbLib::Func, Type1, f1, Type2, s2                 \
    )                                                                          \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> Func                                                    \
(                                                                              \
    const UList<Type1>& f1,                                                    \
    const Type2& s2                                                            \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes(new Field<ReturnType>(f1.size()));             \
    Func(tRes.ref(), f1, s2);                                                  \
    return tRes;                                                               \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> Func                                                    \
(                                                                              \
    const tmp<Field<Type1>>& tf1,                                              \
    const Type2& s2                                                            \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes = reuseTmp<ReturnType, Type1>::New(tf1);       \
    Func(tRes.ref(), tf1(), s2);                                               \
    tf1.clear();                                                               \
    return tRes;                                                               \
}


#define BINARY_TYPE_FUNCTION(ReturnType, Type1, Type2, Func)                   \
    BINARY_TYPE_FUNCTION_SF(ReturnType, Type1, Type2, Func)                    \
    BINARY_TYPE_FUNCTION_FS(ReturnType, Type1, Type2, Func)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define BINARY_OPERATOR(ReturnType, Type1, Type2, Op, OpFunc)                  \
                                                                               \
TEMPLATE                                                                       \
void OpFunc                                                                    \
(                                                                              \
    Field<ReturnType>& res,                                                    \
    const UList<Type1>& f1,                                                    \
    const UList<Type2>& f2                                                     \
)                                                                              \
{                                                                              \
    TFOR_ALL_F_OP_F_OP_F(ReturnType, res, =, Type1, f1, Op, Type2, f2)         \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> operator Op                                             \
(                                                                              \
    const UList<Type1>& f1,                                                    \
    const UList<Type2>& f2                                                     \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes(new Field<ReturnType>(f1.size()));             \
    OpFunc(tRes.ref(), f1, f2);                                                \
    return tRes;                                                               \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> operator Op                                             \
(                                                                              \
    const UList<Type1>& f1,                                                    \
    const tmp<Field<Type2>>& tf2                                               \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes = reuseTmp<ReturnType, Type2>::New(tf2);       \
    OpFunc(tRes.ref(), f1, tf2());                                             \
    tf2.clear();                                                               \
    return tRes;                                                               \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> operator Op                                             \
(                                                                              \
    const tmp<Field<Type1>>& tf1,                                              \
    const UList<Type2>& f2                                                     \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes = reuseTmp<ReturnType, Type1>::New(tf1);       \
    OpFunc(tRes.ref(), tf1(), f2);                                             \
    tf1.clear();                                                               \
    return tRes;                                                               \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> operator Op                                             \
(                                                                              \
    const tmp<Field<Type1>>& tf1,                                              \
    const tmp<Field<Type2>>& tf2                                               \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes =                                              \
        reuseTmpTmp<ReturnType, Type1, Type1, Type2>::New(tf1, tf2);           \
    OpFunc(tRes.ref(), tf1(), tf2());                                          \
    tf1.clear();                                                               \
    tf2.clear();                                                               \
    return tRes;                                                               \
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define BINARY_TYPE_OPERATOR_SF(ReturnType, Type1, Type2, Op, OpFunc)          \
                                                                               \
TEMPLATE                                                                       \
void OpFunc                                                                    \
(                                                                              \
    Field<ReturnType>& res,                                                    \
    const Type1& s1,                                                           \
    const UList<Type2>& f2                                                     \
)                                                                              \
{                                                                              \
    TFOR_ALL_F_OP_S_OP_F(ReturnType, res, =, Type1, s1, Op, Type2, f2)         \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> operator Op                                             \
(                                                                              \
    const Type1& s1,                                                           \
    const UList<Type2>& f2                                                     \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes(new Field<ReturnType>(f2.size()));             \
    OpFunc(tRes.ref(), s1, f2);                                                \
    return tRes;                                                               \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> operator Op                                             \
(                                                                              \
    const Type1& s1,                                                           \
    const tmp<Field<Type2>>& tf2                                               \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes = reuseTmp<ReturnType, Type2>::New(tf2);       \
    OpFunc(tRes.ref(), s1, tf2());                                             \
    tf2.clear();                                                               \
    return tRes;                                                               \
}


#define BINARY_TYPE_OPERATOR_FS(ReturnType, Type1, Type2, Op, OpFunc)          \
                                                                               \
TEMPLATE                                                                       \
void OpFunc                                                                    \
(                                                                              \
    Field<ReturnType>& res,                                                    \
    const UList<Type1>& f1,                                                    \
    const Type2& s2                                                            \
)                                                                              \
{                                                                              \
    TFOR_ALL_F_OP_F_OP_S(ReturnType, res, =, Type1, f1, Op, Type2, s2)         \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> operator Op                                             \
(                                                                              \
    const UList<Type1>& f1,                                                    \
    const Type2& s2                                                            \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes(new Field<ReturnType>(f1.size()));             \
    OpFunc(tRes.ref(), f1, s2);                                                \
    return tRes;                                                               \
}                                                                              \
                                                                               \
TEMPLATE                                                                       \
tmp<Field<ReturnType>> operator Op                                             \
(                                                                              \
    const tmp<Field<Type1>>& tf1,                                              \
    const Type2& s2                                                            \
)                                                                              \
{                                                                              \
    tmp<Field<ReturnType>> tRes = reuseTmp<ReturnType, Type1>::New(tf1);       \
    OpFunc(tRes.ref(), tf1(), s2);                                             \
    tf1.clear();                                                               \
    return tRes;                                                               \
}


#define BINARY_TYPE_OPERATOR(ReturnType, Type1, Type2, Op, OpFunc)             \
    BINARY_TYPE_OPERATOR_SF(ReturnType, Type1, Type2, Op, OpFunc)              \
    BINARY_TYPE_OPERATOR_FS(ReturnType, Type1, Type2, Op, OpFunc)


// ************************************************************************* //