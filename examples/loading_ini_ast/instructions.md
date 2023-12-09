- cd to folder
- run `make` to compile
- run `make test` to run example

## details

- `algodal-parser-header.h` `algodal-parser-vm.c` `config-program.c` are generated from `ini.parser` (with config as parser name).
  feel free to regenerate them however you like.
- `main.c` contains the user custom code to manipulate the AST.
- `config.ini` is the data being parsed
