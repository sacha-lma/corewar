/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** unit tests (Criterion)
*/

#include <criterion/criterion.h>
#include "corewar.h"

/* ── helpers ─────────────────────────────────────────────────────────────── */

static int silence_stdio(int saved[2])
{
    int null_fd = open("/dev/null", O_WRONLY);

    if (null_fd < 0)
        return 84;
    saved[0] = dup(STDOUT_FILENO);
    saved[1] = dup(STDERR_FILENO);
    if (saved[0] < 0 || saved[1] < 0) {
        close(null_fd);
        if (saved[0] >= 0) close(saved[0]);
        if (saved[1] >= 0) close(saved[1]);
        return 84;
    }
    dup2(null_fd, STDOUT_FILENO);
    dup2(null_fd, STDERR_FILENO);
    close(null_fd);
    return 0;
}

static void restore_stdio(int saved[2])
{
    dup2(saved[0], STDOUT_FILENO);
    dup2(saved[1], STDERR_FILENO);
    close(saved[0]);
    close(saved[1]);
}

static int *make_int(int v)
{
    int *p = malloc(sizeof(int));
    if (p) *p = v;
    return p;
}

static void push_int(node_t **head, int v)
{
    int *p = make_int(v);
    if (p) push_back(head, p);
}

static void free_int_list(node_t *head)
{
    node_t *next;
    while (head) { next = head->next; free(head->data); free(head); head = next; }
}

static int cmp_int(void *a, void *b)
{
    return *(int *)((node_t *)a)->data < *(int *)((node_t *)b)->data ? 1 : 0;
}

static void make_process(process_t *p, int pc)
{
    p->pc = pc;
    for (int i = 0; i < REG_NUMBER; i++) p->reg[i] = 0;
    p->carry = false;
    p->last_live = 0;
    p->champion_nb = 1;
}

static champion_t *make_champion(int prog_nb)
{
    champion_t *c = malloc(sizeof(champion_t));
    if (!c) return NULL;
    c->prog_nb = prog_nb;
    c->load_adress = -1;
    c->path = NULL;
    c->header = NULL;
    return c;
}

static void free_champ_list(node_t *head)
{
    node_t *next;
    while (head) { next = head->next; free(head->data); free(head); head = next; }
}

/* ── len helpers ─────────────────────────────────────────────────────────── */

Test(len, array_len_null)   { cr_assert_eq(my_array_len(NULL), 0); }
Test(len, array_len_one)    { char *a[] = {"x", NULL}; cr_assert_eq(my_array_len(a), 1); }
Test(len, array_len_two)    { char *a[] = {"x","y",NULL}; cr_assert_eq(my_array_len(a), 2); }

Test(len, name_len_empty)   { cr_assert_eq(get_name_len(""), 0); }
Test(len, name_len_trim)    { cr_assert_eq(get_name_len("corewar   "), 7); }
Test(len, name_len_no_trim) { cr_assert_eq(get_name_len("abc"), 3); }

Test(len, arg_size_reg)       { cr_assert_eq(get_arg_size(T_REG, 0), 1); }
Test(len, arg_size_dir_full)  { cr_assert_eq(get_arg_size(T_DIR, 0), 4); }
Test(len, arg_size_dir_idx)   { cr_assert_eq(get_arg_size(T_DIR, 1), 2); }
Test(len, arg_size_ind_raw)   { cr_assert_eq(get_arg_size(0x03, 0), 2); }
Test(len, arg_size_ind_flag)  { cr_assert_eq(get_arg_size(T_IND, 0), 0); }
Test(len, arg_size_invalid)   { cr_assert_eq(get_arg_size(0x42, 0), 0); }

/* ── map helpers ─────────────────────────────────────────────────────────── */

Test(map, write_read_int_wrap)
{
    unsigned char map[MEM_SIZE] = {0};
    int pc = MEM_SIZE - 2;

    write_int_to_map(map, pc, 0x11223344);
    cr_assert_eq(map[pc], 0x11);
    cr_assert_eq(map[pc + 1], 0x22);
    cr_assert_eq(map[0], 0x33);
    cr_assert_eq(map[1], 0x44);
    cr_assert_eq(read_int_from_map(map, pc), 0x11223344);
}

Test(map, read_arg_register)
{
    unsigned char map[MEM_SIZE] = {0};
    map[10] = 0xAB;
    cr_assert_eq(read_arg(map, 10, 0x01, 0), 0xAB);
}

Test(map, read_short_and_ind_index)
{
    unsigned char map[MEM_SIZE] = {0};
    map[20] = 0x12; map[21] = 0x34;
    cr_assert_eq(read_short_from_map(map, 20), 0x1234);
    cr_assert_eq(read_arg(map, 20, 0x03, 1), 0x1234);
}

