import sys
sys.dont_write_bytecode = True
from pathlib import Path
import subprocess
import shutil

############################################################
# linux only for now
proj_name = "Conway's Game of Life"
bin_name = "bin"
src_path = "./src/"
build_path = "./build/"
############################################################

def getCFiles() -> list[str]:
    return [str(p) for p in Path(src_path).glob("*.c")]

def compileAll():
    print("\n\t===== {} =====".format(proj_name))
    print("\tCompiling...\n")
    build_dir = Path(build_path)
    cf = getCFiles()

    if build_dir.exists():
        shutil.rmtree(build_dir)

    build_dir.mkdir(parents=True, exist_ok=True)

    out = str(build_dir / bin_name)
    subprocess.run(["gcc", *cf, "-I./lib", "-lraylib", "-lm", "-o", out], check=True)
    print("\tSource files:\n")
    for n in cf:
        try:
            print("\t{}".format(n))
        except Exception as e:
            print(f"Error: {e}.")

    print("\n\tCompilation successful\n")

compileAll()
