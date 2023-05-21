#include "bool_algeabra_test.h"
#include "bool_algeabra.h"


void bool_algeabra_test::Given_a_lesser_than_b_When_testing_is_equal_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_equal(a_lesser, b, count));
}

void bool_algeabra_test::Given_a_greater_than_b_When_testing_is_equal_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_equal(a_greater, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_equal(a_equal, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_equal_Than_operation_count_is_16()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    is_equal(a_equal, b, count);
    QCOMPARE(count.operation, 8);
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_less_than_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_less_than(a_equal, b, count));
}

void bool_algeabra_test::Given_a_lesser_than_b_When_testing_is_less_than_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_less_than(a_lesser, b, count));
}

void bool_algeabra_test::Given_a_greater_than_b_When_testing_is_less_than_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_less_than(a_greater, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_less_than_Than_operation_count_is_8()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    is_less_than(a_equal, b, count);
    QCOMPARE(count.operation, 8);
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_not_equal_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_not_equal(a_equal, b, count));
}

void bool_algeabra_test::Given_a_lesser_than_b_When_testing_is_not_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_not_equal(a_lesser, b, count));
}

void bool_algeabra_test::Given_a_greater_than_b_When_testing_is_not_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_not_equal(a_greater, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_not_equal_Than_operation_count_is_8()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    is_not_equal(a_equal, b, count);
    QCOMPARE(count.operation, 8);
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_greater_than_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    is_greater_than(a_equal, b, count);
    QVERIFY(!is_greater_than(a_equal, b, count));
}

void bool_algeabra_test::Given_a_greater_than_b_When_testing_is_greater_than_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_greater_than(a_greater, b, count));
}

void bool_algeabra_test::Given_a_lesser_than_b_When_testing_is_greater_than_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_greater_than(a_lesser, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_greater_than_Than_operation_count_is_8()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    is_greater_than(a_equal, b, count);
    QCOMPARE(count.operation, 8);
}

void bool_algeabra_test::Given_a_greater_than_b_When_testing_is_less_or_equal_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_less_or_equal(a_greater, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_less_or_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_less_or_equal(a_equal, b, count));
}

void bool_algeabra_test::Given_a_lesser_than_b_When_testing_is_less_or_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_less_or_equal(a_lesser, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_less_or_equal_Than_operation_count_is_8()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    is_less_or_equal(a_equal, b, count);
    QCOMPARE(count.operation, 8);
}

void bool_algeabra_test::Given_a_lesser_than_b_When_testing_is_greater_or_equal_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_greater_or_equal(a_lesser, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_greater_or_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_greater_or_equal(a_equal, b, count));
}

void bool_algeabra_test::Given_a_grater_than_b_When_testing_is_graeter_or_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_greater_or_equal(a_greater, b, count));
}

void bool_algeabra_test::Given_a_equal_b_When_testing_is_greater_or_equal_Than_operation_count_is_8()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    is_greater_or_equal(a_equal, b, count);
    QCOMPARE(count.operation, 8);
}

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

void bool_algeabra_test::Given_1_and_1_When_testing_NOR_Then_return_0()
{
    Count count;
    count_initialization(count);
    bool result = NOR(true, true, count);
    QCOMPARE(result, false);
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

void bool_algeabra_test::Given_0_1_on_3_bits_and_select_0_When_testing_MUX2_Large_Then_return_0()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(0, 3);
    Large b = create_and_initialize_large(1, 3);
    Large expected = create_and_initialize_large(0, 3);
    Large result = MUX2_Large(false, a, b, count);
    QVERIFY(is_equal(result, expected, count));
}

void bool_algeabra_test::Given_0_1_on_3_bits_and_select_1_When_testing_MUX2_Large_Then_return_1()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(0, 3);
    Large b = create_and_initialize_large(1, 3);
    Large expected = create_and_initialize_large(1, 3);
    Large result = MUX2_Large(true, a, b, count);
    QVERIFY(is_equal(result, expected, count));
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

void bool_algeabra_test::Given_1_1_1_When_testing_ADDER_1_bit_Then_correct_gates()
{
    Count count;
    count_initialization(count);
    bool sum; bool cout;
    ADDER_1_bit(true, true, true, sum, cout, count);
    //QCOMPARE(count.operation, 1);
    //QCOMPARE(count.clock, 0);
    //QCOMPARE(count.regs, 0);
    //QCOMPARE(count.NOT_gates, 0);
    ///QCOMPARE(count.AND_gates, 2);
    //QCOMPARE(count.NAND_gates, 0);
    //QCOMPARE(count.OR_gates, 1);
    //QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 2);
    //QCOMPARE(count.XNOR_gates, 0);
}

void bool_algeabra_test::Given_1_2_on_3_bits_When_testing_ADDER_n_bits_Then_sum_is_3()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(1, 3);
    Large b = create_and_initialize_large(2, 3);
    Large sum(4);
    ADDER_n_bits(a, b, sum, false, count);
}

void bool_algeabra_test::Given_1_2_on_3_bits_When_testing_ADDER_n_bits_Then_correct_gates()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(1, 3);
    Large b = create_and_initialize_large(2, 3);
    Large sum(4);
    ADDER_n_bits(a, b, sum, false, count);
    QCOMPARE(count.operation, 3);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 6);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 3);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 6);
    QCOMPARE(count.XNOR_gates, 0);
}

static bool_algeabra_test BOOL_ALGEABRA_TEST;