Test(map, read_arg_direct_full)
{
    unsigned char map[MEM_SIZE] = {0};
    map[30]=0xDE; map[31]=0xAD; map[32]=0xBE; map[33]=0xEF;
    cr_assert_eq(read_arg(map, 30, 0x02, 0), read_int_from_map(map, 30));
    cr_assert_eq(read_arg(map, 30, 0x02, 1), read_short_from_map(map, 30));
}

Test(map, read_arg_invalid_type)
{
    unsigned char map[MEM_SIZE] = {0};
    cr_assert_eq(read_arg(map, 0, 0x99, 0), 0);
}

Test(map, read_short_wrap)
{
    unsigned char map[MEM_SIZE] = {0};
    map[MEM_SIZE - 1] = 0x56; map[0] = 0x78;
    cr_assert_eq(read_short_from_map(map, MEM_SIZE - 1), 0x5678);
}

/* ── list helpers ────────────────────────────────────────────────────────── */

Test(list, push_back_null_head) { int *p = make_int(1); push_back(NULL, p); free(p); }

Test(list, get_at_bounds)
{
    node_t *h = NULL;
    push_int(&h, 3); push_int(&h, 1); push_int(&h, 4); push_int(&h, 2);
    cr_assert_eq(*(int *)get_at(h, 0), 3);
    cr_assert_eq(*(int *)get_at(h, 1), 1);
    cr_assert_eq(*(int *)get_at(h, 3), 2);
    cr_assert_null(get_at(h, -1));
    cr_assert_null(get_at(h, 4));
    free_int_list(h);
}

Test(list, get_to_middle_four)
{
    node_t *h = NULL;
    push_int(&h, 3); push_int(&h, 1); push_int(&h, 4); push_int(&h, 2);
    cr_assert_eq(*(int *)get_to_middle(h)->data, 1);
    free_int_list(h);
}

Test(list, get_to_middle_two)
{
    node_t *h = NULL;
    push_int(&h, 7); push_int(&h, 9);
    cr_assert_eq(*(int *)get_to_middle(h)->data, 7);
    free_int_list(h);
}

Test(list, pop_front_empty)    { node_t *h = NULL; pop_front(&h); cr_assert_null(h); }
Test(list, pop_at_empty)       { node_t *h = NULL; pop_at(&h, 0); cr_assert_null(h); }
Test(list, pop_at_oob)
{
    node_t *h = NULL;
    push_int(&h, 1); push_int(&h, 2);
    pop_at(&h, 10);
    cr_assert_eq(*(int *)get_at(h, 0), 1);
    free_int_list(h);
}

Test(list, pop_front_and_pop_at)
{
    node_t *h = NULL;
    push_int(&h, 3); push_int(&h, 1); push_int(&h, 4); push_int(&h, 2);
    pop_front(&h);
    cr_assert_eq(*(int *)get_at(h, 0), 1);
    pop_at(&h, 1);
    cr_assert_eq(*(int *)get_at(h, 0), 1);
    cr_assert_eq(*(int *)get_at(h, 1), 2);
    free_int_list(h);
}

Test(list, merge_sort_four)
{
    node_t *h = NULL;
    push_int(&h, 4); push_int(&h, 1); push_int(&h, 3); push_int(&h, 2);
    node_t *s = merge_sort_lists(&h, cmp_int);
    cr_assert_eq(*(int *)get_at(s, 0), 1);
    cr_assert_eq(*(int *)get_at(s, 1), 2);
    cr_assert_eq(*(int *)get_at(s, 2), 3);
    cr_assert_eq(*(int *)get_at(s, 3), 4);
    free_int_list(s);
}

Test(list, merge_sort_single)
{
    node_t *h = NULL;
    push_int(&h, 5);
    node_t *s = merge_sort_lists(&h, cmp_int);
    cr_assert_eq(*(int *)get_at(s, 0), 5);
    free_int_list(s);
}

Test(list, merge_sort_empty)
{
    node_t *h = NULL;
    cr_assert_null(merge_sort_lists(&h, cmp_int));
}

Test(list, merge_sort_merge)
{
    node_t *l = NULL, *r = NULL;
    push_int(&l, 1); push_int(&l, 3);
    push_int(&r, 2); push_int(&r, 4);
    node_t *m = merge_sort_merge_list(l, r, cmp_int);
    cr_assert_eq(*(int *)get_at(m, 0), 1);
    cr_assert_eq(*(int *)get_at(m, 1), 2);
    cr_assert_eq(*(int *)get_at(m, 2), 3);
    cr_assert_eq(*(int *)get_at(m, 3), 4);
    free_int_list(m);
}

/* ── input helpers ───────────────────────────────────────────────────────── */

