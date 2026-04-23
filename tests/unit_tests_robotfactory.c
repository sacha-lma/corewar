/*
** EPITECH PROJECT, 2026
** Robot_Factory
** File description:
** criterion unit tests for assembler logic
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <unistd.h>
#include "robotfactory.h"
static void write_file_or_fail(const char *path, const char *content)
{
    FILE *fd = fopen(path, "w");

    cr_assert_not_null(fd);
    cr_assert_neq(fputs(content, fd), EOF);
    fclose(fd);
}

Test(robotfactory_opcode, returns_valid_opcode)
{
    cr_assert_eq(get_opcode("live"), 1);
    cr_assert_eq(get_opcode("sti"), 11);
    cr_assert_eq(get_opcode("aff"), 16);
}

Test(robotfactory_opcode, returns_minus_one_for_unknown)
{
    cr_assert_eq(get_opcode("not_an_opcode"), -1);
}

Test(robotfactory_size, live_size_is_five_bytes)
{
    instr_t instr = {0};

    instr.opcode = 1;
    instr.nb_params = 1;
    instr.params[0].type = T_DIR;
    cr_assert_eq(get_instr_size(&instr), 5);
}

Test(robotfactory_size, sti_size_is_seven_bytes)
{
    instr_t instr = {0};

    instr.opcode = 11;
    instr.nb_params = 3;
    instr.params[0].type = T_REG;
    instr.params[1].type = T_DIR;
    instr.params[2].type = T_DIR;
    cr_assert_eq(get_instr_size(&instr), 7);
}

Test(robotfactory_size, lldi_size_is_seven_bytes)
{
    instr_t instr = {0};

    instr.opcode = 14;
    instr.nb_params = 3;
    instr.params[0].type = T_DIR;
    instr.params[1].type = T_DIR;
    instr.params[2].type = T_REG;
    cr_assert_eq(get_instr_size(&instr), 7);
}

Test(robotfactory_parser, parse_fails_on_missing_file)
{
    robotfactory_t rf = {0};

    cr_assert_eq(parse("this_file_should_not_exist_42.s", &rf), FAILURE);
}

Test(robotfactory_parser, parse_valid_program_sets_expected_values)
{
    robotfactory_t rf = {0};
    char path[] = "/tmp/rf_ut_XXXXXX";
    int fd = mkstemp(path);
    const char *src = ".name \"Abel\"\n"
        ".comment \"L'amer noir.\"\n"
        "\n"
        "sti r1, %:hi, %1\n"
        "hi: live %234\n"
        "ld %0, r3\n"
        "zjmp %:hi\n";

    cr_assert_neq(fd, -1);
    close(fd);
    write_file_or_fail(path, src);
    cr_assert_eq(parse(path, &rf), SUCCESS);
    cr_assert_eq(rf.prog_size, 22);
    cr_assert_eq(rf.header.magic, shift_int(COREWAR_EXEC_MAGIC));
    cr_assert_eq(rf.header.prog_size, shift_int(22));
    unlink(path);
}

Test(robotfactory_parser, parse_fails_when_aff_receives_label)
{
    robotfactory_t rf = {0};
    char path[] = "/tmp/rf_ut_aff_XXXXXX";
    int fd = mkstemp(path);
    const char *src = ".name \"Aff\"\n"
        ".comment \"wrong type\"\n"
        "lbl: live %1\n"
        "aff :lbl\n";

    cr_assert_neq(fd, -1);
    close(fd);
    write_file_or_fail(path, src);
    cr_assert_eq(parse(path, &rf), FAILURE);
    unlink(path);
}

Test(robotfactory_parser, parse_fails_when_lldi_last_argument_is_not_register)
{
    robotfactory_t rf = {0};
    char path[] = "/tmp/rf_ut_lldi_XXXXXX";
    int fd = mkstemp(path);
    const char *src = ".name \"Lldi\"\n"
        ".comment \"wrong last arg\"\n"
        "lbl: live %1\n"
        "lldi %1, %2, :lbl\n";

    cr_assert_neq(fd, -1);
    close(fd);
    write_file_or_fail(path, src);
    cr_assert_eq(parse(path, &rf), FAILURE);
    unlink(path);
}


