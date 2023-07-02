#include "prime_arithmetic_test.h"
#include "prime_arithmetic.h"

void prime_arithmetic_test::Given_5_and_4_on_8_bits_When_testing_addition_Then_return_9()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a(n), b(n), sum(n+1), expected(n+1);
    a.init_with_small_number(5);
    b.init_with_small_number(4);
    expected.init_with_small_number(9);
    addition(a, b, sum, count);
    QVERIFY(is_equal(sum, expected, count));
}

void prime_arithmetic_test::Given_5_and_4_on_8_bits_When_testing_addition_Then_verify_count()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a(n), b(n), sum(n+1);
    a.init_with_small_number(5);
    b.init_with_small_number(4);
    addition(a, b, sum, count);
    QCOMPARE(count.clock, 1);
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

void prime_arithmetic_test::Given_9_and_4_on_8_bits_When_testing_substraction_Then_return_5()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a(n), b(n), difference(n), expected(n);
    a.init_with_small_number(9);
    b.init_with_small_number(4);
    expected.init_with_small_number(5);
    substraction(a, b, difference, count);
    QVERIFY(is_equal(difference, expected, count));
}

void prime_arithmetic_test::Given_9_and_4_on_8_bits_When_testing_substraction_Then_verify_count()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a(n), b(n), difference(n);
    a.init_with_small_number(9);
    b.init_with_small_number(4);
    substraction(a, b, difference, count);
    QCOMPARE(count.clock, 1);
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

void prime_arithmetic_test::Given_5_and_6_on_8_bits_When_testing_multiplication_Then_return_30()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a(n), b(n), product(2*n), expected(2*n);
    a.init_with_small_number(5);
    b.init_with_small_number(6);
    expected.init_with_small_number(30);
    multiplication(a, b, product, count);
    QVERIFY(is_equal(product, expected, count));
}

void prime_arithmetic_test::Given_5_and_6_on_8_bits_When_testing_multiplication_Then_verify_count()
{
    uint64_t n = 8;
    uint64_t m = 6;
    Count count;
    count_initialization(count);
    Large a(n), b(m), product(n+m), expected(n+m);
    a.init_with_small_number(5);
    b.init_with_small_number(6);
    expected.init_with_small_number(30);
    multiplication(a, b, product, count);
    QCOMPARE(count.clock, m);
    QCOMPARE(count.operation, n*m);
    QCOMPARE(count.regs, n*m + m);
    QCOMPARE(count.NOT_gates, 0);
    QCOMPARE(count.AND_gates, 2*n*m);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, n*m);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 2*n*m);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_quotient_is_5()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a(n), b(n), quotient(n), remainder(n), expected(n);
    a.init_with_small_number(17);
    b.init_with_small_number(3);
    expected.init_with_small_number(5);
    division_modulo(a, b, quotient, remainder, count);
    QVERIFY(is_equal(quotient, expected, count));
}

void prime_arithmetic_test::Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_remainder_is_2()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a(n), b(n), quotient(n), remainder(n), expected(n);
    a.init_with_small_number(17);
    b.init_with_small_number(3);
    expected.init_with_small_number(2);
    division_modulo(a, b, quotient, remainder, count);
    QVERIFY(is_equal(remainder, expected, count));
}

void prime_arithmetic_test::Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_verify_count()
{
    uint64_t n = 8;
    uint64_t m = 6;
    Count count;
    count_initialization(count);
    Large a(n), b(m), quotient(n), remainder(m);
    a.init_with_small_number(5);
    b.init_with_small_number(6);
    division_modulo(a, b, quotient, remainder, count);
    QCOMPARE(count.clock, n);
    QCOMPARE(count.operation, 3*n*m + m);
    QCOMPARE(count.regs, n*n + n*m);
    QCOMPARE(count.NOT_gates,  3*n*m + n + m);
    QCOMPARE(count.AND_gates, 5*n*m + 2*m);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 3*m*n + m + n);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 3*m*n);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_17_and_3_on_8_bits_When_testing_modulo_Then_remainder_is_2()
{
    uint64_t n = 8;
    Count count;
    count_initialization(count);
    Large a(n), b(n), quotient(n), remainder(n), expected(n);
    a.init_with_small_number(17);
    b.init_with_small_number(3);
    expected.init_with_small_number(2);
    division_modulo(a, b, quotient, remainder, count);
    QVERIFY(is_equal(remainder, expected, count));
}