Test(inputs, get_prog_nb_valid)
{
    stock_main_t s = {0};
    char *argv[] = {"corewar", "7", NULL};
    s.champ_info.pending_prog_nb = -1;
    cr_assert_eq(get_prog_nb(&s, argv, 1), 0);
    cr_assert_eq(s.champ_info.pending_prog_nb, 7);
}

Test(inputs, get_prog_nb_invalid)
{
    stock_main_t s = {0};
    char *argv[] = {"corewar", "abc", NULL};
    int fds[2]; silence_stdio(fds);
    int r = get_prog_nb(&s, argv, 1);
    restore_stdio(fds);
    cr_assert_eq(r, 84);
}

Test(inputs, get_load_adress_valid)
{
    stock_main_t s = {0};
    char *argv[] = {"corewar", "-42", NULL};
    s.champ_info.pending_load_adress = -1;
    cr_assert_eq(get_load_adress(&s, argv, 1), 0);
    cr_assert_eq(s.champ_info.pending_load_adress, -42);
}

Test(inputs, get_load_adress_invalid)
{
    stock_main_t s = {0};
    char *argv[] = {"corewar", "12a", NULL};
    int fds[2]; silence_stdio(fds);
    int r = get_load_adress(&s, argv, 1);
    restore_stdio(fds);
    cr_assert_eq(r, 84);
}

Test(inputs, get_cycles_valid)
{
    stock_main_t s = {0};
    char *argv[] = {"corewar", "99", NULL};
    cr_assert_eq(get_cycles(&s, argv, 1), 0);
    cr_assert_eq(s.nb_cycle, 99);
}

Test(inputs, get_cycles_invalid)
{
    stock_main_t s = {0};
    char *argv[] = {"corewar", "0", NULL};
    int fds[2]; silence_stdio(fds);
    int r = get_cycles(&s, argv, 1);
    restore_stdio(fds);
    cr_assert_eq(r, 84);
}

Test(inputs, print_help_returns_one)
{
    stock_main_t s = {0};
    char *argv[] = {"corewar", NULL};
    int fds[2]; silence_stdio(fds);
    int r = print_help(&s, argv, 0);
    restore_stdio(fds);
    cr_assert_eq(r, 1);
}

/* ── manage_args ─────────────────────────────────────────────────────────── */

Test(manage_args, help_short)
{
    stock_main_t s = {0};
    char *argv[] = {"corewar", "-h", NULL};
    s.champ_info.pending_prog_nb = -1; s.champ_info.pending_load_adress = -1;
    int fds[2]; silence_stdio(fds);
    int r = manage_args(2, argv, &s);
    restore_stdio(fds);
    cr_assert_eq(r, 1);
}

Test(manage_args, help_long)
{
    stock_main_t s = {0};
    char *argv[] = {"corewar", "-help", NULL};
    s.champ_info.pending_prog_nb = -1; s.champ_info.pending_load_adress = -1;
    int fds[2]; silence_stdio(fds);
    int r = manage_args(2, argv, &s);
    restore_stdio(fds);
    cr_assert_eq(r, 1);
}

Test(manage_args, missing_dump_arg)
{
    stock_main_t s = {0};
    char *argv[] = {"corewar", "-dump", NULL};
    s.champ_info.pending_prog_nb = -1; s.champ_info.pending_load_adress = -1;
    int fds[2]; silence_stdio(fds);
    int r = manage_args(2, argv, &s);
    restore_stdio(fds);
    cr_assert_eq(r, 84);
}

Test(manage_args, invalid_champion)
{
    stock_main_t s = {0};
    char *argv[] = {"corewar", "Makefile", NULL};
    s.champ_info.pending_prog_nb = -1; s.champ_info.pending_load_adress = -1;
    int fds[2]; silence_stdio(fds);
    int r = manage_args(2, argv, &s);
    restore_stdio(fds);
    cr_assert_eq(r, 84);
}

Test(manage_args, valid_full)
{
    stock_main_t s = {0};
    char *argv[] = {
        "corewar",
        "-dump", "1337",
        "-n", "6",
        "-a", "2048",
        "tests/tests_files/abel.cor",
        "tests/tests_files/bill.cor",
        NULL
    };
    s.champ_info.pending_prog_nb = -1; s.champ_info.pending_load_adress = -1;
    cr_assert_eq(manage_args(9, argv, &s), 0);
    cr_assert_eq(s.nb_cycle, 1337);
    cr_assert_eq(s.champ_info.champion_count, 2);
    cr_assert_not_null(s.champ_info.champions);
    cr_assert_not_null(s.champ_info.champions->next);
    champion_t *c1 = s.champ_info.champions->data;
    champion_t *c2 = s.champ_info.champions->next->data;
    cr_assert_eq(c1->prog_nb, 6);
    cr_assert_eq(c1->load_adress, 2048);
    cr_assert_eq(strcmp(c1->path, "tests/tests_files/abel.cor"), 0);
    cr_assert_eq(c2->prog_nb, -1);
    cr_assert_eq(c2->load_adress, -1);
    cr_assert_eq(strcmp(c2->path, "tests/tests_files/bill.cor"), 0);
    free_champ_list(s.champ_info.champions);
}

