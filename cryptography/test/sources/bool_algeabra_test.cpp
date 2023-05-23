#include "bool_algeabra_test.h"
#include "bool_algeabra.h"

void bool_algeabra_test::Given_0_When_testing_NOT_Then_return_1()
{
    Count count;
    count_initialization(count);
    bool result = NOT(false, count);
    QCOMPARE(result, true);
}

void bool_algeabra_test::Given_1_When_testing_NOT_Then_return_0()
{
    Count count;
    count_initialization(count);
    bool result = NOT(true, count);
    QCOMPARE(result, false);
}

void bool_algeabra_test::Given_1_When_testing_NOT_Then_verify_count()
{
    Count count;
    count_initialization(count);
    NOT(true, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 1);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_0_and_0_When_testing_AND_Then_return_0()
{
    Count count;
    count_initialization(count);
    bool result = AND(false, false, count);
    QCOMPARE(result, false);
}

void bool_algeabra_test::Given_0_and_1_When_testing_AND_Then_return_0()
{
    Count count;
    count_initialization(count);
    bool result = AND(false, true, count);
    QCOMPARE(result, false);
}

void bool_algeabra_test::Given_1_and_0_When_testing_AND_Then_return_0()
{
    Count count;
    count_initialization(count);
    bool result = AND(true, false, count);
    QCOMPARE(result, false);
}

void bool_algeabra_test::Given_1_and_1_When_testing_AND_Then_return_1()
{
    Count count;
    count_initialization(count);
    bool result = AND(true, true, count);
    QCOMPARE(result, true);
}

void bool_algeabra_test::Given_1_and_1_When_testing_AND_Then_verify_count()
{
    Count count;
    count_initialization(count);
    AND(true, true, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 1);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_0_and_0_When_testing_NAND_Then_return_1()
{
    Count count;
    count_initialization(count);
    bool result = NAND(false, false, count);
    QCOMPARE(result, true);
}

void bool_algeabra_test::Given_0_and_1_When_testing_NAND_Then_return_1()
{
    Count count;
    count_initialization(count);
    bool result = NAND(false, true, count);
    QCOMPARE(result, true);
}

void bool_algeabra_test::Given_1_and_0_When_testing_NAND_Then_return_1()
{
    Count count;
    count_initialization(count);
    bool result = NAND(true, false, count);
    QCOMPARE(result, true);
}

void bool_algeabra_test::Given_1_and_1_When_testing_NAND_Then_return_0()
{
    Count count;
    count_initialization(count);
    bool result = NAND(true, true, count);
    QCOMPARE(result, false);
}

void bool_algeabra_test::Given_1_and_1_When_testing_NAND_Then_verify_count()
{
    Count count;
    count_initialization(count);
    NAND(true, true, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 1);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_0_and_0_When_testing_OR_Then_return_0()
{
    Count count;
    count_initialization(count);
    bool result = OR(false, false, count);
    QCOMPARE(result, false);
}

void bool_algeabra_test::Given_0_and_1_When_testing_OR_Then_return_1()
{
    Count count;
    count_initialization(count);
    bool result = OR(false, true, count);
    QCOMPARE(result, true);
}

void bool_algeabra_test::Given_1_and_0_When_testing_OR_Then_return_1()
{
    Count count;
    count_initialization(count);
    bool result = OR(true, false, count);
    QCOMPARE(result, true);
}

void bool_algeabra_test::Given_1_and_1_When_testing_OR_Then_return_1()
{
    Count count;
    count_initialization(count);
    bool result = OR(true, true, count);
    QCOMPARE(result, true);
}

void bool_algeabra_test::Given_1_and_1_When_testing_OR_Then_verify_count()
{
    Count count;
    count_initialization(count);
    OR(true, true, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 1);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_0_and_0_When_testing_NOR_Then_return_1()
{
    Count count;
    count_initialization(count);
    bool result = NOR(false, false, count);
    QCOMPARE(result, true);
}

void bool_algeabra_test::Given_0_and_1_When_testing_NOR_Then_return_0()
{
    Count count;
    count_initialization(count);
    bool result = NOR(false, true, count);
    QCOMPARE(result, false);
}

void bool_algeabra_test::Given_1_and_0_When_testing_NOR_Then_return_0()
{
    Count count;
    count_initialization(count);
    bool result = NOR(true, false, count);
    QCOMPARE(result, false);
}

void bool_algeabra_test::Given_1_and_1_When_testing_NOR_Then_verify_count()
{
    Count count;
    count_initialization(count);
    bool result = NOR(true, true, count);
    QCOMPARE(result, false);
}

void bool_algeabra_test::Given_1_and_1_When_testing_NOR_Then_return_0()
{
    Count count;
    count_initialization(count);
    NOR(true, true, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 1);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_0_and_0_When_testing_XOR_Then_return_0()
{
    Count count;
    count_initialization(count);
    bool result = XOR(false, false, count);
    QCOMPARE(result, false);
}

void bool_algeabra_test::Given_0_and_1_When_testing_XOR_Then_return_1()
{
    Count count;
    count_initialization(count);
    bool result = XOR(false, true, count);
    QCOMPARE(result, true);
}

void bool_algeabra_test::Given_1_and_0_When_testing_XOR_Then_return_1()
{
    Count count;
    count_initialization(count);
    bool result = XOR(true, false, count);
    QCOMPARE(result, true);
}

void bool_algeabra_test::Given_1_and_1_When_testing_XOR_Then_return_0()
{
    Count count;
    count_initialization(count);
    bool result = XOR(true, true, count);
    QCOMPARE(result, false);
}

void bool_algeabra_test::Given_1_and_1_When_testing_XOR_Then_verify_count()
{
    Count count;
    count_initialization(count);
    XOR(true, true, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 1);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_0_and_0_When_testing_XNOR_Then_return_1()
{
    Count count;
    count_initialization(count);
    bool result = XNOR(false, false, count);
    QCOMPARE(result, true);
}

void bool_algeabra_test::Given_0_and_1_When_testing_XNOR_Then_return_0()
{
    Count count;
    count_initialization(count);
    bool result = XNOR(false, true, count);
    QCOMPARE(result, false);
}

void bool_algeabra_test::Given_1_and_0_When_testing_XNOR_Then_return_0()
{
    Count count;
    count_initialization(count);
    bool result = XNOR(true, false, count);
    QCOMPARE(result, false);
}

void bool_algeabra_test::Given_1_and_1_When_testing_XNOR_Then_return_1()
{
    Count count;
    count_initialization(count);
    bool result = XNOR(true, true, count);
    QCOMPARE(result, true);
}

void bool_algeabra_test::Given_1_and_1_When_testing_XNOR_Then_verify_count()
{
    Count count;
    count_initialization(count);
    XNOR(true, true, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 1);
}

void bool_algeabra_test::Given_0_1_and_select_0_When_testing_MUX2_bits_Then_return_0()
{
    Count count;
    count_initialization(count);
    bool result = MUX2_bits(false, false, true, count);
    QCOMPARE(result, false);
}

void bool_algeabra_test::Given_0_1_and_select_1_When_testing_MUX2_bits_Then_return_1()
{
    Count count;
    count_initialization(count);
    bool result = MUX2_bits(true, false, true, count);
    QCOMPARE(result, true);
}

void bool_algeabra_test::Given_0_1_and_select_1_When_testing_MUX2_bits_Then_verify_count()
{
    Count count;
    count_initialization(count);
    MUX2_bits(true, false, true, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 1);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 1);
    QCOMPARE(count.AND_gates, 2);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 1);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_0_1_on_3_bits_and_select_0_When_testing_MUX2_Large_Then_return_0()
{
    uint64_t n = 3;
    Count count;
    count_initialization(count);
    Large a(n), b(n), expected(n), result(n);
    a.init_with_small_number(0);
    b.init_with_small_number(1);
    expected.init_with_small_number(0);
    result = MUX2_Large(false, a, b, count);
    QVERIFY(is_equal(result, expected, count));
}

void bool_algeabra_test::Given_0_1_on_3_bits_and_select_1_When_testing_MUX2_Large_Then_return_1()
{
    uint64_t n = 3;
    Count count;
    count_initialization(count);
    Large a(n), b(n), expected(n), result(n);
    a.init_with_small_number(0);
    b.init_with_small_number(1);
    expected.init_with_small_number(1);
    result = MUX2_Large(true, a, b, count);
    QVERIFY(is_equal(result, expected, count));
}

void bool_algeabra_test::Given_0_1_on_3_bits_and_select_1_When_testing_MUX2_Large_Then_verify_count()
{
    uint64_t n = 3;
    Count count;
    count_initialization(count);
    Large a(n), b(n), expected(n), result(n);
    a.init_with_small_number(0);
    b.init_with_small_number(1);
    expected.init_with_small_number(1);
    result = MUX2_Large(true, a, b, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, n);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, n);
    QCOMPARE(count.AND_gates, 2*n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, n);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_0_0_When_testing_HALF_ADDER_Then_sum_is_0()
{
    Count count;
    count_initialization(count);
    bool sum; bool cout;
    HALF_ADDER(false, false, sum, cout, count);
    QCOMPARE(sum, false);
}

void bool_algeabra_test::Given_0_0_When_testing_HALF_ADDER_Then_cout_is_0()
{
    Count count;
    count_initialization(count);
    bool sum; bool cout;
    HALF_ADDER(false, false, sum, cout, count);
    QCOMPARE(cout, false);
}

void bool_algeabra_test::Given_1_0_When_testing_HALF_ADDER_Then_sum_is_1()
{
    Count count;
    count_initialization(count);
    bool sum; bool cout;
    HALF_ADDER(true, false, sum, cout, count);
    QCOMPARE(sum, true);
}

void bool_algeabra_test::Given_1_0_When_testing_HALF_ADDER_Then_cout_is_0()
{
    Count count;
    count_initialization(count);
    bool sum; bool cout;
    HALF_ADDER(true, false, sum, cout, count);
    QCOMPARE(cout, false);
}

void bool_algeabra_test::Given_0_1_When_testing_HALF_ADDER_Then_sum_is_1()
{
    Count count;
    count_initialization(count);
    bool sum; bool cout;
    HALF_ADDER(false, true, sum, cout, count);
    QCOMPARE(sum, true);
}

void bool_algeabra_test::Given_0_1_When_testing_HALF_ADDER_Then_cout_is_0()
{
    Count count;
    count_initialization(count);
    bool sum; bool cout;
    HALF_ADDER(false, true, sum, cout, count);
    QCOMPARE(cout, false);
}

void bool_algeabra_test::Given_1_1_When_testing_HALF_ADDER_Then_sum_is_0()
{
    Count count;
    count_initialization(count);
    bool sum; bool cout;
    HALF_ADDER(true, true, sum, cout, count);
    QCOMPARE(sum, false);
}

void bool_algeabra_test::Given_1_1_When_testing_HALF_ADDER_Then_cout_is_1()
{
    Count count;
    count_initialization(count);
    bool sum; bool cout;
    HALF_ADDER(true, true, sum, cout, count);
    QCOMPARE(cout, true);
}

void bool_algeabra_test::Given_1_1_When_testing_HALF_ADDER_Then_verify_count()
{
    Count count;
    count_initialization(count);
    bool sum; bool cout;
    HALF_ADDER(true, true, sum, cout, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 1);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 1);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_1_1_1_When_testing_ADDER_1_bit_Then_sum_is_1()
{
    Count count;
    count_initialization(count);
    bool sum; bool cout;
    ADDER_1_bit(true, true, true, sum, cout, count);
    QCOMPARE(sum, true);
}

void bool_algeabra_test::Given_1_1_1_When_testing_ADDER_1_bit_Then_cout_is_1()
{
    Count count;
    count_initialization(count);
    bool sum; bool cout;
    ADDER_1_bit(true, true, true, sum, cout, count);
    QCOMPARE(cout, true);
}

void bool_algeabra_test::Given_1_1_1_When_testing_ADDER_1_bit_Then_verify_count()
{
    Count count;
    count_initialization(count);
    bool sum; bool cout;
    ADDER_1_bit(true, true, true, sum, cout, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 1);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 2);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 1);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 2);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_1_2_on_3_bits_When_testing_ADDER_n_bits_Then_sum_is_3()
{
    uint64_t n = 3;
    Count count;
    count_initialization(count);
    Large a(n), b(n), expected(n+1), sum(n+1);
    a.init_with_small_number(1);
    b.init_with_small_number(2);
    expected.init_with_small_number(3);
    ADDER_n_bits(a, b, sum, count);
    QVERIFY(is_equal(sum, expected, count));
}

void bool_algeabra_test::Given_1_2_on_3_bits_When_testing_ADDER_n_bits_Then_verify_count()
{
    uint64_t n = 3;
    Count count;
    count_initialization(count);
    Large a(n), b(n), sum(n+1);
    a.init_with_small_number(1);
    b.init_with_small_number(2);
    ADDER_n_bits(a, b, sum, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, n);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 2*n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, n);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 2*n);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_2_1_on_3_bits_When_testing_SUB_n_bits_Then_sum_is_1()
{
    Count count;
    count_initialization(count);
    uint64_t n = 3;
    Large a(n), b(n), expected(n), difference(n);
    a.init_with_small_number(2);
    b.init_with_small_number(1);
    expected.init_with_small_number(1);
    SUB_n_bits(a, b, difference, count);
    QVERIFY(is_equal(difference, expected, count));
}

void bool_algeabra_test::Given_2_1_on_3_bits_When_testing_SUB_n_bits_Then_verify_count()
{
    uint64_t n = 3;
    Count count;
    count_initialization(count);
    Large a(n), b(n), difference(n);
    a.init_with_small_number(2);
    b.init_with_small_number(1);
    SUB_n_bits(a, b, difference, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, n);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, n);
    QCOMPARE(count.AND_gates, 2*n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, n);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 2*n);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_a_lesser_than_b_When_testing_is_equal_Then_return_false()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_lesser(n), b(n);
    a_lesser.init_with_small_number(4);
    b.init_with_small_number(5);
    QVERIFY(!is_equal(a_lesser, b, count));
}