void prime_arithmetic_test::Given_17_and_3_on_8_bits_When_testing_modulo_Then_verify_count()
{
    uint64_t n = 8;
    uint64_t m = 6;
    Count count;
    count_initialization(count);
    Large a(n), b(m), remainder(m);
    a.init_with_small_number(5);
    b.init_with_small_number(6);
    modulo(a, b, remainder, count);
    QCOMPARE(count.clock, n);
    QCOMPARE(count.operation, 3*n*m + m);
    QCOMPARE(count.regs, n*n + n*m);
    QCOMPARE(count.NOT_gates, 3*n*m + n + m);
    QCOMPARE(count.AND_gates, 5*n*m + 2*m);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 3*n*m + n + m);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 3*n*m);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_18_19_and_5_on_5_bits_When_testing_addition_modulo_Then_result_is_2()
{
    uint64_t n = 5;
    Count count;
    count_initialization(count);
    Large a(n), b(n), p(n), result(n), expected(n);
    a.init_with_small_number(18);
    b.init_with_small_number(19);
    p.init_with_small_number(5);
    expected.init_with_small_number(2);
    addition_modulo(a, b, p, result, count);
    QVERIFY(is_equal(result, expected, count));
}

void prime_arithmetic_test::Given_18_19_and_5_on_5_bits_When_testing_addition_modulo_Then_verify_count()
{
    uint64_t n = 5;
    Count count;
    count_initialization(count);
    Large a(n), b(n), p(n), result(n), expected(n);
    a.init_with_small_number(18);
    b.init_with_small_number(19);
    p.init_with_small_number(5);
    expected.init_with_small_number(2);
    addition_modulo(a, b, p, result, count);
    QCOMPARE(count.clock, n + 2);
    QCOMPARE(count.operation, 3*n*n + 5*n);
    QCOMPARE(count.regs, 2*n*n + 3*n + 1);
    QCOMPARE(count.NOT_gates, 3*n*n + 5*n + 1);
    QCOMPARE(count.AND_gates, 5*n*n + 9*n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 3*n*n + 6*n + 1);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 3*n*n + 5*n);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_18_19_and_5_on_5_bits_When_testing_substraction_modulo_Then_result_is_4()
{
    uint64_t n = 5;
    Count count;
    count_initialization(count);
    Large a(n), b(n), p(n), result(n), expected(n);
    a.init_with_small_number(18);
    b.init_with_small_number(19);
    p.init_with_small_number(5);
    expected.init_with_small_number(4);
    substraction_modulo(a, b, p, result, count);
    QVERIFY(is_equal(result, expected, count));
}

void prime_arithmetic_test::Given_18_19_and_5_on_5_bits_When_testing_substraction_modulo_Then_verify_count()
{
    uint64_t n = 5;
    Count count;
    count_initialization(count);
    Large a(n), b(n), p(n), result(n), expected(n);
    a.init_with_small_number(18);
    b.init_with_small_number(19);
    p.init_with_small_number(5);
    expected.init_with_small_number(4);
    substraction_modulo(a, b, p, result, count);
    QCOMPARE(count.clock, 2*n + 3);
    QCOMPARE(count.operation, 9*n*n + 8*n);
    QCOMPARE(count.regs, 6*n*n+ 3*n + 1);
    QCOMPARE(count.NOT_gates, 9*n*n + 10*n + 1);
    QCOMPARE(count.AND_gates, 15*n*n + 15*n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 9*n*n + 11*n + 1);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 9*n*n + 7*n);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_15_8_and_7_on_4_bits_When_testing_multiplication_modulo_Then_result_is_1()
{
    uint64_t n = 4;
    Count count;
    count_initialization(count);
    Large a(n), b(n), p(n), result(n), expected(n);
    a.init_with_small_number(15);
    b.init_with_small_number(8);
    p.init_with_small_number(7);
    expected.init_with_small_number(1);
    multiplication_modulo(a, b, p, result, count);
    QVERIFY(is_equal(result, expected, count));
}

void prime_arithmetic_test::Given_15_8_and_7_on_4_bits_When_testing_multiplication_modulo_Then_verify_count()
{
    uint64_t n = 4;
    Count count;
    count_initialization(count);
    Large a(n), b(n), p(n), result(n), expected(n);
    a.init_with_small_number(15);
    b.init_with_small_number(8);
    p.init_with_small_number(7);
    expected.init_with_small_number(1);
    multiplication_modulo(a, b, p, result, count);
    QCOMPARE(count.clock, 3*n);
    QCOMPARE(count.operation, 7*n*n + n);
    QCOMPARE(count.regs, 7*n*n + n);
    QCOMPARE(count.NOT_gates, 6*n*n + 3*n);
    QCOMPARE(count.AND_gates, 12*n*n + 2*n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 7*n*n + 3*n);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 8*n*n);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_15_8_and_7_on_4_bits_When_testing_squaring_modulo_Then_result_is_1()
{
    uint64_t n = 4;
    Count count;
    count_initialization(count);
    Large a(n), p(n), result(n), expected(n);
    a.init_with_small_number(15);
    p.init_with_small_number(7);
    expected.init_with_small_number(1);
    squaring_modulo(a, p, result, count);
    QVERIFY(is_equal(result, expected, count));
}