/* ── init / closup ───────────────────────────────────────────────────────── */

Test(init_suite, init_fields)
{
    stock_main_t s;
    init(&s);
    cr_assert_eq(s.nb_cycle, -1);
    cr_assert_null(s.champ_info.champions);
    cr_assert_eq(s.champ_info.pending_prog_nb, -1);
    cr_assert_eq(s.champ_info.pending_load_adress, -1);
    cr_assert_eq(s.champ_info.champion_count, 0);
    cr_assert_eq(s.cycle_to_die, (unsigned)CYCLE_TO_DIE);
    cr_assert_null(s.processes);
    cr_assert_eq(s.nb_live, 0);
    cr_assert_eq(s.next_check_cycle, (unsigned)CYCLE_TO_DIE);
    cr_assert_eq(s.last_live_champion, -1);
    for (int i = 0; i < MEM_SIZE; i++)
        cr_assert_eq(s.map[i], 0);
}

Test(init_suite, closup_frees_all)
{
    stock_main_t *s = malloc(sizeof(stock_main_t));
    cr_assert_not_null(s);
    init(s);

    champion_t *c = malloc(sizeof(champion_t));
    header_t *h = malloc(sizeof(header_t));
    c->header = h; c->prog_nb = 1; c->path = NULL; c->load_adress = -1;
    push_back(&s->champ_info.champions, c);

    process_t *p = malloc(sizeof(process_t));
    make_process(p, 0);
    push_back(&s->processes, p);

    closup(s); /* must not crash / leak */
}

/* ── update_prog_nbr / prog_sorter ───────────────────────────────────────── */

Test(init_suite, update_prog_nbr_auto)
{
    stock_main_t s = {0};
    push_back(&s.champ_info.champions, make_champion(-1));
    push_back(&s.champ_info.champions, make_champion(-1));
    update_prog_nbr(&s);
    cr_assert_eq(((champion_t *)get_at(s.champ_info.champions, 0))->prog_nb, 1);
    cr_assert_eq(((champion_t *)get_at(s.champ_info.champions, 1))->prog_nb, 2);
    free_champ_list(s.champ_info.champions);
}

Test(init_suite, update_prog_nbr_skip_taken)
{
    stock_main_t s = {0};
    push_back(&s.champ_info.champions, make_champion(2));
    push_back(&s.champ_info.champions, make_champion(-1));
    update_prog_nbr(&s);
    cr_assert_eq(((champion_t *)get_at(s.champ_info.champions, 0))->prog_nb, 2);
    cr_assert_eq(((champion_t *)get_at(s.champ_info.champions, 1))->prog_nb, 1);
    free_champ_list(s.champ_info.champions);
}

Test(init_suite, prog_sorter_less)
{
    node_t na = {0}, nb = {0};
    champion_t ca = {0}, cb = {0};
    ca.prog_nb = 1; cb.prog_nb = 2;
    na.data = &ca; nb.data = &cb;
    cr_assert_eq(prog_sorter(&na, &nb), 1);
}

Test(init_suite, prog_sorter_greater)
{
    node_t na = {0}, nb = {0};
    champion_t ca = {0}, cb = {0};
    ca.prog_nb = 3; cb.prog_nb = 2;
    na.data = &ca; nb.data = &cb;
    cr_assert_eq(prog_sorter(&na, &nb), 0);
}

/* ── set_process ─────────────────────────────────────────────────────────── */

Test(init_suite, set_process_ok)
{
    stock_main_t s = {0};
    champion_t c = {0}; c.prog_nb = 3;
    cr_assert_eq(set_process(&s, 100, &c), 0);
    cr_assert_not_null(s.processes);
    process_t *p = s.processes->data;
    cr_assert_eq(p->pc, 100);
    cr_assert_eq(p->reg[0], -3);
    cr_assert_eq(p->carry, false);
    cr_assert_eq(p->last_live, 0);
    cr_assert_eq(p->champion_nb, 3);
    free(s.processes->data);
    free(s.processes);
}

/* ── operations ──────────────────────────────────────────────────────────── */

Test(ops, op_add_basic)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    p.reg[0] = 10; p.reg[1] = 20;
    s.map[2] = 1; s.map[3] = 2; s.map[4] = 3;
    op_add(&s, &p);
    cr_assert_eq(p.reg[2], 30);
    cr_assert_eq(p.carry, false);
    cr_assert_eq(p.pc, 5);
}

