# Parking Patrol

Parking Patrol is an interactive C++ command-line tool for exploring parking citation records. It loads the included CSV dataset and lets you sort tickets by fields such as plate, street, violation, fine, or date; find the top 10 plates and streets by ticket count; and compare Merge Sort and Quick Sort performance, including elapsed time, comparisons, and moves.

## Requirements

- CMake 4.3 or newer (as specified in `CMakeLists.txt`)
- A C++20-compatible compiler
- The included `parking_citations_expanded.csv` dataset in the repository root

## Build and run

From the repository root, configure and build the program:

```sh
cmake -S . -B build
cmake --build build
```

Run it from the repository root so it can find `parking_citations_expanded.csv`:

```sh
./build/parking_patrol
```

On Windows with a Visual Studio CMake generator, run the generated executable from the repository root, for example:

```powershell
.\build\Debug\parking_patrol.exe
```

The program first loads and reports the number of tickets, then displays a menu. Choose an option by entering its number:

1. Sort tickets by a selected field using Merge Sort, Quick Sort, or both.
2. Show the 10 most frequent license plates.
3. Show the 10 streets with the most tickets.
4. Run sorting performance tests on progressively larger data samples.
5. Exit.

## Project layout

- `src/main.cpp` — interactive menu, ticket summaries, and performance tests.
- `src/ticket.h` — ticket record and sortable fields.
- `src/csv_loader.h` — loads the CSV data into ticket records.
- `src/MergeSort.cpp` and `src/MergeSort.h` — Merge Sort implementation.
- `src/quick_sort.cpp` and `src/quick_sort.h` — first-pivot Quick Sort implementation.
- `parking_citations_expanded.csv` — input dataset used by the program.
- `CMakeLists.txt` — CMake build configuration.