void prime_arithmetic_test::Given_15_8_and_7_on_4_bits_When_testing_squaring_modulo_Then_verify_count()
{
    uint64_t n = 4;
    Count count;
    count_initialization(count);
    Large a(n), p(n), result(n), expected(n);
    a.init_with_small_number(15);
    p.init_with_small_number(7);
    expected.init_with_small_number(1);
    squaring_modulo(a, p, result, count);
    QCOMPARE(count.clock, 3*n);
    QCOMPARE(count.operation, 7*n*n + n);
    QCOMPARE(count.regs, 7*n*n + n);
    QCOMPARE(count.NOT_gates, 6*n*n + 3*n);
    QCOMPARE(count.AND_gates, 12*n*n + 2*n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 7*n*n + 3*n);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 8*n*n);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_3_5_and_7_on_3_bits_When_testing_exponentiation_modulo_Then_result_is_5()
{
    uint64_t n = 3;
    uint64_t m = 4;
    Count count;
    count_initialization(count);
    Large a(n), x(m), p(n), result(n), expected(n);
    a.init_with_small_number(3);
    x.init_with_small_number(5);
    p.init_with_small_number(7);
    expected.init_with_small_number(5);
    exponentiation_modulo(a, x, p, result, count);
    QVERIFY(is_equal(result, expected, count));
}

void prime_arithmetic_test::Given_3_5_and_7_on_3_bits_When_testing_exponentiation_modulo_Then_verify_count()
{
    uint64_t n = 3;
    uint64_t m = 3;
    Count count;
    count_initialization(count);
    Large a(n), x(m), p(n), result(n), expected(n);
    a.init_with_small_number(3);
    x.init_with_small_number(5);
    p.init_with_small_number(7);
    expected.init_with_small_number(5);
    exponentiation_modulo(a, x, p, result, count);
    QCOMPARE(count.clock, (m)*(3*n));
    QCOMPARE(count.operation, (2*m - 1)*(7*n*n + n));
    QCOMPARE(count.regs, (2*m - 1)*(7*n*n + n) + (m)*(n));
    QCOMPARE(count.NOT_gates, (2*m - 1)*(6*n*n + 3*n));
    QCOMPARE(count.AND_gates, (2*m - 1)*(12*n*n + 2*n));
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, (2*m - 1)*(7*n*n + 3*n));
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, (2*m - 1)*(8*n*n));
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_6600_and_630_on_16_bits_When_testing_greatest_common_divisor_Then_result_is_30()
{
    uint64_t n = 16;
    Count count;
    count_initialization(count);
    Large greatest_number(n), smallest_number(n), result(n), expected(n);
    greatest_number.init_with_small_number(6600);
    smallest_number.init_with_small_number(630);
    expected.init_with_small_number(30);
    greatest_common_divisor(greatest_number, smallest_number, result, count);
    QVERIFY(is_equal(result, expected, count));
}

void prime_arithmetic_test::Given_5_4_On_10_bits_When_testing_inverse_Then_result_is_1()
{
    uint64_t n = 10;
    Count count;
    count_initialization(count);
    Large a(n), modulus(n), phi_n(n), result(n), expected(n);
    a.init_with_small_number(5);
    modulus.init_with_small_number(4);
    phi_n.init_with_small_number(2);
    expected.init_with_small_number(1);
    inverse(a, modulus, phi_n, result, count);
    QVERIFY(is_equal(result, expected, count));
}

void prime_arithmetic_test::Given_5_4_On_10_bits_When_testing_inverse_Then_result_verify_count()
{
    uint64_t n = 10;
    Count count;
    count_initialization(count);
    Large a(n), modulus(n), phi_n(n), result(n), expected(n);
    a.init_with_small_number(3);
    modulus.init_with_small_number(5);
    phi_n.init_with_small_number(2);
    expected.init_with_small_number(1);
    inverse(a, modulus, phi_n, result, count);
    QCOMPARE(count.clock, 3*n*n + 1);
    QCOMPARE(count.operation, 14*n*n*n - 5*n*n);
    QCOMPARE(count.regs, 14*n*n*n - 4*n*n - n);
    QCOMPARE(count.NOT_gates, 12*n*n*n - 2*n);
    QCOMPARE(count.AND_gates, 24*n*n*n - 8*n*n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 14*n*n*n - n*n - 2*n);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 16*n*n*n - 8*n*n + 2*n);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_5_7_on_10_bits_When_testing_inverse_with_prime_Then_result_is_3()
{
    uint64_t n = 10;
    Count count;
    count_initialization(count);
    Large a(n), p(n), result(n), expected(n);
    a.init_with_small_number(5);
    p.init_with_small_number(7);
    expected.init_with_small_number(3);
    inverse_with_prime(a, p, result, count);
    QVERIFY(is_equal(result, expected, count));
}

