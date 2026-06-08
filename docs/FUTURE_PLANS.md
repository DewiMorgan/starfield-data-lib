# Future Plans - Testing & Hardening

## 📈 Coverage & Visualization
- **Visual Coverage Reports**: Install `lcov` to transform raw `.gcov` data into a navigable HTML report. This allows for "visual gap hunting" to identify uncovered branches instantly.
  - *Requirement*: `sudo apt-get install lcov`

## 🛡️ Security & Robustness
- **Fuzzing**: Implement a fuzzer (e.g., using `libFuzzer`) for the binary parser. This involves feeding the parser millions of mutated, semi-random binary inputs to find edge-case crashes or memory leaks that manual unit tests would never catch.

## 🏗️ Infrastructure
- **CI Integration**: Integrate the `make test` and `make coverage` targets into a GitHub Action or similar CI pipeline to ensure no commit ever drops the coverage percentage.
