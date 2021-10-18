# ft_containers

## Roadmap

- [x] iterator_traits
- [x] reverse_iterator
- [x] enable_if
- [x] lexicographical_compare
- [x] equal
- [x] pair
- [x] vector
- [ ] map
- [x] stack

## Testing

Containers can be tested by performing a simple `make` command at the root of the repository.
That command will generate two binaries named `std` and `ft`. In these two binaries are compiled the tests that can be found
under the `./test` directory, the exact same tests being compiled with the original implementation from the STL and with
the home-made ones.

My [castorno](https://github.com/aurelien-brabant/castorno) testing framework is used to produce an elegant output and record execution
times.

Relevant execution time differences between the two binaries can be reported by simply executing the `compare_execution_time.sh` script, which
will highlight these differences.
`N/A` is displayed if for a given test, the execution time difference is **below 1 ms**. `./compare_execution_time.sh | grep -iv 'n/a'` can be performed if these
lines are not wanted.

## More testing

I essentially used [mli's](https://github.com/mli42/containers_test.git) tester that covers a lot more than my own tests (definitely something I should fix).
