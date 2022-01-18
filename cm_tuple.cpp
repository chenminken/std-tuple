// ref: https://zhuanlan.zhihu.com/p/143715615
#include <iostream>

using namespace std;
namespace cm
{
    // 定义类  
    template <typename ... __args_type>
    class tuple;
    
    //起始空参数条件  
    template <>
    class tuple <>
    {
    public:
        tuple() {}    
    };
    //迭代展开方式
    template <typename __this_type, typename ... __args_type>
    class tuple <__this_type, __args_type ...>: public tuple<__args_type ...>
    {
        public: 
            tuple(__this_type val, __args_type ... params): tuple<__args_type ...>(params ...)
            {
                value_ = val;
            }
            
            __this_type get_value()
            {
                return value_;
            }
        //定义成员变量
        public:
            __this_type value_;
    };
    template <int N, typename ... __args_type>
	struct element;

	template <int N>
	struct element<N, tuple<>> {
		static_assert(0 > N, "Index outside of tuple!");
	};

    //继承方式，开始展开参数包
	template <int N, typename __this_type, typename ... __args_type>
	struct element<N, tuple<__this_type, __args_type ...>> : public element<N - 1, tuple<__args_type ...>> {};

    //模板特化，终止展开参数包的条件
	template <typename __this_type, typename ... __args_type>
	struct element<0, tuple<__this_type, __args_type ...>>
	{
        //别名指定
		using value_type = __this_type;
		using class_type = tuple<__this_type, __args_type ...>;
	};

	template <int N, typename ... __args_type>
	auto get(tuple<__args_type ...> & tu)
	{
		using __class_type = typename element<N, tuple<__args_type ...>>::class_type;
		return ((__class_type &)tu).get_value();
	}

}
int main()
{
    auto [a,b] = pair(2,3);
    cout << a << b<< endl;
    cm::tuple<int, char, double> tup(2,'D', 5.12);

    cout << cm::get<0>(tup) <<" " << cm::get<1>(tup) << endl;
    return 0;
}
