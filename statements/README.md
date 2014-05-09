VPCPC 2014 Statements
=====================

Statement directory. Using TeX typesetting.
Please, do not commit `*.log`, `*.aux` and `*.pdf` files. (They should be ignored)

If you have any questions, write to `sysel@ksp.sk`.

Writing statements
------------------

To write a new statement just edit
`src/lang-en/example/template.tex` file
and save it as `src/<lang>/<day>/<taskname>.tex`.

Compiling statements
--------------------

To compile statements you can use `make.py` script:

  * `pdflatex` command is required
  * using: `python make.py <lang_dir> <task_dir>`
  * both, `<lang_dir>` and `<task_dir>`, can be `ALL`
  * to compile template statement just run: `python make.py lang-en example`
  * compiled files appear in `build/` directory

You can also compile manually,
but compile command should be ran in the directory
which contains this file ---
files in `sys/` and `img/` are required.