void prime_arithmetic_test::Given_5_7_on_10_bits_When_testing_inverse_with_prime_Then_verify_count()
{
    uint64_t n = 10;
    Count count;
    count_initialization(count);
    Large a(n), p(n), result(n), expected(n);
    a.init_with_small_number(5);
    p.init_with_small_number(7);
    expected.init_with_small_number(3);
    inverse_with_prime(a, p, result, count);
    QCOMPARE(count.clock, 3*n*n + 1);
    QCOMPARE(count.operation, 14*n*n*n - 5*n*n);
    QCOMPARE(count.regs, 14*n*n*n - 4*n*n - n);
    QCOMPARE(count.NOT_gates, 12*n*n*n - 2*n);
    QCOMPARE(count.AND_gates, 24*n*n*n - 8*n*n);
    QCOMPARE(count.NAND_gates, 0);
    QCOMPARE(count.OR_gates, 14*n*n*n - n*n - 2*n);
    QCOMPARE(count.NOR_gates, 0);
    QCOMPARE(count.XOR_gates, 16*n*n*n - 8*n*n + 2*n);
    QCOMPARE(count.XNOR_gates, 0);
}

void prime_arithmetic_test::Given_non_prime_25140187_on_32_bits_When_testing_is_prime_with_fermat_little_theorem_Then_return_false()
{
    Count count;
    count_initialization(count);
    uint16_t n = 32;
    Large non_prime(n);
    non_prime.init_with_small_number(25140187);
    QVERIFY(!is_prime_with_fermat_little_theorem(non_prime, count));
}

void prime_arithmetic_test::Given_prime_115249_on_32_bits_When_testing_is_prime_with_fermat_little_theorem_Then_return_true()
{
    Count count;
    count_initialization(count);
    uint16_t n = 32;
    Large prime(n);
    prime.init_with_small_number(115249);
    QVERIFY(is_prime_with_fermat_little_theorem(prime, count));
}

void prime_arithmetic_test::Given_prime_115249_on_32_bits_When_testing_is_prime_with_fermat_little_theorem_Then_verify_count()
{
    Count count;
    count_initialization(count);
    uint16_t n = 32;
    Large prime(n);
    prime.init_with_small_number(115249);
    is_prime_with_fermat_little_theorem(prime, count);
//    QCOMPARE(count.clock, 100*(3*n*n) + 1);
//    QCOMPARE(count.operation, 100*(14*n*n*n - 5*n*n) + n);
//    QCOMPARE(count.regs, 100*(14*n*n*n - 4*n*n - n));
//    QCOMPARE(count.NOT_gates, 100*(12*n*n*n - 3*n) + n);
//    QCOMPARE(count.AND_gates, 100*(24*n*n*n - 8*n*n - n+ 1) + 2*n);
//    QCOMPARE(count.NAND_gates, 0);
//    QCOMPARE(count.OR_gates, 100*(14*n*n*n - n*n -3*n) + n);
//    QCOMPARE(count.NOR_gates, 0);
//    QCOMPARE(count.XOR_gates, 100*(16*n*n*n - 8*n*n) + 2*n);
//    QCOMPARE(count.XNOR_gates, 100*(n));
}
void prime_arithmetic_test::Given_p_13_q_29_When_testing_find_phi_n_Then_phi_n_is_336()
{
    Count count;
    count_initialization(count);
    Large p(6);
    Large q(6);
    Large expected(12);
    p.init_with_small_number(13);
    q.init_with_small_number(29);
    expected.init_with_small_number(336);
    Large phi_n = find_phi_n(p, q, count);
    QVERIFY(is_equal(phi_n, expected, count));
}

void prime_arithmetic_test::Given_phi_n_336_When_testing_find_phi_phi_n_Then_phi_phi_n_is_96()
{
    Count count;
    count_initialization(count);
    Large phi_n(12);
    Large expected(12);
    phi_n.init_with_small_number(336);
    expected.init_with_small_number(96);
    Large phi_phi_n = find_phi_phi_n(phi_n, count);
    QVERIFY(is_equal(phi_phi_n, expected, count));
}

//QCOMPARE(count.clock, 0);
//QCOMPARE(count.operation, 0);
//QCOMPARE(count.regs, 0);
//QCOMPARE(count.NOT_gates, 0);
//QCOMPARE(count.AND_gates, 0);
//QCOMPARE(count.NAND_gates, 0);
//QCOMPARE(count.OR_gates, 0);
//QCOMPARE(count.NOR_gates, 0);
//QCOMPARE(count.XOR_gates, 0);
//QCOMPARE(count.XNOR_gates, 0);

static prime_arithmetic_test PRIME_ARITHMETIC_TEST;
