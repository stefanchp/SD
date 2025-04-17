import os
import subprocess
import shutil
import time
from pathlib import Path

sorting_paths = ["BucketSort", "HeapSort", "MergeSort", "QuickSort", "RadixSort", "ShellSort"]
distribs = ["uni", "gss", "exp", "srt", "rev", "alm"]

def compile_cpp():
    print("Compiling C++ sources...")
    subprocess.run(["g++", "-O3", "-o", "nativesort", "nativesortcpp.cpp"])
    subprocess.run(["g++", "-O3", "-o", "numgen", "numgen.cpp"])

    for dir in sorting_paths:
        for cpp_file in Path(dir).glob("*.cpp"):
            output = str(cpp_file.with_suffix(''))
            subprocess.run(["g++", "-O3", "-o", output, str(cpp_file)])


def generate_batch(num_tests, num_elements, is_float, low, high, distrib, output_dir):
    for i in range(1, num_tests + 1):
        out_file = f"{output_dir}/input_f{int(is_float)}-{i}.txt"
        subprocess.run(["./numgen", str(num_elements), str(int(is_float)), str(low), str(high), distrib, out_file])


def generate_tests(run_dir):
    base = Path(run_dir)
    
    print("Generating tests...")
    # Batch 1
    batch1 = base / "batch1"
    batch1.mkdir(parents=True, exist_ok=True)
    for d in distribs:
        generate_batch(1000, 1000, False, -2048, 2047, d, batch1)

    # Batch 2
    batch2 = base / "batch2"
    batch2.mkdir(parents=True, exist_ok=True)
    for d in distribs:
        generate_batch(100, 10000, False, -2147483648, 2147483647, d, batch2)

    # Batch 3
    batch3 = base / "batch3"
    batch3.mkdir(parents=True, exist_ok=True)
    for d in distribs:
        generate_batch(10, 100000, False, -2147483648, 2147483647, d, batch3)

    # Batch 4
    batch4 = base / "batch4"
    batch4.mkdir(parents=True, exist_ok=True)
    for d in distribs:
        generate_batch(1, 1000000, False, -9223372036854775808, 9223372036854775807, d, batch4)


def call_sort(executable, run_index):
    input_root = f"inputs/run{run_index}"
    output_root = f"outputs/run{run_index}/{executable}"
    result_file_path = f"results/run{run_index}/{executable}.txt"

    os.makedirs(output_root, exist_ok=True)
    os.makedirs(os.path.dirname(result_file_path), exist_ok=True)

    with open(result_file_path, 'w') as result_file:
        for batch in sorted(os.listdir(input_root)):
            print(f"Sorting {batch} with {executable}...")
            batch_path = os.path.join(input_root, batch)
            out_batch_path = os.path.join(output_root, batch)
            os.makedirs(out_batch_path, exist_ok=True)

            result_file.write(f"Batch {batch}:\n")
            batch_start = time.time()

            for infile in sorted(os.listdir(batch_path)):
                input_path = os.path.join(batch_path, infile)
                output_path = os.path.join(out_batch_path, infile)

                t0 = time.time()
                if executable == "nativesortpython.py":
                    result = subprocess.run(["python", executable, input_path, output_path])
                elif executable == 'nativesort':
                    result = subprocess.run([f"./{executable}", input_path, output_path])
                else:
                    sort_dirs = ["QuickSort", "BucketSort", "ShellSort", "HeapSort", "RadixSort", "MergeSort"]
                    exe_found = False
                    executable_name = f"{executable}.exe" if os.name == "nt" else executable

                    for folder in sort_dirs:
                        try:
                            exe_path = Path(folder) / executable_name
                            if not exe_path.exists():
                                continue  # Try next folder
                            result = subprocess.run([str(exe_path.resolve()), input_path, output_path])
                            exe_found = True
                            break  # Stop after first successful run
                        except:
                            continue

                    if not exe_found:
                        raise FileNotFoundError(f"Could not find executable '{executable_name}' in any known folder.")


                t1 = time.time()
                elapsed = int((t1 - t0) * 1000)

                if result.returncode != 0:
                    result_file.write(f"Error while sorting {infile}\n")
                #elif executable not in ["nativesort", "nativesortpython.py"]:
                   # ref_path = f"outputs/run{run_index}/nativesort/{batch}/{infile}"
                   # cmp = subprocess.run(["cmp", "--silent", ref_path, output_path])
                   # if cmp.returncode == 0:
                   #     result_file.write(f"{infile} sorted correctly by {executable} in {elapsed} miliseconds.\n")
                   # else:
                   #     result_file.write(f"{infile} sorted incorrectly by {executable} in {elapsed} miliseconds.\n")
                else:
                    result_file.write(f"{infile} sorted in {elapsed} miliseconds.\n")

            batch_elapsed = int((time.time() - batch_start) * 1000)
            print(f"{batch} sorted in {batch_elapsed} miliseconds.")


def cleanup():
    print("Cleaning up executables...")
    for dir in sorting_paths:
        for file in Path(dir).iterdir():
            if file.is_file() and not file.name.endswith('.cpp'):
                file.unlink()
    for tool in ["numgen", "nativesort"]:
        if Path(tool).exists():
            Path(tool).unlink()


def main(run_count=1):
    compile_cpp()

    for run in range(1, run_count + 1):
        print(f"\n=== Run {run} ===")
        input_dir = f"inputs/run{run}"
        output_dir = f"outputs/run{run}"
        result_dir = f"results/run{run}"
        Path(input_dir).mkdir(parents=True, exist_ok=True)
        Path(output_dir).mkdir(parents=True, exist_ok=True)
        Path(result_dir).mkdir(parents=True, exist_ok=True)

        start = time.time()
        generate_tests(input_dir)
        print(f"Test generation done in {int(time.time() - start)} seconds.")

        print("Sorting with C++ built-in sort...")
        start = time.time()
        call_sort("nativesort", run)
        print(f"C++ sort done in {int(time.time() - start)} seconds.")

        print("Sorting with Python built-in sort...")
        start = time.time()
        call_sort("nativesortpython.py", run)
        print(f"Python sort done in {int(time.time() - start)} seconds.")

        for dir in sorting_paths:
            for cpp_file in Path(dir).glob("*.cpp"):
                exe = cpp_file.with_suffix('').name
                print(f"Sorting with {exe}...")
                start = time.time()
                call_sort(exe, run)
                print(f"{exe} done in {int(time.time() - start)} seconds.")

    cleanup()


if __name__ == "__main__":
    import sys
    run_count = int(sys.argv[1]) if len(sys.argv) > 1 else 1
    main(run_count)
