#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
	template <typename InputIt1, typename InputIt2>
	bool lexicographical_compare(
			InputIt1 first1, InputIt1 last1,
			InputIt2 first2, InputIt2 last2
		)
	{
		InputIt1 it1 = first1;
		InputIt2 it2 = first2;
		
		while (it1 != last1 && it2 != last2) {
			if (*it1 < *it2) {
				return true;
			}
			/* no else statement here: we want to continue looping if *it1 == *it2 */
			if (*it2 < *it1) {
				return false;
			}
			++it1; ++it2;
		}

		/* if first range is a prefix of the second, then the first it is lexigraphically less than the second. */
		return (it1 == last1 && it2 != last2);
	}

	template <typename InputIt1, typename InputIt2, typename Compare>
	bool lexicographical_compare(
			InputIt1 first1, InputIt1 last1,
			InputIt2 first2, InputIt2 last2,
			Compare cmp
		)
	{
		InputIt1 it1 = first1;
		InputIt2 it2 = first2;
		
		while (it1 != last1 && it2 != last2) {
			/* in case *it1 == *it2, the two calls to cmp should return false so that the loop can continue */
			if (cmp(*it1, *it2)) {
				return true;
			}
			/* no else statement here: we want to continue looping if *it1 == *it2 */
			if (cmp(*it2, *it1)) {
				return false;
			}
			++it1; ++it2;
		}

		/* if first range is a prefix of the second, then the first it is lexigraphically less than the second. */
		return (it1 == last1 && it2 != last2);
	}
}

#endif