void bool_algeabra_test::Given_a_greater_than_b_When_testing_is_equal_Then_return_false()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_greater(n), b(n);
    a_greater.init_with_small_number(6);
    b.init_with_small_number(5);
    QVERIFY(!is_equal(a_greater, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_equal_Then_return_true()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_equal(n), b(n);
    a_equal.init_with_small_number(5);
    b.init_with_small_number(5);
    QVERIFY(is_equal(a_equal, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_equal_Then_verify_count()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_equal(n), b(n);
    a_equal.init_with_small_number(5);
    b.init_with_small_number(5);
    is_equal(a_equal, b, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, n);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, n);
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_less_than_Then_return_false()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_equal(n), b(n);
    a_equal.init_with_small_number(5);
    b.init_with_small_number(5);
    QVERIFY(!is_less_than(a_equal, b, count));
}

void bool_algeabra_test::Given_a_lesser_than_b_When_testing_is_less_than_Then_return_true()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_lesser(n), b(n);
    a_lesser.init_with_small_number(4);
    b.init_with_small_number(5);
    QVERIFY(is_less_than(a_lesser, b, count));
}

void bool_algeabra_test::Given_a_greater_than_b_When_testing_is_less_than_Then_return_false()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_greater(n), b(n);
    a_greater.init_with_small_number(6);
    b.init_with_small_number(5);
    QVERIFY(!is_less_than(a_greater, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_less_than_Then_verify_count()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_equal(n), b(n);
    a_equal.init_with_small_number(5);
    b.init_with_small_number(5);
    is_less_than(a_equal, b, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 2*n);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 2*n);
    QCOMPARE(count.AND_gates, 3*n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 2*n);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, n);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_not_equal_Then_return_false()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_equal(n), b(n);
    a_equal.init_with_small_number(5);
    b.init_with_small_number(5);
    QVERIFY(!is_not_equal(a_equal, b, count));
}

