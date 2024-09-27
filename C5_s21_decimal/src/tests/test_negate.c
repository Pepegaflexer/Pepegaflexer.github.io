#include "test.h"

static s21_decimal arr[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  // -1
    {{0xCF5C048C, 0x004D2BEF, 0x00000000, 0x00070000}},  // 2172188218.2812812
    {{0xFEADBDA2, 0x000001FB, 0x00000000, 0x80060000}},  // -2181821.218210
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // -79228162514264337593543950335
    {{0x00000000, 0x00000000, 0x00000000, 0x00020000}},  // 0.00
    {{0x00000000, 0x00000000, 0x00000000, 0x80020000}},  // 0.00
    {{0x000F4240, 0x00000000, 0x00000000, 0x00020000}},  // 10000.00
    {{0x000F4240, 0x00000000, 0x00000000, 0x80020000}},  // -10000.00
    {{0x00000467, 0x0000007A, 0x00000000, 0x00040000}},  // 52398601.1239
    {{0x00000467, 0x0000007A, 0x00000000, 0x80000000}},  // -523986011239
    {{0x00000467, 0x0000007A, 0x00003215,
      0x00010000}},  // 23650570576955414727997.5
    {{0x00000467, 0x0000007A, 0x00205FF0,
      0x80020000}},  // -391386782621189641642978.31
    {{0x000F4240, 0x00002710, 0x00002710,
      0x80050000}},  // -1844674407800451901.20000
};

static s21_decimal result[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},  // 0
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //-1
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0xCF5C048C, 0x004D2BEF, 0x00000000, 0x80070000}},  //-2172188218.2812812
    {{0xFEADBDA2, 0x000001FB, 0x00000000, 0x00060000}},  // 2181821.218210
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  //-79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0x00000000, 0x00000000, 0x00000000, 0x80020000}},  // 0.00
    {{0x00000000, 0x00000000, 0x00000000, 0x00020000}},  // 0.00
    {{0x000F4240, 0x00000000, 0x00000000, 0x80020000}},  //-10000.00
    {{0x000F4240, 0x00000000, 0x00000000, 0x00020000}},  // 10000.00
    {{0x00000467, 0x0000007A, 0x00000000, 0x80040000}},  //-52398601.1239
    {{0x00000467, 0x0000007A, 0x00000000, 0x00000000}},  // 523986011239
    {{0x00000467, 0x0000007A, 0x00003215,
      0x80010000}},  //-23650570576955414727997.5
    {{0x00000467, 0x0000007A, 0x00205FF0,
      0x00020000}},  // 391386782621189641642978.31
    {{0x000F4240, 0x00002710, 0x00002710,
      0x00050000}},  // 1844674407800451901.20000
};

START_TEST(s21_negate_error_00) {
  s21_decimal inp = {{123, 3434, 123, 12341}};
  s21_decimal *out = NULL;
  int error = s21_negate(inp, out);
  ck_assert_ptr_eq(out, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_negate_00) {
  s21_decimal inp = {{123, 0, 0, 0}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_negate(inp, &out);
  s21_decimal res = {{123, 0, 0, 2147483648}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_negate_01) {
  s21_decimal inp = {{45645, 123544, 4566454, 0}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_negate(inp, &out);
  s21_decimal res = {{45645, 123544, 4566454, 2147483648}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_negate_02) {
  s21_decimal inp = {{0, 0, 0, 0}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_negate(inp, &out);
  s21_decimal res = {{0, 0, 0, 2147483648}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_negate_03) {
  s21_decimal inp = {{0, 0, 0, 2147483648}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_negate(inp, &out);
  s21_decimal res = {{0, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_negate_04) {
  s21_decimal inp = {{456456, 123456, 1235456, 2147483648}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_negate(inp, &out);
  s21_decimal res = {{456456, 123456, 1235456, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_negate_05) {
  s21_decimal inp = {{456456, 123456, 1235456, 0}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_negate(inp, &out);
  s21_decimal res = {{456456, 123456, 1235456, 2147483648}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_negate_06) {
  s21_decimal inp = {{789456, 14456, 0, 0}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_negate(inp, &out);
  s21_decimal res = {{789456, 14456, 0, 2147483648}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_negate_07) {
  s21_decimal inp = {{789456, 14456, 0, 2147483648}};
  s21_decimal out = {{0, 123, 123, 1123}};
  int error = s21_negate(inp, &out);
  s21_decimal res = {{789456, 14456, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_negate_08) {
  for (size_t i = 0; i < sizeof(arr) / sizeof(s21_decimal); ++i) {
    s21_decimal value = arr[i];
    s21_decimal tmp;
    int ret = s21_negate(value, &tmp);
    ck_assert_int_eq(result[i].bits[0], tmp.bits[0]);
    ck_assert_int_eq(result[i].bits[1], tmp.bits[1]);
    ck_assert_int_eq(result[i].bits[2], tmp.bits[2]);
    ck_assert_int_eq(result[i].bits[3], tmp.bits[3]);
    ck_assert_int_eq(ret, 0);
  }
}
END_TEST

Suite *test_negate_suite(void) {
  Suite *s = suite_create("\033[45m-=S21_NEAGTE=-\033[0m");
  TCase *tc = tcase_create("s21_negate");

  tcase_add_test(tc, s21_negate_error_00);
  tcase_add_test(tc, s21_negate_00);
  tcase_add_test(tc, s21_negate_01);
  tcase_add_test(tc, s21_negate_02);
  tcase_add_test(tc, s21_negate_03);
  tcase_add_test(tc, s21_negate_04);
  tcase_add_test(tc, s21_negate_05);
  tcase_add_test(tc, s21_negate_06);
  tcase_add_test(tc, s21_negate_07);
  tcase_add_test(tc, s21_negate_08);
  suite_add_tcase(s, tc);
  return s;
}