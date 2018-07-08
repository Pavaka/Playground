#include <type_traits>

struct Warrior
{
	int Courage;
};

struct Troll
{
	int Smell;
};

struct Viking : public Warrior
{};

#define GENERATE_MEMBER_CHECK(MemberName)								\
template<typename T>													\
class HasMember_##MemberName											\
{																		\
	struct Fallback { int MemberName; };								\
	struct Derived : T, Fallback {};									\
																		\
	template<typename U, U> struct Check;								\
																		\
	template<typename U>												\
	static std::false_type Test(Check<int Fallback::*, &U::MemberName>*);\
																		\
	template<typename U>												\
	static std::true_type Test(...);									\
public:																	\
	static const bool Value = decltype(Test<Derived>(nullptr))::value;	\
};

#define GENERATE_MEMBER_CHECK_PRE_11(MemberName)						\
template<typename T>													\
class HasMemberPre11_##MemberName										\
{																		\
	struct Fallback { int MemberName; };								\
	struct Derived : T, Fallback {};									\
																		\
	template<typename U, U> struct Check;								\
																		\
	typedef char ArrayOfOne[1];											\
	typedef char ArrayOfTwo[2];											\
	template<typename U>												\
	static ArrayOfOne& Test(Check<int Fallback::*, &U::MemberName>*);	\
																		\
	template<typename U>												\
	static ArrayOfTwo& Test(...);										\
public:																	\
	enum { Value = (sizeof(Test<Derived>(0)) == sizeof(ArrayOfTwo)) };	\
};


GENERATE_MEMBER_CHECK(Courage);
GENERATE_MEMBER_CHECK_PRE_11(Courage);

static_assert(HasMember_Courage<Warrior>::Value, "error");
static_assert(HasMember_Courage<Viking>::Value, "error");
static_assert(!HasMember_Courage<Troll>::Value, "error");

static_assert(HasMemberPre11_Courage<Warrior>::Value, "error");
static_assert(HasMemberPre11_Courage<Viking>::Value, "error");
static_assert(!HasMemberPre11_Courage<Troll>::Value, "error");

