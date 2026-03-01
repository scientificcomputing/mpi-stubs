import os as _os
import sys as _sys
from pathlib import Path as _Path
from importlib.metadata import metadata as _metadata

meta = _metadata("mpi-stubs")
__version__ = meta["Version"]
__author__ = meta.get("Author", "")
__license__ = meta.get("License", "MIT")
__email__ = meta["Author-email"]
__program_name__ = meta["Name"]


# Find the packaged CMake installation data directory inside the wheel
DATA_DIR = _Path(__file__).parent / "data"
BIN_DIR = DATA_DIR / "bin"


def _program_exit(name: str):
    exe = BIN_DIR / name
    if not exe.exists():
        raise FileNotFoundError(
            f"Executable {name} not found at {exe}. "
            "Ensure the package was compiled and installed correctly."
        )

    # Prepend the package bin directory to PATH so internal scripts can find each other
    _os.environ["PATH"] = f"{BIN_DIR}{_os.pathsep}{_os.environ.get('PATH', '')}"

    # Execute the bash wrapper natively, replacing the current python process
    _os.execl(str(exe), str(exe), *_sys.argv[1:])


def mpicc():
    _program_exit("mpicc")


def mpicxx():
    _program_exit("mpicxx")


def mpif90():
    _program_exit("mpif90")


def mpiexec():
    _program_exit("mpiexec")