Test(ops, op_add_carry)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[2] = 1; s.map[3] = 2; s.map[4] = 3;
    op_add(&s, &p);
    cr_assert_eq(p.reg[2], 0);
    cr_assert_eq(p.carry, true);
}

Test(ops, op_add_invalid_regs)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[2] = 0; s.map[3] = 1; s.map[4] = 1;
    op_add(&s, &p);
    cr_assert_eq(p.pc, 5);
}

Test(ops, op_sub_basic)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    p.reg[0] = 30; p.reg[1] = 10;
    s.map[2] = 1; s.map[3] = 2; s.map[4] = 3;
    op_sub(&s, &p);
    cr_assert_eq(p.reg[2], 20);
    cr_assert_eq(p.carry, false);
}

Test(ops, op_sub_carry)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    p.reg[0] = 5; p.reg[1] = 5;
    s.map[2] = 1; s.map[3] = 2; s.map[4] = 3;
    op_sub(&s, &p);
    cr_assert_eq(p.carry, true);
}

Test(ops, op_sub_invalid_regs)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[2] = 17; s.map[3] = 1; s.map[4] = 1;
    op_sub(&s, &p);
    cr_assert_eq(p.pc, 5);
}

Test(ops, op_zjmp_carry_set)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    p.carry = 1;
    s.map[1] = 0x00; s.map[2] = 0x0A; /* short = 10 */
    op_zjmp(&s, &p);
    cr_assert_eq(p.pc, (0 + 10 % IDX_MOD) % MEM_SIZE);
}

Test(ops, op_zjmp_carry_clear)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    p.carry = 0;
    s.map[1] = 0x00; s.map[2] = 0x0A;
    op_zjmp(&s, &p);
    cr_assert_eq(p.pc, OP_ZJMP_SIZE % MEM_SIZE);
}

Test(ops, op_print_valid)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    p.reg[0] = 65; s.map[1] = 1;
    int fds[2]; silence_stdio(fds);
    op_print(&s, &p);
    restore_stdio(fds);
    cr_assert_eq(p.pc, 2);
}

Test(ops, op_print_invalid_reg)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0; /* reg 0: invalid */
    int fds[2]; silence_stdio(fds);
    op_print(&s, &p);
    restore_stdio(fds);
    cr_assert_eq(p.pc, 2);
}

Test(ops, op_fork_creates_process)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0x00; s.map[2] = 0x0A; /* offset 10 */
    op_fork(&s, &p);
    cr_assert_not_null(s.processes);
    process_t *np = s.processes->data;
    cr_assert_eq(np->pc, (0 + 10 % IDX_MOD) % MEM_SIZE);
    cr_assert_eq(p.pc, OP_FORK_SIZE % MEM_SIZE);
    free(s.processes->data); free(s.processes);
}

Test(ops, op_lfork_creates_process)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0x00; s.map[2] = 0x14; /* offset 20 */
    op_lfork(&s, &p);
    cr_assert_not_null(s.processes);
    process_t *np = s.processes->data;
    cr_assert_eq(np->pc, (0 + 20) % MEM_SIZE);
    cr_assert_eq(p.pc, OP_LFORK_SIZE % MEM_SIZE);
    free(s.processes->data); free(s.processes);
}

Test(ops, op_and_reg_reg)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    p.reg[0] = 0xFF; p.reg[1] = 0x0F;
    /* coding 0x50: type1=REG(01), type2=REG(01) */
    s.map[1] = 0x50; s.map[2] = 1; s.map[3] = 2; s.map[4] = 3;
    op_and(&s, &p);
    cr_assert_eq(p.reg[2], 0x0F);
    cr_assert_eq(p.carry, 0);
}

Test(ops, op_and_carry_zero)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0x50; s.map[2] = 1; s.map[3] = 2; s.map[4] = 3;
    op_and(&s, &p);
    cr_assert_eq(p.carry, 1);
}

Test(ops, op_and_dir_dir)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    /* coding 0xA0: type1=DIR(10), type2=DIR(10) */
    s.map[1] = 0xA0;
    /* arg1 at pc+2 (4 bytes): 5 */
    s.map[5] = 5;
    /* arg2 at pc+6 (4 bytes): 3 */
    s.map[9] = 3;
    /* dest at pc+10 */
    s.map[10] = 1;
    op_and(&s, &p);
    cr_assert_eq(p.reg[0], 1); /* 5 & 3 = 1 */
}

