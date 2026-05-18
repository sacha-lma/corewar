# Corewar — Virtual Machine

Projet Epitech Tek1 — implémentation de la machine virtuelle Corewar en C.

---

## Présentation

Corewar est un jeu de programmation où des programmes en assembleur (*champions*) s'affrontent dans une arène circulaire en mémoire. La VM exécute leurs instructions en parallèle jusqu'à ce qu'il ne reste plus qu'un seul processus vivant.

---

## Compilation

```bash
make          # compile le binaire corewar
make re       # recompile depuis zéro
make clean    # supprime les .o
make fclean   # supprime les .o et le binaire
```

---

## Usage

```
./corewar [-dump nbr_cycle] [[-n prog_number] [-a load_address] prog_name] ...
```

| Option | Description |
|--------|-------------|
| `-dump N` | Démarre la simulation au cycle N (utile pour les tests) |
| `-n N` | Assigne le numéro de programme N au champion suivant |
| `-a ADDR` | Charge le champion suivant à l'adresse ADDR dans l'arène |
| `-h` / `-help` | Affiche cette aide |

### Exemples

```bash
# Un seul champion
./corewar tests/tests_files/abel.cor

# Deux champions en duel
./corewar tests/tests_files/abel.cor tests/tests_files/bill.cor

# Quatre champions avec numéro explicite pour le premier
./corewar -n 6 tests/tests_files/abel.cor \
               tests/tests_files/bill.cor \
               tests/tests_files/pdd.cor  \
               tests/tests_files/tyron.cor

# Démarrage à un cycle avancé
./corewar -dump 500 tests/tests_files/abel.cor tests/tests_files/bill.cor
```

---

## Structure du projet

```
corewar/
├── include/                  # tous les headers
│   ├── corewar.h             # header principal (agrège tout)
│   ├── op/op.h               # types op_t, header_t et constantes VM
│   ├── core/
│   │   ├── core.h            # champion_t, process_t, stock_main_t
│   │   ├── loop/loop.h       # loop, call_op, check_deaths
│   │   └── opperations/      # déclarations des 16 opcodes
│   ├── init/init.h           # init, setup, closup, métadonnées
│   ├── inputs/inputs.h       # parseurs d'arguments
│   ├── display/display.h     # print_help
│   └── utils/                # len, listes, extraction, insertion
│
├── src/
│   ├── core/
│   │   ├── main.c            # point d'entrée
│   │   ├── loop/
│   │   │   ├── loop.c        # boucle principale (un cycle)
│   │   │   ├── call_op.c     # dispatch de l'opcode courant
│   │   │   └── check_death.c # mort des processus + annonce vainqueur
│   │   └── opperations/      # implémentation des 16 opcodes
│   │       ├── op_live.c     # 0x01 — live
│   │       ├── op_ld.c       # 0x02 — ld
│   │       ├── op_st.c       # 0x03 — st
│   │       ├── op_add.c      # 0x04 — add
│   │       ├── op_sub.c      # 0x05 — sub
│   │       ├── op_and.c      # 0x06 — and
│   │       ├── op_or.c       # 0x07 — or
│   │       ├── op_xor.c      # 0x08 — xor
│   │       ├── op_zjmp.c     # 0x09 — zjmp
│   │       ├── op_ldi.c      # 0x0A — ldi
│   │       ├── op_sti.c      # 0x0B — sti
│   │       ├── op_fork.c     # 0x0C — fork
│   │       ├── op_lld.c      # 0x0D — lld
│   │       ├── op_lldi.c     # 0x0E — lldi
│   │       ├── op_lfork.c    # 0x0F — lfork
│   │       └── op_print.c    # 0x10 — aff
│   ├── init/
│   │   ├── init.c            # initialisation de stock_main_t
│   │   ├── setup.c           # tri champions, chargement .cor
│   │   ├── closup.c          # libération mémoire
│   │   └── metadatta/        # prog numbers, processus initiaux
│   ├── inputs/               # parseurs -dump, -n, -a, champions
│   ├── display/print_help.c  # affichage de l'aide
│   ├── op/op.c               # table des 16 opcodes (op_tab)
│   └── utils/                # lecture/écriture arène, listes chaînées
│
├── tests/
│   ├── test_corewar.c        # tests unitaires Criterion (~100 tests)
│   └── tests_files/          # champions .cor de référence
│       ├── abel.cor
│       ├── bill.cor
│       ├── pdd.cor
│       └── tyron.cor
│
├── bonus/                    # visualiseur ncurses (optionnel)
│   ├── Makefile
│   ├── include/visu.h
│   └── src/
│       ├── main_visu.c
│       ├── visu_init.c
│       ├── visu_map.c
│       ├── visu_panel.c
│       └── visu_loop.c
│
└── utilities/
    ├── corewar               # binaire de référence Epitech
    └── robot-factory         # outil de génération de champions
```

---

## Constantes VM

| Constante | Valeur | Description |
|-----------|--------|-------------|
| `MEM_SIZE` | 6144 | Taille de l'arène en octets |
| `IDX_MOD` | 512 | Modulo pour les adresses relatives |
| `REG_NUMBER` | 16 | Nombre de registres par processus |
| `CYCLE_TO_DIE` | 1536 | Cycles avant qu'un processus sans `live` soit tué |
| `CYCLE_DELTA` | 5 | Réduction de `cycle_to_die` à chaque vérification |
| `NBR_LIVE` | 40 | — |
| `PROG_NAME_LENGTH` | 128 | Longueur max du nom d'un champion |

---

## Tests

### Tests unitaires (Criterion)

```bash
make tests_run
```

Couvre : `len`, `map`, `list`, `inputs`, `manage_args`, `init`, `ops`, `loop`, `check_deaths` (~100 tests).

### Tests fonctionnels

```bash
make functional_tests
```

Lance `tests/functional_tests.sh` — 39 scénarios end-to-end sur le binaire compilé :
erreurs d'arguments, flags `-h`/`-n`/`-a`, batailles 1/2/4 champions, vérification du vainqueur.

---

## Bonus — Visualiseur ncurses

```bash
make bonus
./bonus/corewar_visu tests/tests_files/abel.cor tests/tests_files/bill.cor
```

Prérequis : terminal **≥ 173×50** colonnes/lignes et `libncurses` installée.

```
┌─── MEMORY MAP (128 × 48) ───────────────────┬──── PANEL ──────────┐
│  . . # # @ . . . . # . . . . . . . . . .   │  CHAMPIONS          │
│  (rouge = ch1, cyan = ch2,                  │  [1] Abel  LIVE 3p  │
│   vert  = ch3, jaune = ch4)                 │  [2] Bill  DEAD     │
│  @ = position PC d'un processus actif       │  PROCESSES          │
│  # = octet non-nul dans le territoire       │  0x0042 [Abel]      │
│  . = mémoire vide dans le territoire        │  INFO / CONTROLES   │
└─────────────────────────────────────────────┴─────────────────────┘
│ STATUS : Cycle: 1234 | CTD: 1536 | Speed: 30ms | [RUN]            │
└────────────────────────────────────────────────────────────────────┘
```

| Touche | Action |
|--------|--------|
| `ESPACE` | pause / reprendre |
| `+` / `-` | accélérer / ralentir (1–500 ms/cycle) |
| `n` | avancer d'un cycle (en pause) |
| `q` / `ESC` | quitter |

---

## Auteur

Sacha — Epitech Tek1, 2026
