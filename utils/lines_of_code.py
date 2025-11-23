import pathlib as path

CODE_DIRS: list[str] = [
    "../src"
]

line_count: int = 0

for i in CODE_DIRS:
    p = path.Path() / i
    for file in p.iterdir():
        if file.is_file():
            with open(file, "r") as f:
                line_count += f.read().count('\n')

input(f"There are {line_count} lines of code in the project.")