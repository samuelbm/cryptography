#include "prime_arithmetic_test.h"
#include "prime_arithmetic.h"

void prime_arithmetic_test::Given_5_and_4_on_8_bits_When_testing_addition_Then_return_9()
{
    uint16_t n = 8;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5, n);
    Large b = create_and_initialize_large(4, n);
    Large sum = create_and_initialize_large(0, n+1);
    Large expected = create_and_initialize_large(9, n+1);
    addition(a, b, sum, count);
    QVERIFY(is_equal(sum, expected, count));
}

void prime_arithmetic_test::Given_5_and_4_on_8_bits_When_testing_addition_Then_verify_count()
{
    uint16_t n = 8;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5, n);
    Large b = create_and_initialize_large(4, n);
    Large sum = create_and_initialize_large(0, n+1);
    addition(a, b, sum, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_9_and_4_on_8_bits_When_testing_substraction_Then_return_5()
{
    uint16_t n = 8;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(9, n);
    Large b = create_and_initialize_large(4, n);
    Large difference = create_and_initialize_large(0, n);
    Large expected = create_and_initialize_large(5, n);
    substraction(a, b, difference, count);
    QVERIFY(is_equal(difference, expected, count));
}

void prime_arithmetic_test::Given_9_and_4_on_8_bits_When_testing_substraction_Then_verify_count()
{
    uint16_t n = 8;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(9, n);
    Large b = create_and_initialize_large(4, n);
    Large difference = create_and_initialize_large(5, n);
    substraction(a, b, difference, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_5_and_6_on_8_bits_When_testing_multiplication_Then_return_30()
{
    uint16_t n = 8;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5, n);
    Large b = create_and_initialize_large(6, n);
    Large product(2*n);
    Large expected = create_and_initialize_large(30, 2*n);
    multiplication(a, b, product, count);
    QVERIFY(is_equal(product, expected, count));
}

void prime_arithmetic_test::Given_5_and_6_on_8_bits_When_testing_multiplication_Then_verify_count()
{
    uint16_t n = 8;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5, n);
    Large b = create_and_initialize_large(6, n);
    Large product(2*n);
    Large expected = create_and_initialize_large(30, 2*n);
    multiplication(a, b, product, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_quotient_is_5()
{
    uint16_t n = 8;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(17, n);
    Large b = create_and_initialize_large(3, n);
    Large quotient(n);
    Large remainder(n);
    Large expected = create_and_initialize_large(5, n);
    division_modulo(a, b, quotient, remainder, count);
    QVERIFY(is_equal(quotient, expected, count));
}

void prime_arithmetic_test::Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_remainder_is_2()
{
    uint16_t n = 8;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(17, n);
    Large b = create_and_initialize_large(3, n);
    Large quotient(n);
    Large remainder(n);
    Large expected = create_and_initialize_large(2, n);
    division_modulo(a, b, quotient, remainder, count);
    QVERIFY(is_equal(remainder, expected, count));
}

void prime_arithmetic_test::Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_verify_count()
{
    uint16_t n = 8;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5, n);
    Large b = create_and_initialize_large(6, n);
    Large remainder(n);
    Large quotient(n);
    division_modulo(a, b, quotient, remainder, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_17_and_3_on_8_bits_When_testing_modulo_Then_remainder_is_2()
{
    uint16_t n = 8;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(17, n);
    Large b = create_and_initialize_large(3, n);
    Large quotient(n);
    Large remainder(n);
    Large expected = create_and_initialize_large(2, n);
    division_modulo(a, b, quotient, remainder, count);
    QVERIFY(is_equal(remainder, expected, count));
}

void prime_arithmetic_test::Given_17_and_3_on_8_bits_When_testing_modulo_Then_verify_count()
{
    uint16_t n = 8;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5, n);
    Large b = create_and_initialize_large(6, n);
    Large remainder(n);
    Large quotient(n);
    division_modulo(a, b, quotient, remainder, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_18_19_and_5_on_5_bits_When_testing_addition_modulo_Then_result_is_2()
{
    uint16_t n = 5;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(18, n);
    Large b = create_and_initialize_large(19, n);
    Large p = create_and_initialize_large(5, n);
    Large result(n);
    Large expected = create_and_initialize_large(2, n);
    addition_modulo(a, b, p, result, count);
    QVERIFY(is_equal(result, expected, count));
}

void prime_arithmetic_test::Given_18_19_and_5_on_5_bits_When_testing_addition_modulo_Then_verify_count()
{
    uint16_t n = 5;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(18, n);
    Large b = create_and_initialize_large(19, n);
    Large p = create_and_initialize_large(5, n);
    Large result(n);
    Large expected = create_and_initialize_large(2, 5);
    addition_modulo(a, b, p, result, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_18_19_and_5_on_5_bits_When_testing_substraction_modulo_Then_result_is_4()
{
    uint16_t n = 5;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(18, n);
    Large b = create_and_initialize_large(19, n);
    Large p = create_and_initialize_large(5, n);
    Large result(5);
    Large expected = create_and_initialize_large(4, n);
    substraction_modulo(a, b, p, result, count);
    QVERIFY(is_equal(result, expected, count));
}

void prime_arithmetic_test::Given_18_19_and_5_on_5_bits_When_testing_substraction_modulo_Then_verify_count()
{
    uint16_t n = 5;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(18, n);
    Large b = create_and_initialize_large(19, n);
    Large p = create_and_initialize_large(5, n);
    Large result(n);
    Large expected = create_and_initialize_large(4, n);
    substraction_modulo(a, b, p, result, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_15_8_and_7_on_4_bits_When_testing_multiplication_modulo_Then_result_is_1()
{
    uint16_t n = 4;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(15, n);
    Large b = create_and_initialize_large(8, n);
    Large p = create_and_initialize_large(7, n);
    Large result(n);
    Large expected = create_and_initialize_large(1, n);
    multiplication_modulo(a, b, p, result, count);
    QVERIFY(is_equal(result, expected, count));
}

void prime_arithmetic_test::Given_15_8_and_7_on_4_bits_When_testing_multiplication_modulo_Then_verify_count()
{
    uint16_t n = 4;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(15, n);
    Large b = create_and_initialize_large(8, n);
    Large p = create_and_initialize_large(7, n);
    Large result(n);
    Large expected = create_and_initialize_large(1, n);
    multiplication_modulo(a, b, p, result, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_15_8_and_7_on_4_bits_When_testing_squaring_modulo_Then_result_is_1()
{
    uint16_t n = 4;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(15, n);
    Large p = create_and_initialize_large(7, n);
    Large result(n);
    Large expected = create_and_initialize_large(1, n);
    squaring_modulo(a, p, result, count);
    QVERIFY(is_equal(result, expected, count));
}

void prime_arithmetic_test::Given_15_8_and_7_on_4_bits_When_testing_squaring_modulo_Then_verify_count()
{
    uint16_t n = 4;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(15, n);
    Large p = create_and_initialize_large(7, n);
    Large result(n);
    Large expected = create_and_initialize_large(1, n);
    squaring_modulo(a, p, result, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_3_5_and_7_on_3_bits_When_testing_exponentiation_modulo_Then_result_is_5()
{
    uint16_t n = 3;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(3, n);
    Large x = create_and_initialize_large(5, n);
    Large p = create_and_initialize_large(7, n);
    Large result(n);
    Large expected = create_and_initialize_large(5, n);
    exponentiation_modulo(a, x, p, result, count);
    QVERIFY(is_equal(result, expected, count));
}

void prime_arithmetic_test::Given_3_5_and_7_on_3_bits_When_testing_exponentiation_modulo_Then_verify_count()
{
    uint16_t n = 3;
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(3, n);
    Large x = create_and_initialize_large(5, n);
    Large p = create_and_initialize_large(7, n);
    Large result(n);
    Large expected = create_and_initialize_large(5, n);
    exponentiation_modulo(a, x, p, result, count);
    QCOMPARE(count.clock, 0);
    QCOMPARE(count.operation, 0);
    QCOMPARE(count.regs, 0);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 0);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 0);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 0);
    QCOMPARE(count.XNOR_gates, 0);
}

static prime_arithmetic_test PRIME_ARITHMETIC_TEST;