Test(ops, op_and_ind_type)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    /* coding 0xD0: type1=IND(11), type2=REG(01) */
    s.map[1] = 0xD0;
    s.map[2] = 0x00; s.map[3] = 0x14; /* IND offset = 20 */
    write_int_to_map(s.map, 20, 15);  /* value at addr 20 */
    s.map[4] = 1; p.reg[0] = 5;       /* r1 = 5 */
    s.map[5] = 2;                      /* dest r2 */
    op_and(&s, &p);
    cr_assert_eq(p.reg[1], 5); /* 15 & 5 = 5 */
}

Test(ops, op_or_reg_reg)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    p.reg[0] = 0xF0; p.reg[1] = 0x0F;
    s.map[1] = 0x50; s.map[2] = 1; s.map[3] = 2; s.map[4] = 3;
    op_or(&s, &p);
    cr_assert_eq(p.reg[2], 0xFF);
    cr_assert_eq(p.carry, 0);
}

Test(ops, op_or_carry_zero)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0x50; s.map[2] = 1; s.map[3] = 2; s.map[4] = 3;
    op_or(&s, &p);
    cr_assert_eq(p.carry, 1);
}

Test(ops, op_or_ind_type)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0xD0;
    s.map[2] = 0x00; s.map[3] = 0x14;
    write_int_to_map(s.map, 20, 15);
    s.map[4] = 1; p.reg[0] = 3;
    s.map[5] = 2;
    op_or(&s, &p);
    cr_assert_eq(p.reg[1], 15); /* 15 | 3 = 15 */
}

Test(ops, op_xor_reg_reg)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    p.reg[0] = 0xFF; p.reg[1] = 0xFF;
    s.map[1] = 0x50; s.map[2] = 1; s.map[3] = 2; s.map[4] = 3;
    op_xor(&s, &p);
    cr_assert_eq(p.reg[2], 0);
    cr_assert_eq(p.carry, 1);
}

Test(ops, op_xor_ind_type)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0xD0;
    s.map[2] = 0x00; s.map[3] = 0x14;
    write_int_to_map(s.map, 20, 15);
    s.map[4] = 1; p.reg[0] = 15;
    s.map[5] = 2;
    op_xor(&s, &p);
    cr_assert_eq(p.reg[1], 0); /* 15 ^ 15 = 0 */
    cr_assert_eq(p.carry, 1);
}

Test(ops, op_ld_direct)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    /* coding 0x80: type1=DIR */
    s.map[1] = 0x80;
    s.map[5] = 42; /* big-endian int at pc+2: map[2..5] */
    s.map[6] = 1;  /* dest r1 */
    op_ld(&s, &p);
    cr_assert_eq(p.reg[0], 42);
    cr_assert_eq(p.carry, 0);
    cr_assert_eq(p.pc, 7);
}

Test(ops, op_ld_carry_zero)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0x80; s.map[6] = 1;
    op_ld(&s, &p);
    cr_assert_eq(p.carry, 1);
}

Test(ops, op_ld_indirect)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    /* coding 0xC0: type1=IND */
    s.map[1] = 0xC0;
    s.map[2] = 0x00; s.map[3] = 0x14; /* IND offset = 20 */
    write_int_to_map(s.map, 20, 99);
    s.map[4] = 2; /* dest r2 */
    op_ld(&s, &p);
    cr_assert_eq(p.reg[1], 99);
}

Test(ops, op_ld_invalid_dest)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0x80;
    s.map[5] = 7;
    s.map[6] = 17; /* invalid reg (>16) */
    op_ld(&s, &p);
    cr_assert_eq(p.reg[0], 0); /* unchanged */
}

Test(ops, op_lld_direct)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0x80; s.map[5] = 55; s.map[6] = 1;
    op_lld(&s, &p);
    cr_assert_eq(p.reg[0], 55);
}

Test(ops, op_lld_indirect)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0xC0;
    s.map[2] = 0x00; s.map[3] = 0x0A; /* IND offset = 10 */
    write_int_to_map(s.map, 10, 77);
    s.map[4] = 1;
    op_lld(&s, &p);
    cr_assert_eq(p.reg[0], 77);
}

Test(ops, op_st_to_reg)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    p.reg[0] = 123;
    /* coding 0x10: type2=REG (bits 5-4 = 01) */
    s.map[1] = 0x10; s.map[2] = 1; s.map[3] = 2;
    op_st(&s, &p);
    cr_assert_eq(p.reg[1], 123);
    cr_assert_eq(p.pc, 4);
}

Test(ops, op_st_to_indirect)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    p.reg[0] = 0x1234;
    /* coding 0x30: type2=IND (bits 5-4 = 11) */
    s.map[1] = 0x30; s.map[2] = 1;
    s.map[3] = 0x00; s.map[4] = 0x0A; /* short offset = 10 */
    op_st(&s, &p);
    cr_assert_eq(read_int_from_map(s.map, 10), 0x1234);
}

