# Graph-Algorithms

# Algorithms in C/C++

This repository contains implementations of various algorithms in C/C++, including Kruskal's algorithm and Reverse-Delete algorithm.

## Table of Contents

- [Introduction](#introduction)
- [Algorithms Implemented](#algorithms-implemented)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

Algorithms are essential building blocks in computer science and programming. This repository provides implementations of fundamental algorithms in C/C++, allowing developers to study, utilize, and incorporate these algorithms into their projects.

## Algorithms Implemented

### 1. Kruskal's Algorithm

Kruskal's algorithm is a greedy algorithm used to find the minimum spanning tree (MST) of a connected, undirected graph. It repeatedly adds the shortest edge that does not form a cycle until all vertices are included in the MST. Kruskal's algorithm is efficient and straightforward to implement, making it a popular choice for finding MSTs.

### 2. Reverse-Delete Algorithm

The Reverse-Delete algorithm is another method for finding the minimum spanning tree (MST) of a graph. Unlike Kruskal's algorithm, which adds edges in increasing order of weight, Reverse-Delete starts with a full graph and iteratively removes the most expensive edges that are not critical for connectivity. This process continues until the graph becomes connected, resulting in an MST.

## Usage

To use the algorithms implemented in this repository, follow these steps:

1. Clone the repository to your local machine:

    ```bash
    git clone https://github.com/proplayer5555/Graph-Algorithms.git
    ```


2. Compile the C/C++ files using a compatible compiler:

    ```bash
    g++ kruskal.cpp -o kruskal
    ```

3. Run the compiled executable:

    ```bash
    ./kruskal
    ```

5. Follow the prompts or customize the input parameters as needed for your specific problem.

## Contributing

Contributions to this repository are welcome! If you have suggestions for improvements, bug fixes, or new algorithms to add, please feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
