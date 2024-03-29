#include "vector_testing.hpp"
#include <string>

using std::string;

TEST(test_vector_data)
{
    vector<string> vs(42);
    string* data = vs.data();

    for (vector<string>::size_type i = 0; i != vs.size(); ++i) {
        p_assert_eq(vs[i], string());
        assert_expr(&vs[i] == &data[i]);
    }

    return 0;
}