Test(ops, op_live_found)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    champion_t c = {0}; header_t h = {0};
    strcpy(h.prog_name, "TestChamp");
    c.prog_nb = -1; c.header = &h;
    push_back(&s.champ_info.champions, &c);
    write_int_to_map(s.map, 1, 1); /* champion_nb = 1, match prog_nb=-1 */
    s.nb_cycle = 10;
    int fds[2]; silence_stdio(fds);
    op_live(&s, &p);
    restore_stdio(fds);
    cr_assert_eq(s.nb_live, 1);
    cr_assert_eq(p.last_live, 10);
    cr_assert_eq(p.pc, OP_LIVE_SIZE);
    free(s.champ_info.champions);
}

Test(ops, op_live_not_found)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    champion_t c = {0}; header_t h = {0};
    c.prog_nb = 5; c.header = &h;
    push_back(&s.champ_info.champions, &c);
    write_int_to_map(s.map, 1, 1);
    int fds[2]; silence_stdio(fds);
    op_live(&s, &p);
    restore_stdio(fds);
    cr_assert_eq(s.nb_live, 0);
    cr_assert_eq(p.pc, OP_LIVE_SIZE);
    free(s.champ_info.champions);
}

Test(ops, op_ldi_dir_reg)
{
    /* coding 0x90: type1=DIR(10), type2=REG(01) */
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0x90;
    s.map[2] = 0x00; s.map[3] = 0x14; /* arg1=20 (short, index) */
    s.map[4] = 1;                       /* arg2=r1 */
    p.reg[0] = 5;                       /* r1=5 */
    s.map[5] = 2;                       /* dest r2 */
    /* addr = (0 + (20+5) % IDX_MOD) % MEM_SIZE = 25 */
    write_int_to_map(s.map, 25, 77);
    op_ldi(&s, &p);
    cr_assert_eq(p.reg[1], 77);
}

Test(ops, op_ldi_ind_type)
{
    /* type1=IND(11): reads indirect offset, fetches int at that addr */
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0xD0;
    s.map[2] = 0x00; s.map[3] = 0x0A; /* IND offset = 10 */
    write_int_to_map(s.map, 10, 20);   /* value at addr 10 = 20 → arg1=20 */
    s.map[4] = 1; p.reg[0] = 0;        /* r1=0 → arg2=0 */
    s.map[5] = 2;                       /* dest r2 */
    /* addr = (0 + (20+0)%IDX_MOD)%MEM_SIZE = 20 */
    write_int_to_map(s.map, 20, 88);
    op_ldi(&s, &p);
    cr_assert_eq(p.reg[1], 88);
}

Test(ops, op_lldi_dir_reg)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0x90;
    s.map[2] = 0x00; s.map[3] = 0x05; /* arg1=5 */
    s.map[4] = 1; p.reg[0] = 2;        /* r1=2 */
    s.map[5] = 2;
    /* addr = (0 + 5 + 2) % MEM_SIZE = 7 */
    write_int_to_map(s.map, 7, 42);
    op_lldi(&s, &p);
    cr_assert_eq(p.reg[1], 42);
}

Test(ops, op_lldi_ind_type)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[1] = 0xD0;
    s.map[2] = 0x00; s.map[3] = 0x14; /* IND offset = 20 */
    write_int_to_map(s.map, 20, 30);   /* value at addr 20 = 30 → arg1=30 */
    s.map[4] = 1; p.reg[0] = 0;        /* r1=0 → arg2=0 */
    s.map[5] = 2;                       /* dest r2 */
    /* addr = (0 + 30 + 0) % MEM_SIZE = 30 (no IDX_MOD) */
    write_int_to_map(s.map, 30, 55);
    op_lldi(&s, &p);
    cr_assert_eq(p.reg[1], 55);
}

Test(ops, op_sti_reg_reg_reg)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    p.reg[0] = 0xDEAD; p.reg[1] = 0; p.reg[2] = 10;
    /* coding 0x54: type0=REG(01), type1=REG(01), type2=REG(01) */
    s.map[1] = 0x54;
    s.map[2] = 1; /* arg0: r1 */
    s.map[3] = 2; /* arg1: r2 */
    s.map[4] = 3; /* arg2: r3 */
    /* addr = (r2+r3) % IDX_MOD = 10; write to pc+10 = 10 */
    op_sti(&s, &p);
    cr_assert_eq(read_int_from_map(s.map, 10), (int)0xDEAD);
    cr_assert_eq(p.pc, 5);
}

/* ── call_op ─────────────────────────────────────────────────────────────── */

Test(loop_suite, call_op_valid_opcode)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[0] = 4; /* op_add */
    s.map[2] = 1; s.map[3] = 2; s.map[4] = 3;
    push_back(&s.processes, &p);
    call_op(&s);
    cr_assert_eq(p.pc, 5);
    free(s.processes);
}