void bool_algeabra_test::Given_a_lesser_than_b_When_testing_is_not_equal_Then_return_true()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_lesser(n), b(n);
    a_lesser.init_with_small_number(4);
    b.init_with_small_number(5);
    QVERIFY(is_not_equal(a_lesser, b, count));
}

void bool_algeabra_test::Given_a_greater_than_b_When_testing_is_not_equal_Then_return_true()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_greater(n), b(n);
    a_greater.init_with_small_number(6);
    b.init_with_small_number(5);
    QVERIFY(is_not_equal(a_greater, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_not_equal_Then_verify_count()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_equal(n), b(n);
    a_equal.init_with_small_number(5);
    b.init_with_small_number(5);
    is_not_equal(a_equal, b, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, n);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 1);
    QCOMPARE(count.AND_gates, n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, n);
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_greater_than_Then_return_false()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_equal(n), b(n);
    a_equal.init_with_small_number(5);
    b.init_with_small_number(5);
    is_greater_than(a_equal, b, count);
    QVERIFY(!is_greater_than(a_equal, b, count));
}

void bool_algeabra_test::Given_a_greater_than_b_When_testing_is_greater_than_Then_return_true()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_greater(n), b(n);
    a_greater.init_with_small_number(6);
    b.init_with_small_number(5);
    QVERIFY(is_greater_than(a_greater, b, count));
}

