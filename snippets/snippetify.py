# "INIT": {
# 	"scope" : "cpp",
# 	"description" : "initial snippet file",
# 	"body": [
# 		"#include \"bits/stdc++.h\""
# 		"using namespace std;"
# 		"$1"
# 	],
# }


import os
import argparse
import pathlib

parser = argparse.ArgumentParser(
    prog="snippetify",
    description="Converts a directory into json snippets for vscode.",
)

parser.add_argument("--directory", default=os.getcwd(), type=pathlib.Path)


def calculate_body(filename: pathlib.Path) -> list[str]:
    with open(filename) as fin:
        lines = list(fin)
    return [line.strip("\n").replace('"', '\\"') for line in lines]


def write(snippets: dict[str, list[str]]):
    print("{")
    for filename, lines in snippets.items():
        key = filename.removesuffix(".cpp").upper()
        print(f'\t"{key}": {{')
        print('\t\t"scope": "cpp",')
        print(f'\t\t"prefix": "{key}",')
        print('\t\t"body": [')
        for line in lines:
            print(f'\t\t\t"{line}"')
        print("\t\t],")  # body
        print("\t}")  # snippet
    print("}")


def main(args):
    directory = args.directory.resolve()
    cpp_files = [file for file in os.listdir(directory) if file.endswith(".cpp")]
    snippets = {f: calculate_body(os.path.join(directory, f)) for f in cpp_files}
    write(snippets)


if __name__ == "__main__":
    main(args=parser.parse_args())