Test(loop_suite, call_op_invalid_opcode)
{
    stock_main_t s = {0}; process_t p; make_process(&p, 0);
    s.map[0] = 99;
    push_back(&s.processes, &p);
    call_op(&s);
    cr_assert_eq(p.pc, 1);
    free(s.processes);
}

Test(loop_suite, call_op_all_opcodes)
{
    /* smoke-test every opcode 1-16 to catch crashes */
    stock_main_t s = {0};
    int fds[2]; silence_stdio(fds);
    for (int op = 1; op <= 16; op++) {
        process_t p; make_process(&p, 0);
        s.map[0] = (unsigned char)op;
        node_t *n = NULL;
        push_back(&n, &p);
        s.processes = n;
        call_op(&s);
        free(s.processes);
        s.processes = NULL;
    }
    restore_stdio(fds);
}

/* ── check_deaths ────────────────────────────────────────────────────────── */

Test(loop_suite, check_deaths_kills_dead_process)
{
    stock_main_t s = {0};
    process_t *p = malloc(sizeof(process_t));
    make_process(p, 0); p->last_live = 0;
    s.nb_cycle = 2000; s.cycle_to_die = 100; s.last_live_champion = -1;
    push_back(&s.processes, p);
    int fds[2]; silence_stdio(fds);
    check_deaths(&s);
    restore_stdio(fds);
    cr_assert_null(s.processes);
    /* p is freed inside delete_process */
}

Test(loop_suite, check_deaths_keeps_alive_process)
{
    stock_main_t s = {0};
    process_t *p = malloc(sizeof(process_t));
    make_process(p, 0); p->last_live = 1990;
    s.nb_cycle = 2000; s.cycle_to_die = 100;
    push_back(&s.processes, p);
    check_deaths(&s);
    cr_assert_not_null(s.processes);
    free(s.processes->data); free(s.processes);
}

Test(loop_suite, check_deaths_winner_printed)
{
    stock_main_t s = {0};
    process_t *p = malloc(sizeof(process_t));
    make_process(p, 0); p->last_live = 0;
    s.nb_cycle = 2000; s.cycle_to_die = 100;
    champion_t c = {0}; header_t h = {0};
    strcpy(h.prog_name, "Winner");
    c.prog_nb = 1; c.header = &h;
    s.last_live_champion = 1;
    push_back(&s.champ_info.champions, &c);
    push_back(&s.processes, p);
    int fds[2]; silence_stdio(fds);
    check_deaths(&s);
    restore_stdio(fds);
    cr_assert_null(s.processes);
    free(s.champ_info.champions);
}

Test(loop_suite, check_deaths_cycle_to_die_small)
{
    stock_main_t s = {0};
    process_t *p = malloc(sizeof(process_t));
    make_process(p, 0); p->last_live = 1998;
    s.nb_cycle = 2000; s.cycle_to_die = 3; /* <= CYCLE_DELTA */
    push_back(&s.processes, p);
    check_deaths(&s);
    cr_assert_eq(s.cycle_to_die, 1u);
    cr_assert_not_null(s.processes);
    free(s.processes->data); free(s.processes);
}

/* ── loop ────────────────────────────────────────────────────────────────── */

Test(loop_suite, loop_no_processes)
{
    stock_main_t s = {0};
    cr_assert_eq(loop(&s), 84);
}

Test(loop_suite, loop_basic_no_check)
{
    stock_main_t s = {0};
    process_t *p = malloc(sizeof(process_t));
    make_process(p, 0); p->last_live = 0;
    s.map[0] = 99;
    s.nb_cycle = -1; s.cycle_to_die = CYCLE_TO_DIE;
    s.next_check_cycle = CYCLE_TO_DIE;
    push_back(&s.processes, p);
    cr_assert_eq(loop(&s), 0);
    cr_assert_eq(s.nb_cycle, 0);
    free(s.processes->data); free(s.processes);
}

Test(loop_suite, loop_triggers_check_deaths)
{
    stock_main_t s = {0};
    process_t *p = malloc(sizeof(process_t));
    make_process(p, 0); p->last_live = 0;
    s.map[0] = 99;
    s.nb_cycle = CYCLE_TO_DIE - 1;
    s.cycle_to_die = CYCLE_TO_DIE;
    s.next_check_cycle = CYCLE_TO_DIE;
    s.last_live_champion = -1;
    push_back(&s.processes, p);
    int fds[2]; silence_stdio(fds);
    int r = loop(&s);
    restore_stdio(fds);
    cr_assert_eq(r, 0);
    cr_assert_null(s.processes);
    /* p freed by delete_process inside check_deaths */
}