void bool_algeabra_test::Given_a_lesser_than_b_When_testing_is_greater_than_Then_return_false()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_lesser(n), b(n);
    a_lesser.init_with_small_number(4);
    b.init_with_small_number(5);
    QVERIFY(!is_greater_than(a_lesser, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_greater_than_Then_verify_count()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_equal(n), b(n);
    a_equal.init_with_small_number(5);
    b.init_with_small_number(5);
    is_greater_than(a_equal, b, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 2*n);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 2*n);
    QCOMPARE(count.AND_gates, 3*n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 2*n);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, n);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_a_greater_than_b_When_testing_is_less_or_equal_Then_return_false()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_greater(n), b(n);
    a_greater.init_with_small_number(6);
    b.init_with_small_number(5);
    QVERIFY(!is_less_or_equal(a_greater, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_less_or_equal_Then_return_true()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_equal(n), b(n);
    a_equal.init_with_small_number(5);
    b.init_with_small_number(5);
    QVERIFY(is_less_or_equal(a_equal, b, count));
}

void bool_algeabra_test::Given_a_lesser_than_b_When_testing_is_less_or_equal_Then_return_true()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_lesser(n), b(n);
    a_lesser.init_with_small_number(4);
    b.init_with_small_number(5);
    QVERIFY(is_less_or_equal(a_lesser, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_less_or_equal_Then_verify_count()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_equal(n), b(n);
    a_equal.init_with_small_number(5);
    b.init_with_small_number(5);
    is_less_or_equal(a_equal, b, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 2*n);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 2*n + 1);
    QCOMPARE(count.AND_gates, 3*n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 2*n);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, n);
    QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_a_lesser_than_b_When_testing_is_greater_or_equal_Then_return_false()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_lesser(n), b(n);
    a_lesser.init_with_small_number(4);
    b.init_with_small_number(5);
    QVERIFY(!is_greater_or_equal(a_lesser, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_greater_or_equal_Then_return_true()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_equal(n), b(n);
    a_equal.init_with_small_number(5);
    b.init_with_small_number(5);
    QVERIFY(is_greater_or_equal(a_equal, b, count));
}

void bool_algeabra_test::Given_a_grater_than_b_When_testing_is_graeter_or_equal_Then_return_true()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_greater(n), b(n);
    a_greater.init_with_small_number(6);
    b.init_with_small_number(5);
    QVERIFY(is_greater_or_equal(a_greater, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_greater_or_equal_Then_verify_count()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a_equal(n), b(n);
    a_equal.init_with_small_number(5);
    b.init_with_small_number(5);
    is_greater_or_equal(a_equal, b, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 2*n);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 2*n + 1);
    QCOMPARE(count.AND_gates, 3*n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 2*n);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, n);
    QCOMPARE(count.XNOR_gates, 0);
}

static bool_algeabra_test BOOL_ALGEABRA_TEST;
